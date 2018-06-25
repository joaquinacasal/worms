#ifndef __MESSAGE__
#define __MESSAGE__

#include "client_SdlTexture.h"
#include "client_Camera.h"

class Message {
public:
    Message(SdlTexture* message_texture, int time);
    int render(Camera& camera);
    void set_message_texture(SdlTexture* message_texture);
    void set_time_alive(int time);
    ~Message();

private:
    SdlTexture* message_texture;
    int time_alive;
};

#endif //__MESSAGE__
