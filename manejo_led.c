/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <stdbool.h>
#include <allegro5/allegro_color.h>

#include "datos_generales.h"
#include "manejo_led.h"
#include "manejo_estruct.h"


#define SEPA_ENTRE_LEDS 10
#define SEPA_PUERTOS_AUX 50

//PROTOTIPOS//


float calc_posx_led (int nro_led, int tamano_puerto);

//calcula la posicion en x que tendria un led teniendo en cuenta que numero de led es.
//la posicion que se calcula es para que el led esté centrado con respecto al display

float calc_posy_led (int nro_puerto_aux, int tamano_puerto);
//calcula la posicion en y que tendria un puerto auxiliar (ejemplo puerto A)
//teniendo en cuenta que numero de puerto auxiliar es dentro del puerto "principal" (ejemplo puerto D).
//la posicion que se calcula es para que el puerto auxiliar esté centrado con respecto al display


//DEFINICION FUNCIONES//


int identificar_led (float coordenada_x, float coordenada_y)
{
    int i; //led
    int j; //puerto
    float led_x;
    float led_y;
    int led = ERROR;
    bool identificado = false;
    
    for (j = 0; (j < CANT_PUERTOS_AUX) && !identificado; j++)
    {
        led_y = calc_posy_led(j, CANT_PUERTOS_AUX);
        
        if ( (coordenada_y >= led_y) && (coordenada_y <= led_y + ALTO_LED))
        {
            for (i = 0; (i< CANT_LEDS_PUERTO) && !identificado; i++)
            {
                 led_x = calc_posx_led(i,CANT_LEDS_PUERTO);
            
                 if ( (coordenada_x >= led_x) && (coordenada_x <= (led_x + ANCHO_LED) ) )
                {
                     led = i + (j*CANT_LEDS_PUERTO);
                     identificado = true;        
                }
            
            }
        }
        
    }
    
    return led;
    
}

void cambiar_estado_leds (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * led_apagado, 
        ALLEGRO_BITMAP * led_prendido, dos_byte_t datos, ALLEGRO_BITMAP * fondo)
{
    char estado;
    
    int cont_puerto;
    int cont_leds;
     
    al_set_target_bitmap(led_prendido);
    al_clear_to_color(al_color_name(PRENDIDO));
    
    al_set_target_bitmap(led_apagado);
    al_clear_to_color(al_color_name(APAGADO));
    
    al_set_target_backbuffer(display);
    al_draw_bitmap(fondo,0,0,0);     
    
    for(cont_puerto=0;cont_puerto<CANT_PUERTOS_AUX;cont_puerto++)
    {
        for(cont_leds=0;cont_leds<CANT_LEDS_PUERTO;cont_leds++)
        {
            estado = bitGet(cont_puerto*CANT_LEDS_PUERTO+cont_leds,datos,D);
            float posx = calc_posx_led(cont_leds,CANT_LEDS_PUERTO);
            float posy = calc_posy_led(cont_puerto,CANT_PUERTOS_AUX);
                    
            if(estado == ON)
            {
                al_draw_bitmap(led_prendido,posx,posy,0);
            } else
            {
                al_draw_bitmap(led_apagado,posx,posy,0);
            }
                   
        }
    }
            
          
}
        

float calc_posx_led (int nro_led, int tamano_puerto)
{
     float posx = ANCHO_DIS/2.0;
     if(nro_led<tamano_puerto/2)
        {   
            int contador_aux =  tamano_puerto/2.0 - nro_led ;
            posx+= (contador_aux -0.5)*SEPA_ENTRE_LEDS +(contador_aux -1)*ANCHO_LED; 
           
        
        } 
     else
        {
            int contador_aux = nro_led - tamano_puerto/2.0;
            posx-= (0.5 +contador_aux)*SEPA_ENTRE_LEDS +(contador_aux+1)*ANCHO_LED;
            
        }
     
     return posx;

    
    
}

float calc_posy_led (int nro_puerto_aux, int tamano_puerto)
{
    
    float posy = ALTO_DIS/2.0;
        
    if(nro_puerto_aux<tamano_puerto/2)
    {
        int contador_aux =  tamano_puerto/2.0 - nro_puerto_aux ;
        posy+= (contador_aux - 0.5)*SEPA_PUERTOS_AUX +(contador_aux -1)*ALTO_LED;
    } else
    {
        int contador_aux = nro_puerto_aux - tamano_puerto/2;
        posy-= (contador_aux +0.5)*SEPA_PUERTOS_AUX +(contador_aux+1)*ALTO_LED;

    }
    
    return posy;
}

