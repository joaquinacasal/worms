#include "client_SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "client_SdlWindow.h"
#include "client_SdlException.h"

using std::string;

SdlTexture::SdlTexture(SDL_Texture* texture, const SdlWindow& window,\
                       Area position)
    : renderer(window.getRenderer()), texture(texture), position(position) {
}

int SdlTexture::render(int angle) const {
    SDL_Rect position_rec = position.toRect();
    if (angle == 0) {
        return SDL_RenderCopy(this->renderer, this->texture, NULL,\
                              &position_rec);
    } else {
        return SDL_RenderCopyEx(this->renderer, this->texture, NULL,\
                                &position_rec, angle, NULL, SDL_FLIP_NONE);
    }
}

void SdlTexture::set_position(int x, int y){
    position.setPosition(x, y);
}
