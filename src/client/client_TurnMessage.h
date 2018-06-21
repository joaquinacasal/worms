#ifndef __TURNMESSAGE__
#define __TURNMESSAGE__

#include "client_SdlTexture.h"

class TurnMessage {
public:
    TurnMessage(SdlTexture* message_texture, int time);
    int render();
    void set_message_texture(SdlTexture* message_texture);
    void set_time_alive(int time);
    ~TurnMessage();

private:
    SdlTexture* message_texture;
    int time_alive;
};

#endif
