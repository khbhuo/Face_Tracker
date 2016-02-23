#!/usr/bin/python

import signal
import cv2
import sys
import serial
import time
import threading
import serial_checker

def signal_handler(signal, frame):
    print "You pressed Ctrl+C"
    thread1.exitThread()
    thread1.join()
    sys.exit(0)


# Main function
ser = serial.Serial('/dev/ttyACM4', 57600)
global thread1
thread1 = serial_checker.checkthread(1, "Checker Thread", ser)


ser.timeout = None

cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)

# Get centre of the image
video_capture = cv2.VideoCapture(1)
center_width = video_capture.get(3)/2
center_height = video_capture.get(4)/2

msg = 'c' + str(center_width) + ',' + str(center_height) + '\n'
ser.write(msg)

# Thread begin
thread1.start()

signal.signal(signal.SIGINT, signal_handler)

while True:
    face_on_xAxis = center_width
    face_on_yAxis = center_height
    
    #TODO remove only send once
    msg = 'c' + str(center_width) + ',' + str(center_height) + '\n'
    ser.write(msg)

    # Capture frame-by-frame
    ret, frame = video_capture.read()    

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.25,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.cv.CV_HAAR_SCALE_IMAGE
    )
    
    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        face_on_xAxis = (x+w)/2.0
        face_on_yAxis = (y+h)/2.0

    # Serial print the distance
    #print "[", x_dist_from_center, ", ", y_dist_from_center, "]"
    msg = 'x' + str(face_on_xAxis) + ',' + str(face_on_yAxis)
    print "to arduino: " + msg
    msg += "\n"
    ser.write(msg)
   
    # Display the resulting frame
    cv2.imshow('Video', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    time.sleep(0.1)

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
ser.close()
