#ifndef __WORMREPRESENTATION__
#define __WORMREPRESENTATION__

#include "client_Animation.h"
#include "client_TextureFactory.h"
#include "client_Camera.h"

#define JUMPING_FRAMES 7
#define WALKING_FRAMES 15
#define RESTING_FRAMES 20
#define DEAD_FRAMES 1

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

enum WormState { RESTING, WALKING, JUMPING, DEAD };

class WormRepresentation {
public:
    WormRepresentation(WormState state, Area position, const SdlWindow& window,\
        SDL_Texture* life_texture, bool is_facing_right, size_t life_points,\
        int angle, TextureFactory& texture_factory, bool is_the_selected_worm);
    void render(Camera& camera) const;
    void set_position(int x, int y);
    void set_life_points(size_t points, SDL_Texture* life_texture);
    void set_state(WormState state, int angle, bool is_facing_right);
    void select_worm();
    void deselect_worm();
    Area get_life_position() const;
    size_t get_life_points() const;
    bool is_facing_right() const;
    ~WormRepresentation();

private:
    Animation* worm_animation;
    SDL_Renderer* renderer;
    SDL_Texture* life_texture;
    Area life_area;
    SDL_Texture* arrow_texture;
    Area arrow_area;
    bool _is_facing_right;
    size_t life_points;
    int angle;
    WormState state;
    TextureFactory& texture_factory;
    bool _is_the_selected_worm;

    void get_texture_by_state(WormState state, SDL_Texture** texture, \
                              int* frames);
};

#endif
