#include "forth.h"
#include "words.h"

#include <stdio.h>

#define MAX_DATA 16384
#define MAX_STACK 16384

int main(int argc, char** argv)
{
    FILE *input;
    
    if (argc != 1){
        struct forth forth = {0};
        if((input = fopen(argv[1], "r")) == NULL){
            printf("Can't open file %s\n", argv[1]);
            return 0;
        }    
        forth_init(&forth, input, MAX_DATA, MAX_STACK);
        words_add(&forth);
        forth_run(&forth);
        fclose(input);
        int i = 2;
        while (argv[i] != 0){
            if(*argv[i] != '-'){
                if((input = fopen(argv[i], "r")) == NULL){
                    printf("Can't open file %s\n", argv[i]);
                    return 0;
                }
                forth.input = input;
                
                forth_run(&forth);
                fclose(input);
            }
            else{
                forth.input = stdin;
                forth_run(&forth);
            }
            i++;
        }
        return 0;
        
    } else {
        struct forth forth = {0};
        forth_init(&forth, stdin, MAX_DATA, MAX_STACK);
        words_add(&forth);
        forth_run(&forth);
        
    }
    return 0;
}
