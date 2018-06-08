#ifndef __NOTIFIERTHREAD__
#define __NOTIFIERTHREAD__

#include "../common/common_BlockingQueue.h"
#include "../common/common_Thread.h"

#include "server_BeamNotification.h"
#include "server_ClosedConnectionNotification.h"
#include "server_DynamiteNotification.h"
#include "server_EndTurnNotification.h"
#include "server_INotification.h"
#include "server_RadiocontrolledNotification.h"
#include "server_StageNotification.h"
#include "server_StartTurnNotification.h"
#include "server_TurnTimeNotification.h"
#include "server_WormNotification.h"

class NotifierThread : public Thread {
  private:
    BlockingQueue<INotification*> blocking_queue;
    bool continue_sending;
    NotifierThread(const NotifierThread &other) = delete;
    NotifierThread& operator=(const NotifierThread &other) = delete;
  public:
    NotifierThread();

    void run() override;

    void stop();

    void send_worm_info(ClientHandler* client, size_t id, size_t life_points, int x, int y, \
                                int angle, bool is_facing_right);

    void send_stage_info(ClientHandler* client, size_t width, size_t height);
    void send_beam_info(ClientHandler* client, int x, int y, int length, int width, int angle);
    void send_dynamite_info(ClientHandler* client, int x, int y, int time_to_explosion);
    void send_radiocontrolled_info(ClientHandler* client, int x, int y);
    void send_turn_time_info(ClientHandler* client, int turn_chrono);
    void send_start_turn_notif(ClientHandler* client);
    void send_end_turn_notif(ClientHandler* client);
    void send_closed_connection_notif(ClientHandler* client);


};


#endif
