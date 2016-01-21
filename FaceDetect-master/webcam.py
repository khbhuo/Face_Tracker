#!/usr/bin/python

import cv2
import sys
import serial

ser = serial.Serial('COM16', 57600)
ser.timeout = None

cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)
center_width = video_capture.get(3)/2
center_height = video_capture.get(4)/2

while True:
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

        # Get the distance from center of frame
        x_dist_from_center = x+(h/2) - center_width
        y_dist_from_center = y+(w/2) - center_height

    # Serial print the distance
    print "[", x_dist_from_center, ", ", y_dist_from_center, "]"
    msg = 'x' + x_dist_from_center + ',' + y_dist_from_center + '\n'
    ser.write(msg)
    
    # Display the resulting frame
    cv2.imshow('Video', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
ser.close()
