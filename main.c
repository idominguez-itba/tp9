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




#warning primitivas no se usan (image_addon)


//////////
#define ALLEGRO_TO_DEC (9-(ALLEGRO_KEY_9 - tecla))

#define SET 0
#define CLEAR 1
#define NOT_VALID (((tecla > ALLEGRO_KEY_9)&&(tecla < ALLEGRO_KEY_0))&&(tecla != ALLEGRO_KEY_A)&&(tecla != ALLEGRO_KEY_B)&&(tecla != ALLEGRO_KEY_D)&&(tecla != ALLEGRO_KEY_S)&&(tecla != ALLEGRO_KEY_C))




/*
 * 
 */
int main(int argc, char** argv) {
    
    //ALLEGRO
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * maneja_evento = NULL;
    ALLEGRO_BITMAP * led_prendido = NULL;                                   //LEDS
    ALLEGRO_BITMAP * led_apagado = NULL;
    ALLEGRO_BITMAP * fondo = NULL;
    ALLEGRO_TIMER *timer = NULL;
    
    //booleans
    bool control = true;
    bool redibujar = false;
    bool salir = false;
    bool cambiar_fondo = false;
    
    bool caps_lock = false;
   
    //enteros
    int contador_bitmap;
    int led_tocado;
    int contador_blinks;
    int funcion;
    int tecla;
    
    
    unsigned char reinicio = 0;
    
    
    dos_byte_t puertoD = {0x00, 0x00};
    info_t info_leds;
    
    puertoD.puertoA = reinicio;
    
    puertoD.puertoB = reinicio;
    
    
   if(!al_init())  //instalo (si puedo) allegro         //ALLEGRO
   {
       printf( "Fallo al inicializar allegro\n");
       return -1;
   }
   
   if(!al_install_keyboard()) //instalo (si puedo) teclado      //TECLADO
   {
       printf("Fallo al inicializar teclado\n");
       return -1;
   }
    
   if (!al_install_mouse()) //instalo (si puedo) mouse      //MOUSE
   {
       printf("Fallo al inicializar mouse\n"); 
       return -1;
   }
    
    timer = al_create_timer(1.0 / FPS);
    if(!timer) 
    {
        printf("fallo al inicializar timer\n");
	return -1;
    }
    
   if(!al_init_image_addon())                       //IMAGE_ADDON
   {
       printf("Fallo al inicializar primitivas\n");
       al_destroy_timer(timer);
       return -1;
   }

    
   
   
   maneja_evento = al_create_event_queue();         //EVENT_QUEUE
                                                            
   if(!maneja_evento)  //verifico que se haya creado correctamente la EVENT_QUEUE
   {
       al_destroy_event_queue(maneja_evento);
       al_shutdown_primitives_addon();
       al_destroy_timer(timer);
       return -1;
        
   }
 
                                  //FONDO
   
   fondo = al_create_bitmap(ANCHO_DIS,ALTO_DIS);
   
   if(!fondo)
   {
       al_destroy_bitmap(fondo);
       al_destroy_event_queue(maneja_evento);
       al_shutdown_primitives_addon();
       al_destroy_timer(timer);
       
       return -1;
   }
   
   
   
   led_prendido = al_create_bitmap(ANCHO_LED,ALTO_LED);
   led_apagado = al_create_bitmap(ANCHO_LED,ALTO_LED);
   
   if(!led_apagado&&!led_prendido)
   {       
       al_destroy_event_queue(maneja_evento);
        
       al_destroy_bitmap(led_apagado);
       al_destroy_bitmap(led_prendido);
      
       al_destroy_bitmap(fondo);
       
       al_shutdown_primitives_addon();
       al_destroy_timer(timer);
       
       return -1;
       
       
   }
  
                                               //DISPLAY
   display = al_create_display(ANCHO_DIS,ALTO_DIS); //creo el display
   
   if (!display)    //verifico que se haya creado correctamente el display
   {
       printf("Fallo al inicializar display");
        
       al_destroy_bitmap(led_apagado);
       al_destroy_bitmap(led_prendido);  
       
       al_destroy_event_queue(maneja_evento);
   
       al_destroy_bitmap(fondo);
       
       al_shutdown_primitives_addon();
       al_destroy_timer(timer);
       
       return -1;
       
       
   }

   
   al_set_target_bitmap(fondo);
   al_clear_to_color(al_color_name(COLOR1));
   al_set_target_bitmap(al_get_backbuffer(display));
   
   al_register_event_source(maneja_evento, al_get_display_event_source(display));
   al_register_event_source(maneja_evento, al_get_timer_event_source(timer));
   al_register_event_source(maneja_evento, al_get_mouse_event_source());
   al_register_event_source(maneja_evento,al_get_keyboard_event_source());
   
   al_start_timer(timer);   //aquí arranca el timer
   
   while(!salir)                                        //hasta que se cierre la ventana
   {
        ALLEGRO_EVENT ev;
	if( al_get_next_event(maneja_evento, &ev) )     //levanto un evento
	{ 
            if(ev.type == ALLEGRO_EVENT_TIMER)
            {
                redibujar = true;
            }    
            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {    
                salir = true;
            }

            else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
            {
		led_tocado = identificar_led(ev.mouse.x, ev.mouse.y);   
                actualizar_puerto(&info_leds, &puertoD, led_tocado, &funcion, &contador_blinks);
                if (led_tocado == ERROR)
                {
                    cambiar_fondo = true;
                }
                
            }
          ///////////////TECLADO 
            else if(ev.type == ALLEGRO_EVENT_KEY_CHAR) //
            {
                tecla = ev.keyboard.keycode;
                if (tecla == ALLEGRO_KEY_TAB)
                {   
                     caps_lock = !caps_lock;
                }
                else if((ALLEGRO_KEY_B)&&(caps_lock)&&(info_leds.letra!=0))
                {
                       blink_leds(puertoD, display , led_apagado, led_prendido, fondo);
                }
                else if(NOT_VALID)
                {
                      info_leds = limpio_info();
                }
                else if((info_leds.letra !=0)&&((tecla == ALLEGRO_KEY_S)||(tecla == ALLEGRO_KEY_C)))
                {
                    if (tecla == ALLEGRO_KEY_S)
                    {
                        puertoD = maskOn(65535, puertoD, info_leds.letra);
                        cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo); 
                        al_flip_display();
                        info_leds = limpio_info();
                     }
                     else
                     {
                         puertoD = maskOff(65535, puertoD, info_leds.letra);
                         cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo); 
                         al_flip_display();
                         info_leds = limpio_info();
                      }
                 }
                 else
                 {
                     info_leds = analizo_cambio(tecla, info_leds);
                     if(info_leds.unused == 0)
                     {
                        puertoD = bitModif(info_leds.bit, puertoD, info_leds.letra, ON);
                        cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo); 
                        al_flip_display();
                        info_leds = limpio_info();
                      }
                      else if ((info_leds.unused == 1)&&(info_leds.letra == 0)) 
                                        info_leds = limpio_info();
                   }
                           
                 }////////////////////////////////   

			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Si se quiere cerrar el display
			{
                            salir = true;
                        }
		   
	}
 
	if(redibujar && al_is_event_queue_empty(maneja_evento)) 
	{
            redibujar = false;
            
          
            
            cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo);
            al_flip_display();
	}
	  
    }
   
   





   /////////////////////////////////////////////////////////////////
  /* cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo);

     
   al_flip_display();
   
 
   
   
   al_flip_display();
   
   //registro los eventos
  
   
  
   
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
   al_rest(2.5);*/
   
   
                                                                    //destruyo todo lo que cree 
     al_destroy_bitmap(led_apagado);
     al_destroy_bitmap(led_prendido);  
     al_destroy_event_queue(maneja_evento);
     al_destroy_bitmap(fondo);
     al_shutdown_primitives_addon();
     al_destroy_timer(timer);
     al_destroy_display(display);
         
    return (EXIT_SUCCESS);
}



