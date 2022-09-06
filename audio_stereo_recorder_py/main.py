import serial
import wave
import os
import time
import numpy as np

# Audio config
SERIAL_BAUDRATE = 460800
SAMPLE_RATE_HZ = 4000
SAMPLE_PERIOD_US = int(round(1000000 / SAMPLE_RATE_HZ))
SAMPLE_WIDTH = 1
CHANNELS_N = 1

# Receiving config
CHUNK_SIZE_SAMPLES = 1000
RECORD_TIME_SEC = 10

# Write config
FILE_PATH = "out.bin"
FILE_WAV_PATH = "out.wav"

# Global variables
ser = None
data = []

def get_now_s():
    return int(round(time.time()))

def get_now_ms():
    return int(round(time.time_ns() / 1000000))

def get_now_us():
    return int(round(time.time_ns() / 1000))

def init():
    # clean old files
    try:
        os.remove(FILE_PATH)
        os.remove(FILE_WAV_PATH)
    except FileNotFoundError:
        pass
    
    # init serial
    global ser
    ser = serial.Serial('COM7', SERIAL_BAUDRATE)  # open serial port
    while not ser.is_open:
        pass
    ser.flush()
    print(f"[ START ] Serial: {ser.name}")

def get_data():
    BYTES_TO_GET = RECORD_TIME_SEC * SAMPLE_RATE_HZ * SAMPLE_WIDTH * CHANNELS_N
    bytes_rcvd_n = 0
    while bytes_rcvd_n < BYTES_TO_GET:
        bytes_to_read = CHUNK_SIZE_SAMPLES*SAMPLE_WIDTH
        new_data = ser.read(bytes_to_read)
        data.extend(list(new_data))
        bytes_rcvd_n += bytes_to_read
        # print(f"Read  {bytes_rcvd_n} of {BYTES_TO_GET} - {list(new_data)}")
    print(f"[ DATA IS READY ]")    

def get_data_localtiming():
    # BYTES_TO_GET = RECORD_TIME_SEC * SAMPLE_RATE * SAMPLE_WIDTH * CHANNELS_N
    bytes_rcvd_n = 0
    start_time_ms  = get_now_ms()
    end_time_ms = start_time_ms + RECORD_TIME_SEC * 1000
    
    while get_now_ms() < end_time_ms:
        current_sample_time_ns = time.time_ns()
        new_data = ser.read()
        bytes_rcvd_n += 1
        data.extend(list(new_data))
        # print(f"Read  {bytes_rcvd_n}")
        while time.time_ns() - current_sample_time_ns < SAMPLE_PERIOD_US * 1000:
            # print(f"{time.time_ns() - current_sample_time_ns} < {SAMPLE_PERIOD_US * 1000}")
            pass  # wait for a time for the next sample
    print(f"[ DATA IS READY ] {bytes_rcvd_n} bytes")

def write_data():
    with wave.open(FILE_WAV_PATH, "w") as f:
        f.setnchannels(CHANNELS_N)
        f.setsampwidth(SAMPLE_WIDTH)
        f.setframerate(SAMPLE_RATE_HZ)
        f.writeframes(bytearray(data))
    print(f"[ WROTE TO FILE ]")    
    
        
        
def finalize():
    ser.close()  # close port
    print("[ DONE ]")  # check which port was really used

if __name__ == "__main__":
    init()
    get_data()
    # get_data_localtiming()
    write_data()
    finalize()
