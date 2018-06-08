#include "server_Teletransportation.h"

Teletransportation::Teletransportation(){

}

bool Teletransportation::teletransport_to(Worm* worm, int x, int y){
  if (munitions == 0) return false;
  worm->teletransport(x, y);
  --munitions;
  return true;
}

size_t Teletransportation::get_munitions(){
  return munitions;
}
