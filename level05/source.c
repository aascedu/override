#include <stdio.h>
#include <stdlib.h>

void main(void) {
    // Variables used in the code
    unsigned int index = 0;    // Tracks current position in input
    unsigned int length;
    unsigned int max_len;
    char input[100];           // Buffer to store input
    char current_char;
    
    // Read up to 100 characters from stdin (including newline if present)
    fgets(input, 100, stdin);
    
    index = 0;
    while (1) {
        // Manual strlen: start with max unsigned int (0xFFFFFFFF)
        max_len = 0xFFFFFFFF;
        
        // Pointer to beginning of input buffer
        char *ptr = input;
        
        // Find string length by scanning for null terminator
        while (max_len != 0) {
            max_len--;
            current_char = *ptr;
            // Move pointer forward by 1 (since bVar4 = 0)
            ptr = ptr + 1;
            if (current_char == 0) {
                break;
            }
        }
        
        // Check if current index is beyond string length (dangerous!)
        if ((~max_len - 1) <= index) {
            // Vulnerability: prints the string without format specifier!
            printf(input);
            // Exit program
            exit(0);
        }
        
        // If current character is uppercase A-Z, convert to lowercase
        if ((input[index] > '@') && (input[index] < '[')) {
            input[index] ^= 0x20;  // Flip 6th bit to convert case
        }
        
        index++;
    }
}
