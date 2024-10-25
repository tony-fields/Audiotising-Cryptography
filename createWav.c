//proof of concept to create .wav file that just plays middle C

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct wav_header
{
  char riff[4];           // "RIFF"                                  
  int32_t flength;        // file length in bytes                    
  char wave[4];           // "WAVE"                                  
  char fmt[4];            // "fmt "                                  
  int32_t chunk_size;     // size of FMT chunk in bytes (usually 16) 
  int16_t format_tag;     // 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM 
  int16_t num_chans;      // 1=mono, 2=stereo                        
  int32_t srate;          // Sampling rate in samples per second     
  int32_t bytes_per_sec;  // bytes per second = srate*bytes_per_samp 
  int16_t bytes_per_samp; // 2=16-bit mono, 4=16-bit stereo          
  int16_t bits_per_samp;  // Number of bits per sample               
  char data[4];           // "data"                                  
  int32_t dlength;        // data length in bytes (filelength - 44)  
};

#define sample_rate 44100

void initMyWav(struct wav_header *wav){
    strncpy(wav->riff, "RIFF", 4);
    strncpy(wav->wave, "WAVE", 4);
    strncpy(wav->fmt, "fmt ", 4);
    strncpy(wav->data, "data", 4);

    wav->chunk_size = 16;
    wav->format_tag = 1;
    wav->num_chans = 1;
    wav->srate = sample_rate;
    wav->bits_per_samp = 16;

    wav->bytes_per_sec = wav->srate * wav->bits_per_samp / 8 * wav->num_chans;
    wav->bytes_per_samp = wav->bits_per_samp / 8 * wav->num_chans;
}


int main(){
    const int duration_seconds = 10;
    const int buffer_size = sample_rate * duration_seconds;
    short int buffer[buffer_size] = {};
    float MIDDLE_C = 256.00;
    int header_length = sizeof(struct wav_header);
    struct wav_header myWav;

    struct wav_header *myWavP = &myWav;

    initMyWav(myWavP);
    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = (short int)((cos((2 * M_PI * MIDDLE_C * i) / sample_rate) * 1000));
    }

    myWav.dlength = buffer_size * myWav.bytes_per_samp;
    myWav.flength = myWav.dlength + header_length;

    FILE *wavfp = fopen("test.wav", "w");
    fwrite(&myWav, 1, header_length,wavfp);
    fwrite(buffer, 2, buffer_size, wavfp);

    return 0;
}
