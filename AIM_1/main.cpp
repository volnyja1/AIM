#include <stdio.h>
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

using namespace std;
 
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int BOUNCER_SIZE = 32;
const int BOUNCER_W = 512;
const int BOUNCER_H = 384;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_NEGATIVE, KEY_ORIGINAL
};

void negative(ALLEGRO_BITMAP *image, ALLEGRO_DISPLAY *display){
	al_set_target_bitmap(image);
	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READWRITE);
	for(int i=0;i<BOUNCER_W;++i)
	   for(int j=0;j<BOUNCER_H;++j){
		   ALLEGRO_COLOR col = al_get_pixel(image,i,j);
		   float a = 1.0-col.r;
		   col.r = a;
		   col.g = a;
		   col.b = a;
		   al_put_pixel(i,j,col);//al_map_rgb(255,0,255));
	   }
	al_unlock_bitmap(image);
	al_set_target_backbuffer(display);
}

void threshold(ALLEGRO_BITMAP *image, float thr, ALLEGRO_DISPLAY *display){
	al_set_target_bitmap(image);
	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READWRITE);
	for(int i=0;i<BOUNCER_W;++i)
	   for(int j=0;j<BOUNCER_H;++j){
		   ALLEGRO_COLOR col = al_get_pixel(image,i,j);
		   float a = col.r>thr?1.0:0.0;
		   col.r = a;
		   col.g = a;
		   col.b = a;
		   al_put_pixel(i,j,col);
	   }
	al_unlock_bitmap(image);
	al_set_target_backbuffer(display);
}

void gamma(ALLEGRO_BITMAP *image, float gamma, ALLEGRO_DISPLAY *display){
	al_set_target_bitmap(image);
	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READWRITE);
	for(int i=0;i<BOUNCER_W;++i)
	   for(int j=0;j<BOUNCER_H;++j){
		   ALLEGRO_COLOR col = al_get_pixel(image,i,j);
		   float a = pow(col.r,gamma);
		   col.r = a;
		   col.g = a;
		   col.b = a;
		   al_put_pixel(i,j,col);
	   }
	al_unlock_bitmap(image);
	al_set_target_backbuffer(display);
}

void quantization(ALLEGRO_BITMAP *image, float q, ALLEGRO_DISPLAY *display){
	al_set_target_bitmap(image);
	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READWRITE);
	for(int i=0;i<BOUNCER_W;++i)
	   for(int j=0;j<BOUNCER_H;++j){
		   ALLEGRO_COLOR col = al_get_pixel(image,i,j);
		   float a = (floor(col.r*q))/q;
		   col.r = a;
		   col.g = a;
		   col.b = a;
		   al_put_pixel(i,j,col);
	   }
	al_unlock_bitmap(image);
	al_set_target_backbuffer(display);
}

void nonLinear(ALLEGRO_BITMAP *image, float alpha, ALLEGRO_DISPLAY *display){
	al_set_target_bitmap(image);
	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READWRITE);
	for(int i=0;i<BOUNCER_W;++i)
	   for(int j=0;j<BOUNCER_H;++j){
		   ALLEGRO_COLOR col = al_get_pixel(image,i,j);
		   float gamma = 1/(1-alpha);
		   float a = col.r<0.5?0.5*pow(2*col.r,gamma):1-0.5*pow(2-2*col.r,gamma);
		   col.r = a;
		   col.g = a;
		   col.b = a;
		   al_put_pixel(i,j,col);
	   }
	al_unlock_bitmap(image);
	al_set_target_backbuffer(display);
}

void logarithmicScale(ALLEGRO_BITMAP *image, float s, ALLEGRO_DISPLAY *display){
	al_set_target_bitmap(image);
	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READWRITE);
	for(int i=0;i<BOUNCER_W;++i)
	   for(int j=0;j<BOUNCER_H;++j){
		   ALLEGRO_COLOR col = al_get_pixel(image,i,j);
		   float a = log(1+col.r*s)/log(1+s);
		   col.r = a;
		   col.g = a;
		   col.b = a;
		   al_put_pixel(i,j,col);
	   }
	al_unlock_bitmap(image);
	al_set_target_backbuffer(display);
}

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_W / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_H / 2.0;
   bool key[10] = { false, false, false, false, false, false, false, false, false, false };
   bool redraw = true;
   bool doexit = false;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

   if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }

   if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   //bouncer = al_load_bitmap("apple_tree.tga");
   bouncer = al_load_bitmap("data/data.png");
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_register_event_source(event_queue, al_get_mouse_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_UP] && bouncer_y >= 4.0) {
            bouncer_y -= 4.0;
         }
 
		 if(key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_H - 4.0) {
            bouncer_y += 4.0;
         }
 
         if(key[KEY_LEFT] && bouncer_x >= 4.0) {
            bouncer_x -= 4.0;
         }
 
		 if(key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_W - 4.0) {
            bouncer_x += 4.0;
         }

		 if(key[KEY_ORIGINAL]) {
			 cout << "reload" << endl;
			 bouncer = al_load_bitmap("data/apple_tree.tga");
			 key[KEY_ORIGINAL] = false;
         }

		 if(key[KEY_NEGATIVE]) {
			 cout << "negative" << endl;
			 negative(bouncer, display);
			 key[KEY_NEGATIVE] = false;
         }
 
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
 
            case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
 
            case ALLEGRO_KEY_LEFT: 
				key[KEY_LEFT] = true;
				break;
 
            case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_PAD_0:
				key[KEY_ORIGINAL] = true;
                break;

			case ALLEGRO_KEY_0:
				key[KEY_ORIGINAL] = true;
                break;

			case ALLEGRO_KEY_PAD_1:
				key[KEY_NEGATIVE] = true;
                break;

			case ALLEGRO_KEY_1:
				key[KEY_NEGATIVE] = true;
                break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;
 
            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;
 
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;
 
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;
 
			case ALLEGRO_KEY_PAD_0:
				key[KEY_ORIGINAL] = false;
                break;

			case ALLEGRO_KEY_0:
				key[KEY_ORIGINAL] = false;
                break;

			case ALLEGRO_KEY_PAD_1:
				key[KEY_NEGATIVE] = false;
                break;

			case ALLEGRO_KEY_1:
				key[KEY_NEGATIVE] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
         }
	  } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		  int x = 0;
		  int y = 0;
		  al_get_mouse_cursor_position(&x, &y);
		  cout << "mouse down: " << x << ", " << y << endl;
	  } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		  int x = 0;
		  int y = 0;
		  al_get_mouse_cursor_position(&x, &y);
		  cout << "mouse up: " << x << ", " << y << endl;
	  }
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));

         al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
 
         al_flip_display();
      }
   }
 
   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}