#include "client_WormRepresentation.h"
#include "client_SdlWindow.h"

class SDL_Texture;
class SDL_Renderer;
class Area;

WormRepresentation::WormRepresentation(WormState state, Area position, \
      const SdlWindow& window, SDL_Texture* life_texture, bool is_facing_right,\
      size_t life_points, int angle, TextureFactory& texture_factory, \
      bool is_the_selected_worm) :
      renderer(window.getRenderer()), life_texture(life_texture),
      _is_facing_right(is_facing_right), life_points(life_points), \
      angle(angle), state(state), texture_factory(texture_factory), \
      _is_the_selected_worm(is_the_selected_worm) {
    SDL_Texture* texture;
    int frames;
    get_texture_by_state(state, &texture, &frames);
    worm_animation = new Animation(texture, window, position, frames);
    life_area = Area(position.getX() + 10, position.getY() - 20, 20, 20);
    arrow_area = Area(position.getX() + 10, position.getY() - 40, 20, 20);
    arrow_texture = texture_factory.get_texture_by_name("arrow");
}

int WormRepresentation::render(Camera& camera) const {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (this->is_facing_right())
        flip = SDL_FLIP_HORIZONTAL;
    this->worm_animation->render(camera, angle, flip);
    Area pos = camera.adapt_area(this->life_area);
    SDL_Rect life_rect = pos.toRect();
    SDL_RenderCopy(this->renderer, this->life_texture, NULL, &life_rect);
    if (_is_the_selected_worm) {
      SDL_Rect arrow_rect = this->arrow_area.toRect();
      SDL_RenderCopy(this->renderer, this->arrow_texture, NULL, &arrow_rect);
    }
}

void WormRepresentation::set_position(int x, int y){
    worm_animation->set_position(x, y);
    life_area.setPosition(x + 10, y - 20);
    arrow_area.setPosition(x + 10, y - 40);
}

void WormRepresentation::set_life_points(size_t points, \
                                         SDL_Texture* life_texture){
    if (this->life_points == points){
        return;
    }
    this->life_points = points;
    SDL_DestroyTexture(this->life_texture);
    this->life_texture = life_texture;
}

void WormRepresentation::set_state(WormState state, int angle, \
                                   bool is_facing_right){
    this->angle = angle;
    this->_is_facing_right = is_facing_right;
    if (this->state == state){
        return;
    }
    this->state = state;
    SDL_Texture* texture;
    int frames;
    get_texture_by_state(state, &texture, &frames);
    this->worm_animation->set_texture(texture, frames);
}

void WormRepresentation::select_worm(){
    _is_the_selected_worm = true;
}

void WormRepresentation::deselect_worm(){
    _is_the_selected_worm = false;
}

Area WormRepresentation::get_life_position() const{
    return this->life_area;
}

size_t WormRepresentation::get_life_points() const{
    return this->life_points;
}

bool WormRepresentation::is_facing_right() const{
    return this->_is_facing_right;
}

void WormRepresentation::get_texture_by_state(WormState state, \
                                              SDL_Texture** texture, \
                                              int* frames){
    if (state == JUMPING){
        *texture = texture_factory.get_texture_by_name("worm_jumping");
        *frames = JUMPING_FRAMES;
    } else if (state == WALKING){
        *texture = texture_factory.get_texture_by_name("worm_walking");
        *frames = WALKING_FRAMES;
    } else if (state == RESTING){
        *texture = texture_factory.get_texture_by_name("worm_resting");
        *frames = RESTING_FRAMES;
    } else if (state == DEAD){
        *texture = texture_factory.get_texture_by_name("grave");
        *frames = DEAD_FRAMES;
    }
}

WormRepresentation::~WormRepresentation(){
    delete this->worm_animation;
    SDL_DestroyTexture(this->life_texture);
    SDL_DestroyTexture(this->arrow_texture);
}
