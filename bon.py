import serial
import time
import datetime

serialcomm = serial.Serial('COM4', 9600)


serialcomm.timeout = 1

while True:
    
    

    

    serialcomm.write("zaterdag, 5 juni 2021".encode())
    #serialcomm.write("20".encode())

    time.sleep(0.5)

    print(serialcomm.readline().decode('ascii'))

serialcomm.close()