import serial
from tkinter import *
from tkinter import ttk

# CHANGE THIS TO THE COM PORT WHERE THE ARDUINO IS CONNECTED, eg 'COM3' or 'COM4'
port = 'COM4'   
#############

def left():
    ser.write(bytes("l1\n", 'utf-8'))

def right():
    ser.write(bytes("r1\n", 'utf-8'))

root = Tk()
frm = ttk.Frame(root, padding=10)
frm.grid()
#variable = StringVar(root)
#variable.set('COM1') # default value
#w = OptionMenu(root, variable, 'COM1', 'COM2', 'COM3', 'COM4', 'COM5').grid(column=0, row=1)
ser = serial.Serial(port, 9600, timeout=1)  # open serial port
ttk.Button(frm, text="Turn Left", command=left).grid(column=0, row=0)
ttk.Button(frm, text="Turn Right", command=right).grid(column=1, row=0)
root.mainloop()

