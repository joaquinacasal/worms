#ifndef __WORMREPRESENTATION__
#define __WORMREPRESENTATION__

#include "client_SdlTexture.h"

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class WormRepresentation {
public:
    WormRepresentation(SdlTexture* worm_texture, const SdlWindow& window, SDL_Texture* life_texture, Area life_rect,
                        bool is_facing_right, size_t life_points, int angle);
    int render() const;
    void set_texture(SdlTexture* worm_texture);
    void set_life_texture(SDL_Texture* life_texture);
    void set_position(int x, int y);
    void set_life_points(size_t points);
    void set_angle(int angle);
    void set_facing_right(bool is_facing_right);
    Area get_life_position();
    size_t get_life_points();
    bool is_facing_right();
    ~WormRepresentation();
private:
    SdlTexture* worms_texture;
    SDL_Renderer* renderer;
    SDL_Texture* life_texture;
    Area life_area;
    bool _is_facing_right;
    size_t life_points;
    int angle;
};

#endif
