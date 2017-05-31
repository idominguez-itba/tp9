/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   datos_generales.h
 * Author: ignacio
 *
 * Created on 26 de mayo de 2017, 20:28
 */

#ifndef DATOS_GENERALES_H
#define DATOS_GENERALES_H


#include <stdio.h>
#include <stdlib.h>
#include <allegro5/events.h>
#include <allegro5/alcompat.h>
#include <allegro5/system.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>

#include <stdbool.h>

#define ANCHO_DIS   640
#define ALTO_DIS    480

#define ANCHO_LED  60
#define ALTO_LED    60

#define SEPA_ENTRE_LEDS 10
#define SEPA_PUERTOS_AUX 50

#define CANT_PUERTOS_AUX 2
#define CANT_LEDS_PUERTO 8
#define CANT_LEDS_D 2*CANT_LEDS_PUERTO



#define CANT_AUDIOS 3


#define FPS 60.0

#define ERROR -1   //debe ser un numero negativo


#endif /* DATOS_GENERALES_H */

