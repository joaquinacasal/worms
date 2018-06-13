#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
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
    for (auto it = textures.begin(); it != textures.end(); ++it){
        it->second->render();
    }
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
}

void SdlWindow::draw(WormDrawable* drawable) {
    size_t id = drawable->get_id();
    double x = drawable->get_x();
    double y = drawable->get_y();
    if (textures.count(id)){
        SdlTexture* worm = textures.at(id);
        worm->set_position(x, y);
    } else {
        SdlTexture* worm = new SdlTexture("../assets/worm.png", *this, x, y, 40, 40); //TODO: tamaño no hardcodeaddo
        textures[id] = worm;
    }
}

void SdlWindow::draw(StageDrawable* drawable) {
}

void SdlWindow::draw(BeamDrawable* drawable) {
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
}

void SdlWindow::draw(RadiocontrolledDrawable* drawable){
}

void SdlWindow::draw(ClosedConnectionDrawable* drawable) {
}

void SdlWindow::draw(IDrawable* drawable) {
    drawable->be_drawn(this);
}


void SdlWindow::run(){
  IDrawable* drawable = NULL;
  while(connected) {
    if (safe_queue.pop(drawable)){
      draw(drawable);
      delete drawable;
    }
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
