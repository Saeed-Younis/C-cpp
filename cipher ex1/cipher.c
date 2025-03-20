#include "cipher.h"
#include <stdio.h>
#include "tests.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.
#define NUMALPHABET 26
// See full documentation in header file
void cipher(char s[], int k) {

    if (k < 0) { decipher(s, -k); }
    else {
        for (int i = 0; s[i] != '\0'; i++) // for the upper case
        {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] = ((s[i] - 'A' + k) % NUMALPHABET) + 'A'; // to calculate the new vaule of the char after the move
            }
            if ((s[i] >= 'a' && s[i] <= 'z')) // for the lower case
            {
                s[i] = ((s[i] - 'a' + k) % NUMALPHABET + 'a'); // to calculate the new vaule of the char after the move
            }
        }
    }
}

// See full documentation in header file
void decipher(char s[], int k) {
    if (k < 0) { cipher(s, -k); }
    else {
        if (k > NUMALPHABET) { k %= NUMALPHABET; }
        for (int i = 0; s[i] != '\0'; i++) // for the upper case
        {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] = 'A' + (s[i] - 'A' - k + NUMALPHABET) % NUMALPHABET;
                // to calculate the new vaule of the char after the move (+26) to ensure possitive value
            }
            if ((s[i] >= 'a' && s[i] <= 'z')) // for the lower case
            {
                s[i] = (s[i] - 'a' - k + NUMALPHABET) % NUMALPHABET + 'a';
                // to calculate the new vaule of the char after the move (+26)to ensure possistive value
            }
        }
    }
}
