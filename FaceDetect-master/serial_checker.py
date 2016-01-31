#!/usr/bin/python

import time
import sys
import threading
import serial
import random

exitFlag = True

class checkthread(threading.Thread):
	def __init__(self, threadID, name, ser):
		threading.Thread.__init__(self)
		self.threadID = threadID
		self.name = name
		self.ser = ser
	def run(self):
		print "Starting " + self.name
		print_msg(self.name, self.ser)
		print "Exiting " + self.name

def print_msg(threadName, ser):
    while exitFlag:
        if ser.inWaiting():
            print "I'm in inWaiting"
            msg_from_serial = ser.readline()
            print "%s: %s" % (threadName, msg_from_serial)

def exitThread():
	exitFlag = False

# Create the serial object
ser1 = serial.Serial('/dev/ttyACM0', 9600)

# Create new threads
thread1 = checkthread(1, "Checker Thread", ser1)

# Start new Threads
thread1.start()

# Send random stuff
n = 0
while n < 10:
	msg = 'x' + "%.3f" % random.random() + ',' + "%.3f" % random.random() + '\n'
	ser1.write(msg)
	print "to arduino: " + msg
	time.sleep(1)
	n += 1
exitFlag = 0

ser1.close()
