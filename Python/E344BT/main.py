import serial
import time

def setSpeed(x):
    packet = bytearray()    
    packet.append(123)
    packet.append(111)
    packet.append(3) #length
    packet.append(0) #set 
    packet.append(50) #RW speed
    #packet.append(23) #increment value
    packet.append(int(x))
    arduino.write(packet)

def getRWNibble():
    packet = bytearray()    
    packet.append(123)
    packet.append(111)
    packet.append(2) #length
    packet.append(1) #get
    packet.append(2) #right speed
    arduino.write(packet)
    time.sleep(0.05)
    #and now read it
    pkttype = ord(arduino.read()) #type
    pktlen = ord(arduino.read()) #msgID
    valueret = ord(arduino.read())
    print("Type = ", pkttype,". Len = ",pktlen, ". RW nibble: ",valueret,"\n")


def getRWCurrent():
    packet = bytearray()    
    packet.append(123)
    packet.append(111)
    packet.append(2) #length
    packet.append(1) #get
    packet.append(0) #right speed
    arduino.write(packet)
    pkttype = ord(arduino.read()) #type
    pktlen = ord(arduino.read()) #msgID
    valueret = ord(arduino.read());
    valueret = valueret + ord(arduino.read())*256;
    print("Type = ", pkttype,". Len = ",pktlen,". RW Current: ",valueret,"\n")
  

def menu():
        return int(input(" 1. Set speed to 10,\n 2. Set speed to 20\n 3. Read speed,\n 4. Read RW current \n 5. To exit.\n\n"))

arduino = serial.Serial(port='COM12', baudrate=115200, timeout=1)
#print(arduino)


choice = 0
while True:
    choice = menu()
    if choice == 1: 
        setSpeed(10)    
    if choice == 2: 
        setSpeed(20) 
    if choice == 3: 
        getRWNibble()
    if choice == 4: 
        getRWCurrent()       
    # Do stuff
    if choice == 5: #Or whatever end condition
        break

#print(arduino.read())
arduino.close()