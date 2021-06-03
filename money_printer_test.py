import json
import requests
import serial
import time
arduino = serial.Serial('COM3', 115200)


serial_in = arduino.readline().decode('utf-8')[:-2]
while serial_in != "start":
    serial_in = arduino.readline().decode('utf-8')[:-2]
print(serial_in)
# time.sleep(1)
print('send geld')
arduino.write("geld".encode())
print('1')
print(arduino.readline().decode('utf-8')[:-2])
# print(arduino.readline().decode('utf-8')[:-2])
# print('2')
# IBAN = arduino.readline().decode('utf-8')[:-2]
# print('ontvangen')
# print(IBAN)
# if IBAN:
#     arduino.flushInput()
#     landcode = IBAN[0:4].upper()
#     bankcode = IBAN[4:8].upper()
#     print(IBAN)
#     arduino.write("pin".encode())
#     pin = arduino.readline().decode('utf-8')[:-2]
