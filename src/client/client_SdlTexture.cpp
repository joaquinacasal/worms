#include "client_SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "client_SdlWindow.h"
#include "client_SdlException.h"

using std::string;

SdlTexture::SdlTexture(SDL_Texture* texture, const SdlWindow& window, int x, int y, int width, int heigth)
    : renderer(window.getRenderer()), texture(texture) {
    position = { x, y, width, heigth };
}

int SdlTexture::render() const {
    return SDL_RenderCopy(this->renderer, this->texture, NULL, &position);
}

void SdlTexture::set_position(int x, int y){
    position = { x, y, position.w, position.h };
}
