# Understanding the level03

First we need to decompile the binary file and analyze the code.
we see 3 functions, test, main, and decrypt.

the input is passed to the test function, which checks for the difference between the input and a specific value. If it's between 1 and 9 or between 16 and 21, it calls decrypt with the difference as an argument. If it's not, it calls decrypt with a totally random value.

# Our strategy
As there is only 15 possibilities for it not to be random, we can brute force it.
so I'm trying different values until i get to 322424845 which makes a difference of 18 between the original value and my output. The program now launches a shell as the user level04 and i can now read the flag.

The fact that 18 as the difference in the test function worked is explainable by the XOR operation used in the decrypt function on every character of a hardcoded string between the character itself and 18.
doing a xor operation on every char of "Q}|u`sfg~sf{}|a3" and 18 gives us "Congratulations!" and later in the code the string is compared to this to spawn a shell or not.