////TECLADO

info_t analizo_cambio(int tecla, info_t info)
{
    static unsigned char bit = -1;
    
    if((tecla == ALLEGRO_KEY_A)||(tecla == ALLEGRO_KEY_B)||(tecla == ALLEGRO_KEY_D))
    {
        info.letra = (char) ((tecla == ALLEGRO_KEY_D)?(3):(tecla));
    }
    else if (((tecla >= ALLEGRO_KEY_0)&&(tecla <= ALLEGRO_KEY_9))&&(info.letra != 0))
    {
        if(bit == 255)
        {
            bit = (unsigned char) ALLEGRO_TO_DEC;
            if((info.letra == A )||(info.letra == B))
            {    
                info.bit = bit;
                info.unused = 0;
                if((info.letra == A)||(info.letra == B))
                {    
                    bit = 255;
                }
            }
        }   
        else if((bit == 1)||(bit == 0)&&(info.letra == D))
        {
            bit = bit*10 + (unsigned char) ALLEGRO_TO_DEC;
            info.bit = bit;
            bit = 255;
            info.unused = 0;
        }
        else info.unused = 1; 
    }
    else if(((tecla == ALLEGRO_KEY_C)||(tecla == ALLEGRO_KEY_S))&&(info.letra != 0)&&(bit == -1))
    {
        if(tecla == ALLEGRO_KEY_C)
        {
            info.modo = CLEAR;
            info.unused = 0;
        }
        else if(tecla == ALLEGRO_KEY_S)
        {
            info.modo = SET;
            info.unused = 0;
        }
    }
    else info.unused = 1;
    return info;
}

info_t limpio_info()
{
    static info_t info = {0,0,0,1};
    return info;
}

void blink_leds(dos_byte_t puertoD, ALLEGRO_DISPLAY * display , ALLEGRO_BITMAP * led_apagado, ALLEGRO_BITMAP * led_prendido, ALLEGRO_BITMAP * fondo)
{
    dos_byte_t puerto_aux={0,0};
    int cont;
    bool estado = true;
    dos_byte_t arr_puertos[]={puertoD,puerto_aux};
    for(cont = 0; cont<10; cont++)
    {
        cambiar_estado_leds(display, led_apagado, led_prendido, arr_puertos[estado], fondo); 
        al_flip_display();
        al_rest(1.0);
        estado = !estado;
    }
    
}
    

