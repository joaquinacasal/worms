#include "client_MunitionsInformation.h"

MunitionsInformation::MunitionsInformation(double x, double y,\
                FontFactory& _font_factory, ColorsFactory& _colors_factory,\
                SDL_Renderer* renderer) :\
                font_factory(_font_factory), colors_factory(_colors_factory) {

  std::string title_message = "MUNICIONES";
  titulo = font_factory.get_texture_small_font(title_message.c_str(), colors_factory.get_color_by_name("black"), renderer);
  rect_titulo = Area(x, y, BOX_WIDTH, BOX_HEIGHT);
  dinamita = NULL;
  rect_dinamita = Area(x, y + BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT);
  teledirigido = NULL;
  rect_teledirigido = Area(x, y + BOX_HEIGHT * 2, BOX_WIDTH, BOX_HEIGHT);
  teletransportacion = NULL;
  rect_teletransportacion = Area(x, y + BOX_HEIGHT * 3, BOX_WIDTH, BOX_HEIGHT);

  last_dynamite_munitions = 0;
  last_radiocontrolled_munitions = 0;
  last_teletransportation_munitions = 0;
  this->renderer = renderer;
}

int MunitionsInformation::render() {
  SDL_Rect munitions_info_rect_titulo = rect_titulo.toRect();
  SDL_Rect munitions_info_rect_dinamita = rect_dinamita.toRect();
  SDL_Rect munitions_info_rect_teledirigido = rect_teledirigido.toRect();
  SDL_Rect munitions_info_rect_teletransportacion = rect_teletransportacion.toRect();
  SDL_RenderCopy(this->renderer, titulo, NULL, &munitions_info_rect_titulo);
  SDL_RenderCopy(this->renderer, dinamita, NULL, &munitions_info_rect_dinamita);
  SDL_RenderCopy(this->renderer, teledirigido, NULL, &munitions_info_rect_teledirigido);
  SDL_RenderCopy(this->renderer, teletransportacion, NULL, &munitions_info_rect_teletransportacion);
}

void MunitionsInformation::set_dynamite_munitions(int dynamite_q) {
  std::string dynamite_m = std::to_string(dynamite_q);
  if (dynamite_m == "-1") dynamite_m = "INFINITO";

  std::string dynamite_message = "Dinamita: " + dynamite_m;
  if (dinamita)
    SDL_DestroyTexture(dinamita);
  dinamita = font_factory.get_texture_small_font(dynamite_message.c_str(), colors_factory.get_color_by_name("black"), renderer);
  last_dynamite_munitions = dynamite_q;
}

void MunitionsInformation::set_radiocontrolled_munitions(int radiocontrolled_q) {
  std::string radiocontrolled_m = std::to_string(radiocontrolled_q);
  if (radiocontrolled_m == "-1") radiocontrolled_m = "INFINITO";

  std::string radiocontrolled_message = "Teledirigido: " + radiocontrolled_m;
  if (teledirigido)
    SDL_DestroyTexture(teledirigido);
  teledirigido = font_factory.get_texture_small_font(radiocontrolled_message.c_str(), colors_factory.get_color_by_name("black"), renderer);
  last_radiocontrolled_munitions = radiocontrolled_q;
}

void MunitionsInformation::set_teletransportation_munitions(int teletransportation_q) {
  std::string teletransportation_m = std::to_string(teletransportation_q);
  if (teletransportation_m == "-1") teletransportation_m = "INFINITO";

  std::string teletransportation_message = "Teletransportacion: " + teletransportation_m;
  if (teletransportacion)
    SDL_DestroyTexture(teletransportacion);
  teletransportacion = font_factory.get_texture_small_font(teletransportation_message.c_str(), colors_factory.get_color_by_name("black"), renderer);
  last_teletransportation_munitions = teletransportation_q;
}

void MunitionsInformation::set_munitions(int dynamite_q, int radiocontrolled_q, int teletransportation_q) {
  if (last_dynamite_munitions != dynamite_q)
    set_dynamite_munitions(dynamite_q);
  if (last_radiocontrolled_munitions != radiocontrolled_q)
    set_radiocontrolled_munitions(radiocontrolled_q);
  if (last_teletransportation_munitions != teletransportation_q)
    set_teletransportation_munitions(teletransportation_q);
}

MunitionsInformation::~MunitionsInformation(){
  if (titulo)
    SDL_DestroyTexture(titulo);
  if (dinamita)
    SDL_DestroyTexture(dinamita);
  if (teledirigido)
    SDL_DestroyTexture(teledirigido);
  if (teletransportacion)
    SDL_DestroyTexture(teletransportacion);
}
