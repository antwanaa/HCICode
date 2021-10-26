import serial
from tkinter import *
from tkinter import ttk

# CHANGE THIS TO THE COM PORT WHERE THE ARDUINO IS CONNECTED, eg 'COM3' or 'COM4'
port = 'COM4'   
#############

def startNav():
    ser.write(bytes("a1\n", 'utf-8'))
def wrongWay():
    ser.write(bytes("a2\n", 'utf-8'))
def left():
    ser.write(bytes("l1\n", 'utf-8'))
def leftNextBlock():
    ser.write(bytes("l2\n", 'utf-8'))
def right():
    ser.write(bytes("r1\n", 'utf-8'))
def rightNextBlock():
    ser.write(bytes("r2\n", 'utf-8'))
def lostLocation():
    ser.write(bytes("a3\n", 'utf-8'))
def alarm():
    ser.write(bytes("a0\n", 'utf-8'))


root = Tk()
frm = ttk.Frame(root, padding=10)
frm.grid()
#variable = StringVar(root)
#variable.set('COM1') # default value
#w = OptionMenu(root, variable, 'COM1', 'COM2', 'COM3', 'COM4', 'COM5').grid(column=0, row=1)
#ser = serial.Serial(port, 9600, timeout=1)  # open serial port
ttk.Button(frm, text="Starting Navigation", command=startNav).grid(column=0, row=0)
ttk.Button(frm, text="      Turn Left Now      ", command=left).grid(column=0, row=1)
ttk.Button(frm, text="      Turn Right Now      ", command=right).grid(column=1, row=1)
ttk.Button(frm, text="Turn Left at next block", command=leftNextBlock).grid(column=0, row=2)
ttk.Button(frm, text="Turn Right at next block", command=rightNextBlock).grid(column=1, row=2)
ttk.Button(frm, text="Wrong Way", command=wrongWay).grid(column=0, row=3)
ttk.Button(frm, text="Location Lost", command=lostLocation).grid(column=1, row=3)
ttk.Button(frm, text="Get off the bus/metro", command=alarm).grid(column=2, row=3)
root.mainloop()

