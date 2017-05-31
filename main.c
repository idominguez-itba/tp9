




#include "datos_generales.h"
#include "manejo_led.h"
#include "manejo_audio.h"








#define SET 0
#define CLEAR 1




/*
 * 
 */
int main(int argc, char** argv) {
    
    //ALLEGRO
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * maneja_evento = NULL;
    ALLEGRO_BITMAP * led_prendido = NULL;                                   
    ALLEGRO_BITMAP * led_apagado = NULL;
    ALLEGRO_BITMAP * fondo = NULL;
    ALLEGRO_BITMAP * fondo1 = NULL;
    ALLEGRO_BITMAP * auxiliar = NULL;
    ALLEGRO_SAMPLE *aud_fondo = NULL;
    ALLEGRO_SAMPLE_ID *id_aud_fondo = NULL;
    ALLEGRO_SAMPLE *aud_r2d2 = NULL;
    ALLEGRO_SAMPLE *aud_sable = NULL;
    ALLEGRO_TIMER *timer = NULL;
    
    //booleans
    bool control = true;
    bool redibujar = false;
    bool salir = false;
    bool cambiar_fondo = false;
    bool cambiar_led = false;
    
    
    bool caps_lock = false;     //para el teclado
   
    //enteros
    int contador_bitmap;    //para el cambio de fondo
    int led_tocado = 0;     //para el mouse. (lo inicializo distinto de ERROR, sabiendo que ERROR es un entero negativo)
    int contador_blinks = 0;    //para la funcion blink ingresada por teclado
    
    int funcion;        //para las funciones ingresadas por teclado
    int tecla;  //para el teclado
    
    int flag_dibujo = 0;   //para seguir dibujando cuando hay blinks
    
    
    
    
    
    
    
    
    
    dos_byte_t puertoD = {0x00, 0x00};  //comienzan todos los leds apagados
    info_t info_leds = {00,A,00, 00}; //puerto A por defecto
    
    
    
    
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
    
   if(!al_install_audio())
   {
       printf("Fallo al instalar audio\n");
       return -1;
   }
    
   if(!al_init_acodec_addon())
   {
       printf("Fallo al inicializar Acodec\n");
       return -1;
   }
    
   if(!al_reserve_samples(CANT_AUDIOS))
   {
       printf("Fallo al reservar los samples de audio\n");
       return -1;
   }
    
   if(!al_init_image_addon())                       //IMAGE_ADDON
   {
       printf("Fallo al inicializar primitivas\n");
       al_destroy_timer(timer);
       return -1;
   }
    
    aud_fondo = al_load_sample("marcha.wav");
  
    
   if(!(aud_fondo))
   {
        al_destroy_sample(aud_fondo);
        al_destroy_timer(timer);
       
        
        printf("Fallo al cargar los audios\n");
        return -1;
    }
  
   aud_r2d2 = al_load_sample("r2d2.wav");
   
   if(!(aud_r2d2))
   {
      al_destroy_sample(aud_fondo);
      al_destroy_sample(aud_r2d2);
      al_destroy_timer(timer);
      
      printf("Fallo al cargar los audios\n");
      return -1;
   }
   
   aud_sable = al_load_sample("sable.wav");
   
   
   if(!(aud_sable))
   {
      al_destroy_sample(aud_fondo);
      al_destroy_sample(aud_r2d2);
      al_destroy_sample(aud_sable);
      al_destroy_timer(timer);
       
      printf("Fallo al cargar los audios\n");
      return -1;
       
   }

    
   
   
   maneja_evento = al_create_event_queue();         //EVENT_QUEUE
                                                            
   if(!maneja_evento)  //verifico que se haya creado correctamente la EVENT_QUEUE
   {
       al_destroy_event_queue(maneja_evento);
       al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       al_destroy_timer(timer);
       return -1;
        
   }
 
  fondo = al_load_bitmap("halcon.jpg");
   
   if(!fondo)
   {
       
       al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       
       al_destroy_bitmap(fondo);
       al_destroy_event_queue(maneja_evento);
       
       al_destroy_timer(timer);
       
       return -1;
   }
   
   fondo1 = al_load_bitmap("estrella.jpg");
   
   if(!fondo1)
   {
       al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       
       al_destroy_bitmap(fondo);
       al_destroy_bitmap(fondo1);
       
       al_destroy_event_queue(maneja_evento);
       
       al_destroy_timer(timer);
       return -1;
   }
   
   
   auxiliar = fondo;
   
   if(!auxiliar)
   {
      al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       
       al_destroy_bitmap(fondo);
       al_destroy_bitmap(fondo1);
       al_destroy_bitmap(auxiliar);
       al_destroy_event_queue(maneja_evento);
       
       al_destroy_timer(timer);
       return -1;  
   }
   
   led_apagado = al_load_bitmap("storm.png");
   
   if(!led_apagado)
   {   
       al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       al_destroy_bitmap(auxiliar);
       al_destroy_bitmap(fondo1);
       al_destroy_event_queue(maneja_evento);
        
       al_destroy_bitmap(led_apagado);
       
      
       al_destroy_bitmap(fondo);
       
       
       al_destroy_timer(timer);
       
       printf("falla");
       
       return -1;
       
       
   }
   
   led_prendido = al_load_bitmap("chubi.png");
   
   
   if(!led_prendido)
   {
          
       al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       
       al_destroy_bitmap(fondo1);
       al_destroy_event_queue(maneja_evento);
       al_destroy_bitmap(auxiliar); 
       al_destroy_bitmap(led_apagado);
       al_destroy_bitmap(led_prendido);
      
       al_destroy_bitmap(fondo);
       
       
       al_destroy_timer(timer);
       
       
       
       return -1;
       
       
   
   }
   
                                               //DISPLAY
   display = al_create_display(ANCHO_DIS,ALTO_DIS); //creo el display
   
   if (!display)    //verifico que se haya creado correctamente el display
   {
       printf("Fallo al inicializar display");
       al_destroy_bitmap(fondo1);
       al_destroy_sample(aud_fondo);
       al_destroy_sample(aud_r2d2);
       al_destroy_sample(aud_sable);
       
       al_destroy_bitmap(auxiliar);
       al_destroy_bitmap(led_apagado);
       al_destroy_bitmap(led_prendido);  
       
       al_destroy_event_queue(maneja_evento);
   
       al_destroy_bitmap(fondo);
       
       al_destroy_timer(timer);
       
       
       
       return -1;
       
       
   }

   
   
   
   al_register_event_source(maneja_evento, al_get_display_event_source(display));
   al_register_event_source(maneja_evento, al_get_timer_event_source(timer));
   al_register_event_source(maneja_evento, al_get_mouse_event_source());
   al_register_event_source(maneja_evento,al_get_keyboard_event_source());
   
   al_start_timer(timer);   //aquí arranca el timer
   
    id_aud_fondo = reproducir_aud_fondo(aud_fondo);
   
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
                
                if(led_tocado != ERROR)
                {
                    cambiar_led = true;
                } else
                {
                    auxiliar = fondo;
                    fondo = fondo1;
                    fondo1 = auxiliar;
                    
                }
                
               
                
            }
          ///////////////TECLADO 
            else if(ev.type == ALLEGRO_EVENT_KEY_CHAR) //
            {
                tecla = ev.keyboard.keycode;
                
                
                    cambiar_led = manejo_teclado_led(tecla, &info_leds, &funcion, &puertoD, &contador_blinks);
                
                    
                     
                    
                    
                
                
                
                
                
            }
            
                
                  

            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Si se quiere cerrar el display
            {
                 salir = true;
            }
		   
	}
 
	if(redibujar && al_is_event_queue_empty(maneja_evento)) 
	{
            flag_dibujo = 0;
            
            redibujar = false;
            
          
             while (flag_dibujo == 0)
            {
               cambiar_estado_leds(display, led_apagado, led_prendido, puertoD, fondo);
               al_flip_display(); 
               
               if(cambiar_led == true)
               {
                   reproducir_audio(aud_r2d2);
                   cambiar_led = false;
               }
               
               if (contador_blinks > 0) //esto significa que el blink esta activado
               {
                   proceso(&info_leds, &funcion, &puertoD, &contador_blinks); //actualizo estructuras
                   
                   reproducir_audio(aud_sable);
                   
               }
               else
               {
                   flag_dibujo = 1;           ////ALGO ASI ES LA IDEA PERO NO FUNCIONA
               }
            }

            
	}
	  
    }
                                                //detengo la musica de fondo
   
     al_stop_sample(id_aud_fondo);
     
   
   
   
   
   
  
    
                                                                    //destruyo todo lo que cree 
     al_destroy_bitmap(led_apagado);
     al_destroy_bitmap(led_prendido);  
     al_destroy_event_queue(maneja_evento);
     al_destroy_bitmap(fondo);
     al_destroy_bitmap(fondo1);
     al_destroy_bitmap(auxiliar);
     al_destroy_timer(timer);
     al_destroy_display(display);
     
     al_destroy_sample(aud_fondo);
     al_destroy_sample(aud_r2d2);
     al_destroy_sample(aud_sable);
     
     al_uninstall_audio();
     al_uninstall_keyboard();
     al_uninstall_mouse();
       
    return (EXIT_SUCCESS);
}
