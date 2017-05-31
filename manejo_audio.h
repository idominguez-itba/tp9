/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manejo_audio.h
 * Author: matias
 *
 * Created on May 31, 2017, 2:51 PM
 */

#ifndef MANEJO_AUDIO_H
#define MANEJO_AUDIO_H

#include <allegro5/system.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//Reproducir_aud_fondo: le pasas un puntero del audio que se va a reproducir indefinidamente durante todo
//el programa y devuelve un puntero que identifica a la cancion para que al final de programa se detenga
//el audio. la funcion comienza con la reproduccion del audio

ALLEGRO_SAMPLE_ID * reproducir_aud_fondo (ALLEGRO_SAMPLE *audio);

//reproducir_audio: le pasas un puntero del audio que se va a reproducir una sola vez, y reproduce el mismo
void reproducir_audio (ALLEGRO_SAMPLE *audio);

#endif /* MANEJO_AUDIO_H */


