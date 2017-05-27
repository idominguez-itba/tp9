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

bool crear_puertoD(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * puerto[]);
//creo la cantidad de LEDS que hay en el puerto (necesito el display donde va aparecer el puerto)
//inicializa todos los leds APAGADOS
//devuelve un bool en que si es true, significa que se pudo crear el puertoD correctamente; caso contrario, fallo
//al crear el puertoD

bool cambiar_estado_leds (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * puerto [],dos_byte_t datos);
//se pasan como parametros el puerto y el estado de los leds en el puertoD
//(necesito como argumento el display donde va a cambiar el led)
//devuelve un bool en que si es true, significa que se pudo modificar todos los leds correctamente o false
//si no se pudo modificar correctamente los leds del puertoD

#endif /* MANEJO_LED_H */

