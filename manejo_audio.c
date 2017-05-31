/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "manejo_audio.h"

#define VEL_NORMAL 1.0
#define VOL_NORMAL 1.0
#define CENTRADO 0.0



ALLEGRO_SAMPLE_ID * reproducir_aud_fondo (ALLEGRO_SAMPLE *audio)
{
    ALLEGRO_SAMPLE_ID * auxiliar = NULL;
    al_play_sample(audio,VOL_NORMAL,CENTRADO,VEL_NORMAL,ALLEGRO_PLAYMODE_LOOP,auxiliar);
    
    return auxiliar;
}



void reproducir_audio (ALLEGRO_SAMPLE *audio)
{
    al_play_sample(audio,VOL_NORMAL,CENTRADO,VEL_NORMAL,ALLEGRO_PLAYMODE_ONCE,NULL);
    
}