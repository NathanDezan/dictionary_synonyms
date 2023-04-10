#include "aux.h"
#include <ctype.h>

/*Função responsável por verificar a primeira letra da palavra e aplicar a função de dispersão*/
int search_position(char *word){
    char temp_word[MAX_WORD_LENGTH];
    int asc_value;

    strcpy(temp_word, word);
    asc_value = temp_word[0];

    return (asc_value + 7) % HASH_TABLE_SIZE;
}

/*Função de inicialização da tabela hash*/
/*Aloca memória para cada célula, seta a letra referente a cada célula da tabela hash e os ponteiros como NULO, as letras utilizadas não possuem aplicação prática para o programa, apenas foram utilizadas para teste*/
Dictionary *initializate_hash_table(){
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    Dictionary *dict = malloc(sizeof(Dictionary));

    for (int i = 0; i < HASH_TABLE_SIZE; i++){
        dict->hash_table[i].letter = letters[i];
        dict->hash_table[i].dictionary = NULL;
    }

    return dict;
}

/*Função responsável por realizar a impressão das palavras e sinônimos associados a elas*/
/*Não tem aplicação prática para o programa, apenas foi utilizada para realizar testes*/
void print_dictionary(Dictionary *dict){
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        Word *temp_word = dict->hash_table[i].dictionary;

        if(temp_word->word != NULL){
            while(temp_word != NULL){
                printf("--%s--\n", temp_word->word);
                Synonym *temp_synonym = temp_word->synonyms;
            
                while(temp_synonym != NULL){
                    printf("%s-", temp_synonym->word);

                    temp_synonym = temp_synonym->next_synonym;
                }
                printf("NULL\n");
                temp_word = temp_word->next_word;
            }
        }
    }
}

char *strtrim(char *str){
    char *end;

    // Removendo espaços em branco à esquerda
    while (isspace((unsigned char) *str)) {
        str++;
    }

    // Se a string está vazia
    if (*str == '\0') {
        return str;
    }

    // Removendo espaços em branco à direita
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) {
        end--;
    }

    // Adicionando terminador nulo
    *(end + 1) = '\0';

    return str;
}
