

#ifndef MARIAN_BAZA_DANYCH_TOKENIZER_H
#define MARIAN_BAZA_DANYCH_TOKENIZER_H
typedef struct {
    char* type;
    char* value;
} token;
size_t get_tokens(char* input, token* tokens);
void add_types_to_token(char* input, token* tokens, size_t token_index);
#endif //MARIAN_BAZA_DANYCH_TOKENIZER_H