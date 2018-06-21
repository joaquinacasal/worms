#ifndef __AREA_H__
#define __AREA_H_

#include <SDL2/SDL_image.h>

class Area {
public:
	Area() = default;
	Area(int x, int y, int width, int height);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setPosition(int x, int y);
	SDL_Rect toRect() const;
private:
	int x, y;
	int width, height;
};

#endif
