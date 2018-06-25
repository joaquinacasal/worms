#ifndef __YOULOSEMESSAGE__
#define __YOULOSEMESSAGE__

#include "client_SdlTexture.h"

class YouLoseMessage {
public:
    YouLoseMessage(SdlTexture* message_texture, int time);
    int render();
    void set_message_texture(SdlTexture* message_texture);
    void set_time_alive(int time);
    ~YouLoseMessage();

private:
    SdlTexture* message_texture;
    int time_alive;
};

#endif
