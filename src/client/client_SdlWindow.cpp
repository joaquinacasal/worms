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

SdlWindow::SdlWindow(SafeQueue<IDrawable*>& _safe_queue) :
        safe_queue(_safe_queue), connected(true),\
        change_turn_message(NULL, 0), you_win_message(NULL, 0),\
        you_lose_message(NULL, 0) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    errCode = SDL_CreateWindowAndRenderer(
        0, 0, SDL_RENDERER_ACCELERATED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED,
        &this->window, &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana", SDL_GetError());
    }
    SDL_GetWindowSize(this->window, &width, &height);
    camera.set_position(Area(0, 0, 1980, 1080)); //TODO: reemplazar por width y height, que no funciona

    // Cronometro del turno.
    turn_chrono = {font_factory.get_texture_big_font("60.0", \
                   colors_factory.get_color_by_name("white"), renderer),\
                   Area(10, 10, 100, 80)};
    dynamite_chrono = {NULL, Area(0, 0, 0, 0)};
    texture_factory.init(renderer);
    background_texture = NULL;
    munitions_info = new MunitionsInformation(10, 100, font_factory, \
                                              colors_factory, renderer);
    std::cout << "Fin del constructor SdlWindow" << std::endl;
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
      this->background_texture->render(camera);
}

void SdlWindow::render() {
    for (size_t i = 0; i < beams_textures.size(); ++i){
      beams_textures[i]->beam_texture->render(camera, beams_textures[i]->angle);
    }
    water_representation->render(camera);
    for (auto it = worms_textures.begin(); it != worms_textures.end(); ++it){
        it->second->render(camera);
    }
    for (auto it = weapons_textures.begin(); it != weapons_textures.end();\
                                                                        ++it){
        it->second->render(camera);
    }

    // Render turn_chrono
    SDL_Rect turn_chrono_rect = turn_chrono.rect.toRect();
    SDL_RenderCopy(this->renderer, turn_chrono.texture, NULL,\
                   &turn_chrono_rect);

    // Render dynamite_chrono
    Area dynamite_chrono_pos = camera.adapt_area(dynamite_chrono.rect);
    SDL_Rect dynamite_chrono_rect = dynamite_chrono_pos.toRect();
    SDL_RenderCopy(this->renderer, dynamite_chrono.texture, NULL, \
                   &dynamite_chrono_rect);

    // Render munitions information
    munitions_info->render();

    // Render change_turn_message
    change_turn_message.render(camera);

    // Render you_win_message
    you_win_message.render(camera);

    // Render you_lose_message
    you_lose_message.render(camera);

    SDL_RenderPresent(this->renderer);
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}

void SdlWindow::draw(YouWinDrawable* drawable) {
    Area area(0, 0, YOU_WIN_MESSAGE_SIZE, YOU_WIN_MESSAGE_SIZE);
    you_win_message.set_message_texture(new SdlTexture(texture_factory.\
                                get_texture_by_name("you_win"), *this, area));
    you_win_message.set_time_alive(YOU_WIN_MESSAGE_DURATION);
}

void SdlWindow::draw(YouLoseDrawable* drawable) {
    Area area(0, 0, YOU_LOSE_MESSAGE_SIZE, YOU_LOSE_MESSAGE_SIZE);
    you_lose_message.set_message_texture(new SdlTexture(texture_factory.\
                                get_texture_by_name("you_lose"), *this, area));
    you_lose_message.set_time_alive(YOU_LOSE_MESSAGE_DURATION);
    printf("Perdiste!\n");
}

void SdlWindow::draw(StartTurnDrawable* drawable) {
    Area area(0, 0, CHANGE_TURN_MESSAGE_SIZE, CHANGE_TURN_MESSAGE_SIZE);
    change_turn_message.set_message_texture(new SdlTexture(texture_factory.\
                              get_texture_by_name("start_turn"), *this, area));
    change_turn_message.set_time_alive(CHANGE_TURN_MESSAGE_DURATION);
}

void SdlWindow::draw(EndTurnDrawable* drawable) {
    Area area(0, 0, CHANGE_TURN_MESSAGE_SIZE, CHANGE_TURN_MESSAGE_SIZE);
    change_turn_message.set_message_texture(new SdlTexture(texture_factory.\
                              get_texture_by_name("end_turn"), *this, area));
    change_turn_message.set_time_alive(CHANGE_TURN_MESSAGE_DURATION);

    for (const auto& sm_pair : worms_textures){
      sm_pair.second->deselect_worm();
    }
}

