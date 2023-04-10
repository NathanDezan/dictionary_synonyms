#include "operations.h"

/*Função para adicionar uma palavra e um sinonimo para a palavra*/
void add_word(Dictionary *dict, char *str1, char *str2){
    int hashValue = search_position(str1);
    Word *temp_word = malloc(sizeof(Word));
    Word *current_word = dict->hash_table[hashValue].dictionary;

    Synonym *temp_synonym = malloc(sizeof(Synonym));
    strcpy(temp_synonym->word, str2);
    temp_synonym->next_synonym = NULL;

    strcpy(temp_word->word, str1);
    temp_word->next_word = NULL;

    if (current_word == NULL) {
        temp_word->synonyms = temp_synonym;
        dict->hash_table[hashValue].dictionary = temp_word;
    } else {
        Word *prev_word = NULL;
        while (current_word != NULL && strcmp(current_word->word, str1) < 0) {
            prev_word = current_word;
            current_word = current_word->next_word;
        }
        if (current_word == NULL || strcmp(current_word->word, str1) > 0) {
            temp_word->synonyms = temp_synonym;
            temp_word->next_word = current_word;
            if (prev_word == NULL) {
                dict->hash_table[hashValue].dictionary = temp_word;
            } else {
                prev_word->next_word = temp_word;
            }
        } else {
            Synonym *current_synonym = current_word->synonyms;
            Synonym *prev_synonym = NULL;
            while (current_synonym != NULL && strcmp(current_synonym->word, str2) < 0) {
                prev_synonym = current_synonym;
                current_synonym = current_synonym->next_synonym;
            }
            if (current_synonym == NULL || strcmp(current_synonym->word, str2) > 0) {
                if (prev_synonym == NULL) {
                    temp_synonym->next_synonym = current_word->synonyms;
                    current_word->synonyms = temp_synonym;
                } else {
                    temp_synonym->next_synonym = current_synonym;
                    prev_synonym->next_synonym = temp_synonym;
                }
            }
        }
    }
}

/*Função que realiza a busca da palavra e imprime os sinonimos associados a ela*/
void search_synonyms(Dictionary *dict, char *word){
    int hashValue = search_position(word);
    Word *current_word = dict->hash_table[hashValue].dictionary;
    while (current_word != NULL) {
        if (strcmp(current_word->word, word) == 0) {
            Synonym *current_synonym = current_word->synonyms;
            // printf("%s", word);
            while (current_synonym != NULL) {
                printf("%s\n", current_synonym->word);
                current_synonym = current_synonym->next_synonym;
            }
            printf("\n");
            return;
        }
        current_word = current_word->next_word;
    }
    printf("hein?\n");
}

/*Função que realiza a remoção */
void remove_word(Dictionary *dict, char *word){
    int hashValue = search_position(word);
    Word *current_word = dict->hash_table[hashValue].dictionary;
    Word *previous_word = NULL;

    while (current_word != NULL) {
        if (strcmp(current_word->word, word) == 0) {
            if (previous_word == NULL) { // Primeira palavra da lista
                dict->hash_table[hashValue].dictionary = current_word->next_word;
            } else { // Palavra no meio ou final da lista
                previous_word->next_word = current_word->next_word;
            }

            // Remove os sinônimos da palavra
            Synonym *current_synonym = current_word->synonyms;
            while (current_synonym != NULL) {
                Synonym *temp = current_synonym;
                current_synonym = current_synonym->next_synonym;
                free(temp);
            }

            // Remove a palavra
            free(current_word);
            return;
        }
        previous_word = current_word;
        current_word = current_word->next_word;
    }
}

// void remove_two_words(Dictionary *dict, char *str1, char *str2){
//     int hashValue1 = search_position(dict, str1);
//     int hashValue2 = search_position(dict, str2);
//     Word *current_word1 = dict->hash_table[hashValue1].dictionary;
//     Word *previous_word1 = NULL;
//     Word *current_word2 = dict->hash_table[hashValue2].dictionary;
//     Word *previous_word2 = NULL;

//     // Localiza as duas palavras
//     while (current_word1 != NULL || current_word2 != NULL) {
//         if (current_word1 != NULL && strcmp(current_word1->word, str1) == 0) {
//             break;
//         }
//         previous_word1 = current_word1;
//         current_word1 = current_word1->next_word;
//         if (current_word2 != NULL && strcmp(current_word2->word, str2) == 0) {
//             break;
//         }
//         previous_word2 = current_word2;
//         current_word2 = current_word2->next_word;
//     }

//     // Verifica se as palavras foram encontradas
//     if (current_word1 == NULL || current_word2 == NULL) {
//         printf("Erro: uma ou ambas as palavras nao foram encontradas!\n");
//         return;
//     }

//     // Remove o sinonimo da primeira palavra
//     Synonym *current_synonym1 = current_word1->synonyms;
//     Synonym *previous_synonym1 = NULL;
//     while (current_synonym1 != NULL) {
//         if (strcmp(current_synonym1->word, str2) == 0) {
//             if (previous_synonym1 == NULL) { // Primeiro sinonimo da lista
//                 current_word1->synonyms = current_synonym1->next_synonym;
//             } else { // Sinonimo no meio ou final da lista
//                 previous_synonym1->next_synonym = current_synonym1->next_synonym;
//             }
//             free(current_synonym1);
//             break;
//         }
//         previous_synonym1 = current_synonym1;
//         current_synonym1 = current_synonym1->next_synonym;
//     }

//     // Remove o sinonimo da segunda palavra
//     Synonym *current_synonym2 = current_word2->synonyms;
//     Synonym *previous_synonym2 = NULL;
//     while (current_synonym2 != NULL) {
//         if (strcmp(current_synonym2->word, str1) == 0) {
//             if (previous_synonym2 == NULL) { // Primeiro sinonimo da lista
//                 current_word2->synonyms = current_synonym2->next_synonym;
//             } else { // Sinonimo no meio ou final da lista
//                 previous_synonym2->next_synonym = current_synonym2->next_synonym;
//             }
//             free(current_synonym2);
//             break;
//         }
//         previous_synonym2 = current_synonym2;
//         current_synonym2 = current_synonym2->next_synonym;
//     }

//     // Verifica se a primeira palavra ainda tem sinonimos
//     if (current_word1->synonyms == NULL) {
//         // Remove a palavra
//         if (previous_word1 == NULL) { // Primeira palavra da lista
//             dict->hash_table[hashValue1].dictionary = current_word1->next_word;
//         }else{ // Palavra no meio ou final da lista
//           previous_word1->next_word = current_word1->next_word;
//       }
//       free(current_word1);
//       printf("Palavra removida");

//       // Verifica se a segunda palavra ainda tem sinonimos
//       if (current_word2->synonyms == NULL) {
//           // Remove a palavra
//           if (previous_word2 == NULL) { // Primeira palavra da lista
//               dict->hash_table[hashValue2].dictionary = current_word2->next_word;
//           } else { // Palavra no meio ou final da lista
//               previous_word2->next_word = current_word2->next_word;
//           }
//           free(current_word2);
//           printf("Palavra %s removida com sucesso!\n", str2);
//       }