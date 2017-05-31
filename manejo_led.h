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
// recibe como parámetro dos coordenadas (x e y) y se fija si se encuentran en el interior
//de los bitmaps inicializados en el output (display). Si no se identifica ninguno, se devuelve ERROR
//En caso de identificarse algun bitmap, se devuelve el numero de orden.
//Los bitmaps estan ordenados de 0 a ((CANT_LEDS_PUERTO * CANT_PUERTOS_AUX) -1) arrancando el 0 en el
//lado inferior derecho. Ejemplo: (si hubiera 15 bitmaps)
// bmap_15  bmap_14 bmap_13 bmap_12 bmap_11 bmap_10 bmap_9  bmap_8
// bmap_7  bmap_6 bmap_5 bmap_4 bmap_3 bmap_2 bmap_1  bmap_0




bool manejo_teclado_led(int tecla, info_t *info_leds, int *p_funcion, dos_byte_t *puertoD, int *contador);
//recibe como parámetro una tecla que representa un ALLEGRO_KEY, un puntero a la estructura info_t, otro a la estructura dos_byte_t
//otro a un entero que representa una rutina (o funcion) a realizar, y otro a un entero que representa un contador
//(visualizado desde el exterior).
//si la tecla representa un dato válido (KEYs válidas: entre 0 y 9, TAB, A, B, D, S, C, B), 
//entonces actualiza la estructura de info_t y dependiendo de el caso, tambien actualiza la estructura dos_byte_t.
//devuelve un bool que es true si se actualizo la estructura dos_byte_t o un false si no se actualizo.










#endif /* MANEJO_LED_H */