void SdlWindow::draw(TurnTimeDrawable* drawable) {
  std::string value = std::to_string((int)drawable->get_time_left());
  SDL_DestroyTexture(turn_chrono.texture);
  turn_chrono.texture = font_factory.get_texture_big_font(value.c_str(),\
                          colors_factory.get_color_by_name("white"), renderer);
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
    WormState state;
    if (drawable->is_still())
      state = RESTING;
    else if (drawable->is_moving())
      state = WALKING;
    else if (drawable->is_flying())
      state = JUMPING;
    else
      state = DEAD;
    bool is_the_selected_worm = drawable->is_the_selected_worm();

    if (worms_textures.count(id)){
        WormRepresentation* worm = worms_textures.at(id);
        worm->set_position(new_x, new_y);
        worm->set_life_points(new_life_points_q, font_factory.\
                              get_texture_small_font(new_life_points_s.c_str(),\
                              colors_factory.get_color_by_id(team), renderer));
        worm->set_state(state, new_angle, new_facing_right);
        if (is_the_selected_worm)
          worm->select_worm();
        else
          worm->deselect_worm();
    } else {
        Area position(new_x, new_y, WORM_SIZE, WORM_SIZE);
        SDL_Texture* life_texture = font_factory.get_texture_small_font(\
                                    new_life_points_s.c_str(),\
                                    colors_factory.get_color_by_id(team),\
                                    renderer);
        WormRepresentation* worm = new WormRepresentation(state, position, \
                    *this, life_texture, new_facing_right, new_life_points_q,\
                    new_angle, texture_factory, is_the_selected_worm);
        worms_textures[id] = worm;
    }
}

void SdlWindow::draw(WormDeathDrawable* drawable) {
  size_t id = drawable->get_id();
  int team = drawable->get_team();
  if (worms_textures.count(id) == 0) return;
  WormRepresentation* worm = worms_textures.at(id);

  worm->set_life_points(0, font_factory.get_texture_small_font(0, \
                              colors_factory.get_color_by_id(team), renderer));
  worm->set_state(DEAD, 0, false);
  Area life_area = worm->get_life_position();
  worm->set_position(life_area.getX(), life_area.getY());
}

void SdlWindow::draw(StageDrawable* drawable) {
  width = drawable->get_width();
  height = drawable->get_height();
  camera.set_map_size(width, height);
  SDL_Texture* background = texture_factory.load_texture(\
                              string(BACKGROUNDS_FOLDER) + \
                              drawable->get_background(), renderer);

  Area area(0, 0, width, height);
  this->background_texture = new SdlTexture(background, *this, area);

  // Water
  Area water_area(0, height - WATER_HEIGTH, width, WATER_HEIGTH);
  water_representation = new SdlTexture(texture_factory.\
                              get_texture_by_name("water"), *this, water_area);
}

void SdlWindow::draw(BeamDrawable* drawable) {
  double x = drawable->get_x() - (drawable->get_length() / 2);
  double y = drawable->get_y() - (drawable->get_width() / 2);
  Area area(x, y, drawable->get_length(), drawable->get_width());
  SdlTexture* beam = new SdlTexture(texture_factory.\
                                    get_texture_by_name("beam"), *this, area);
  beam_representation* b_r = new beam_representation({beam,\
                                                      drawable->get_angle()});
  beams_textures.push_back(b_r);
}

void SdlWindow::draw(DynamiteDrawable* drawable) {
  double x = drawable->get_x() - DYNAMITE_SIZE / 2;
  double y = drawable->get_y() - DYNAMITE_SIZE / 2;
  Area area(x, y, DYNAMITE_SIZE, DYNAMITE_SIZE);
  SdlTexture* dynamite = new SdlTexture(texture_factory.\
                                get_texture_by_name("dynamite"), *this, area);
  weapons_textures[DYNAMITE_ID] = dynamite;

  // Dynamite chornometer
  std::string time_left = std::to_string((int)drawable->\
                                                  get_time_to_explosion() + 1);
  if (dynamite_chrono.texture){
    SDL_DestroyTexture(dynamite_chrono.texture);
  }
  dynamite_chrono.rect = Area(x + 10, y - 20, 20, 20);
  dynamite_chrono.texture = font_factory.get_texture_small_font(\
                              time_left.c_str(), \
                              colors_factory.get_color_by_name("red"),\
                              renderer);
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
      SdlTexture* radiocontrolled = new SdlTexture(\
          texture_factory.get_texture_by_name("radioControlled"), *this, area);
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
  while (connected) {
    fill();
    if (safe_queue.pop(drawable)){
      draw(drawable);
      delete drawable;
    }
    render();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

bool SdlWindow::is_connected(){
  return connected;
}

void SdlWindow::stop(){
  connected = false;
}

void SdlWindow::move_camera(CameraMovement movement){
    camera.move(movement);
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
    while (safe_queue.pop(drawable)) {
      delete drawable;
    }

    for (int i = 0; i < beams_textures.size(); i++){
        delete beams_textures[i];
    }

    for (auto it = worms_textures.begin(); it != worms_textures.end(); ++it){
        delete it->second;
    }

    SDL_DestroyTexture(turn_chrono.texture);

    delete munitions_info;
}
