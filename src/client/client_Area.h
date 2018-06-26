#ifndef __AREA_H__
#define __AREA_H__

#include <SDL2/SDL_image.h>

/*
 * Clase que representa un área rectangular de la ventana en una posición y
 * con un tamaño determinado. Además permite obtener, a partir de dicha
 * clase, un SDL_Rect.
 */
class Area {
public:
	Area() = default;
	Area(int x, int y, int width, int height);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
	SDL_Rect toRect() const;
private:
	int x, y;
	int width, height;
};

#endif
