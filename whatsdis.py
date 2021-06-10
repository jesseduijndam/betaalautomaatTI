import json
import requests
import serial
import time
from datetime import datetime
arduino = serial.Serial ('COM4', 115200)
arduino.timeout = 5
url = "http://tic5.duckdns.org:8001/"
# while True:
IBAN = arduino.readline().decode('utf-8')[:-2]
if IBAN:
    arduino.flushInput()
    landcode = IBAN[0:4].upper()
    bankcode = IBAN[4:8].upper()
    print(IBAN)
    arduino.write("pin".encode())
    pin = arduino.readline().decode('utf-8')[:-2]
    print("pin = "+pin)

    
    #now = datetime.now()
    #dtstring = now.strftime("%d/%m/%Y/ %H:%M:%S")
    


    #arduino.write(dtstring.encode())
    #time.sleep(0.5)
    arduino.write("print".encode())
    time.sleep(20)



    payload = { "body": { "pin": str(pin), "IBAN": IBAN,"amount": "1" }, "header": { "receiveCountry": landcode, "receiveBankName": bankcode } }
    res = requests.post(url+"withdraw", json=payload)
    print(res.json())
            # if res.ok:
            #     res=res.json()
            #     response_body=res["body"]
            #     response_header=res["header"]
            #     print("pin = "+response_body['pin'])
            #     print("IBAN = "+response_body['IBAN'])
            #     print("amount = "+str(response_body['amount']))
            #     print("receiveCountry = "+response_header['receiveCountry'])
            #     print("receiveBankName = "+response_header['receiveBankName'])    




            # print(IBAN)
            # IBAN = IBAN.translate({ord(' '): None})
            # arduino.flushInput()
            # print(IBAN + "|")
            # arduino.write("pin".encode())
            # pin = arduino.readline().decode('utf-8')[:-2]
            # print("pin = "+pin)
            # # data1 = requests.get(url+"pin?IBAN="+IBAN+"&pin="+str(pin)).json()
            # data1 = requests.get(url+"pin", params = {"IBAN": IBAN, "pin": str(pin)}).json()
            # print(data1)