import serial

# COM ports (Check Device Manager)
msp_port = 'COM9'    # MSP432 Serial
hc05_port = 'COM14'  # HC-05 Bluetooth Outgoing COM

try:
    # Open Serial connections
    msp = serial.Serial(msp_port, 115200, timeout=1)
    hc05 = serial.Serial(hc05_port, 9600, timeout=1)

    print("Mars Rover")

    while True:  # Indented inside the try block
        # MSP to HC05
        if msp.in_waiting:
            data_from_MSP = msp.readline().decode().strip()  # Read MSP432 data
            if data_from_MSP in ['F', 'B', 'L', 'R', 'S', 'W', 'P']:  # Forward,Backward,Left,Right,Stationary,W,P
                if data_from_MSP in ['W','P']:
                    print(f"Sending:----------{data_from_MSP}----------")#stamp on cmd 
                hc05.write(data_from_MSP.encode())  # Send via Bluetooth 

        # HC05 to MSP
        if hc05.in_waiting:
            data_from_hc05 = hc05.readline().decode().strip() #Read HC05 data
            print(f"Receiving: {data_from_hc05}")  #Print on cmd
            #check if the message is LED ON/OFF, looking at this message I can know the status of the led on the robot
            if data_from_hc05 in ['LED ON', 'LED OFF']:  
                msp.write(data_from_hc05.encode())  

except KeyboardInterrupt:
    print("\nStopping relay...")
finally:
    msp.close()
    hc05.close()
    print("Ports closed.")
