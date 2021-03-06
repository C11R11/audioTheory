//from https://stackoverflow.com/questions/17217829/sending-sine-wave-values-from-array-to-audio-output
//for raspberry problem linking math library run add the lm to add the math library
//  gcc -Wall sin_wave_stackOverflow.cc -lasound -o wave2 -lm
//in order to make work iostream is needed to use g++

#include <iostream>
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>
#include <math.h>
#define BUFFER_LEN 22050

static char *device = "default";                       //soundcard
snd_output_t *output = NULL;
float buffer [BUFFER_LEN];


int main(void)
{
    int err;
    int j,k;

    float f, fs;

    std::cout << "Freq: "; // no flush needed
    std::cin >> f;

    std::cout << "Sampling rate:";
    std::cin >> fs;

    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;


    // ERROR HANDLING

    if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
            printf("Playback open error: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
    }

    if ((err = snd_pcm_set_params(handle,
                                  SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  1,
                                  BUFFER_LEN,
                                  1,
                                  500000)) < 0) {   
            printf("Playback open error: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);


    }

    // SINE WAVE
    printf("Sine tone at %dHz ",f);
    int typeWave = 1;

    int countBuf = 0;

        for (k=0; k<BUFFER_LEN; k++){

        if (typeWave == 0)
            buffer[k] = (sin(2*M_PI*f/fs*k));                 //sine wave value generation                        

        else
            if(countBuf < BUFFER_LEN/100)
	    {
	       buffer[k] = 1;
	    }
        else
        {
              buffer[k] = -1;
              countBuf = 0;
        }
            countBuf++;
            }       

        for (j=0; j<5; j++){
            frames = snd_pcm_writei(handle, buffer, BUFFER_LEN);    //sending values to sound driver
            }

    snd_pcm_close(handle);
    return 0;

}
