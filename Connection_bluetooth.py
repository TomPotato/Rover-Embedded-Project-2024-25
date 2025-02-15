import serial

# COM ports (Check Device Manager)
msp_port = 'COM9'   # MSP432 Serial
hc05_port = 'COM14'  # HC-05 Bluetooth Outgoing COM

try:
    # Open Serial connections
    msp = serial.Serial(msp_port, 9600, timeout=1)
    hc05 = serial.Serial(hc05_port, 9600, timeout=1)

    print("Relaying joystick commands from MSP432 to Arduino via Bluetooth...")

    while True:
        if msp.in_waiting:
            command = msp.readline().decode().strip()  # Read MSP432 data
            if command in ['F', 'B', 'L', 'R', 'S']:  # Valid commands
                print(f"{command}")
                hc05.write(command.encode())  # Send via Bluetooth

except KeyboardInterrupt:
    print("\n Stopping relay...")
finally:
    msp.close()
    hc05.close()
    print("Ports closed.")