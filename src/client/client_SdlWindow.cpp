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
        safe_queue(_safe_queue), width(width), height(height), connected(true),\
        change_turn_message(NULL, 0), you_win_message(NULL, 0) {
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

    // Cronometro del turno.
    turn_chrono = {font_factory.get_texture_big_font("60.0", colors_factory.get_color_by_name("white"), renderer), Area(10, 10, 100, 80)};
    dynamite_chrono = {NULL, Area(0, 0, 0, 0)};
    texture_factory.init(renderer);
    background_texture = NULL;
    munitions_info = new MunitionsInformation(10, 100, font_factory, colors_factory, renderer);
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
    for (size_t i = 0; i < static_textures.size(); ++i){
      static_textures[i]->beam_texture->render(static_textures[i]->angle);
    }
    for (auto it = worms_textures.begin(); it != worms_textures.end(); ++it){
        it->second->render();
    }
    for (auto it = weapons_textures.begin(); it != weapons_textures.end(); ++it){
        it->second->render();
    }

    // Render turn_chrono
    SDL_Rect turn_chrono_rect = turn_chrono.rect.toRect();
    SDL_RenderCopy(this->renderer, turn_chrono.texture, NULL, &turn_chrono_rect);

    // Render dynamite_chrono
    SDL_Rect dynamite_chrono_rect = dynamite_chrono.rect.toRect();
    SDL_RenderCopy(this->renderer, dynamite_chrono.texture, NULL, &dynamite_chrono_rect);

    // Render munitions information
    munitions_info->render();

    // Render change_turn_message
    change_turn_message.render();

    // Render you_win_message
    you_win_message.render();

    SDL_RenderPresent(this->renderer);
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}

void SdlWindow::draw(YouWinDrawable* drawable) {
    Area area(width/2 - YOU_WIN_MESSAGE_SIZE / 2, height/2 - YOU_WIN_MESSAGE_SIZE / 2, YOU_WIN_MESSAGE_SIZE, YOU_WIN_MESSAGE_SIZE);
    you_win_message.set_message_texture(new SdlTexture(texture_factory.get_texture_by_name("you_win"), *this, area));
    you_win_message.set_time_alive(YOU_WIN_MESSAGE_DURATION);
}

void SdlWindow::draw(StartTurnDrawable* drawable) {
    Area area(width/2 - CHANGE_TURN_MESSAGE_SIZE / 2, height/2 - CHANGE_TURN_MESSAGE_SIZE / 2, CHANGE_TURN_MESSAGE_SIZE, CHANGE_TURN_MESSAGE_SIZE);
    change_turn_message.set_message_texture(new SdlTexture(texture_factory.get_texture_by_name("start_turn"), *this, area));
    change_turn_message.set_time_alive(CHANGE_TURN_MESSAGE_DURATION);
}

void SdlWindow::draw(EndTurnDrawable* drawable) {
    Area area(width/2 - CHANGE_TURN_MESSAGE_SIZE / 2, height/2 - CHANGE_TURN_MESSAGE_SIZE / 2, CHANGE_TURN_MESSAGE_SIZE, CHANGE_TURN_MESSAGE_SIZE);
    change_turn_message.set_message_texture(new SdlTexture(texture_factory.get_texture_by_name("end_turn"), *this, area));
    change_turn_message.set_time_alive(CHANGE_TURN_MESSAGE_DURATION);
}

void SdlWindow::draw(TurnTimeDrawable* drawable) {
  std::string value = std::to_string((int)drawable->get_time_left());
  SDL_DestroyTexture(turn_chrono.texture);
  turn_chrono.texture = font_factory.get_texture_big_font(value.c_str(), colors_factory.get_color_by_name("white"), renderer);
}

