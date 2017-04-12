#include "Resources.h"

Resources* Resources::instance = NULL;

Resources* Resources::getInstance() {
	if (instance == NULL) instance = new Resources();
	return instance;
}

Resources::Resources() { 
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	loadAllResources();
}

Resources::~Resources() {
	//delete all resources
	for (auto it = bitmapResources.begin(); it != bitmapResources.end(); ++it) {
		if (it->second) {
			al_destroy_bitmap(it->second);
		}
	}
	bitmapResources.clear();

	for (auto it = fontResources.begin(); it != fontResources.end(); ++it) {
		if (it->second) {
			al_destroy_font(it->second);
		}
	}
	fontResources.clear();

	for (auto it = sounds.begin(); it != sounds.end(); ++it) {
		al_destroy_sample(it->second);
	}
	sounds.clear();
}

ALLEGRO_BITMAP* Resources::getBitmap(std::string name) {
	std::unordered_map<std::string, ALLEGRO_BITMAP*>::const_iterator bitmap = bitmapResources.find(name);
	if (bitmap == bitmapResources.end()) return NULL;
	return bitmap->second;
}

ALLEGRO_FONT* Resources::getFont(std::string name) {
	std::unordered_map<std::string, ALLEGRO_FONT*>::const_iterator font = fontResources.find(name);
	if (font == fontResources.end()) return NULL;
	return font->second;
}

ALLEGRO_SAMPLE* Resources::getSample(std::string name) {
	std::unordered_map<std::string, ALLEGRO_SAMPLE*>::const_iterator sample = sounds.find(name);
	if (sample == sounds.end()) return NULL;
	return sample->second;
}

void Resources::destroyResources() {
	if (instance != NULL) {
		delete instance;
	}
}

void Resources::loadAllResources() {

	//bitmaps
	loadBitmap("spider", "spider_icon.jpg");
	loadBitmap("menu_background", "menu_background.jpg");
	loadBitmap("logo", "logo.png");
	loadBitmap("birdf1", "frame-1.png");
	loadBitmap("birdf2", "frame-2.png");
	loadBitmap("tubeUp", "tubeUp.png");
	loadBitmap("tubeDown", "tubeDown.png");
	loadBitmap("gameover", "gameover.png");

	//fonts
	loadFont("oswald-bold25", "Oswald-Bold.ttf", 25);
	loadFont("pacifico18", "Pacifico.ttf", 18);
	loadFont("lato-regular16", "Lato-Regular.ttf", 16);

	//samples
	al_reserve_samples(10);
	loadSample("jump", "jump.wav");
	loadSample("point", "point.wav");

}

bool Resources::loadBitmap(std::string key, std::string fileName) {
	ALLEGRO_BITMAP* bitmap = al_load_bitmap(fileName.c_str());
	if (bitmap != NULL) {
		bitmapResources.insert(std::make_pair(key, bitmap));
		return true;
	}
	else {
		std::cout << "Could not load bitmap. key: " << key << ", fileName: " << fileName << std::endl;
		return false;
	}
}

bool Resources::loadFont(std::string key, std::string fileName, int size) {
	ALLEGRO_FONT* font = al_load_font(fileName.c_str(), size, 0);
	if (font != NULL) {
		fontResources.insert(std::make_pair(key, font));
		return true;
	}
	else {
		std::cout << "Could not load font. key: " << key << ", fileName" << fileName << std::endl;
		return false;
	}
}

bool Resources::loadSample(std::string key, std::string fileName) {
	ALLEGRO_SAMPLE* sample = al_load_sample(fileName.c_str());
	if (sample != NULL) {
		sounds.insert(std::make_pair(key, sample));
		return true;
	}
	else {
		std::cout << "Could not load sample. key: " << key << ", fileName: " << fileName << std::endl;
		return false;
	}
}