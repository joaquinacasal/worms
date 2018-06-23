#ifndef __MUNITIONSINFORMATION__
#define __MUNITIONSINFORMATION__

#include "client_SdlTexture.h"
#include "client_FontFactory.h"
#include "client_ColorsFactory.h"

#define BOX_WIDTH 180
#define BOX_HEIGHT 40

class Area;


class MunitionsInformation {
public:
    MunitionsInformation(double x, double y, FontFactory& _font_factory,\
        ColorsFactory& _colors_factory, SDL_Renderer* renderer);
    int render();
    void set_munitions(int dynamite_q, int radiocontrolled_q, int teletransportation_q);
    ~MunitionsInformation();

private:
  FontFactory& font_factory;
  ColorsFactory& colors_factory;
  SDL_Renderer* renderer;

  SDL_Texture* titulo;
  Area rect_titulo;
  SDL_Texture* dinamita;
  Area rect_dinamita;
  SDL_Texture* teledirigido;
  Area rect_teledirigido;
  SDL_Texture* teletransportacion;
  Area rect_teletransportacion;

  int last_dynamite_munitions;
  int last_radiocontrolled_munitions;
  int last_teletransportation_munitions;

  void set_dynamite_munitions(int dynamite_q);
  void set_radiocontrolled_munitions(int radiocontrolled_q);
  void set_teletransportation_munitions(int teletransportation_q);
};

#endif //__MUNITIONSINFORMATION__
