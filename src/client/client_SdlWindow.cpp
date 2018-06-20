#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "client_SdlException.h"
#include "client_SdlWindow.h"
#include "client_SdlTexture.h"
#include "config.h"

using std::string;

SdlWindow::SdlWindow(SafeQueue<IDrawable*>& _safe_queue, int width, int height) :
        safe_queue(_safe_queue), width(width), height(height), connected(true) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    errCode = SDL_CreateWindowAndRenderer(
        width, height, SDL_RENDERER_ACCELERATED,
        &this->window, &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana", SDL_GetError());
    }
    if(TTF_Init() < 0)
        throw SdlException("No se pudo inicializar la librería TTF", TTF_GetError());

    change_turn_message = {NULL, 0};
    // Cronometro del turno.
    White = {255, 255, 255, 0};
    string font = string(ASSETS_FOLDER) + string(FONT_ASSET);
    Sans_big = TTF_OpenFont(font.c_str(), 24);
    Sans_small = TTF_OpenFont(font.c_str(), 16);

    SDL_Surface* turn_chrono_surface = TTF_RenderText_Solid(Sans_big, "60.0", White);
    turn_chrono_texture = SDL_CreateTextureFromSurface(renderer, turn_chrono_surface);
    SDL_FreeSurface(turn_chrono_surface);

    turn_chrono_rect.x = 0;  //controls the rect's x coordinate
    turn_chrono_rect.y = 0; // controls the rect's y coordinte
    turn_chrono_rect.w = 100; // controls the width of the rect
    turn_chrono_rect.h = 80; // controls the height of the rect

    worm_r_texture = loadTexture(string(ASSETS_FOLDER) + string(WORM_R_ASSET));
    worm_l_texture = loadTexture(string(ASSETS_FOLDER) + string(WORM_L_ASSET));
    beam_texture = loadTexture(string(ASSETS_FOLDER) + string(BEAM_ASSET));
    start_turn_texture = loadTexture(string(ASSETS_FOLDER) + string(START_TURN_ASSET));
    end_turn_texture = loadTexture(string(ASSETS_FOLDER) + string(FINISH_TURN_ASSET));
    dynamite_texture = loadTexture(string(ASSETS_FOLDER) + string(DYNAMITE_ASSET));
    radioControlled_texture = loadTexture(string(ASSETS_FOLDER) + string(RADIOCONTROLLED_ASSET));
    grave_texture = loadTexture(string(ASSETS_FOLDER) + string(GRAVE_ASSET));
    background_texture = NULL;
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
    if (background_texture == NULL)
      this->fill(0x33,0x33,0x33,0xFF);
    else
      this->background_texture->render();
}

void SdlWindow::render() {
    for (auto it = worms_textures.begin(); it != worms_textures.end(); ++it){
        it->second->worms_texture->render(it->second->angle);

        SDL_RenderCopy(this->renderer, \
                        it->second->life_texture, \
                        NULL, \
                        &it->second->life_rect);
    }
    for (auto it = weapons_textures.begin(); it != weapons_textures.end(); ++it){
        it->second->render();
    }
    for (size_t i = 0; i < static_textures.size(); ++i){
        static_textures[i]->beam_texture->render(static_textures[i]->angle);
    }

    // Render turn_chrono
    SDL_RenderCopy(this->renderer, turn_chrono_texture, NULL, &turn_chrono_rect);

    // Render change_turn_message
    if (change_turn_message.time_alive > 0) {
        change_turn_message.message_texture->render();
        change_turn_message.time_alive--;
        if (change_turn_message.time_alive == 0){
          delete change_turn_message.message_texture;
          change_turn_message.message_texture = NULL;
        }
    }

    SDL_RenderPresent(this->renderer);
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}


void SdlWindow::draw(StartTurnDrawable* drawable) {
    if (change_turn_message.message_texture)
        delete change_turn_message.message_texture;
    Area area(width/2 - CHANGE_TURN_MESSAGE_SIZE / 2, height/2 - CHANGE_TURN_MESSAGE_SIZE / 2, CHANGE_TURN_MESSAGE_SIZE, CHANGE_TURN_MESSAGE_SIZE);
    change_turn_message.message_texture = new SdlTexture(start_turn_texture, *this, area);
    change_turn_message.time_alive = CHANGE_TURN_MESSAGE_DURATION;
}