void SdlWindow::draw(WormDrawable* drawable) {
    size_t id = drawable->get_id();
    double new_x = drawable->get_x() - (WORM_SIZE / 2);
    double new_y = drawable->get_y() - (WORM_SIZE / 2);
    int new_angle = drawable->get_angle();
    size_t new_life_points_q = drawable->get_life_points();
    std::string new_life_points_s(std::to_string(new_life_points_q));
    bool new_facing_right = drawable->get_is_facing_right();
    int team = drawable->get_team();
    if (worms_textures.count(id)){
        WormRepresentation* worm = worms_textures.at(id);
        worm->set_position(new_x, new_y);
        worm->set_angle(new_angle);

        // Actualizo la vida si cambió
        if (worm->get_life_points() != new_life_points_q){
          worm->set_life_texture(font_factory.get_texture_small_font(new_life_points_s.c_str(), colors_factory.get_color_by_id(team), renderer));
          worm->set_life_points(new_life_points_q);
        }

        // Actualizo el lado para el que mira si cambió
        if (worm->is_facing_right() != new_facing_right) {
          SdlTexture* worms_texture = NULL;
          Area area(new_x, new_y, WORM_SIZE, WORM_SIZE);
          if (new_facing_right) {
              worms_texture = new SdlTexture(texture_factory.get_texture_by_name("worm_r"), *this, area);
          } else {
              worms_texture = new SdlTexture(texture_factory.get_texture_by_name("worm_l"), *this, area);
          }
          worm->set_texture(worms_texture);
          worm->set_facing_right(new_facing_right);
        }


    } else {
        SdlTexture* worms_texture = NULL;
        Area area(new_x, new_y, WORM_SIZE, WORM_SIZE);
        if (new_facing_right) {
          worms_texture = new SdlTexture(texture_factory.get_texture_by_name("worm_r"), *this, area);
        } else {
          worms_texture = new SdlTexture(texture_factory.get_texture_by_name("worm_l"), *this, area);
        }
        Area life_area(new_x + 10, new_y - 20, 20, 20);
        SDL_Texture* life_texture = font_factory.get_texture_small_font(new_life_points_s.c_str(), colors_factory.get_color_by_id(team), renderer);
        WormRepresentation* worm = new WormRepresentation(worms_texture, *this, life_texture, life_area,
                                                        new_facing_right, new_life_points_q, new_angle);
        worms_textures[id] = worm;
    }
}

void SdlWindow::draw(WormDeathDrawable* drawable) {
  size_t id = drawable->get_id();
  int team = drawable->get_team();
  if (worms_textures.count(id) == 0) return;
  WormRepresentation* worm = worms_textures.at(id);

  worm->set_life_texture(font_factory.get_texture_small_font(0, colors_factory.get_color_by_id(team), renderer));
  worm->set_life_points(0);
  worm->set_angle(0);

  Area life_area = worm->get_life_position();
  Area area(life_area.getX(), life_area.getY(), WORM_SIZE, WORM_SIZE);
  worm->set_texture(new SdlTexture(texture_factory.get_texture_by_name("grave"), *this, area));
}

void SdlWindow::draw(StageDrawable* drawable) {
  width = drawable->get_width();
  height = drawable->get_height();
  SDL_SetWindowSize(this->window, width, height);
  SDL_Texture* background = texture_factory.load_texture(string(BACKGROUNDS_FOLDER) + drawable->get_background(), renderer);

  Area area(0, 0, width, height);
  this->background_texture = new SdlTexture(background, *this, area);
}

void SdlWindow::draw(BeamDrawable* drawable) {
  double x = drawable->get_x() - (drawable->get_length() / 2);
  double y = drawable->get_y() - (drawable->get_width() / 2);
  Area area(x, y, drawable->get_length(), drawable->get_width());
  SdlTexture* beam = new SdlTexture(texture_factory.get_texture_by_name("beam"), *this, area);
  beam_representation* b_r = new beam_representation({ beam, drawable->get_angle() });
  static_textures.push_back(b_r);
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
  double x = drawable->get_x() - DYNAMITE_SIZE / 2;
  double y = drawable->get_y() - DYNAMITE_SIZE / 2;
  Area area(x, y, DYNAMITE_SIZE, DYNAMITE_SIZE);
  SdlTexture* dynamite = new SdlTexture(texture_factory.get_texture_by_name("dynamite"), *this, area);
  weapons_textures[DYNAMITE_ID] = dynamite;

  // Dynamite chornometer
  std::string time_left = std::to_string((int)drawable->get_time_to_explosion() + 1);
  if (dynamite_chrono.texture)
    SDL_DestroyTexture(dynamite_chrono.texture);
  dynamite_chrono.rect = Area(x + 10, y - 20, 20, 20);
  dynamite_chrono.texture = font_factory.get_texture_small_font(time_left.c_str(), colors_factory.get_color_by_name("red"), renderer);

}

void SdlWindow::draw(DynamiteExplosionDrawable* drawable) {
  delete weapons_textures[DYNAMITE_ID];
  weapons_textures.erase(DYNAMITE_ID);
  SDL_DestroyTexture(dynamite_chrono.texture);
  dynamite_chrono.texture = NULL;
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
      SdlTexture* radiocontrolled = new SdlTexture(texture_factory.get_texture_by_name("radioControlled"), *this, area);
      weapons_textures[id] = radiocontrolled;
  }
}

void SdlWindow::draw(RadiocontrolledExplosionDrawable* drawable) {
  delete weapons_textures[drawable->get_id()];
  weapons_textures.erase(drawable->get_id());
}

void SdlWindow::draw(MunitionsDrawable* drawable){
  munitions_info->set_munitions(drawable->get_dynamite_munitions(),\
                               drawable->get_radiocontrolled_munitions(),\
                               drawable->get_teletransportation_munitions());
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
        delete it->second;
    }

    SDL_DestroyTexture(turn_chrono.texture);

    delete munitions_info;
}
