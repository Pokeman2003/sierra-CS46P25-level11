// You know, I really should've fucking checked the file descriptions first instead of trying to figure out why example0.txt and enable1.txt yielded 0/6494 for 2 hours.
// Was debugging a bug that wasn't even a BUG.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int main(int argc, char *argv[])
{
    // Initialization.
    FILE *passwords;
    int size;
    int hashCount;
    double hashTotal;
    char inputStr[PASS_LEN+1];
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }
    passwords = fopen(argv[2], "r");
    if (passwords == NULL) {
        perror("Failed to open passwords file");
        return -1;
    }
    char **hashes = loadFileAA(argv[1], &size);
    hashCount = 0;

    // CHALLENGE1: Sort the hashes using qsort.
    // TODO: I want to do this later.


    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    while (fgets(inputStr, PASS_LEN+1, passwords)) {
        char *hash = malloc(HASH_LEN * (sizeof(char)));
        char *match;
        int strLength = strlen(inputStr) - 1;
        inputStr[strLength] = 0; // Remove CRLF.
        // printf("%s\n", inputStr);
        hash = md5(inputStr, strLength);
        match = substringSearchAA(hash, hashes, size);
        if (match != NULL) {
            printf("Found: %s => %s\n", inputStr, match);
            hashCount++;
        }
        free(hash);
    }
    
    // CHALLENGE2: Use binary search instead of linear search.
    // TODO: The challenges.
    
    hashTotal = (hashCount / size) * 100;
    printf("Finished! Found %d/%d passwords! (%0.02f%% of the hashes)\n", hashCount, size, hashTotal);
    fclose(passwords);
    freeAA(hashes, size);
}
