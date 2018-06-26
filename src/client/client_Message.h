#ifndef __MESSAGE__
#define __MESSAGE__

#include "client_SdlTexture.h"
#include "client_Camera.h"

/*
 * Abstracción de un mensaje de texto en la ventana, con una textura y un
 * tiempo por el cual permanecerá visible.
 */
class Message {
public:
    Message(SdlTexture* message_texture, int time);
    void render(Camera& camera);
    void set_message_texture(SdlTexture* message_texture);
    void set_time_alive(int time);
    ~Message();

private:
    SdlTexture* message_texture;
    int time_alive;
};

#endif //__MESSAGE__
