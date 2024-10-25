//print wav header of a command line argument wav file

#include <stdio.h>
#include "wavHeader.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Please have a valid argument type");
        return 1;
    }

    char *wavName = argv[1];
    FILE *wavFP = fopen(wavName, "rb");

    if (wavFP == 0) {
       perror("Error opening file");
       return 1;
   }

   
   struct wav_header wav;

   fread(&wav, sizeof(struct wav_header),1, wavFP);

   toPrint(&wav);
   fclose(wavFP);
   return 0;
}
