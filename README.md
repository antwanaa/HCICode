# HCICode
Code for our HCI Project

Rules for messages sent through serial:
- Message is a string
- If desired recipient is
    - Left wearable: start message with 'l'
    - Right wearable: start message with 'r'
    - computer: start message with 'c' (not implemented yet)
    - both left and right wearable: start message with 'a' (implemented but needs refinement e.g introduce delay between right and left)
- finish all strings with '\n'


Wiring:
- pin 2 of RIGHT to pin 1 or LEFT
- pin 3 of RIGHT to pin 0 of LEFT

libraries required:
pyserial : to install do: pip install pyserial

IMPORTANT: for GUI to work, the setting needs to be edited in the code.

