//#include <Python.h>
#include <stdio.h>
#include "wavHeader.h"
#include <string.h>

//method to split file into header.bin and content.bin
void splitWav(char *file){
    int bufferSize = 128*1024; //128kb
    FILE *fp = fopen(file, "rb");
    FILE *header = fopen("header.bin", "wb");
    FILE *content = fopen("content.bin", "wb");

    if(fp == 0){
        printf("could not open given wav file");
        return;
    }

    struct wav_header wavH;
    fread(&wavH, sizeof(struct wav_header), 1, fp);
    fwrite(&wavH, sizeof(struct wav_header), 1, header);
    fclose(header);

    char buffer[bufferSize];

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufferSize, fp)) > 0) {
        fwrite(buffer, 1, bytesRead, content);
    }


    fclose(fp);
    fclose(content);

}

//combine a header and contents of file to make new wav file
void combineFiles(char *fileName, char *header, char *content){
    int bufferSize = 128*1024; //128kb
    FILE *fp = fopen(fileName, "wb");
    FILE *head = fopen(header, "rb");
    FILE *cont = fopen(content, "rb");
    
    struct wav_header wavH;
    fread(&wavH, sizeof(struct wav_header), 1, head);
    fwrite(&wavH, sizeof(struct wav_header), 1, fp);
    fclose(head);

    char buffer[bufferSize];

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufferSize, cont)) > 0) {
        fwrite(buffer, 1, bytesRead, fp);
    }

    fclose(fp);
    fclose(cont);
}

int main(int argc, char *argv[]){
    if(argc!=3){
        printf("plz input right amount of args");
        return 1;
    }

//    splitWav(argv[1]);
    combineFiles(argv[2], "header.bin","content.bin");

    return 0;
}