void SdlWindow::draw(EndTurnDrawable* drawable) {
    if (change_turn_message.message_texture)
        delete change_turn_message.message_texture;
    Area area(width/2 + CHANGE_TURN_MESSAGE_SIZE, height/2 + CHANGE_TURN_MESSAGE_SIZE / 2, CHANGE_TURN_MESSAGE_SIZE, CHANGE_TURN_MESSAGE_SIZE);
    change_turn_message.message_texture = new SdlTexture(end_turn_texture, *this, area);
    change_turn_message.time_alive = CHANGE_TURN_MESSAGE_DURATION;
}

void SdlWindow::draw(TurnTimeDrawable* drawable) {
  std::string value = std::to_string((int)drawable->get_time_left());
  SDL_Surface* turn_chrono_surface = TTF_RenderText_Solid(Sans_big, value.c_str(), White);
  SDL_DestroyTexture(turn_chrono_texture);
  turn_chrono_texture = SDL_CreateTextureFromSurface(renderer, turn_chrono_surface);
  SDL_FreeSurface(turn_chrono_surface);
}

void SdlWindow::draw(WormDrawable* drawable) {
    size_t id = drawable->get_id();
    double new_x = drawable->get_x() - (WORM_SIZE / 2);
    double new_y = drawable->get_y() - (WORM_SIZE / 2);
    int new_angle = drawable->get_angle();
    size_t new_life_points_q = drawable->get_life_points();
    std::string new_life_points_s(std::to_string(new_life_points_q));
    bool new_facing_right = drawable->get_is_facing_right();
    if (worms_textures.count(id)){
        worm_representation* w_r = worms_textures.at(id);
        w_r->worms_texture->set_position(new_x, new_y);
        w_r->life_rect.x = new_x + 10;
        w_r->life_rect.y = new_y - 20;
        w_r->angle = new_angle;

        // Actualizo la vida si cambió
        if (w_r->life_points != new_life_points_q){
          SDL_DestroyTexture(w_r->life_texture);
          SDL_Surface* life_surface = TTF_RenderText_Solid(Sans_small, new_life_points_s.c_str(), White);
          w_r->life_texture =  SDL_CreateTextureFromSurface(renderer, life_surface);
          SDL_FreeSurface(life_surface);
          w_r->life_points = new_life_points_q;
        }

        // Actualizo el lado para el que mira si cambió
        if (w_r->is_facing_right != new_facing_right) {
          delete w_r->worms_texture;
          Area area(new_x, new_y, WORM_SIZE, WORM_SIZE);
          if (new_facing_right) {
              w_r->worms_texture = new SdlTexture(worm_r_texture, *this, area);
          } else {
              w_r->worms_texture = new SdlTexture(worm_l_texture, *this, area);
          }
          w_r->is_facing_right = new_facing_right;
        }


    } else {
        SdlTexture* worms_texture = NULL;
        Area area(new_x, new_y, WORM_SIZE, WORM_SIZE);
        if (new_facing_right) {
          worms_texture = new SdlTexture(worm_r_texture, *this, area);
        } else {
          worms_texture = new SdlTexture(worm_l_texture, *this, area);
        }

        SDL_Rect life_rect;
        life_rect.x = new_x + 10;  //controls the rect's x coordinate
        life_rect.y = new_y - 20;  //controls the rect's y coordinate
        life_rect.w = 20; // controls the width of the rect
        life_rect.h = 20; // controls the height of the rect

        SDL_Surface* life_surface = TTF_RenderText_Solid(Sans_small, new_life_points_s.c_str(), White);

        worm_representation* w_r = new worm_representation({ worms_texture, life_rect, SDL_CreateTextureFromSurface(renderer, life_surface), new_facing_right, new_life_points_q, new_angle });
        worms_textures[id] = w_r;
        SDL_FreeSurface(life_surface);
    }
}

void SdlWindow::draw(WormDeathDrawable* drawable) {
  size_t id = drawable->get_id();
  if (worms_textures.count(id) == 0) return;
  worm_representation* w_r = worms_textures.at(id);

  SDL_DestroyTexture(w_r->life_texture);
  SDL_Surface* life_surface = TTF_RenderText_Solid(Sans_small, "0", White);
  w_r->life_texture =  SDL_CreateTextureFromSurface(renderer, life_surface);
  SDL_FreeSurface(life_surface);
  w_r->life_points = 0;

  delete w_r->worms_texture;
  Area area(w_r->life_rect.x, w_r->life_rect.y, WORM_SIZE, WORM_SIZE);
  w_r->worms_texture = new SdlTexture(grave_texture, *this, area);
}

