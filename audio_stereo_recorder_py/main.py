import serial
import os

if __name__ == "__main__":
    ser = serial.Serial('COM7', 230400)  # open serial port
    print(ser.name)         # check which port was really used
    file_path = "out.bin"
    os.remove(file_path)
    
    count = 128
    ser.flush()
    with open(file_path, "wb") as f:
        while count:
            f.write(ser.read())
            count -= 1
    ser.close()             # close port
    print("[ DONE ]")         # check which port was really used
    
