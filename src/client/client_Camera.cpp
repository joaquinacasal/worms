#include "client_Camera.h"

void Camera::set_position(Area position){
    this->position = position;
}

void Camera::set_map_size(int map_width, int map_height){
    this->map_width = map_width;
    this->map_height = map_height;
}

void Camera::adapt_coordinates(int* x, int* y) const{
    int aux_x = *x - position.getX();
    int aux_y = *y - position.getY();
    *x = aux_x;
    *y = aux_y;
}

Area Camera::adapt_area(Area area){
    int x = area.getX();
    int y = area.getY();
    adapt_coordinates(&x, &y);
    return Area(x, y, area.getWidth(), area.getHeight());
}

void Camera::coordinates_to_absolut(int* x, int* y){
    int aux_x = *x + position.getX();
    int aux_y = *y + position.getY();
    *x = aux_x;
    *y = aux_y;
}

Area Camera::get_center(int width, int height){
    int x = position.getWidth() / 2 - width / 2;
    int y = position.getHeight() / 2 - height / 2;
    return Area(x, y, width, height);
}

void Camera::move(CameraMovement movement){
    switch(movement){
        case UP:
            move_up();
            break;
        case DOWN:
            move_down();
            break;
        case RIGHT:
            move_right();
            break;
        case LEFT:
            move_left();
            break;
    }
    check_position();
}

void Camera::center(int x, int y){
    position.setPosition(x - position.getWidth() / 2,\
                        y - position.getHeight() / 2);
    check_position();
}

void Camera::check_position(){
    if (position.getX() < 0)
    {
        position.setX(0);
    }
    if (position.getY() < 0)
    {
        position.setY(0);
    }
    if (position.getX() > map_width - position.getWidth())
    {
        position.setX(map_width - position.getWidth());
    }
    if (position.getY() > map_height - position.getHeight())
    {
        position.setY(map_height - position.getHeight());
    }
}

void Camera::move_up(){
    int y = position.getY();
    y -= speed;
    position.setY(y);
}

void Camera::move_down(){
    int y = position.getY();
    y += speed;
    position.setY(y);
}

void Camera::move_right(){
    int x = position.getX();
    x += speed;
    position.setX(x);
}

void Camera::move_left(){
    int x = position.getX();
    x -= speed;
    position.setX(x);
}
