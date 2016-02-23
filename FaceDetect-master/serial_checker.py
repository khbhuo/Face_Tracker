#!/usr/bin/python

import time
import sys
import threading
import serial
import random
import signal

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
            #print self.exitFlag
            print_msg(self.name, self.ser)
        print "Exiting " + self.name
    
    def exitThread(self):
        self.exitFlag = False

def print_msg(threadName, ser):
    #time.sleep(0.5)
    if bool(ser.inWaiting()):
        msg_from_serial = ser.readline()
        print "%s: %s" % (threadName, msg_from_serial)

