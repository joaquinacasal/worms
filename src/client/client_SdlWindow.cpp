#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "client_SdlException.h"
#include "client_SdlWindow.h"
#include "client_SdlTexture.h"

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
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;

    // Cronometro del turno.
    White = {255, 255, 255, 0};
    Sans = TTF_OpenFont("../assets/BebasNeueRegular.ttf", 24);

    turn_chrono_surface = TTF_RenderText_Solid(Sans, "60.0", White);
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
        it->second->render();
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
  turn_chrono_surface = TTF_RenderText_Solid(Sans, value.c_str(), White);
}

void SdlWindow::draw(WormDrawable* drawable) {
    size_t id = drawable->get_id();
    double x = drawable->get_x() - (WORM_SIZE / 2);
    double y = drawable->get_y() - (WORM_SIZE / 2);
    if (worms_textures.count(id)){
        SdlTexture* worm = worms_textures.at(id);
        worm->set_position(x, y);
    } else {
        SdlTexture* worm = new SdlTexture("../assets/worm.png", *this, x, y, WORM_SIZE, WORM_SIZE);
        worms_textures[id] = worm;
    }
}

void SdlWindow::draw(StageDrawable* drawable) {
  SDL_SetWindowSize(this->window, drawable->get_width(), drawable->get_height());
}

void SdlWindow::draw(BeamDrawable* drawable) {
  double x = drawable->get_x() - (drawable->get_length() / 2);
  double y = drawable->get_y() - (drawable->get_width() / 2);
  SdlTexture* beam = new SdlTexture("../assets/grdl0.png", *this, x, y, drawable->get_length(), drawable->get_width());
  static_textures.push_back(beam);
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
  double x = drawable->get_x() - DYNAMITE_SIZE / 2;
  double y = drawable->get_y() - DYNAMITE_SIZE / 2;
  SdlTexture* dynamite = new SdlTexture("../assets/dynamite.png", *this, x, y, DYNAMITE_SIZE, DYNAMITE_SIZE);
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
