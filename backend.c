/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//backend8.c
//Este módulo representa el BACKEND

#include <unistd.h>   /* sleep() */
#include "stdint.h"
#include "manejo_estruct.h"
#include "backend.h"



#define	ERROR	-1
#define OK	1



#define CANT_BITXCHAR 8

#define MASK_ALL_ON 0xffff   


#define N_BLINKS 4
#define TIME_BLINKS 1
#define PUERTO_NULO 0x00




// Funcion maskSwitch: recibe una mascara de dos bytes, una estructura de un puertoD, y una estructura con informacion necesaria.
// la mascara (en representacion binaria) determina en unos para los bits que se quieren modificar, y ceros los que no se desean
// cambiar. El puerto que recibe es el que va a modificar y es a su vez lo que delvuelve la funcion. En la estructura info se 
// debe especificar si se quieren prender o apagar esos bits (modo) y el puerto a modificar (letra).

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



// Funcion Blink: Función que recibe una estructura que representa 2 puertos, otra estructura que da informacion sobre
// sobre que puerto trabajar, y un puntero a un contador, que le indica al exterior cuantas veces restan por llamar
// a la funcion, para que cumpla su finalidad. El contador incializa en N_BLINKS.
// En el primer llamado a la funcion, se limpian los bits del puerto indicado,  y se devuelve la estructura dos_byte_t
// por la estructura info_t. En el segundo llamado se prenden los que estaban prendidos originalmente y 
// se devuelve nuevamente la estructura. En los siguientes llamados, se repite lo mismo, hasta que no se la llame más
// (el contador que se va restando en cada llamada a función llega a FIN).
// IMPORTANTE: En cada llamado, la estructura demora una cantidad de tiempo directamente proporcional a TIME_BLINKS.

dos_byte_t blink (dos_byte_t puertoD, info_t info, int *p_contador);



// Definicion de funciones:

dos_byte_t maskSwitch(uint16_t mascara, dos_byte_t puertoD, info_t info)
{
	if((info.letra == A)||(info.letra == B))	
	{	
		char a_comparar;	// donde se lee, modifica y escribe al puerto
		char mask_8bit = (char) mascara;	
		if(info.letra == A)
		{
			a_comparar = puertoD.puertoA;
			if(info.modo == ON)
			{
				a_comparar = ((a_comparar)|(mask_8bit));
				puertoD.puertoA = a_comparar;
			}
			else if (info.modo == OFF)
			{
				a_comparar = ((a_comparar)&(~mask_8bit));
				puertoD.puertoA = a_comparar;
			} 
			}
		else if(info.letra == B)
		{
			a_comparar = puertoD.puertoB;
			if(info.modo == ON)
			{
				a_comparar = ((a_comparar)|(mask_8bit));
				puertoD.puertoB = a_comparar;
			}
			else if (info.modo == OFF)
			{
				a_comparar = ((a_comparar)&(~mask_8bit));
				puertoD.puertoB = a_comparar;
			} 
		}	
	}
	else if(info.letra == D)
	{		
		uint16_t a_comparar = (uint16_t) puertoD.puertoA;
		a_comparar <<= CANT_BITXCHAR;	// shift necesario para que la mascara el puerto A quede en el MSB
		a_comparar += (uint16_t) puertoD.puertoB;		// agrego mascara del puerto B
		if(info.modo == ON)
		{
			a_comparar = ((a_comparar)|(mascara));
		}
		else if (info.modo == OFF)
		{
			a_comparar = ((a_comparar)&(~mascara));	
		}
		puertoD.puertoB = (char) a_comparar; // guardo LSB en puerto B
		a_comparar >>= CANT_BITXCHAR; // shifts para poder guardar en el puerto A
		puertoD.puertoA = (char) a_comparar; // guardo MSB en puerto A
	}
	return puertoD;
}

dos_byte_t maskOff(uint16_t mascara, dos_byte_t puertoD, char puertoN)
{
	info_t info ={0,puertoN,OFF};
	puertoD = maskSwitch(mascara, puertoD, info);
	return puertoD;
}

dos_byte_t maskOn(uint16_t mascara, dos_byte_t puertoD, char puertoN)
{
	info_t info ={0,puertoN,ON};
	puertoD = maskSwitch(mascara, puertoD, info);
	return puertoD; 
}


