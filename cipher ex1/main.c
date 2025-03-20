#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TEST_ERR "Usage: cipher test\n"
#define ARG_ERR "The program receives 1 or 4 arguments only.\n"
#define CMD_ERR "The given command is invalid.\n"
#define VALUE_ERR  "The given shift value is invalid.\n"
#define FILE_ERR "The given file is invalid.\n"
#define BASE 10
#define MAXLENGTH 1024
#define MAXARGS 5
#define MINARGS 2

int is_k_number(const char *str) {
    if (*str == '-') // check aditional minus
    {
        str++;
    }
    if (*str=='\0'){
      return 0;

    }
    while (*str) {
        if (!isdigit((unsigned char)*str)) // to check if the charcter isnt digit
        {
            return 0;
        }
        str++;
    }
    return 1;
}

int file_check(const char *infile, const char *outfile) {
    FILE *in = fopen(infile, "r");
    FILE *out = fopen(outfile, "w");
    if (out==NULL && in==NULL){
        return 0;
    }
    if (out == NULL){
        fclose(in);
        return 0;
    }
    if (in == NULL ) {
        fclose(out);
        return 0;
    }
    fclose(out);
    fclose(in);
    return 1;
}

int check_tests() {
    if (test_cipher_non_cyclic_lower_case_positive_k() || test_cipher_cyclic_lower_case_special_char_positive_k()
        || test_cipher_non_cyclic_lower_case_special_char_negative_k() || test_cipher_cyclic_lower_case_negative_k()
        || test_cipher_cyclic_upper_case_positive_k() || test_decipher_non_cyclic_lower_case_positive_k()
        || test_decipher_cyclic_lower_case_special_char_positive_k()
        || test_decipher_non_cyclic_lower_case_special_char_negative_k()
        || test_decipher_cyclic_lower_case_negative_k() || test_decipher_cyclic_upper_case_positive_k()) {
        return 0;
    }
    return 1;
}

int cipher_decipher_work(const char *arg1, const char *arg2, const char *arg3, const char *arg4) {
    FILE *infile = fopen(arg3, "r");
    FILE *outfile = fopen(arg4, "w");
    char line[MAXLENGTH];
    if (strcmp(arg1, "cipher") == 0) // to check the command
    {
        while (fgets(line,MAXLENGTH, infile) != NULL) // untill you finish the file
        {
            cipher(line, strtol(arg2,NULL,BASE));
            fputs(line, outfile);
        }
        fclose(infile);
        fclose(outfile);
        return EXIT_SUCCESS;
    }
    if (strcmp(arg1, "decipher") == 0) // to check the command
    {
        while (fgets(line,MAXLENGTH, infile) != NULL) // get lines untill you finish the file
        {
            decipher(line, strtol(arg2,NULL,BASE));
            fputs(line, outfile);
        }

        fclose(infile);
        fclose(outfile);
        return EXIT_SUCCESS;
    }
  fprintf(stderr,CMD_ERR); // the input command are invalid
  return EXIT_FAILURE;

}


int main(int argc, char *argv[])
{
    if (argc == MINARGS) {
        if (strcmp(argv[1], "test") != 0 )// if we got a paramter and not test
        {
            fprintf(stderr,TEST_ERR);
            return EXIT_FAILURE;
        }
        if (check_tests() == 0) // if one of the tests failed
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    if (argc == MAXARGS) {
        if (strcmp(argv[1], "cipher") != 0 && strcmp(argv[1], "decipher") != 0)

        //to check the givin coomand
        {
            fprintf(stderr,CMD_ERR);
            return EXIT_FAILURE;
        }
        if (is_k_number(argv[2]) == 0) // to check the given shift
        {
            fprintf(stderr,VALUE_ERR);
            return EXIT_FAILURE;
        }
        if (file_check(argv[3],argv[4]) == 0) // to check the giving file
        {
            fprintf(stderr,FILE_ERR);
            return EXIT_FAILURE;
        }
        if (cipher_decipher_work(argv[1], argv[2], argv[3], argv[4])==0)
          {return EXIT_SUCCESS;}else{return EXIT_FAILURE;}
        // the function will cipher\decipher and will check if the giving command are valid
    }
  fprintf (stderr,ARG_ERR);
    return EXIT_FAILURE;

}