/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   manejo_estruct.h
 * Author: ignacio
 *
 * Created on 27 de mayo de 2017, 10:18
 */

#ifndef MANEJO_ESTRUCT_H
#define MANEJO_ESTRUCT_H

#define A	1
#define B	2
#define D	3

#define	ON	1
#define	OFF	0

#define FIN 0


#define PARPADEAR_PRENDIDOS 'b'
#define APAGAR_TODOS 'c'
#define PRENDER_TODOS 's'
#define VACIO '0'







typedef struct
{
	unsigned char puertoA;
	unsigned char puertoB;

} dos_byte_t;

typedef struct
{
	unsigned char bit	:4; // nro de bit
	unsigned char letra	:2; // puerto 
	unsigned char modo	:1; //lectura o escritura
	unsigned char unused	:1;

}info_t;


void actualizar_puerto (info_t *info_leds, dos_byte_t *puertoD, int led_tocado, int *funcion, int *contador_blinks);

char bitGet (uint16_t bit, dos_byte_t puertoD, char puertoN);

//Funcion bitGet:
//Recibe el nombre del puerto y te devuelve un char que puede ser 1 o 0, dependiendo del 
//estado del bit que se quiere obtener. Tambien se debe dar como argumento el 
//el puerto principal al cual pertence dicho puerto que se quiere obtener el bit.
//Devuelve 1 si el bit estaba en 1, y devuelve un 0 si el bit esta en 0

/////teclado

info_t analizo_cambio(int tecla, info_t info);
dos_byte_t dibujo_leds(info_t info, dos_byte_t puertoD);
info_t limpio_info();
void blink_leds(dos_byte_t puertoD, ALLEGRO_DISPLAY * display , ALLEGRO_BITMAP * led_apagado, ALLEGRO_BITMAP * led_prendido, ALLEGRO_BITMAP * fondo);




///////////
dos_byte_t maskSwitch(uint16_t mascara, dos_byte_t puertoD, info_t info);

// Funcion maskOff: recibe una mascara de dos bytes, una estructura de un puertoD y un char con el puerto con el que se va a trabajar.
// con esta informacion llama a maskSwitch cpn la info necesaria para que se apaguen todos los bits de la mascara. Devuelve como
// parametro la estructura modificada del puertoD.

dos_byte_t maskOff(uint16_t mascara, dos_byte_t puertoD, char puertoN);

// Funcion maskOff: recibe una mascara de dos bytes, una estructura de un puertoD y un char con el puerto con el que se va a trabajar.
// con esta informacion llama a maskSwitch cpn la info necesaria para que se prendan todos los bits de la mascara. Devuelve como
// parametro la estructura modificada del puertoD.

dos_byte_t maskOn(uint16_t mascara, dos_byte_t puertoD, char puertoN);

// Funcion bitClear: recibe int del 0 al 15, una estructura de un puertoD y un char con el puerto con el que se va a trabajar.
// con esta informacion llama a bitModif con la info necesaria para que se apague el bit seleccionado. Devuelve como
// parametro la estructura modificada del puertoD.

dos_byte_t bitClear (uint16_t bit, dos_byte_t puertoD, char puertoN);

// Funcion bitGet: recibe int del 0 al 15, una estructura de un puertoD y un char con el puerto con el que se va a trabajar.
// con esta informacion llama a bitModif con la info necesaria para que se prenda el bit seleccionado. Devuelve como
// parametro la estructura modificada del puertoD.

dos_byte_t bitSet (uint16_t bit, dos_byte_t puertoD, char puertoN);

// Funcion bitModif: recibe int del 0 al 15, una estructura de un puertoD, un char con el puerto con el que se va a trabajar
// y el modo en el que se quiere trabajar (set o clear). Con esta informacion crea una mascara acorde a lo pedido y llama a
// maskOff o maskOn dependiendo de la situacion.

dos_byte_t bitModif(uint16_t bit, dos_byte_t puertoD, char puertoN, char modo);

#endif /* MANEJO_ESTRUCT_H */

