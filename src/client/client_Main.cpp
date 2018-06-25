#include <iostream>
#include <mutex>
#include <SDL2/SDL.h>
#include "client_SdlWindow.h"
#include "../common/common_SocketProtocol.h"
#include "../common/common_SafeQueue.h"
#include "../common/common_BlockingQueue.h"
#include "client_ConsoleDrawer.h"
#include "drawables/client_DrawableFactory.h"
#include "capturedEvents/client_CapturedEventFactory.h"
#include "capturedEvents/client_CapturedEventSender.h"
#include "../common/common_Lock.h"

enum InputState { WAITING_COMMAND, WAITING_RADIO_CLICK, WAITING_TELE_CLICK };

int main(int argc, char* argv[]){
  SocketProtocol sp("127.0.0.1", argv[1]);
  SafeQueue<IDrawable*> safe_queue;
  BlockingQueue<ICapturedEvent*> blocking_queue;

  //ConsoleDrawer console_drawer(safe_queue);
  //console_drawer.start();
  //SdlWindow window(safe_queue, 1920, 1080);
  std::mutex camera_mutex;
  SdlWindow window(safe_queue, camera_mutex);
  window.start();
  DrawableFactory drawable_factory(sp, safe_queue);
  drawable_factory.start();

  CapturedEventSender captured_event_sender(blocking_queue);
  captured_event_sender.start();
  CapturedEventFactory captured_event_factory(sp, blocking_queue);

  window.fill();
  InputState state = WAITING_COMMAND;
  int x, y;
  while (true){
      if (!drawable_factory.is_connected()) break;
      SDL_Event event;
      SDL_WaitEvent(&event);
      switch (event.type) {
        case SDL_KEYUP: {
          SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
          switch (keyEvent.keysym.sym) {
            case SDLK_d: {
              captured_event_factory.create_move_right_event();
              state = WAITING_COMMAND;
              break;
            }
            case SDLK_a: {
              captured_event_factory.create_move_left_event();
              state = WAITING_COMMAND;
              break;
            }
            case SDLK_s: {
              captured_event_factory.create_stop_moving_event();
              state = WAITING_COMMAND;
              break;
            }
            case SDLK_w: {
              captured_event_factory.create_jump_forward_event();
              state = WAITING_COMMAND;
              break;
            }
            case SDLK_BACKSPACE: {
              captured_event_factory.create_jump_backward_event();
              state = WAITING_COMMAND;
              break;
            }
            case SDLK_UP: {
              Lock camera_lock(camera_mutex);
              window.move_camera(UP);
              break;
            }
            case SDLK_LEFT: {
              Lock camera_lock(camera_mutex);
              window.move_camera(LEFT);
              break;
            }
            case SDLK_DOWN: {
              Lock camera_lock(camera_mutex);
              window.move_camera(DOWN);
              break;
            }
            case SDLK_RIGHT: {
              Lock camera_lock(camera_mutex);
              window.move_camera(RIGHT);
              break;
            }
            case SDLK_b: {
              captured_event_factory.create_dynamite_event();
              state = WAITING_COMMAND;
              break;
            }
            case SDLK_r: {
              state = WAITING_RADIO_CLICK;
              break;
            }
            case SDLK_t: {
              state = WAITING_TELE_CLICK;
              break;
            }
            case SDLK_q: {
              captured_event_factory.create_closed_connection_event();
              break;
            }
          }
        }
        case SDL_MOUSEBUTTONDOWN: {
          if (event.button.button != SDL_BUTTON_LEFT ||
          (state != WAITING_RADIO_CLICK && state != WAITING_TELE_CLICK)){
            break;
          }
          SDL_GetMouseState(&x, &y);
          if (state == WAITING_RADIO_CLICK){
            captured_event_factory.create_radiocontrolled_event(x, y, \
                                  drawable_factory.get_scenario_height());
          } else {
            captured_event_factory.create_teletransportation_event(x, y,\
                                  drawable_factory.get_scenario_height());
          }
          state = WAITING_COMMAND;
          break;
        }
      }
  }
  drawable_factory.join();
  //console_drawer.stop();
  //console_drawer.join();
  window.stop();
  window.join();
  captured_event_sender.stop();
  captured_event_sender.join();
  return 0;
}
