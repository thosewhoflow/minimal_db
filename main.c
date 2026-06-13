#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
char* get_input();
void app_close();
int main(void) {
    token tokens[100] = {0}; // set everything to null to initialize it lol
    size_t tokens_amount = 0;
    for (;;) {
        printf("MarianDB> ");
        char* input = get_input();
        if (input == NULL) continue;
        for (int i = 0; i < tokens_amount; i++) {
            free(tokens[i].value);
            tokens[i].type = NULL;
        }
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
            free(input);
            app_close();
        }
        tokens_amount = get_tokens(input, tokens);
        free(input);
        input = NULL;
        printf("tokens: %zu\n", tokens_amount);
        for (int i = 0; i < tokens_amount; i++) {
            printf("token[%d]: TYPE: %s \t VALUE: %s\n", i, tokens[i].type, tokens[i].value);
        }
    }
}

char* get_input() {
    char* input = NULL;
    size_t buf = 0;
    ssize_t const len = getline(&input, &buf, stdin);
    if (len <= 0) return NULL;
    input[len-1] = '\0';
    return input;
}

void app_close() {
    printf("Closing database...\n");
    exit(0);
}