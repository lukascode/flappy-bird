#pragma once

#pragma once


#include <allegro5/allegro.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Resources {
public:
	ALLEGRO_BITMAP* getBitmap(std::string name);
	ALLEGRO_FONT* getFont(std::string name);
	ALLEGRO_SAMPLE* getSample(std::string name);
	~Resources();

	static Resources* getInstance();

	static void destroyResources();

private:
	Resources();
	std::unordered_map<std::string, ALLEGRO_BITMAP*> bitmapResources;
	std::unordered_map<std::string, ALLEGRO_FONT*> fontResources;
	std::unordered_map<std::string, ALLEGRO_SAMPLE*> sounds;

	static Resources* instance;
	
	void loadAllResources();

	bool loadBitmap(std::string key, std::string fileName);
	bool loadFont(std::string key, std::string fileName, int size);
	bool loadSample(std::string key, std::string fileName);

};