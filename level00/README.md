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