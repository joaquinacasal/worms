#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "../common/common_Thread.h"
#include "../common/common_SafeQueue.h"
#include "client_SdlTexture.h"
#include "drawables/client_IDrawable.h"
#include "drawables/client_BeamDrawable.h"
#include "drawables/client_ClosedConnectionDrawable.h"
#include "drawables/client_DynamiteDrawable.h"
#include "drawables/client_DynamiteExplosionDrawable.h"
#include "drawables/client_EndTurnDrawable.h"
#include "drawables/client_RadiocontrolledDrawable.h"
#include "drawables/client_RadiocontrolledExplosionDrawable.h"
#include "drawables/client_StageDrawable.h"
#include "drawables/client_StartTurnDrawable.h"
#include "drawables/client_TurnTimeDrawable.h"
#include "drawables/client_YouWinDrawable.h"
#include "drawables/client_WormDrawable.h"
#include "drawables/client_WormDeathDrawable.h"
#include "drawables/client_YouLoseDrawable.h"
#include "drawables/client_MunitionsDrawable.h"
#include "client_WormRepresentation.h"
#include "client_Message.h"
#include "client_MunitionsInformation.h"
#include "client_FontFactory.h"
#include "client_ColorsFactory.h"
#include "client_TextureFactory.h"
#include "client_Camera.h"

#define WORM_SIZE 36
#define DYNAMITE_SIZE 36
#define RADIOCONTROLLED_SIZE 36
#define DYNAMITE_ID -1
#define CHANGE_TURN_MESSAGE_DURATION 600
#define CHANGE_TURN_MESSAGE_SIZE 450
#define YOU_WIN_MESSAGE_DURATION 6000
#define YOU_WIN_MESSAGE_SIZE 900
#define YOU_LOSE_MESSAGE_DURATION 8000
#define YOU_LOSE_MESSAGE_SIZE 1000
#define WATER_HEIGTH 80

class SdlWindow;
class SdlTexture;
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
class WormDeathDrawable;
class YouWinDrawable;
class YouLoseDrawable;
class MunitionsDrawable;
class WormRepresentation;
class Message;
class MunitionsInformation;
class FontFactory;
class ColorsFactory;
class TextureFactory;

struct beam_representation {
  SdlTexture* beam_texture;
  int angle;
};

struct chrono_representation {
  SDL_Texture* texture;
  Area rect;
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

    Message change_turn_message;
    Message you_win_message;
    Message you_lose_message;
    chrono_representation turn_chrono;
    chrono_representation dynamite_chrono;
    MunitionsInformation* munitions_info;
    FontFactory font_factory;
    ColorsFactory colors_factory;
    TextureFactory texture_factory;
    SdlTexture* background_texture;
    Camera camera;
    std::mutex& camera_mutex;

    map<int, WormRepresentation*> worms_textures;
    map<int, SdlTexture*> weapons_textures;
    std::vector<beam_representation*> beams_textures;
    SdlTexture* water_representation;


    void draw(IDrawable* drawable);
    SDL_Texture* loadTexture(const std::string &filename);

    explicit SdlWindow(const ConsoleDrawer&) = delete;
    SdlWindow& operator=(const ConsoleDrawer&) = delete;

public:
    SdlWindow(SafeQueue<IDrawable*>& _safe_queue, std::mutex& camera_mutex);
    SdlWindow(SdlWindow&& other) = default;
    void draw(StartTurnDrawable* drawable);
    void draw(EndTurnDrawable* drawable);
    void draw(TurnTimeDrawable* drawable);
    void draw(WormDrawable* drawable);
    void draw(WormDeathDrawable* drawable);
    void draw(StageDrawable* drawable);
    void draw(BeamDrawable* drawable);
    void draw(DynamiteDrawable* drawable);
    void draw(DynamiteExplosionDrawable* drawable);
    void draw(RadiocontrolledDrawable* drawable);
    void draw(RadiocontrolledExplosionDrawable* drawable);
    void draw(YouWinDrawable* drawable);
    void draw(YouLoseDrawable* drawable);
    void draw(MunitionsDrawable* drawable);
    void draw(ClosedConnectionDrawable* drawable);
    void run() override;
    void stop();
    bool is_connected();
    void fill();
    void fill(int r, int g, int b, int alpha);
    void render();
    void move_camera(CameraMovement movement);
    SDL_Renderer* getRenderer() const;
    ~SdlWindow();
};

#endif
