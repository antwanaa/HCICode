import asyncio
from bleak import BleakScanner

# This is a tool to discover bluetooth devices around. Useful to gather the addresses and UUIDs to 
# connect to the correct arduino

def detection_callback(device, advertisement_data):
    print(device.address, "RSSI:", device.rssi, advertisement_data)

async def main():
    scanner = BleakScanner()
    scanner.register_detection_callback(detection_callback)
    await scanner.start()
    await asyncio.sleep(5.0)
    await scanner.stop()

    for d in scanner.discovered_devices:
        print(d)

asyncio.run(main())