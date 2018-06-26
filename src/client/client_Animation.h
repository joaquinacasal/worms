#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <string>
#include <SDL2/SDL_image.h>
#include "client_Area.h"
#include "client_Camera.h"

using std::string;

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;

/*
 * Clase que abstrae la complejidad de mostrar una animación. Recibe una
 * textura y la cantidad de frames que tiene la imagen, y se encarga de en
 * cada render mostrar una imagen diferente de tamaño ancho x alto / frames.
 * Para que las animaciones sean más reales, se muentra un número constante
 * de veces un mismo sprite, para luego recién cambiar al siguiente.
 */
class Animation {
public:
    Animation(SDL_Texture* texture, const SdlWindow& window,\
              Area position, int frames);
    void render(Camera& camera, int angle = 0,\
                SDL_RendererFlip flip_flags = SDL_FLIP_NONE);
    void set_position(int x, int y);
    void set_texture(SDL_Texture* texture, int frames);
    ~Animation() = default;
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Area position;
    int frames;
    int frame_counter;
    int frame_counter_counter;
    Area current_frame;
    float frame_height;
};

#endif
