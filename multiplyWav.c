#include "wavHeader.h"
#include <stdio.h>


int main(int argc, char **argv){
    if(argc!=2){
        printf("usage: <file.wav>");
    }
    
    FILE *wav = fopen(argv[1], "rb");

    if(fp == 0){
        printf("could not open given wav file");
        return 1;
    }
    struct wav_header wavH; 
    fread(&wavH, sizeof(struct wav_header), 1, fp);

    char *copyName = "-multiply";
    int sizeOfWavName = strlen(argv[1])+strlen(copyName);
    char fileCPname[sizeOfWavName+1];
    strcpy(fileCPname,argv[1]);
    strcpy(fileCPname+strlen(argv[1])-4,copyName);

    FILE *wavW = fopen(fileCPname, "wb");
    if(wavW == 0){
        printf("there was a problem duplicating your file");
        return 1;
    }

    fwrite(&wavH, sizeof(struct wav_header), 1, wavW);

    int 
