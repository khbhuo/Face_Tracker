#!/usr/bin/python

import time
import sys
import threading
import serial
import random
import signal

#global exitFlag
#exitFlag = True

def signal_handler(signal, frame):
    print "You pressed Ctrl+C"
    thread1.exitThread()
    thread1.join()
    sys.exit(0)

class checkthread(threading.Thread):
    def __init__(self, threadID, name, ser):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.ser = ser
        self.exitFlag = True


    def run(self):
        print "Starting " + self.name
        while self.exitFlag:
            time.sleep(.1)
            print self.exitFlag
            print_msg(self.name, self.ser)
        print "Exiting " + self.name
    
    def exitThread(self):
        self.exitFlag = False

    

def print_msg(threadName, ser):
    #time.sleep(0.5)
    if bool(ser.inWaiting()):
        msg_from_serial = ser.readline()
        print "%s: %s" % (threadName, msg_from_serial)


# Create the serial object
ser1 = serial.Serial('/dev/ttyACM0', 57600)

global thread1
# Create new threads
thread1 = checkthread(1, "Checker Thread", ser1)

# Start new Threads
#thread1.start()

signal.signal(signal.SIGINT, signal_handler)
# Send random stuff
n = 0
while n < 100:
	  msg = 'x' + "%.3f" % random.random() + ',' + "%.3f" % random.random() + '\n'
	  ser1.write(msg)
	  print "to arduino: " + msg
	  time.sleep(0.1)
	  n += 1
#exitFlag = False
#thread1.exit()
ser1.close()
