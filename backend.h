/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   backend.h
 * Author: ignacio
 *
 * Created on 27 de mayo de 2017, 10:23
 */

#ifndef BACKEND_H
#define BACKEND_H

#include "stdint.h"


//Funcion proceso: esta funcion recibe un puntero a una estructura info_t, un puntero a entero que representa una funcion,
// un puntero a la estructura dos_byte_t, y un puntero a un contador (entero). Esta funcion, segun los parámetros pasados
// en la estructura info_t y la funcion representada por el entero apuntado, modifica la estructura dos_byte_t.
// Si el puntero apunta a VACIO, entonces se tendra en cuenta el campo "bit" de la estructura info_t. 
// En caso contrario, no se tendra en cuenta este campo.
// Luego, no devuelve nada.

void proceso(info_t *info, int *p_funcion, dos_byte_t *puertoD, int *contador);






#endif /* BACKEND_H */

