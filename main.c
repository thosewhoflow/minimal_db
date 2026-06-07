#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_input();
void app_close();
char* get_a_word(char* input);
typedef struct {
    char* type;
    char* value;
} token;
int main(void) {
    for (;;) {
        printf("MarianDB> ");
        char* input = get_input();
        if (input == NULL) continue;
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
            free(input);
            app_close();
        }
        get_a_word(input);
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

char* get_a_word(char* input) {
    char* word = malloc(strlen(input) + 1);
    printf("input = %s\n", input);
}
token tokenize(char* input) {
    token t;

}