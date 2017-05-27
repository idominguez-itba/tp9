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
#define ANCHO_LED  25
#define ALTO_LED    50


#define SEPA_ENTRE_LEDS 10
#define SEPA_PUERTOS_AUX 50

//PROTOTIPOS//


bool crear_led (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *led,float ancho, float alto, float posx, float posy);
//se crea un LED APAGADO
//devuelve un bool en que si es true, significa que se pudo crear el led correctamente; caso contrario, fallo
//al crear el led
//(necesito como argumento el display donde va a ser creado el led)


float calc_posx_led (int nro_led, int tamano_puerto);

//calcula la posicion en x que tendria un led teniendo en cuenta que numero de led es.
//la posicion que se calcula es para que el led esté centrado con respecto al display

float calc_posy_led (int nro_puerto_aux, int tamano_puerto);
//calcula la posicion en y que tendria un puerto auxiliar (ejemplo puerto A)
//teniendo en cuenta que numero de puerto auxiliar es dentro del puerto "principal" (ejemplo puerto D).
//la posicion que se calcula es para que el puerto auxiliar esté centrado con respecto al display


//DEFINICION FUNCIONES//

bool crear_puertoD(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * puerto[])
{
    bool control = true;
    
    int cont_puertos;
    int cont_leds;
    
    for (cont_puertos=0;cont_puertos<CANT_PUERTOS_AUX;cont_puertos++) 
    //dibujo el puerto total en el display
    //en el caso mas basico en el que haya dos puertos (CANT_PUERTO_AUX=2),
    // cuando cont_puertos = 0, creo en el display la cantidad de leds 
    //correspondiente (CANT_LEDS_PUERTO) del puerto B y cuando sea
    //cont_puertos = 1 idem lo anterior pero del puerto A.
    //Las consideraciones que se toman para ver si el puerto que estoy creando
    //en pantalla es menor a la mitad de la cantidad total es para centrar
    //al puerto total en el centro del display.
    {
        float posy = calc_posy_led (cont_puertos, CANT_PUERTOS_AUX);
        
        for(cont_leds = 0; cont_leds < CANT_LEDS_PUERTO; cont_leds++) //creo en pantalla al puerto B
        {
        //dibujo un puerto auxiliar (ejemplo el puerto A) en el display
        //en el caso mas basico en el que haya dos Leds en el puerto (CANT_LEDS_PUERTO=2),
        //creo la cantidad de leds que me determina el define CANT_LEDS_PUERTO
        //las consideraciones que se realizan es para que el puerto que se esta creando
        //este centrado en el ancho del display
        
            float posx = calc_posx_led (cont_leds, CANT_LEDS_PUERTO);


            control = crear_led(display,puerto[cont_leds+cont_puertos*CANT_LEDS_PUERTO],
                    ANCHO_LED,ALTO_LED,posx,posy);
            
            if (control == false)
            {
                cont_leds = CANT_LEDS_PUERTO;
                cont_puertos = CANT_PUERTOS_AUX; 
            }
        }

    }
    
    return control;
}







bool cambiar_estado_led (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP * puerto [], int nro_puerto,
        int nro_led, bool estado)
{
           
    ALLEGRO_BITMAP * led = puerto[nro_puerto*CANT_LEDS_PUERTO + nro_led];
    
    bool control = true;
    
    float posx = calc_posx_led(nro_led,CANT_LEDS_PUERTO);
    float posy = calc_posy_led(nro_puerto,CANT_PUERTOS_AUX);
    
    
    led = al_create_bitmap(ANCHO_LED,ALTO_LED);
    
    if(!led)
    {
        control = false;
        
    } else
    {
        al_set_target_bitmap(led);
   
        if(estado==true)
        {
           al_clear_to_color(al_color_name(PRENDIDO));
        } else
        {
           al_clear_to_color(al_color_name(APAGADO));
        }
    
    
        al_set_target_backbuffer(display);
        al_draw_bitmap(led,posx,posy,0);
        al_flip_display();
     
        
    }
    
    return control;
    
}   
bool crear_led(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *led, float ancho, float alto, float posx, float posy)
{
    
    bool control = true;
    
    led = al_create_bitmap(ancho,alto);
    
    if(!led)
    {
       control = false;
       
    } else
    {
        al_set_target_bitmap(led);
        al_clear_to_color(al_color_name(APAGADO));
        al_set_target_backbuffer(display);
        al_draw_bitmap(led,posx,posy,0);
        
        
    }
    
    return control;
    
}


float calc_posx_led (int nro_led, int tamano_puerto)
{
     float posx = ANCHO_DIS/2.0;
     if(nro_led<tamano_puerto/2)
        {
            posx-= ((tamano_puerto/2.0) -0.5 -nro_led)*SEPA_ENTRE_LEDS +(tamano_puerto/2.0 -nro_led)*ANCHO_LED; 
        
        } else
        {
            int contador_aux = nro_led - tamano_puerto/2.0;
            posx+= ((tamano_puerto/2.0) +0.5 +contador_aux)*SEPA_ENTRE_LEDS +contador_aux*ANCHO_LED;
            
        }
     
     return posx;

    
    
}

float calc_posy_led (int nro_puerto_aux, int tamano_puerto)
{
    
    float posy = ALTO_DIS/2.0;
        
    if(nro_puerto_aux<tamano_puerto/2)
    {
        posy-= ((tamano_puerto/2.0) -0.5 -nro_puerto_aux)*SEPA_PUERTOS_AUX +(tamano_puerto/2.0 -nro_puerto_aux)*ALTO_LED;
    } else
    {
        int contador_aux = nro_puerto_aux - tamano_puerto/2;
        posy+= ((tamano_puerto/2.0) +0.5 +contador_aux)*SEPA_PUERTOS_AUX +contador_aux*ALTO_LED;

    }
    
    return posy;
}