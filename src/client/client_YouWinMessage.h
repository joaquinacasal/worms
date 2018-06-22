#ifndef __YOUWINMESSAGE__
#define __YOUWINMESSAGE__

#include "client_SdlTexture.h"

class YouWinMessage {
public:
    YouWinMessage(SdlTexture* message_texture, int time);
    int render();
    void set_message_texture(SdlTexture* message_texture);
    void set_time_alive(int time);
    ~YouWinMessage();

private:
    SdlTexture* message_texture;
    int time_alive;
};

#endif
