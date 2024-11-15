//program to copy a wav a file just as a proof of concept 
#include <stdio.h>
#include "wavHeader.h"
#include <string.h>

char *copyName = "-wav-copy.wav";
int bufferSize = 128*1024; //128kb

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Please have a valid argument type");
        return 1;
    }
    if(strlen(argv[1])<4){
        printf("please enter a valid .wav name");
        return 1;
    }
    FILE *fp = fopen(argv[1],"rb");

    if(fp == 0){
        printf("could not open given wav file");
        return 1;
    }

    struct wav_header wavH; 
    fread(&wavH, sizeof(struct wav_header), 1, fp);

    int sizeOfWavName = strlen(argv[1])+strlen(copyName);
    char fileCPname[sizeOfWavName+1];
    strcpy(fileCPname,argv[1]);
    strcpy(fileCPname+strlen(argv[1])-4,copyName);

    FILE *wavW = fopen(fileCPname, "wb");
    if(wavW == 0){
        printf("there was a problem duplicating your file");
        return 1;
    }

    //copy header from og wav to copy wav
    fwrite(&wavH, sizeof(struct wav_header), 1, wavW);

    char buffer[bufferSize];


    if(wavH.flength-wavH.dlength != 44){
        printf("meta data error, please check if meta data is correct");
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufferSize, fp)) > 0) {
        fwrite(buffer, 1, bytesRead, wavW);
    }
    /*
    int cpNum = (wavH.flength-44)/bufferSize;
    int cpRm = wavH.dlength%bufferSize;
    printf("cpRm: %d, dlength: %d, cpNUm: %d\n",cpRm, wavH.dlength, cpNum);
    for(int i=0; i<cpNum; i++){
        valOfRead = fread(buffer, bufferSize, 1, fp);
        if(valOfRead == 1){
            fwrite(buffer, bufferSize, 1, wavW);
        } else {
            printf("there has been an error copying data");
            return 1;
        }
    }
    if(wavH.dlength%bufferSize){
        fwrite(buffer, wavH.dlength%bufferSize, 1, wavW);
    }

*/

    fclose(fp);
    fclose(wavW);
    return 0;
}
