# include "testing.h"

/*Função para leitura dos arquivos do diretório ./archives_test*/
/*Está função apenas coleta o nome dos arquivos no diretório e passa como parametro para a função add_words_from_file*/
void hard_test(Dictionary *dict){
    struct dirent *dir;
    char dir_name[] = "./archives_test/";
    char temp_string[100] = "";

    DIR *d;
    d = opendir(dir_name);

    if(d){
        while((dir = readdir(d)) != NULL){
            if((strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))){
                strcat(temp_string, dir_name);
                strcat(temp_string, dir->d_name);
                add_words_from_file(dict, temp_string);
                strcpy(temp_string, "");
            }
        }
        closedir(d);
    }
}

/*Função para realizar a leitura do arquivo.txt e fazer a inserção das palavras*/
/*Está função só é utilizada para realização de testes*/
void add_words_from_file(Dictionary *dict, char *filename){
    FILE *fp;
    char line[256];

    fp = fopen(filename, "r");
    if(fp == NULL){
        return;
    }

    while(fgets(line, sizeof(line), fp)){
        char *str1 = strtok(line, " ");
        char *str2 = strtok(NULL, " \n");
        add_word(dict, str1, str2);
        add_word(dict, str2, str1);
    }
    fclose(fp);
}