import serial

arduino = serial.Serial("/dev/ttyACM0", 115)

rawdata = []
count=0

while count < 3:
    rawdata.append(str(arduino.readline()))
    count+=1
print(rawdata)
