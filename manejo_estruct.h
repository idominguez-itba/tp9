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




char bitGet (uint16_t bit, dos_byte_t puertoD, char puertoN);

//Funcion bitGet:
//Recibe el nombre del puerto y te devuelve un char que puede ser 1 o 0, dependiendo del 
//estado del bit que se quiere obtener. Tambien se debe dar como argumento el 
//el puerto principal al cual pertence dicho puerto que se quiere obtener el bit.
//Devuelve 1 si el bit estaba en 1, y devuelve un 0 si el bit esta en 0




#endif /* MANEJO_ESTRUCT_H */

