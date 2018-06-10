#include <iostream>
#include "../common/common_SocketProtocol.h"
#include "../common/common_SafeQueue.h"
#include "../common/common_BlockingQueue.h"
#include "client_ConsoleDrawer.h"
#include "client_DrawableFactory.h"
#include "client_CapturedEventFactory.h"
#include "client_CapturedEventSender.h"

bool is_valid_coordinate(int x, int y){
  if (x < 0 || y < 0) return false;
  return true;
}


int main(int argc, char* argv[]){
  SocketProtocol sp("127.0.0.1", argv[1]);
  SafeQueue<IDrawable*> safe_queue;
  BlockingQueue<ICapturedEvent*> blocking_queue;

  ConsoleDrawer console_drawer(safe_queue);
  console_drawer.start();
  DrawableFactory drawable_factory(sp, safe_queue);
  drawable_factory.start();

  CapturedEventSender captured_event_sender(blocking_queue);
  captured_event_sender.start();
  CapturedEventFactory captured_event_factory(sp, blocking_queue);

  int x, y;
  while (true){
      std::cout << "Ingresá un comando: ";
      std::string input;
      std::cin >> input;
      if (!drawable_factory.is_connected()) break;
      if (input.length() != 1) continue;
      if (input.at(0) == 'q') {
        captured_event_factory.create_closed_connection_event();
        break;
      }
      switch (input.at(0)) {
        case 'd': captured_event_factory.create_move_right_event(); break; // Right arrow
        case 'a': captured_event_factory.create_move_left_event(); break;  // Left arrow
        case 's': captured_event_factory.create_stop_moving_event(); break; // Down arrow
        case 'w': captured_event_factory.create_jump_forward_event(); break;       // Enter
        case 'r': captured_event_factory.create_jump_backward_event(); break;   // Backspace
        case '7': captured_event_factory.create_dynamite_event(); break; // Dynamite
        case '8': // Radiocontrolled
          std::cout << "Ingresá la coordenada:\nX: ";
          std::cin >> x;
          std::cout << "Y: ";
          std::cin >> y;
          if (is_valid_coordinate(x, y))
            captured_event_factory.create_radiocontrolled_event(x, y);
          break;
        case '9': // Teletransportation
          std::cout << "Ingresá la coordenada:\nX: ";
          std::cin >> x;
          std::cout << "Y: ";
          std::cin >> y;
          if (is_valid_coordinate(x, y))
            captured_event_factory.create_teletransportation_event(x, y);
          break;
        default:
          std::cout << "Comando no reconocido\n";
          break;
      }
  }
  drawable_factory.join();
  console_drawer.stop();
  console_drawer.join();
  captured_event_sender.stop();
  captured_event_sender.join();
  return 0;
}
