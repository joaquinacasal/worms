#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "../common/common_Thread.h"
#include "../common/common_SafeQueue.h"
#include "client_Area.h"
#include "client_SdlTexture.h"
#include "client_IDrawable.h"
#include "client_BeamDrawable.h"
#include "client_ClosedConnectionDrawable.h"
#include "client_DynamiteDrawable.h"
#include "client_DynamiteExplosionDrawable.h"
#include "client_EndTurnDrawable.h"
#include "client_RadiocontrolledDrawable.h"
#include "client_RadiocontrolledExplosionDrawable.h"
#include "client_StageDrawable.h"
#include "client_StartTurnDrawable.h"
#include "client_TurnTimeDrawable.h"
#include "client_WormDrawable.h"

#define WORM_SIZE 40
#define DYNAMITE_SIZE 40
#define RADIOCONTROLLED_SIZE 40
#define DYNAMITE_ID -1
#define CHANGE_TURN_MESSAGE_DURATION 600
#define CHANGE_TURN_MESSAGE_SIZE 500
#define WORM_ASSET "worm.png"
#define BEAM_ASSET "grdl0.png"
#define DYNAMITE_ASSET "dynamite.png"
#define RADIOCONTROLLED_ASSET "radiocontrolled.png"
#define START_TURN_ASSET "startTurn.png"
#define FINISH_TURN_ASSET "finishTurn.png"
#define FONT_ASSET "BebasNeueRegular.ttf"

class SdlWindow;
class SdlTexture;
class Area;
class IDrawable;
class BeamDrawable;
class ClosedConnectionDrawable;
class DynamiteDrawable;
class DynamiteExplosionDrawable;
class EndTurnDrawable;
class RadiocontrolledDrawable;
class RadiocontrolledExplosionDrawable;
class StageDrawable;
class StartTurnDrawable;
class TurnTimeDrawable;
class WormDrawable;

struct worm_representation {
  SdlTexture* worms_texture;
  SDL_Rect life_rect;
  SDL_Texture* life_texture;
};

struct turn_message {
  SdlTexture* message_texture;
  int time_alive;
};

using std::map;

class SdlWindow : public Thread {
private:
    SafeQueue<IDrawable*>& safe_queue;
    int width;
    int height;
    bool connected;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    map<int, worm_representation*> worms_textures;
    map<int, SdlTexture*> weapons_textures;
    std::vector<SdlTexture*> static_textures;

    turn_message change_turn_message;
    SDL_Texture* turn_chrono_texture;
    SDL_Color White;
    TTF_Font* Sans_big;
    TTF_Font* Sans_small;
    SDL_Rect turn_chrono_rect;

    SDL_Texture* worm_texture;
    SDL_Texture* beam_texture;
    SDL_Texture* start_turn_texture;
    SDL_Texture* end_turn_texture;
    SDL_Texture* dynamite_texture;
    SDL_Texture* radioControlled_texture;

    void draw(IDrawable* drawable);
    SDL_Texture* loadTexture(const std::string &filename);

    SdlWindow(const ConsoleDrawer&) = delete;
    SdlWindow& operator=(const ConsoleDrawer&) = delete;
public:
    SdlWindow(SafeQueue<IDrawable*>& _safe_queue, int width, int height);
    SdlWindow(SdlWindow&& other) = default;
    void draw(StartTurnDrawable* drawable);
    void draw(EndTurnDrawable* drawable);
    void draw(TurnTimeDrawable* drawable);
    void draw(WormDrawable* drawable);
    void draw(StageDrawable* drawable);
    void draw(BeamDrawable* drawable);
    void draw(DynamiteDrawable* drawable);
    void draw(DynamiteExplosionDrawable* drawable);
    void draw(RadiocontrolledDrawable* drawable);
    void draw(RadiocontrolledExplosionDrawable* drawable);
    void draw(ClosedConnectionDrawable* drawable);
    void run() override;
    void stop();
    bool is_connected();
    void fill();
    void fill(int r, int g, int b, int alpha);
    void render();
    SDL_Renderer* getRenderer() const;
    ~SdlWindow();
};

#endif
