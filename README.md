# HCICode
Code for our HCI Project


Rules for messages sent through serial:
- Message is a string
- If desired recipient is
    - Left wearable: start message with 'l'
    - Right wearable: start message with 'r'
    - computer: start message with 'c' (not implemented)
    - both left and right wearable: start message with 'a' (not implemented yet)
- finish all strings with '\n'


Wiring:
- pin 2 of RIGHT to pin 1 or LEFT
- pin 3 of RIGHT to pin 0 of LEFT
