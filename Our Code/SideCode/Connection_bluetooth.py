import serial

# COM ports (Check Device Manager)
msp_port = 'COM9'    # MSP432 Serial
hc05_port = 'COM14'  # HC-05 Bluetooth Outgoing COM

try:
    # Open Serial connections
    msp = serial.Serial(msp_port, 9600, timeout=1)
    hc05 = serial.Serial(hc05_port, 9600, timeout=1)

    print("Relaying joystick commands from MSP432 to Arduino via Bluetooth...")

    while True:
        # MSP to HC05
        if msp.in_waiting:
            data_from_MSP = msp.readline().decode().strip()  # Read MSP432 data
            if data_from_MSP in ['F', 'B', 'L', 'R', 'S', 'W', 'P']:  # Valid commands
                print(f"Sending:----------{data_from_MSP}----------")
                hc05.write(data_from_MSP.encode())  # Send via Bluetooth

        # HC05 to MSP
        if hc05.in_waiting:
            data_from_hc05 = hc05.readline().decode().strip()
            print(f"Receiving: {data_from_hc05}")
            # msp.write(data_from_hc05.encode())

except KeyboardInterrupt:
    print("\nStopping relay...")
finally:
    msp.close()
    hc05.close()
    print("Ports closed.")