#!/usr/bin/python

import cv2
import sys
import serial
import time

# Import the serial_checker.py
import serial_checker

ser = serial.Serial('/dev/ttyACM0', 9600)
ser.timeout = None

cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)

# Get centre of the image
video_capture = cv2.VideoCapture(1)
center_width = video_capture.get(3)/2
center_height = video_capture.get(4)/2

msg = 'c' + str(center_width) + ',' + str(center_height) + '\n'
ser.write(msg)



while True:
    face_on_xAxis = center_width
    face_on_yAxis = center_height
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
    
    # Draw a circle around 
    cv2.circle

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

    # Serial print the distance
    #print "[", x_dist_from_center, ", ", y_dist_from_center, "]"
    msg = 'x' + str(face_on_xAxis) + ',' + str(face_on_yAxis) + '\n'
    print msg
    ser.write(msg)
   
    # Display the resulting frame
    cv2.imshow('Video', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    if ser.inWaiting() >= 4:
    	print "from Arduino" +  ser.readline()
	ser.flushInput()   

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
#ser.close()
