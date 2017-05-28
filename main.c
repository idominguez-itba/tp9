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
   
    int contador_bitmap;
    
    dos_byte_t puertoD;
    
    unsigned char reinicio = 0;
    
    puertoD.puertoA = reinicio;
    
    puertoD.puertoB = reinicio;
    
    
   if(!al_init())  //instalo (si puedo) allegro         //ALLEGRO
   {
       printf( "Fallo al inicializar allegro");
       return -1;
   }
   
   if(!al_install_keyboard()) //instalo (si puedo) teclado      //TECLADO
   {
       printf("Fallo al inicializar teclado");
       return -1;
   }
    
   if (!al_install_mouse()) //instalo (si puedo) mouse      //MOUSE
   {
       printf("Fallo al inicializar mouse"); 
       return -1;
   }
    
   if(!al_init_image_addon())                       //IMAGE_ADDON
   {
       printf("Fallo al inicializar imagen ADDON");
       return -1;
   }

    
   ALLEGRO_EVENT_QUEUE * maneja_evento = NULL;
   
   maneja_evento = al_create_event_queue();         //EVENT_QUEUE
                                                            
   if(!maneja_evento)  //verifico que se haya creado correctamente la EVENT_QUEUE
   {
       al_destroy_event_queue(maneja_evento);
       return -1;
        
   }
 
   ALLEGRO_BITMAP * fondo = NULL;                                  //FONDO
   
   fondo = al_create_bitmap(ANCHO_DIS,ALTO_DIS);
   
   if(!fondo)
   {
       al_destroy_bitmap(fondo);
       al_destroy_event_queue(maneja_evento);
       
       return -1;
   }
   
   ALLEGRO_BITMAP * led_prendido;                                   //LEDS
   ALLEGRO_BITMAP * led_apagado;
   
   led_prendido = al_create_bitmap(ANCHO_LED,ALTO_LED);
   led_apagado = al_create_bitmap(ANCHO_LED,ALTO_LED);
   
   if(!led_apagado&&!led_prendido)
   {       
       al_destroy_event_queue(maneja_evento);
        
       al_destroy_bitmap(led_apagado);
       al_destroy_bitmap(led_prendido);
      
       al_destroy_bitmap(fondo);
       
       return -1;
       
       
   }
  
   ALLEGRO_DISPLAY * display = NULL;                                            //DISPLAY
   display = al_create_display(ANCHO_DIS,ALTO_DIS); //creo el display
   
   if (!display)    //verifico que se haya creado correctamente el display
   {
       printf("Fallo al inicializar display");
        
       al_destroy_bitmap(led_apagado);
       al_destroy_bitmap(led_prendido);  
       
       al_destroy_event_queue(maneja_evento);
       
       al_destroy_display(display);
       
       al_destroy_bitmap(fondo);
       
       return -1;
       
       
   }

   
   al_set_target_bitmap(fondo);
   al_clear_to_color(al_color_name("blue"));
   al_set_target_bitmap(al_get_backbuffer(display));
   
   
   cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo);

     
   al_flip_display();
   
 
   
   
   al_flip_display();
   
   //registro los eventos
   al_register_event_source(maneja_evento,al_get_keyboard_event_source());
   al_register_event_source(maneja_evento,al_get_mouse_event_source());
   al_register_event_source(maneja_evento,al_get_display_event_source(display));
   
  
   
   al_rest(2.5);
   
   puertoD.puertoA=0x00;
   puertoD.puertoB=0x01;
   
   
   al_set_target_bitmap(fondo);
   al_clear_to_color(al_color_name("yellow"));
   al_set_target_bitmap(al_get_backbuffer(display));
   
   
   cambiar_estado_leds(display, led_apagado, led_prendido,  puertoD, fondo);
   al_flip_display();
   al_rest(2.5);
   
   
   
   al_set_target_bitmap(fondo);
   al_clear_to_color(al_color_name("white"));
   al_set_target_bitmap(al_get_backbuffer(display));
  
   cambiar_estado_leds(display, led_apagado, led_prendido,  puertoD, fondo);
   al_flip_display();
   al_rest(2.5); 
   
   puertoD.puertoA = 0x10;
   puertoD.puertoB = 0x0A;
   
   
   al_set_target_bitmap(fondo);
   al_clear_to_color(al_color_name("purple"));
   al_set_target_bitmap(al_get_backbuffer(display));
   
   cambiar_estado_leds(display, led_apagado,led_prendido, puertoD, fondo);
   al_flip_display();
   al_rest(2.5);
   
   puertoD.puertoA = 0x0B;
   puertoD.puertoB = 0xF2;
   
   
   al_set_target_bitmap(fondo);
   al_clear_to_color(al_color_name("brown"));
   al_set_target_bitmap(al_get_backbuffer(display));
   
   cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo);
   al_flip_display();
   al_rest(2.5);
   
   
                                                                    //destruyo todo lo que cree
   
   
    al_destroy_bitmap(led_apagado);
    al_destroy_bitmap(led_prendido);  
       
    al_destroy_event_queue(maneja_evento);
    
    al_destroy_display(display);
       
    al_destroy_bitmap(fondo);
   
   
   
   
   
   

   
   
   
   
   
    
    
    
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
    
    
    
    return (EXIT_SUCCESS);
}

