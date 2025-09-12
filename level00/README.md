# level00
## Protections

| Protection     | Status              | Explanation |
|----------------|---------------------|-------------|
| **RELRO**      | Partial RELRO       | Global Offset Table (GOT) is not fully protected. Vulnerable to GOT overwrite attacks. |
| **Stack Canary** | No canary found   | Stack overflows are not detected. Return address can be overwritten freely. |
| **NX (No-eXecute)** | NX enabled     | Stack is non-executable. Injected shellcode won't run; must use ROP or ret2libc. |
| **PIE (Position Independent Executable)** | No PIE | Binary is loaded at a fixed address in memory. Easier to perform ROP as addresses are predictable. |
| **RPATH / RUNPATH** | None           | No custom dynamic linker paths. No impact on typical exploitation. |
---

## Decompiled code
```C
bool main(void)

{
  int local_14 [4];
  
  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf(&DAT_08048636,local_14);
  if (local_14[0] != 0x149c) {
    puts("\nInvalid Password!");
  }
  else {
    puts("\nAuthenticated!");
    system("/bin/sh");
  }
  return local_14[0] != 0x149c;
}
```

## Exploit
We need `local_14`, which is the input from the user we get with `scanf`, equal to `0x149c` (5276 in decimal base).

## Flag
`uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL`