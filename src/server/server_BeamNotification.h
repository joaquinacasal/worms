#ifndef __BEAMNOTIFICATION__
#define __BEAMNOTIFICATION__

#include "server_INotification.h"

class BeamNotification : public INotification {
private:
    ClientHandler* client;
    int x;
    int y;
    int length;
    int width;
    int angle;

    BeamNotification(const BeamNotification&) = delete;
    BeamNotification& operator=(const BeamNotification&) = delete;
public:
    BeamNotification(ClientHandler* client, int x, int y, int length, \
                                                    int width, int angle);

    void run();

    ~BeamNotification() = default;
};


#endif //__BEAMNOTIFICATION__
