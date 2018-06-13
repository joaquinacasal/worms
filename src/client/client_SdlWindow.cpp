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
    double x = drawable->get_x() - (WORM_SIZE / 2);
    double y = drawable->get_y() - (WORM_SIZE / 2);
    printf("DEBUG: la posición en x,y es: (%f, %f)\n", x, y);
    if (textures.count(id)){
        SdlTexture* worm = textures.at(id);
        worm->set_position(x, y);
    } else {
        SdlTexture* worm = new SdlTexture("../assets/worm.png", *this, x, y, WORM_SIZE, WORM_SIZE);
        textures[id] = worm;
    }
}

void SdlWindow::draw(StageDrawable* drawable) {
  SDL_SetWindowSize(this->window, drawable->get_width(), drawable->get_height());
}

void SdlWindow::draw(BeamDrawable* drawable) {
  double x = drawable->get_x() - (drawable->get_length() / 2);
  double y = drawable->get_y() - (drawable->get_width() / 2);
  SdlTexture* beam = new SdlTexture("../assets/grdl0.png", *this, x, y, drawable->get_length(), drawable->get_width());
  textures[x] = beam; // TODO: QUE HACEMOS CON EL ID? COMO SE GUARDA?
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
  double x = drawable->get_x() - DYNAMITE_SIZE / 2;
  double y = drawable->get_y() - DYNAMITE_SIZE / 2;
  SdlTexture* dynamite = new SdlTexture("../assets/dynamite.png", *this, x, y, DYNAMITE_SIZE, DYNAMITE_SIZE);
  textures['d'] = dynamite; // TODO: QUE HACEMOS CON EL ID? COMO SE GUARDA?
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
