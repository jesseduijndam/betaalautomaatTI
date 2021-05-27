import serial
import time

serialcomm = serial.Serial('COM4', 9600)

serialcomm.timeout = 1

while True:

    i = input("Bonetje? Typ Ja/Nee ").strip()

    if i == "Nee":

        print('Tot ziens!')

        break
    if i == "Ja":
        print('Aan het printen')
        print('Tot ziens!')
        

        


    serialcomm.write(i.encode())

    time.sleep(0.5)

    print(serialcomm.readline().decode('ascii'))

serialcomm.close()