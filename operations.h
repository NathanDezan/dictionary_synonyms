#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 46 /*pneumoultramicroscopicossilicovulcanoconiótico*/
#define HASH_TABLE_SIZE 26 /*devido ao fato de que o alfabeto possui 26 letras, e inicialmente foi a solução mais adequada que encontrei*/

typedef struct Synonym {
    char word[MAX_WORD_LENGTH];
    struct Synonym *next_synonym;
} Synonym;

typedef struct Word {
    char word[MAX_WORD_LENGTH];
    Synonym* synonyms;
    struct Word *next_word;
} Word;

typedef struct Hash {
    char letter;
    Word *dictionary;
} Hash;

typedef struct Dictionary{
    Hash hash_table[HASH_TABLE_SIZE];
} Dictionary;

void add_word(Dictionary *dict, char *str1, char *str2);
void search_synonyms(Dictionary *dict, char *word);
void remove_word(Dictionary *dict, char *word);
// void remove_two_words(Dictionary *dict, char *str1, char *str2);