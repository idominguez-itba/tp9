/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manejo_led.h
 * Author: ignacio
 *
 * Created on 26 de mayo de 2017, 23:05
 */

#ifndef MANEJO_LED_H
#define MANEJO_LED_H

#include "manejo_estruct.h"


void cambiar_estado_leds (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * led_apagado, 
        ALLEGRO_BITMAP * led_prendido, dos_byte_t datos, ALLEGRO_BITMAP * fondo);
//se pasan como parametros el puerto y el estado de los leds en el puertoD
//(necesito como argumento el display donde va a cambiar el led)
//(ademas necesito como argumento los leds prendido y apagado que dibujar en caso
//de que el bit este prendido o apagado)


int identificar_led (float coordenada_x, float coordenada_y);
// recibe como parámetro dos coordenadas y 






#endif /* MANEJO_LED_H */

