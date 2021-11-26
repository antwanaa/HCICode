import asyncio
from asyncio.windows_events import NULL
from bleak import BleakClient
from threading import Thread
from tkinter import *
from tkinter import ttk


address1 = "BB:3D:B1:4B:81:80"  # Arduino 1
address2 = "95:7D:75:64:94:9A"  # Arduino 2
MODEL_NBR_UUID = "19b10001-e8f2-537e-4f6c-d104768a1214"


async def disconnectFromDevice():
    await client1.disconnect()
    await client2.disconnect()

def on_closing():
    disconnectFromDevice()
    root.destroy()

async def connect():
    global client1 
    global client2
    client1 = BleakClient(address1)
    client2 = BleakClient(address2)
    
    while not (client1.is_connected and client2.is_connected):    
        if not client1.is_connected:
            try:
                await client1.connect()
                model_number = await client1.read_gatt_char(MODEL_NBR_UUID)
                print("Arduino 1")
                print("Model Number: {0}".format("".join(map(chr, model_number))))
            except Exception as e:
                print(e)
        
        if not client2.is_connected:
            try:
                await client2.connect()
                model_number = await client2.read_gatt_char(MODEL_NBR_UUID)
                print("Arduino 2")
                print("Model Number: {0}".format("".join(map(chr, model_number))))
            except Exception as e:
                print(e)
            # finally:
                # await client1.write_gatt_char(MODEL_NBR_UUID,b'\x00', True)
                # print("Done connecting")
    
    print("done connecting")
        
def startConnect():
    # call startScan() from main thread
    asyncio.run_coroutine_threadsafe(connect(), loop)

async def send1(parameter):
    await client1.write_gatt_char(MODEL_NBR_UUID, parameter, True)
    # await client2.write_gatt_char(MODEL_NBR_UUID, parameter, True)
async def send2(parameter):
    await client2.write_gatt_char(MODEL_NBR_UUID, parameter, True)

def startNav():
        asyncio.run_coroutine_threadsafe(send1(b'\xA1'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xA1'), loop)
def left():
        asyncio.run_coroutine_threadsafe(send1(b'\xC1'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xC1'), loop)
def right():
        asyncio.run_coroutine_threadsafe(send1(b'\xB1'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xB1'), loop)
def leftNextBlock():
        asyncio.run_coroutine_threadsafe(send1(b'\xC2'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xC2'), loop)
def rightNextBlock():
        asyncio.run_coroutine_threadsafe(send1(b'\xB2'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xB2'), loop)
def wrongWay():
        asyncio.run_coroutine_threadsafe(send1(b'\xA2'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xA2'), loop)
def alarm():
        asyncio.run_coroutine_threadsafe(send1(b'\xA0'), loop)
        asyncio.run_coroutine_threadsafe(send2(b'\xA0'), loop)

if __name__ == "__main__":
    
    root = Tk()
    frm = ttk.Frame(root, padding=10)
    frm.grid()
    # ...
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
    # ttk.Button(frm, text="Directions to Coffee shop", command=coffee).grid(column=0, row=6)
    # ttk.Button(frm, text="Bluetooth", command=coffee).grid(column=1, row=6)
    # ttk.Label(frm, text="Connected").grid(column=1, row=7)
    # ttk.Button(frm, text="   Directions home   ", command=home).grid(column=0, row=7)
    # ttk.Button(frm, text="  Directions to work  ", command=work).grid(column=0, row=8)
    # ttk.Button(frm, text="Directions to friend's place", command=friend).grid(column=0, row=9)

    loop = asyncio.get_event_loop()
    def bleak_thread(loop):
        asyncio.set_event_loop(loop)
        loop.run_forever()
    t = Thread(target=bleak_thread, args=(loop,))
    t.start()
       
    startConnect()
    

    root.mainloop()
    loop.call_soon_threadsafe(loop.stop)