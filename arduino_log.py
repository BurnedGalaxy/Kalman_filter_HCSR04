import serial

port = "/dev/ttyACM0"
filename = "sensor.dat"
samples = 60

arduino = serial.Serial(port, 115200)

file = open(filename, 'a')
count = 0

while count < samples:
    buffer = str(arduino.readline(), 'utf-8')
    if count:
        file.write(buffer)
    count = count + 1

file.close()
