#include "server_Teletransportation.h"

Teletransportation::Teletransportation(){
  was_used = false;
}

bool Teletransportation::teletransport_to(Worm* worm, int x, int y){
  if (munitions == 0) return false;
  worm->teletransport(x, y);
  --munitions;
  was_used = true;
  return true;
}

int Teletransportation::get_munitions(){
  return munitions;
}

bool Teletransportation::was_teletransportation_used(){
  bool aux = was_used;
  was_used = false;
  return aux;
}
