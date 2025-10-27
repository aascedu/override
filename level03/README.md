# Understanding the level03

First we need to decompile the binary file and analyze the code.
we see 3 functions, test, main, and decrypt.

the input is passed to the test function, which checks for the difference between the input and 322424845. If it's between 1 and 9 or between 16 and 21, it calls decrypt with the difference of `322424845 - input` as an argument. If it's not, it calls decrypt with a totally random value.

# Our strategy
As there is only 15 possibilities for it not to be random, we can brute force it.
The case which worked was when 322424845 - input = 18.