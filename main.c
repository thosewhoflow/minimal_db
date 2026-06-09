#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* type;
    char* value;
} token;
char* get_input();
void app_close();
size_t get_tokens(char* input, token* tokens);
void add_types_to_token(char* input, token* tokens, size_t token_index);
int main(void) {
    token tokens[100] = {0}; // set everything to null to initialize it lol
    size_t tokens_amount = 0;
    for (;;) {
        printf("MarianDB> ");
        char* input = get_input();
        if (input == NULL) continue;
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
            free(input);
            app_close();
        }
        tokens_amount = get_tokens(input, tokens);
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

size_t get_tokens(char* input, token* tokens) {
    bool in_token = false, in_quotes = false;
    size_t word_start = 0, word_end = 0, tokens_amount = 0;
    char one_token[255];
    for (size_t i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"' && !in_quotes) {
            in_quotes = true;
            in_token = true;
            word_start = i;
            // printf("start quotes get tokens\n");
            // printf("i = %zu\n", i);
            continue;
        }
        if (input[i] == '"' && in_quotes && in_token) {
            in_quotes = false;
            word_end = i;
            // printf("i = %zu\n", i);
            // printf("end quotes get tokens\n");
        }
        if (in_quotes) continue;
        if (input[i] != ' ' && !in_token) {
            in_token = true;
            word_start = i;
        }
        if (input[i] == ' ' && in_token ) {
            in_token = false;
            word_end = i;
            i--;
            // printf("word_end = %zu\n", word_end);
            for (size_t j = word_start, c = 0; j < word_end; j++, c++) {
                one_token[c] = tolower(input[j]);
                // printf("%c", one_token[c]);
            }
            one_token[word_end] = '\0';
            tokens[tokens_amount].value = one_token;
            // printf("one token = %s\n", one_token);
            add_types_to_token(one_token, tokens, tokens_amount);
            memset(one_token, 0, 255);
            tokens_amount++;
        }
    }
    return tokens_amount;
}
void add_types_to_token(char* input, token* tokens, size_t token_index) {
    size_t token_length = strlen(input);
    bool quotes = false;
    // errors
    // printf("token in types function = '%s'\n", input);
    // printf("token len = %zu\n", token_length);
    for (size_t i = 0; i < token_length; i++) {
        if (input[i] == '"' && !quotes) {
            // printf("quote open\n");
            quotes = true;
            i++;
        }
        if (input[i] == '"' && quotes) {
            // printf("quote close\n");
            quotes = false;
            break;
        }
        // printf("%c\n", input[i]);
        // printf("i = %zu\n", i);
    }
    if (quotes) {
        // printf("unclosed quotes\n");
        return;
    }
    // printf("closed quotes\n");
    // type assign
    if (strcmp(input, "select") == 0) {
        tokens[token_index].type = "TOKEN_SELECT";
        printf("Token SELECT\n");
        return;
    }
    if (strcmp(input, "insert") == 0) {
        tokens[token_index].type = "TOKEN_INSERT";
        printf("Token INSERT\n");
        return;
    }
    if (strcmp(input, "from") == 0) {
        tokens[token_index].type = "TOKEN_FROM";
        printf("Token FROM\n");
        return;
    }
    if (strcmp(input, "into") == 0) {
        tokens[token_index].type = "TOKEN_INTO";
        printf("Token INTO\n");
        return;
    }
    if (strcmp(input, "values") == 0) {
        tokens[token_index].type = "TOKEN_VALUES";
        printf("Token VALUES\n");
        return;
    }
    if (input[0] == '"' && input[token_length - 1] == '"') {
        tokens[token_index].type = "TOKEN_STRING";
        printf("Token STRING\n");
        return;
    }
    if (strcmp(input, "*") == 0) {
        tokens[token_index].type = "TOKEN_STAR";
        printf("Token STAR\n");
        return;
    }
    if (strcmp(input, ",") == 0) {
        tokens[token_index].type = "TOKEN_COMMA";
        printf("Token COMMA\n");
        return;
    }
    if (strcmp(input, ";") == 0) {
        tokens[token_index].type = "TOKEN_SEMICOLON";
        printf("Token SEMICOLON\n");
        return;
    }
    for (int i = 0; i < token_length; i++) {
        if (!isdigit(input[i])) {
            break;
        }
        if (i == token_length-1) {
            tokens[token_index].type = "TOKEN_NUMBER";
            printf("Token NUMBER\n");
            return;
        }
    }
    printf("Unrecognized token: %s\n", input);

}