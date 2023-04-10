#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "operations.c"
#include "testing.c"
#include "aux.c"
#include "file.c"

int main(int argc, char *argv[]){
    char input[100], str1[MAX_WORD_LENGTH], str2[MAX_WORD_LENGTH];
    char file_name[] = "data";
    int op;
    // Hash hash_table[HASH_TABLE_SIZE];

    Dictionary *dict = initializate_hash_table();
    load_data(dict, "data");

    while(1){
        fgets(input, 100, stdin); // lê a entrada do usuário

        op = -1; // inicializa op como um valor inválido

        // verifica qual operação deve ser executada
        if(sscanf(input, "insere %s %s", str1, str2) == 2){
            op = 1;
        }else if(sscanf(input, "remove %s %s", str1, str2) == 2){
            op = 2;
        }else if(sscanf(input, "remove %s", str1) == 1){
            op = 3;
        }else if(sscanf(input, "busca %s", str1) == 1){
            op = 4;
        }else if(strcmp(input, "fim\n") == 0){
            op = 5;
        }else if(strcmp(input, "print\n") == 0){
            op = 6;
        }else if(strcmp(input, "test\n") == 0){
            op = 7;
        }

        switch(op){
            case 1:
                add_word(dict, str1, str2);
                add_word(dict, str2, str1);
                break;
            case 2:
                printf("Operação de remoção: str1=%s, str2=%s\n", str1, str2);
                // remove_two_words(dict, str1, str2);
                // remove_two_words(dict, str2, str1);
                break;
            case 3:
                remove_word(dict, str1);
                break;
            case 4:
                search_synonyms(dict, str1);
                break;
            case 5:
                write_data(dict, "data");
                exit(0); // sai do programa com sucesso
            case 6:
                //system("clear");
                // print_dictionary(dict);
                for(int i = 0; i < 26; i++){
                    Word *current_word = dict->hash_table[i].dictionary;
                    int count_word = 0;
                    int count_synonym = 0;

                    while (current_word != NULL){
                        // if (strcmp(current_word->word, word) == 0) {
                        Synonym *current_synonym = current_word->synonyms;
                        printf("-%s-\n", current_word);
                        while (current_synonym != NULL) {
                            printf("%s-", current_synonym->word);
                            count_synonym++;
                            current_synonym = current_synonym->next_synonym;
                        }
                        printf("NULL\n");
                        count_word++;
                        current_word = current_word->next_word;
                    }
                    printf("Possui %d palavras e %d sinonimos\n\n\n", count_word, count_synonym);
                }
                break;
            case 7:
                hard_test(dict);
                // add_words_from_file(dict, "./archives_test/a.txt");

                for(int i = 0; i < 26; i++){
                    Word *current_word = dict->hash_table[i].dictionary;
                    int count_word = 0;
                    int count_synonym = 0;

                    while (current_word != NULL){
                        // if (strcmp(current_word->word, word) == 0) {
                        Synonym *current_synonym = current_word->synonyms;
                        printf("-%s-\n", current_word);
                        while (current_synonym != NULL) {
                            printf("%s-", current_synonym->word);
                            count_synonym++;
                            current_synonym = current_synonym->next_synonym;
                        }
                        printf("NULL\n");
                        count_word++;
                        current_word = current_word->next_word;
                    }
                    printf("Possui %d palavras e %d sinonimos\n\n\n", count_word, count_synonym);
                }
                break;
            default:
                break;
        }
    }
    return 0;
}