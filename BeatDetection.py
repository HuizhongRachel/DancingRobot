import pyaudio # from http://people.csail.mit.edu/hubert/pyaudio/
import numpy   
import sys
import math
import struct
import serial
import RPi.GPIO as GPIO
import os, time



def main():
    chunk      = 4096
    samplerate = 44100
    multi = 67
    scale = 0.015
    # used to count time
    k = 0
    scope = [20,200,400,800,1600,3200]
    # after 4s, start printing
    Y = int(samplerate*3/chunk)
    print "Y = ",Y
    n_band = len(scope)-1
    # history  is n slots more than con.
    n = 15

    # M slots of history to do average
    M = 10

    levelhis = [[0 for x in range(n_band)] for x in range(M)]
    #record the last 54 differ value
    Matrix = [[0 for x in range(n_band)] for x in range(Y+n)]
    Con5 = [[0 for x in range(n_band)] for x in range(Y)]
    Con6 = [[0 for x in range(n_band)] for x in range(Y)]
    Con7 = [[0 for x in range(n_band)] for x in range(Y)]
    Con8 = [[0 for x in range(n_band)] for x in range(Y)]
    Con9 = [[0 for x in range(n_band)] for x in range(Y)]
    # used to record the levels of last time
    history = [0]*n_band
    # the difference between this levels and last levels
    differ = [0]*n_band


    # dance related variables
    # after detect start point
    timeline = 0
    frequency_band = 0 # 5-9
    frequency = 0 # 0~4
    next_peak_index = 0 # compare to timeline
    dance = []
    wrongmark = []
    # if detect rynthm
    startornot = 0
    stopornot = 0

    # sum of past M point for all bands
    power = 0

    # serial communicatin
    portnumber = 0;
    portstring = '';

    p = pyaudio.PyAudio()
    stream = p.open(format = pyaudio.paInt16,
                    channels = 1,
                    rate = 44100,
                    input = True,
                    frames_per_buffer = chunk,
                    input_device_index=2)


    try:
        while True:
            scope = [20,200,400,800,1600,3200]
            sumstar = 500
            data = stream.read(chunk)
            dataArray = numpy.frombuffer(data, dtype=numpy.int16)  #4096
            # print "the lenght of  dataArray is ", len(dataArray)
            fftVals = numpy.fft.rfft(dataArray)/chunk  #2049
            # print "the lenght of  fftVals is ", len(fftVals)
            fftVals = numpy.abs(fftVals)
            k += 1

            # divide band according to scope
            for i in xrange(0,len(scope),1) :
                scope[i] = len(fftVals)*scope[i]/22050

            # define the length of levels
            levels = [0] * n_band

            # aquire levels and store levels history
            for i in xrange(0,n_band,1):
                levels[i] = sum(fftVals[scope[i]:scope[i+1]])
                if k < M :
                    levelhis[k][i] = levels[i]

            # store levels history
            if k >= M :
                for m in range(1,M,1):
                    for i in xrange(0,n_band,1):
                        levelhis[m-1][i] = levelhis[m][i]
                        power += levelhis[m][i]
                for i in xrange(0,n_band,1):
                    levelhis[M-1][i] = levels[i]
            # calculate levels/(average levels in past M point)
            # calculate differ and store differ data
            for i in xrange(0,n_band,1):
                levels[i] = levels[i]*M/sum(row[i] for row in levelhis)
                if levels[i] > history[i] :
                    differ[i] = levels[i] - history[i]
                if levels[i] <= history[i] :
                    differ[i] = -(levels[i] - history[i])/50
                if k < Y+n :
                    Matrix[k][i] = differ[i]

            # calculate the con val
            if 0 <= k-n < Y :
                for i in xrange(0,n_band,1):
                    Con9[k-n][i] = Matrix[k][i]*Matrix[k-9][i]
                    Con8[k-n][i] = Matrix[k][i]*Matrix[k-8][i]
                    Con7[k-n][i] = Matrix[k][i]*Matrix[k-7][i]
                    Con6[k-n][i] = Matrix[k][i]*Matrix[k-6][i]
                    Con5[k-n][i] = Matrix[k][i]*Matrix[k-5][i]

            # store new data to Matrix
            if (k-n) >= Y :
                print power

                # define variables
                final_eva = [] # 25*4
                keylist = []
                keyindex = 0 # used to calculate where to start
                last5 = [0]*5
                for m in range(1,Y+n,1):
                    for i in xrange(0,n_band,1):
                        Matrix[m-1][i] = Matrix[m][i]
                for i in xrange(0,n_band,1):
                    Matrix[Y+n-1][i] = differ[i]
                # store data to the position before
                for m in range(1,Y,1):
                    for i in xrange(0,n_band,1):
                        Con9[m-1][i] = Con9[m][i]
                        Con8[m-1][i] = Con8[m][i]
                        Con7[m-1][i] = Con7[m][i]
                        Con6[m-1][i] = Con6[m][i]
                        Con5[m-1][i] = Con5[m][i]
                # calculate the lastest con val
                for i in xrange(0,n_band,1):
                    Con9[Y-1][i] = Matrix[Y-1+n][i]*Matrix[Y-1+n-9][i]
                    Con8[Y-1][i] = Matrix[Y-1+n][i]*Matrix[Y-1+n-8][i]
                    Con7[Y-1][i] = Matrix[Y-1+n][i]*Matrix[Y-1+n-7][i]
                    Con6[Y-1][i] = Matrix[Y-1+n][i]*Matrix[Y-1+n-6][i]
                    Con5[Y-1][i] = Matrix[Y-1+n][i]*Matrix[Y-1+n-5][i]
                    # divide the avg value
                    # Con5[Y-1][i] = Con5[Y-1][i]*Y/sum(row[i] for row in Con5)

                # here do evaluation print out which.
                if startornot == 0 :
                    eva_matrix = []
                    eva_matrix.append(evaluation(Con5,5))
                    eva_matrix.append(evaluation(Con6,6))
                    eva_matrix.append(evaluation(Con7,7))
                    eva_matrix.append(evaluation(Con8,8))
                    eva_matrix.append(evaluation(Con9,9))
                    for i in xrange(0,5,1):
                        for j in xrange(0,5,1):
                            final_eva.append(eva_matrix[i][j])
                    best = []
                    for i in xrange(25):
                        best.append(final_eva[i][2])
                    maxbest = max(best)
                    print maxbest
                    if max(best) > 50 and power > 60000:
                        index = best.index(maxbest)
                        frequency = final_eva[index][0]
                        frequency_band = final_eva[index][1]
                        startornot = 1
                        stopornot = 0
                        keylist = final_eva[(frequency-5)*5+frequency_band][3]
                        keyindex = keylist[-1]
                        next_peak_index = keyindex+frequency-Y+2
                        print frequency, frequency_band, maxbest, final_eva[(frequency-5)*5+frequency_band][3]
                    # else :
                    #     # print "none"

                # START DANCING
                if startornot == 1 :
                    timeline += 1
                    # print "timeline = ",timeline
                    # print "dance = ",dance
                    # print "next peak = ",next_peak_index

                    if timeline == next_peak_index+2 :
                        # acquire the last five conx value for brand_i
                        for i in range(Y-5,Y,1):
                            if frequency == 5 :
                                last5[i-Y+5] = Con5[i][frequency_band]
                            if frequency == 6 :
                                last5[i-Y+5] = Con6[i][frequency_band]
                            if frequency == 7 :
                                last5[i-Y+5] = Con7[i][frequency_band]
                            if frequency == 8 :
                                last5[i-Y+5] = Con8[i][frequency_band]
                            if frequency == 9 :
                                last5[i-Y+5] = Con9[i][frequency_band]
                        # print last5

                        if len(wrongmark)>5 and wrongmark[-1]==1 and wrongmark[-2]==1 and wrongmark[-3]==1 and wrongmark[-4]==1 and wrongmark[-5]==1 and wrongmark[-6]==1 or power < 30000:
                            if power < 30000 :
                                print "music down"
                            timeline = 0
                            frequency_band = 0 # 5-9
                            frequency = 0 # 0~4
                            next_peak_index = 0 # compare to timeline
                            dance = []
                            startornot = 0
                            stopornot = 1
                            wrongmark = []
                            # stop dancing
                            # send signal to reset all the servo
                            port.write('s')


                        else :
                            if last5[2]>last5[1] and last5[2]>last5[3] and last5[2]>scale :
                                next_peak_index += frequency
                                dance.append(next_peak_index)
                                wrongmark.append(0)
                            elif last5[1]>last5[0] and last5[1]>last5[2] and last5[1]>scale :
                                next_peak_index += frequency -1
                                dance.append(next_peak_index)
                                wrongmark.append(0)
                            elif last5[3]>last5[2] and last5[3]>last5[4] and last5[3]>scale :
                                next_peak_index += frequency +1
                                dance.append(next_peak_index)
                                wrongmark.append(0)
                            else :
                                # print "wrong"
                                wrongmark.append(1)
                                next_peak_index += frequency
                                dance.append(next_peak_index)

                    if len(dance)>0 and timeline == dance[-1] and stopornot == 0 :
                        print "*"*40

                        portnumber=frequency
                        portstring=str(portnumber)
                        port.write(portstring)
                    else:
                        print "none"
                # print "7","*"*(Con7[Y-1][4]*50)
                # print eva_matrix
                power = 0

            history = levels

            # print "@@@@@@@@@@@@@",k

    except KeyboardInterrupt:
        pass
    finally:
        print "stopping"
        stream.close()
        p.terminate()
        time = k*chunk/44100
        print "Total time = %ds , k = %d" %(time,k)

