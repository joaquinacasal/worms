#ifndef __STAGENOTIFICATION__
#define __STAGENOTIFICATION__

#include "server_INotification.h"

class StageNotification : public INotification {
private:
    ClientHandler* client;
    int width;
    int height;
    std::string background;

    StageNotification(const StageNotification&) = delete;
    StageNotification& operator=(const StageNotification&) = delete;
public:
    StageNotification(ClientHandler* client, int width, int height, std::string background);

    void run();

    ~StageNotification() = default;
};


#endif //__STAGENOTIFICATION__