dos_byte_t bitModif(uint16_t bit, dos_byte_t puertoD, char puertoN, char modo)
{
	dos_byte_t resultado;

	if(!((bit>CANT_BITXCHAR-1)&&((puertoN==A)||(puertoN==B))))
	{
		uint16_t mascara = 1;
		uint16_t contador = 0;

		
		while (contador<bit)
		{
			mascara<<=1;
			contador++;
		}

		if(modo == ON)
		{
			resultado = maskOn(mascara, puertoD, puertoN);

		} else if(modo ==OFF)
		{
			resultado = maskOff(mascara, puertoD, puertoN);
		}


	} else
	{
	}

	return resultado;

}

dos_byte_t bitClear (uint16_t bit, dos_byte_t puertoD, char puertoN)
{

	return bitModif(bit, puertoD, puertoN, OFF);

}

dos_byte_t bitSet (uint16_t bit, dos_byte_t puertoD, char puertoN)
{

	return bitModif(bit, puertoD, puertoN, ON);

}

char bitGet (uint16_t bit, dos_byte_t puertoD, char puertoN)
{

	char resultado;

	dos_byte_t auxiliar;

	uint16_t mascara = 1;

	uint16_t contador = 0;

	while(contador<bit)
	{
		mascara<<=1;
		contador++;
	}

	if(puertoN == A)
	{
		mascara<<=CANT_BITXCHAR;
	}

	mascara = ~mascara;

	auxiliar = maskOff(mascara, puertoD, D);

	if ((auxiliar.puertoA==0)&&(auxiliar.puertoB==0))
	{
		resultado = OFF;
	} else
	{
		resultado = ON;
	}

	return resultado;

}

dos_byte_t blink (dos_byte_t puertoD, info_t info, int *p_contador)
{
	static int contador = N_BLINKS;

	static unsigned char puerto_aux_A = PUERTO_NULO;
	static unsigned char puerto_aux_B = PUERTO_NULO;

	

	if (info.letra == A)
	{
		if (puertoD.puertoA != PUERTO_NULO)
		{
			puerto_aux_A = puertoD.puertoA;
			puertoD.puertoA = PUERTO_NULO;
		}
		else
		{
			puertoD.puertoA = puerto_aux_A;    //lo seteo con el estado original.
		}
			
	}

	else if (info.letra == B)
	{
		if (puertoD.puertoB != PUERTO_NULO)
		{
			puerto_aux_B = puertoD.puertoB;
			puertoD.puertoB = PUERTO_NULO;
		}
		else
		{
			puertoD.puertoB = puerto_aux_B;    //lo seteo con el estado original.
		}
			
	}
	
	else if (info.letra == D)
	{
		if ((puertoD.puertoA != PUERTO_NULO) || ((puertoD.puertoB != PUERTO_NULO)))  //es decir, si D es no nulo
		{
			puerto_aux_A = puertoD.puertoA;
			puertoD.puertoA = PUERTO_NULO;
			
			puerto_aux_B = puertoD.puertoB;
			puertoD.puertoB = PUERTO_NULO;
		}
		else
		{
			puertoD.puertoA = puerto_aux_A;    //lo seteo con el estado original.
			puertoD.puertoB = puerto_aux_B;
		}
	}

	contador--;
	(*p_contador) = contador;

	if (contador == FIN)			//si no me van a volver a llamar, seteo todo como lo tenia originalmente
	{
		contador = N_BLINKS;
		puerto_aux_A = PUERTO_NULO;
		puerto_aux_B = PUERTO_NULO;
	}

	sleep(TIME_BLINKS);

	return puertoD;
		
}


void proceso(info_t *info, int *p_funcion, dos_byte_t *puertoD, int *contador)
{

	if ((*p_funcion) == VACIO)
	{
            
            switch (bitGet(info -> bit, (*puertoD), info -> letra))
            {
                case OFF: (*puertoD) = bitSet(info-> bit, (*puertoD), info-> letra); break;
                case ON: (*puertoD) = bitClear(info-> bit, (*puertoD), info-> letra); break;
            }
		
	}
	else
	{
		switch ((*p_funcion))
		{
			case APAGAR_TODOS : (*puertoD) = maskOff(MASK_ALL_ON, (*puertoD), (info)->letra); break;
			case PRENDER_TODOS : (*puertoD) = maskOn(MASK_ALL_ON, (*puertoD), (info)->letra); break;
			case PARPADEAR_PRENDIDOS : (*puertoD) = blink((*puertoD), (*info), contador); break;
		}
	}
}



void actualizar_puerto (info_t *info_leds, dos_byte_t *puertoD, int led_tocado, int *funcion, int *contador_blinks)
{
    if (led_tocado != ERROR)
    {
        
        
        (info_leds) -> letra = D;
        (info_leds) -> bit = led_tocado;
        (*funcion) = VACIO;
        
        proceso(info_leds, funcion, puertoD, contador_blinks);
        
     }
}
















