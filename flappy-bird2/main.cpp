#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#include <iostream>

#include "Resources.h"
#include "Globals.h"
#include "Spider.h"
#include "MenuBackground.h"
#include "Logo.h"
#include "Text.h"
#include "Menu.h"
#include "Bird.h"
#include "Game.h"
#include "TubeUp.h"
#include "TubeDown.h"


int main() {

	srand(time(NULL));

	if (!al_init()) {
		std::cout << "Could not initialize allegro" << std::endl;
		return -1;
	}

	ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);

	if (!display) {
		std::cout << "Could not initialize display" << std::endl;
		return -1;
	}

	const int FPS = 60;
	bool done = false;
	bool redraw = true;
	float gameTime = 0.0;
	int frames = 0;
	int gameFPS = 0;
	GameState gameState = MENU;


	//INSTALL AND INIT
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	
	

	Resources* res = Resources::getInstance();

	Menu menu;
	Game game;
	
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = timer = al_create_timer(1.0 / FPS);

	//REGISTER
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//al_hide_mouse_cursor(display); // hide cursor

	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (gameState == MENU) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE: done = true; break;
				case ALLEGRO_KEY_UP: menu.up(); break;
				case ALLEGRO_KEY_DOWN: menu.down(); break;
				case ALLEGRO_KEY_ENTER: 
					ActionMenu action = menu.action();
					switch (action) {
					case QUIT: done = true; break;
					case NEWGAME: 
						gameState = GAME; 
						game.init();
						break;
					}
				break;
				}
			}
			else if (gameState == GAME) {
				game.handleEvent(&ev);
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE: gameState = MENU;
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER && al_event_queue_is_empty(event_queue)) {
			redraw = true;
			//update fps
			frames++;
			if (al_current_time() - gameTime >= 1) {
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//update objects
			game.update();
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {

			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (gameState == MENU) {
				menu.draw();
			}
			else if (gameState == GAME) {
				game.render();
			}
			al_flip_display();
		}


	}

	Resources::destroyResources();

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	
	return 0;
}