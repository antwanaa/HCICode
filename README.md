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



libraries required:
pyserial : to install do: pip install pyserial

IMPORTANT: for GUI to work, the setting needs to be edited in the code.

Messages

  message               | string    | hex
________________________|___________|______
Turn right              | r1        | 0xB1
Turn right next block   | r2        | 0xB2
Turn left               | l1        | 0xC1
Turn left next block    | l2        | 0xC2
Alarm/get off bus/metro | a0        | 0xA0
Starting navigation     | a1        | 0xA1
Wrng trn/dir, locn lost | a2        | 0xA2
Locn lost (deprecated)  | a3        | 0xA3
Arriv. at dest on right | a4        | 0xA4
Arriv. at dest on left  | a5        | 0xA5

To know which arduino is which, press on the white button. This reboots the arduinos. Pay attention the the small LEDs.
The RIGHT arduino will light up GREEN very briefly.
The LEFT arduino will light up RED very briefly.

When a bluetooth connection is established, a blue light turns on.