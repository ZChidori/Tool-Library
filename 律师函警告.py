import cv2
while True:
        frame=cv2.VideoCapture('footage.mp4').read()
        if frame is None:
                break
        cv2.imshow('img_opening_blurred',cv2.GaussianBlur(cv2.bitwise_not(cv2.morphologyEx(cv2.bitwise_not(cv2.threshold(cv2.GaussianBlur(cv2.adaptiveThreshold(cv2.GaussianBlur(cv2.cvtColor(frame,cv2.COLOR_RGB2GRAY),(5,5),0),255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,5,2),(5,5),0),200,255,cv2.THRESH_BINARY)),cv2.MORPH_OPEN,cv2.getStructuringElement(cv2.MORPH_RECT,(3,3)))),(3,3),0))
        if cv2.waitKey(40)&0xFF==ord('q'):
                break
cv2.destroyAllWindows()
