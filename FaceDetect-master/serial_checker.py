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
		msg_from_serial = ser.readline()
		print "%s: %s" % (threadName, msg_from_serial)

def exitThread():
	exitFlag = False

# Create the serial object
ser1 = serial.Serial('/dev/ttyACM0', 9600)

# Create new threads
thread1 = checkthread(1, "Checker Thread")

# Start new Threads
thread1.start()

# Send random stuff
n = 0
while n < 20:
	msg = 'x' + str(random.random()) + ',' + str(random.random()) + '\n'
	ser1.write(msg)
	print "from arduino: " + msg
	time.sleep(0.02)
	n += 1
exitFlag = 