void SdlWindow::draw(StageDrawable* drawable) {
  width = drawable->get_width();
  height = drawable->get_height();
  SDL_SetWindowSize(this->window, width, height);
  SDL_Texture* background = loadTexture(string(BACKGROUNDS_FOLDER) + drawable->get_background());

  Area area(0, 0, width, height);
  this->background_texture = new SdlTexture(background, *this, area);

}

void SdlWindow::draw(BeamDrawable* drawable) {
  double x = drawable->get_x() - (drawable->get_length() / 2);
  double y = drawable->get_y() - (drawable->get_width() / 2);
  Area area(x, y, drawable->get_length(), drawable->get_width());
  SdlTexture* beam = new SdlTexture(beam_texture, *this, area);
  beam_representation* b_r = new beam_representation({ beam, drawable->get_angle() });
  static_textures.push_back(b_r);
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
  double x = drawable->get_x() - DYNAMITE_SIZE / 2;
  double y = drawable->get_y() - DYNAMITE_SIZE / 2;
  Area area(x, y, DYNAMITE_SIZE, DYNAMITE_SIZE);
  SdlTexture* dynamite = new SdlTexture(dynamite_texture, *this, area);
  weapons_textures[DYNAMITE_ID] = dynamite;
}

void SdlWindow::draw(DynamiteExplosionDrawable* drawable) {
  delete weapons_textures[DYNAMITE_ID];
  weapons_textures.erase(DYNAMITE_ID);
}


void SdlWindow::draw(RadiocontrolledDrawable* drawable){
  size_t id = drawable->get_id();
  double x = drawable->get_x() - (RADIOCONTROLLED_SIZE / 2);
  double y = drawable->get_y() - (RADIOCONTROLLED_SIZE / 2);
  if (weapons_textures.count(id)){
      SdlTexture* radiocontrolled = weapons_textures.at(id);
      radiocontrolled->set_position(x, y);
  } else {
      Area area(x, y, RADIOCONTROLLED_SIZE, RADIOCONTROLLED_SIZE);
      SdlTexture* radiocontrolled = new SdlTexture(radioControlled_texture, *this, area);
      weapons_textures[id] = radiocontrolled;
  }
}

void SdlWindow::draw(RadiocontrolledExplosionDrawable* drawable) {
  delete weapons_textures[drawable->get_id()];
  weapons_textures.erase(drawable->get_id());
}

void SdlWindow::draw(ClosedConnectionDrawable* drawable) {
}

void SdlWindow::draw(IDrawable* drawable) {
    drawable->be_drawn(this);
}

void SdlWindow::run(){
  IDrawable* drawable = NULL;
  while(connected) {
    fill();
    if (safe_queue.pop(drawable)){
      draw(drawable);
      delete drawable;
    }
    render();
    // TODO: acá también se hacen las animaciones.
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

bool SdlWindow::is_connected(){
  return connected;
}

void SdlWindow::stop(){
  connected = false;
}

SdlWindow::~SdlWindow() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    IDrawable* drawable = NULL;
    while(safe_queue.pop(drawable)) {
      delete drawable;
    }

    for (int i = 0; i < static_textures.size(); i++){
        delete static_textures[i];
    }

    for (auto it = worms_textures.begin(); it != worms_textures.end(); ++it){
        SDL_DestroyTexture(it->second->life_texture);
        delete it->second->worms_texture;
        delete it->second;
    }

    SDL_DestroyTexture(worm_l_texture);
    SDL_DestroyTexture(worm_r_texture);
    SDL_DestroyTexture(beam_texture);
    SDL_DestroyTexture(start_turn_texture);
    SDL_DestroyTexture(end_turn_texture);
    SDL_DestroyTexture(dynamite_texture);
    SDL_DestroyTexture(radioControlled_texture);
    SDL_DestroyTexture(grave_texture);

    delete change_turn_message.message_texture;
    SDL_DestroyTexture(turn_chrono_texture);
    TTF_CloseFont(Sans_big);
    TTF_CloseFont(Sans_small);
}

SDL_Texture* SdlWindow::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,
                                           filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }
    return texture;
}
