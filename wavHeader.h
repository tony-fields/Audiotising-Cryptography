//header file that contains wav header and functions related

#ifndef _wavHeader_H_
#define _wavHeader_H_

#include <string.h>
#include <inttypes.h>
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

#define sample_rate441 44100
#define sample_rateHiRes 88200


void initMyWav(struct wav_header *wav){
    strncpy(wav->riff, "RIFF", 4);
    strncpy(wav->wave, "WAVE", 4);
    strncpy(wav->fmt, "fmt ", 4);
    strncpy(wav->data, "data", 4);

    wav->chunk_size = 16;
    wav->format_tag = 1;
    wav->num_chans = 1;
    wav->srate = sample_rate441;
    wav->bits_per_samp = 16;

    wav->bytes_per_sec = wav->srate * wav->bits_per_samp / 8 * wav->num_chans;
    wav->bytes_per_samp = wav->bits_per_samp / 8 * wav->num_chans;
}

//initalize 8 out of 13 common wav standards
//still need to init bytes_per_sec, bytes_per_sample, srate, dlength, flength
void initMostWav(struct wav_header *wav){
    strncpy(wav->riff, "RIFF", 4);
    strncpy(wav->wave, "WAVE", 4);
    strncpy(wav->fmt, "fmt ", 4);
    strncpy(wav->data, "data", 4);
    
    wav->chunk_size = 16;
    wav->format_tag = 1;
    wav->num_chans = 2;
    wav->bits_per_samp = 16;
}

//init bytes_per_sec, bytes_per_sample, srate, dlength, flength
void initRestWav(struct wav_header *wav, int duration_sec, int sample_rate){
    int buffer_size = wav->srate * duration_sec;
    int header_length = sizeof(struct wav_header);
    
    wav->dlength = buffer_size * wav->bytes_per_samp;
    wav->flength = wav->dlength + header_length;

    wav->srate = sample_rate;

    wav->bytes_per_sec = wav->srate * wav->bits_per_samp / 8 * wav->num_chans;
    wav->bytes_per_samp = wav->bits_per_samp / 8 * wav->num_chans;
}

void copyWav(struct wav_header *destination, const struct wav_header *source){
    strncpy(destination->riff,source->riff,4);
    destination->flength = source->flength;
    strncpy(destination->wave,source->wave,4);
    strncpy(destination->fmt,source->fmt,4);
    destination->chunk_size = source->chunk_size;
    destination->format_tag = source->format_tag;
    destination->num_chans = source->num_chans;
    destination->srate = source->srate;
    destination->bytes_per_sec = source->bytes_per_sec;
    destination->bytes_per_samp = source->bytes_per_samp;
    strncpy(destination->data,source->data,4);
    destination->dlength = source->dlength;
    destination->bits_per_samp = source->bits_per_samp;
}
void toPrint(struct wav_header *wav){
    printf("riff: %.*s ", 4, wav->riff);
    printf("flength: %" PRId32 " ", wav->flength); 
    printf("wave: %.*s ",4, wav->wave);
    printf("fmt: %.*s ",4, wav->fmt);
    printf("chunk size: %" PRId32 " ", wav->chunk_size);
    printf("format tag: %" PRId16 " ", wav->format_tag);
    printf("num chans: %" PRId16 " ", wav->num_chans);
    printf("srate: %" PRId32 " ", wav->srate);
    printf("bytes per sec: %" PRId32 " ", wav->bytes_per_sec);
    printf("bytes per samp: %" PRId16 " ", wav->bytes_per_samp);
    printf("bits per samp: %" PRId16 " ", wav->bits_per_samp);
    printf("data: %.*s ", 4, wav->data);
    printf("dlength: %" PRId32 "\n", wav->dlength);
}



#endif
