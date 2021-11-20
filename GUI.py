import serial as ser
from tkinter import *
from tkinter import ttk
import time

#############
# CHANGE THIS TO THE COM PORT WHERE THE ARDUINO IS CONNECTED, eg 'COM3' or 'COM4'
port = 'COM4'   
#############
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
def lostLocation():                     # we are removing this part
    ser.write(bytes("a3\n", 'utf-8'))   
def alarm():
    ser.write(bytes("a0\n", 'utf-8'))

def coffee():   # directions to the coffee shop
    ser.write(bytes("a1\n", 'utf-8')) # Starting navigation
    time.sleep(3)
    ser.write(bytes("r1\n", 'utf-8')) # turn right now
    time.sleep(30)
    ser.write(bytes("l2\n", 'utf-8')) # turn left at next block
    time.sleep(15)
    ser.write(bytes("l1\n", 'utf-8')) # turn left now
    time.sleep(15)
    ser.write(bytes("a5\n", 'utf-8')) # Arriving at destination on the left
def home():     # Directions home
    ser.write(bytes("a1\n", 'utf-8')) # Starting navigation
    time.sleep(3)
    ser.write(bytes("l1\n", 'utf-8')) # Turn left now
    time.sleep(40)
    ser.write(bytes("l2\n", 'utf-8')) # turn left at next block
    time.sleep(15)
    ser.write(bytes("l1\n", 'utf-8')) # turn left now
    time.sleep(15)
    ser.write(bytes("a4\n", 'utf-8')) # Arriving at destination on the right
def work():     # Directions to work
    ser.write(bytes("a1\n", 'utf-8')) # Starting navigation
    time.sleep(3)
    ser.write(bytes("l1\n", 'utf-8')) # Turn left now
    time.sleep(20)
    ser.write(bytes("r2\n", 'utf-8')) # turn right at next block
    time.sleep(15)
    ser.write(bytes("r1\n", 'utf-8')) # turn right now
    time.sleep(25)
    ser.write(bytes("l2\n", 'utf-8')) # turn left at next block
    time.sleep(15)
    ser.write(bytes("l1\n", 'utf-8')) # turn left now
    time.sleep(25)
    ser.write(bytes("a4\n", 'utf-8')) # Arriving at destination on the right
def friend():   # Directions to friend's place
    ser.write(bytes("a1\n", 'utf-8')) # Starting navigation
    time.sleep(3)
    ser.write(bytes("r1\n", 'utf-8')) # turn right now
    time.sleep(25)
    ser.write(bytes("r2\n", 'utf-8')) # turn right at next block
    time.sleep(15)
    ser.write(bytes("r1\n", 'utf-8')) # turn right now
    time.sleep(35)
    ser.write(bytes("l2\n", 'utf-8')) # turn left at next block
    time.sleep(15)
    ser.write(bytes("l1\n", 'utf-8')) # turn left now
    time.sleep(25)
    ser.write(bytes("a4\n", 'utf-8')) # Arriving at destination on the right


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
#ttk.Button(frm, text="Location Lost", command=lostLocation).grid(column=1, row=3)
ttk.Button(frm, text="ALARM / Get off the bus/metro", command=alarm).grid(column=1, row=3)

ttk.Label(frm, text=" ").grid(column=0, row=4)
ttk.Label(frm, text="Directions:").grid(column=0, row=5)
ttk.Button(frm, text="Directions to Coffee shop", command=coffee).grid(column=0, row=6)
ttk.Button(frm, text="Bluetooth", command=coffee).grid(column=1, row=6)
ttk.Label(frm, text="Connected").grid(column=1, row=7)
ttk.Button(frm, text="   Directions home   ", command=home).grid(column=0, row=7)
ttk.Button(frm, text="  Directions to work  ", command=work).grid(column=0, row=8)
ttk.Button(frm, text="Directions to friend's place", command=friend).grid(column=0, row=9)
root.mainloop()

