#pragma once

#include "Object.h"
#include "Globals.h"
#include "Resources.h"

class Spider : public Object {
public:
	void init() {
		Resources* res = Resources::getInstance();
		bitmap = res->getBitmap("spider");
		scaleFactorX = scaleFactorY = 0.5;
		rotDegree = 15;
		
		Object::init();

		x = WIDTH / 2 - width / 2;
		y = HEIGHT / 2 - height / 2;
		
	}

	void render() {
		int width = al_get_bitmap_width(bitmap);
		int height = al_get_bitmap_height(bitmap);
		//2 i 3 parametr to punkt na bitmapie, 3 i 5 to szerokosc i wys kawalka
		//do wyciecia, 1 i 2 par po kolorze to punkt na wycietym kawalku,
		//3 i 4 to pozycja na ekranie wzg tamtego pnktu, 5 i 6 skalowanie,
		//7 rotacja
		al_draw_tinted_scaled_rotated_bitmap_region(bitmap, 50, 50, 50, 50,
			al_map_rgb(255, 255, 255), 0, 0, 0, 0, 2, 2, (15*3.14*0)/180, 0);
	}

};

