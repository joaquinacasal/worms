#include "client_SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "client_SdlWindow.h"
#include "client_SdlException.h"

using std::string;

SdlTexture::SdlTexture(const string& filename, const SdlWindow& window, int x, int y, int width, int heigth)
    : renderer(window.getRenderer()) {
    this->texture = loadTexture(filename);
    position = { x, y, width, heigth };
}

SdlTexture::~SdlTexture() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* SdlTexture::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,
                                           filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }
    return texture;
}

int SdlTexture::render() const {
    return SDL_RenderCopy(this->renderer, this->texture, NULL, &position);
}

void SdlTexture::set_position(int x, int y){
    position = { x, y, position.w, position.h };
}
