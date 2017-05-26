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


#define CANT_LEDS   16

#define ANCHO_DIS   640
#define ALTO_DIS    480



/*
 * 
 */
int main(int argc, char** argv) {

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
   
   ALLEGRO_BITMAP arreglo_de_bitmaps[CANT_LEDS];    //creo un arreglo de LEDS
   
   int contador_bitmap;
   
   for (contador_bitmap = 0; contador_bitmap < CANT_LEDS; contador_bitmap++) //verifico que se hayan creado correctamente los LEDS
   {
     
       if (!arreglo_de_bitmaps[contador_bitmap])
       {
           int contador_error;
           
           for (contador_error = 0; contador_error <= contador_bitmap; contador_error++)
           {
               al_destroy_bitmap(arreglo_de_bitmaps[contador_error]);

           }
           
           al_destroy_event_queue(maneja_evento);
           
           return -1;
        }

   }
   
   ALLEGRO_DISPLAY * display = NULL;
   
   display = al_create_display(ANCHO_DIS,ALTO_DIS); //creo el display
   
   if (!display)    //verifico que se haya creado correctamente el display
   {
       printf("Fallo al inicializar display");
       
       al_destroy_event_queue(maneja_evento);
       
       for(contador_bitmap=0;contador_bitmap<CANT_LEDS;contador_bitmap++)
       {
           al_destroy_bitmap(arreglo_de_bitmaps[contador_bitmap]);
       }
       
       return -1;
       
       
   }

                                                                            //registro los eventos
   al_register_event_source(maneja_evento,al_get_keyboard_event_source());
   al_register_event_source(maneja_evento,al_get_mouse_event_source());
   al_register_event_source(maneja_evento,al_get_display_event_source(display));
   
  
   
   
   
   
   
   
   
   
   
   
   

   
   
   
   
   
    
    
    
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
    
    
    
    return (EXIT_SUCCESS);
}

