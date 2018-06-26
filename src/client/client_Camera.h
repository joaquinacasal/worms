#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "client_Area.h"

#define CAMERA_SPEED 30

enum CameraMovement { UP, DOWN, RIGHT, LEFT };
/*
 * Clase encargada de la cámara del cliente. Ésta define qué espacio del
 * escenario mostrar, y para ello hace todas las conversiones necesarias.
 * Además, permite centrar la cámara en una coordenada dada, y navegar a
 * través del escenario.
 */
class Camera {
public:
    Camera() = default;
    void set_position(Area position);
    void set_map_size(int map_width, int map_height);
    void adapt_coordinates(int* x, int* y) const;
    Area adapt_area(Area area);
    void coordinates_to_absolut(int* x, int* y);
    Area get_center(int width, int height);
    void move(CameraMovement movement);
    void center(int x, int y);
    ~Camera() = default;
private:
    void move_up();
    void move_down();
    void move_right();
    void move_left();
    void check_position();

    Area position;
    int map_width;
    int map_height;
    int speed = CAMERA_SPEED;
};

#endif
