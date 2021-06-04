import serial
import time

aantal_50 = 5
aantal_10 = 2
arduino = serial.Serial('COM3', 115200)


serial_in = arduino.readline().decode('utf-8')[:-2]
while serial_in != "start":
    serial_in = arduino.readline().decode('utf-8')[:-2]
print(serial_in)


arduino.write("geld\n".encode())

receive = arduino.readline().decode('utf-8')[:-2]
if receive == "send aantal 50":
    arduino.write(f"{aantal_50}\n".encode())


receive = arduino.readline().decode('utf-8')[:-2]
if receive == "send aantal 10":
    arduino.write(f"{aantal_10}\n".encode())

# print(arduino.readline().decode('utf-8')[:-2])
# print(arduino.readline().decode('utf-8')[:-2])
