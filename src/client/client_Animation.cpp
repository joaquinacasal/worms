#include "client_Animation.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "client_SdlWindow.h"
#include "client_SdlException.h"

using std::string;

Animation::Animation(SDL_Texture* texture, const SdlWindow& window, Area position, int frames)
    : renderer(window.getRenderer()), texture(texture), position(position), frames(frames), frame_counter(0),
    frame_counter_counter(0) {
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        this->frame_height = height / frames;
        this->current_frame = Area(0, 0, width, frame_height);
}

void Animation::render(int angle, SDL_RendererFlip flip_flags) {
    SDL_Rect position_rec = position.toRect();
    SDL_Rect src_frame = current_frame.toRect();
    
    SDL_RenderCopyEx(this->renderer, this->texture, &src_frame, &position_rec, angle, NULL, flip_flags);
    frame_counter_counter += 1;
    if (frame_counter_counter == 50){
        frame_counter_counter = 0;
        frame_counter += 1;
        if (frame_counter == frames){
            frame_counter = 0;
        }
    }
    current_frame.setPosition(0, frame_height * frame_counter);
}

void Animation::set_position(int x, int y){
    position.setPosition(x, y);
}

void Animation::set_texture(SDL_Texture* texture, int frames){
    this->frames = frames;
    this->frame_counter = 0;
    this->frame_counter_counter = 0;
    this->texture = texture;
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    this->frame_height = height / frames;
    this->current_frame = Area(0, 0, width, frame_height);
}
