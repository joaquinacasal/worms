#include <iostream>
#include <iomanip>
#include "client_ConsoleDrawer.h"

ConsoleDrawer::ConsoleDrawer(SafeQueue<IDrawable*>& _safe_queue) : \
                              safe_queue(_safe_queue) {
  connected = true;
}

void ConsoleDrawer::draw(StartTurnDrawable* drawable) {
  std::cout << "\n\n\n\n\n\n\n\n\nInicio de tu turno\n";
}

void ConsoleDrawer::draw(EndTurnDrawable* drawable) {
  std::cout << "Fin de tu turno\n";
}

void ConsoleDrawer::draw(TurnTimeDrawable* drawable) {
  std::cout << "Quedan " << std::fixed << std::setprecision(2) << drawable->get_time_left() << " segundos para que finalice el turno.\n";
}

void ConsoleDrawer::draw(WormDrawable* drawable) {
  std::cout << "Worm con id: " << drawable->get_id() << ", del equipo " << drawable->get_team() <<", vida: " << drawable->get_life_points() << ", posición (" << std::fixed << std::setprecision(2) << drawable->get_x() << ", " << std::fixed << std::setprecision(2) << drawable->get_y() << "), ángulo: " << drawable->get_angle() << ". Mirando hacia la ";
  if (drawable->get_is_facing_right()) std::cout << "derecha.\n";
  else std::cout << "izquierda.\n";
  std::string estado;
  if (drawable->is_still()) estado = "quieto";
  if (drawable->is_moving()) estado = "moviendose";
  if (drawable->is_flying()) estado = "volando";
  std::cout << "El estado es " << estado << '\n';
  if (drawable->is_the_selected_worm())
  std::cout << "Es el gusano actual.\n";
}

void ConsoleDrawer::draw(StageDrawable* drawable) {
  std::cout << "El escenario tiene ancho: " << drawable->get_width() << " y alto: " << drawable->get_height() << ".\n";
  std::cout << "El nombre de la foto es '" << drawable->get_background() << "'.\n";
}

void ConsoleDrawer::draw(BeamDrawable* drawable) {
  std::cout << "Viga en la posición (" << drawable->get_x() << ", " << drawable->get_y() << "), ángulo: " << drawable->get_angle() << ". Largo de " << drawable->get_length() << ", ancho de " << drawable->get_width() << ".\n";
}

void ConsoleDrawer::draw(DynamiteDrawable* drawable) {
  std::cout << "Dinamita en la posición (" << drawable->get_x() << ", " << drawable->get_y() << "), explota en: " << std::fixed << std::setprecision(2) << drawable->get_time_to_explosion() << ".\n";
}

void ConsoleDrawer::draw(DynamiteExplosionDrawable* drawable) {
  std::cout << "Boom\n";
}

void ConsoleDrawer::draw(RadiocontrolledDrawable* drawable){
  std::cout << "Teledirigido en (" << std::fixed << std::setprecision(2) << drawable->get_x() << ", " << std::fixed << std::setprecision(2) << drawable->get_y() << ").\n";
}

void ConsoleDrawer::draw(RadiocontrolledExplosionDrawable* drawable){
  std::cout << "Boom de la bomba con id " << drawable->get_id() << '\n';
}

void ConsoleDrawer::draw(WormDeathDrawable* drawable){
  std::cout << "Murio el gusano con id " << drawable->get_id() << ", del equipo " << drawable->get_team() << '\n';
}

void ConsoleDrawer::draw(YouWinDrawable* drawable){
  std::cout << "Ganaste!\n";
}

void ConsoleDrawer::draw(MunitionsDrawable* drawable){
  std::cout << "Dinamita: " << drawable->get_dynamite_munitions() << ", teledirigido: " << drawable->get_radiocontrolled_munitions() << ", y teletransportacion: " << drawable->get_teletransportation_munitions() << ".\n";
}

void ConsoleDrawer::draw(ClosedConnectionDrawable* drawable) {
  std::cout << "Se cerró la conección desde el servidor.\n";
}

void ConsoleDrawer::draw(IDrawable* drawable) {
  drawable->be_drawn_by_console(this);
}


void ConsoleDrawer::run(){
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

bool ConsoleDrawer::is_connected(){
  return connected;
}


void ConsoleDrawer::stop(){
  connected = false;
}

ConsoleDrawer::~ConsoleDrawer(){
  IDrawable* drawable = NULL;
  while(safe_queue.pop(drawable)) {
      delete drawable;
  }
}
