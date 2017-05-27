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

bool crear_puertoD(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * puerto[]);
//creo la cantidad de LEDS que hay en el puerto (necesito el display donde va aparecer el puerto)
//inicializa todos los leds APAGADOS
//devuelve un bool en que si es true, significa que se pudo crear el puertoD correctamente; caso contrario, fallo
//al crear el puertoD

bool cambiar_estado_led (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * puerto [], int nro_puerto,
        int nro_led, bool estado);
//se pasan como parametros el puerto, el tamaño del puerto, el puerto al cual se quiere cambiar el estado y
//el estado al cual se lo quiere cambiar al led mismo.
//(necesito como argumento el display donde va a cambiar el led)
//devuelve un bool en que si es true, significa que se pudo modificar el led correctamente; caso contrario, fallo
//al modificar el led

#endif /* MANEJO_LED_H */

