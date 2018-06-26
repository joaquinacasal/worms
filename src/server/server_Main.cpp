#include <iostream>
#include <string>
#include "server_GameThread.h"
#include "config.h"

int main(int argc, char* argv[]) try {
  GameThread gt(argv[1], string(SCENARIOS_FOLDER) + \
                string(argv[3]), atoi(argv[2]));
  gt.start_connection();
  while (true){
      std::string input;
      std::cin >> input;
      if (input.length() == 1 && input.at(0) == 'q'){
        if (gt.is_alive()) gt.stop();
        break;
      }
  }
  if (gt.was_connected()) gt.join();
  return 0;
} catch (std::exception& ex){
    std::cout << ex.what() << std::endl;
    return -1;
} catch (...){
  std::cout << "Ocurrió un problema" << std::endl;
  return -1;
}
