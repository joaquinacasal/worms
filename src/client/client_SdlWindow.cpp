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

    // Cronometro del turno.
    White = {255, 255, 255, 0};
    string font = string(ASSETS_FOLDER) + string(FONT_ASSET);
    Sans_big = TTF_OpenFont(font.c_str(), 24);
    Sans_small = TTF_OpenFont(font.c_str(), 16);

    turn_chrono_surface = TTF_RenderText_Solid(Sans_big, "60.0", White);
    turn_chrono_rect.x = 0;  //controls the rect's x coordinate
    turn_chrono_rect.y = 0; // controls the rect's y coordinte
    turn_chrono_rect.w = 100; // controls the width of the rect
    turn_chrono_rect.h = 80; // controls the height of the rect
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::render() {
    for (auto it = worms_textures.begin(); it != worms_textures.end(); ++it){
        it->second->worms_texture->render();

        SDL_RenderCopy(this->renderer, \
                        SDL_CreateTextureFromSurface(renderer, it->second->life_surface), \
                        NULL, \
                        &it->second->life_rect);
    }
    for (auto it = weapons_textures.begin(); it != weapons_textures.end(); ++it){
        it->second->render();
    }
    for (size_t i = 0; i < static_textures.size(); ++i){
        static_textures[i]->render();
    }

    // Render turn_chrono
    turn_chrono_texture = SDL_CreateTextureFromSurface(renderer, turn_chrono_surface);
    SDL_RenderCopy(this->renderer, turn_chrono_texture, NULL, &turn_chrono_rect);

    SDL_RenderPresent(this->renderer);
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}


void SdlWindow::draw(StartTurnDrawable* drawable) {
}

void SdlWindow::draw(EndTurnDrawable* drawable) {
}

void SdlWindow::draw(TurnTimeDrawable* drawable) {
  std::string value = std::to_string((int)drawable->get_time_left());
  turn_chrono_surface = TTF_RenderText_Solid(Sans_big, value.c_str(), White);
}

void SdlWindow::draw(WormDrawable* drawable) {
    size_t id = drawable->get_id();
    double x = drawable->get_x() - (WORM_SIZE / 2);
    double y = drawable->get_y() - (WORM_SIZE / 2);
    std::string life_points(std::to_string(drawable->get_life_points()));
    if (worms_textures.count(id)){
        worm_representation* w_r = worms_textures.at(id);
        w_r->worms_texture->set_position(x, y);
        w_r->life_rect.x = x;
        w_r->life_rect.y = y - 20;
        delete w_r->life_surface;
        w_r->life_surface = TTF_RenderText_Solid(Sans_small, life_points.c_str(), White);
    } else {
        SdlTexture* worms_texture = new SdlTexture(string(ASSETS_FOLDER) + string(WORM_ASSET), *this, x, y, WORM_SIZE, WORM_SIZE);

        SDL_Rect life_rect;
        life_rect.x = x;  //controls the rect's x coordinate
        life_rect.y = y - 20;  //controls the rect's y coordinate
        life_rect.w = 20; // controls the width of the rect
        life_rect.h = 20; // controls the height of the rect

        SDL_Surface* life_surface = TTF_RenderText_Solid(Sans_small, life_points.c_str(), White);

        worm_representation* w_r = new worm_representation({ worms_texture, life_rect, life_surface });

        worms_textures[id] = w_r;
    }
}

void SdlWindow::draw(StageDrawable* drawable) {
  SDL_SetWindowSize(this->window, drawable->get_width(), drawable->get_height());
}

void SdlWindow::draw(BeamDrawable* drawable) {
  double x = drawable->get_x() - (drawable->get_length() / 2);
  double y = drawable->get_y() - (drawable->get_width() / 2);
  SdlTexture* beam = new SdlTexture(string(ASSETS_FOLDER) + string(BEAM_ASSET), *this, x, y, drawable->get_length(), drawable->get_width());
  static_textures.push_back(beam);
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
  double x = drawable->get_x() - DYNAMITE_SIZE / 2;
  double y = drawable->get_y() - DYNAMITE_SIZE / 2;
  SdlTexture* dynamite = new SdlTexture(string(ASSETS_FOLDER) + string(DYNAMITE_ASSET), *this, x, y, DYNAMITE_SIZE, DYNAMITE_SIZE);
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
      SdlTexture* radiocontrolled = new SdlTexture("../assets/radiocontrolled.png", *this, x, y, RADIOCONTROLLED_SIZE, RADIOCONTROLLED_SIZE);
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
}
