/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ignacio
 *
 * Created on 26 de mayo de 2017, 18:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/events.h>
#include <allegro5/alcompat.h>
#include <allegro5/system.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/allegro_color.h>
#include <stdbool.h>

#include "datos_generales.h"
#include "manejo_led.h"
#include "manejo_estruct.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    
    bool control = true;
    
    dos_byte_t puertoD;
    
    unsigned char reinicio = 0;
    
    puertoD.puertoA = reinicio;
    
    puertoD.puertoB = reinicio;
    
    
   if(!al_init())  //instalo (si puedo) allegro
   {
       printf( "Fallo al inicializar allegro");
       return -1;
   }
   
   if(!al_install_keyboard()) //instalo (si puedo) teclado
   {
       printf("Fallo al inicializar teclado");
       return -1;
   }
    
   if (!al_install_mouse()) //instalo (si puedo) mouse
   {
       printf("Fallo al inicializar mouse"); 
       return -1;
   }
    
   if(!al_init_image_addon())
   {
       printf("Fallo al inicializar imagen ADDON");
       return -1;
   }

    
   ALLEGRO_EVENT_QUEUE * maneja_evento = NULL;
   
   maneja_evento = al_create_event_queue();
    
   if(!maneja_evento)  //verifico que se haya creado correctamente la EVENT_QUEUE
   {
       al_destroy_event_queue(maneja_evento);
       return -1;
        
   }
   
   ALLEGRO_BITMAP * ledsA[CANT_LEDS_PUERTO];    //creo puerto A
   ALLEGRO_BITMAP * ledsB[CANT_LEDS_PUERTO];  //creo puerto B
   
   ALLEGRO_BITMAP * ledsD[CANT_LEDS_D];
   
   
   
   int contador_bitmap;
   
   //hago que el puertoD este conformado por el puertoA y el puertoB
   for(contador_bitmap=0;contador_bitmap<CANT_LEDS_D;contador_bitmap++) 
   {
       if(contador_bitmap<CANT_LEDS_PUERTO)
       {
           ledsD[contador_bitmap]=ledsB[contador_bitmap];
       
       } else
       {
           ledsD[contador_bitmap]=ledsA[contador_bitmap-CANT_LEDS_PUERTO];
      
       }
       
       
   }
   
   
   ALLEGRO_DISPLAY * display = NULL;
   display = al_create_display(ANCHO_DIS,ALTO_DIS); //creo el display
   
   if (!display)    //verifico que se haya creado correctamente el display
   {
       printf("Fallo al inicializar display");
       
       al_destroy_event_queue(maneja_evento);
       
       al_destroy_display(display);
       
       return -1;
       
       
   }


   control = crear_puertoD(display, ledsD);
   al_flip_display();
   
   if(control==false)
   {
       
   
        for (contador_bitmap = 0; contador_bitmap < CANT_LEDS_D; contador_bitmap++) //verifico que se hayan creado correctamente los LEDS
        {
            al_destroy_bitmap(ledsD[contador_bitmap]);
                
        }
        
        al_destroy_event_queue(maneja_evento);
        al_destroy_display(display);
        
        return -1;
    }
   
   
   
   al_flip_display();
   
   //registro los eventos
   al_register_event_source(maneja_evento,al_get_keyboard_event_source());
   al_register_event_source(maneja_evento,al_get_mouse_event_source());
   al_register_event_source(maneja_evento,al_get_display_event_source(display));
   
   
   al_rest(5.0);
   
   puertoD.puertoA=0x00;
   puertoD.puertoB=0x01;
   cambiar_estado_leds(display, ledsD, puertoD);
   al_flip_display();
   al_rest(5.0);
   
   puertoD.puertoA = 0x10;
   puertoD.puertoB = 0x0A;
   cambiar_estado_leds(display, ledsD, puertoD);
   al_flip_display();
   al_rest(5.0);
   
   puertoD.puertoA = 0x0B;
   puertoD.puertoB = 0xF2;
   cambiar_estado_leds(display, ledsD ,puertoD);
   al_flip_display();
   al_rest(5.0);
   
   
  //destruyo todo lo que cree
   al_destroy_event_queue(maneja_evento);
   
   for(contador_bitmap=0;contador_bitmap<CANT_LEDS_D;contador_bitmap++)
   {
       al_destroy_bitmap(ledsD[contador_bitmap]);
   }
   al_destroy_display(display);
   
   
   
   
   
   
   
   
   

   
   
   
   
   
    
    
    
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
    
    
    
    return (EXIT_SUCCESS);
}

