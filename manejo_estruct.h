

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


//Funcion actualizar_puerto:
//recibe el led apuntado, si es ERROR no hace nada. Si no es ERROR analiza el bit del puertoD indicado por el led apuntado
// y lo cambia de estado. (en uno si estaba en cero y en cero si estaba en uno).
//Para esto además es necesario pasarle por parámetro un puntero a la estructura info_t, otro a la estructura dos_byte_t
// y otros dos punteros a enteros. Estos últimos no necesariamente deben estar inicializados con algún valor en especial.

void actualizar_puerto (info_t *info_leds, dos_byte_t *puertoD, int led_tocado, int *funcion, int *contador_blinks);


//Funcion bitGet:
//Recibe el nombre del puerto y te devuelve un char que puede ser 1 o 0, dependiendo del 
//estado del bit que se quiere obtener. Tambien se debe dar como argumento el 
//el puerto principal al cual pertence dicho puerto que se quiere obtener el bit.
//Devuelve 1 si el bit estaba en 1, y devuelve un 0 si el bit esta en 0
char bitGet (uint16_t bit, dos_byte_t puertoD, char puertoN);







//Funcion proceso: esta funcion recibe un puntero a una estructura info_t, un puntero a entero que representa una funcion,
// un puntero a la estructura dos_byte_t, y un puntero a un contador (entero). Esta funcion, segun los parámetros pasados
// en la estructura info_t y la funcion representada por el entero apuntado, modifica la estructura dos_byte_t.
// Si el puntero apunta a VACIO, entonces se tendra en cuenta el campo "bit" de la estructura info_t. 
// En caso contrario, no se tendra en cuenta este campo.
// Luego, no devuelve nada.

void proceso(info_t *info, int *p_funcion, dos_byte_t *puertoD, int *contador);



#endif /* MANEJO_ESTRUCT_H */