# define evaluation function
def evaluation (Con, n):
    multi = 67
    scale = 0.015
    chunk      = 4096
    samplerate = 44100
    Y = int(samplerate*3/chunk)
    eva_matrix = [[0 for x in range(4)] for x in range(5)]
    for i in xrange(0,5,1):
        peak_index = []
        eva_matrix[i][0] = n
        eva_matrix[i][1] = i
        peak = []
        possibility = 0
        if Con[0][i]>Con[1][i] and Con[0][i] > scale :
            peak.append(0)
            peak.append(min(200,int(Con[0][i]*multi)))
        for m in range(1,Y-1,1):
            if  Con[m-1][i]< Con[m][i] and Con[m][i]>Con[m+1][i] and Con[m][i]> scale :
                peak.append(m)
                peak.append(min(200,int(Con[m][i]*multi)))
        if Con[Y-1][i]>Con[Y-2][i] and Con[Y-1][i] > scale :
            peak.append(Y-1)
            peak.append(min(200,int(Con[Y-1][i]*multi)))
        # print peak
        # find at least n_peak peaks :
        if len(peak) >= 5*2 :
            truepeak = max(peak[1::2])
            index = peak.index(truepeak)
            index = peak[index-1]
            if_meet_blank = 0
            is_peak = 0
            not_peak = 0
            # the truepeak is the assumped peak
            for m in range(0,Y-1,1):
                if numpy.abs(m-index)%n == 0 :
                    if m in peak[0::2]:
                        is_peak += peak[peak.index(m)+1]
                        peak_index.append(m)
                    else :
                        if_meet_blank = 1
                        break
                if numpy.abs(m-index)%n != 0 and m in peak[0::2] :
                    not_peak += peak[peak.index(m)+1]
            if if_meet_blank == 0 :
                possibility = is_peak/(not_peak+1)
        eva_matrix[i][2] = possibility
        eva_matrix[i][3] = peak_index
    return eva_matrix

if __name__ == '__main__':
    GPIO.setmode(GPIO.BOARD)
    port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=0.0001)
    #list_devices()
    main()
