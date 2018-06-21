#include "client_WormRepresentation.h"
#include "client_SdlWindow.h"

class SDL_Texture;
class SDL_Renderer;
class Area;

WormRepresentation::WormRepresentation(SdlTexture* worm_texture, const SdlWindow& window, SDL_Texture* life_texture,
                        Area life_rect, bool is_facing_right, size_t life_points, int angle) :
                        worms_texture(worm_texture), renderer(window.getRenderer()), life_texture(life_texture),
                        life_area(life_rect), _is_facing_right(is_facing_right), life_points(life_points), angle(angle) {}

int WormRepresentation::render() const {
    this->worms_texture->render();
    SDL_Rect life_rect = {
            this->life_area.getX(), this->life_area.getY(),
            this->life_area.getWidth(), this->life_area.getHeight()
    };
    SDL_RenderCopy(this->renderer, this->life_texture, NULL, &life_rect);
}

void WormRepresentation::set_texture(SdlTexture* worm_texture){
    delete this->worms_texture;
    this->worms_texture = worm_texture;
}

void WormRepresentation::set_life_texture(SDL_Texture* life_texture){
    SDL_DestroyTexture(this->life_texture);
    this->life_texture = life_texture;
}

void WormRepresentation::set_position(int x, int y){
    worms_texture->set_position(x, y);
    life_area.setPosition(x + 10, y - 20);
}

void WormRepresentation::set_life_points(size_t points){
    this->life_points = points;
}

void WormRepresentation::set_angle(int angle){
    this->angle = angle;
}

void WormRepresentation::set_facing_right(bool is_facing_right){
    this->_is_facing_right = is_facing_right;
}

Area WormRepresentation::get_life_position(){
    return this->life_area;
}

size_t WormRepresentation::get_life_points(){
    return this->life_points;
}

bool WormRepresentation::is_facing_right(){
    return this->_is_facing_right;
}

WormRepresentation::~WormRepresentation(){
    delete this->worms_texture;
    delete this->life_texture;
}
