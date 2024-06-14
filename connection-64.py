#Python Code:

import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui

ArduinoSerial = serial.Serial('COM6',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print(incoming)
    
    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)

    if 'Volume-Down' in incoming:
        pyautogui.hotkey('down')

    if 'Volume-Up' in incoming:
        pyautogui.hotkey('up')

    if 'Fast-Forward' in incoming:
        pyautogui.hotkey('ctrl', 'right') 

    if 'Rewind' in incoming:
        pyautogui.hotkey('ctrl', 'left')

    if 'Next' in incoming:
        pyautogui.hotkey('n') 

    if 'Previous' in incoming:
        pyautogui.hotkey('p')  

    incoming = "";
