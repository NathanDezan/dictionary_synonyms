#include "file.h"
#define MAX_LINE_LENGTH 46000

/*Função para escrita dos dados da estrutura em um arquivo chamado "data"*/
void write_data(Dictionary *dict, char *filename){
    FILE *fp;
    Word *word;
    Synonym *synonym;

    fp = fopen(filename, "w");
    if(fp == NULL){
        exit(1);
    }

    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        word = dict->hash_table[i].dictionary;

        while(word != NULL){
            fprintf(fp, "%s: ", word->word);
            synonym = word->synonyms;

            while(synonym != NULL){
                fprintf(fp, "%s", synonym->word);

                if(synonym->next_synonym != NULL){
                    fprintf(fp, ", ");
                }
                synonym = synonym->next_synonym;
            }
            fprintf(fp, "\n");
            word = word->next_word;
        }
    }
    fclose(fp);
}

/*Função para carregamento da estrutura de dados do arquivo "data" para dentro da estrutura da aplicação*/
void load_data(Dictionary *dict, char *filename){
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char *word;
    char *synonym;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return;
    }

    while(fgets(line, MAX_LINE_LENGTH, fp) != NULL){
        word = strtok(line, ":");
        synonym = strtok(NULL, ",");

        while(synonym != NULL){
            add_word(dict, strtrim(word), strtrim(synonym));
            synonym = strtok(NULL, ",");
        }
    }
    fclose(fp);
}