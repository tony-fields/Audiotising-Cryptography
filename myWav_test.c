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






int main(int argc, char *argv[]){
    if(argc!=3){
        printf("plz input right amount of args");
        return 1;
    }

    splitWav(argv[1]);

    return 0;
}
