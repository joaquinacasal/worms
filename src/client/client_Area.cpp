#include "client_Area.h"
#include <SDL2/SDL_image.h>

Area::Area(int x, int y, int width, int height) :
	x(x), y(y), width(width), height(height){
}
	
int Area::getX() const {
	return this->x;
}

int Area::getY() const {
	return this->y;
}

int Area::getWidth() const {
	return this->width;
}

int Area::getHeight() const {
	return this->height;
}

void Area::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

SDL_Rect Area::toRect() const{
	SDL_Rect rec = {
            this->x, this->y, this->width, this->height
    };
	return rec;
}
