#ifndef __NOTIFIERTHREAD__
#define __NOTIFIERTHREAD__

#include "../common/common_BlockingQueue.h"
#include "../common/common_Thread.h"

#include "notifications/server_BeamNotification.h"
#include "notifications/server_ClosedConnectionNotification.h"
#include "notifications/server_DynamiteNotification.h"
#include "notifications/server_DynamiteExplosionNotification.h"
#include "notifications/server_EndTurnNotification.h"
#include "notifications/server_INotification.h"
#include "notifications/server_RadiocontrolledNotification.h"
#include "notifications/server_RadiocontrolledExplosionNotification.h"
#include "notifications/server_MunitionsNotification.h"
#include "notifications/server_StageNotification.h"
#include "notifications/server_StartTurnNotification.h"
#include "notifications/server_TurnTimeNotification.h"
#include "notifications/server_WormNotification.h"
#include "notifications/server_WormDeathNotification.h"
#include "notifications/server_YouWinNotification.h"
#include "notifications/server_YouLoseNotification.h"

#include <string>

/* Clase que hereda de Thread. Se encarga de recibir toda la información
 * necesaria para crear las notificaciones, crear objetos del tipo INotification
 * y encolarlos en una cola bloqueante. Además, al ser un thread aparte, durante
 * su ejecución saca objetos INotification de la cola (se queda esperando en
 * caso que no tenga ninguno para sacar) y los ejecuta (llama a su método run).
 * Internamente esos objetos envían la información al cliente correcto.
 * Es no copiable.
 */
class NotifierThread : public Thread {
  private:
    BlockingQueue<INotification*> blocking_queue;
    bool continue_sending;

    // No copiable.
    NotifierThread(const NotifierThread &other) = delete;
    NotifierThread& operator=(const NotifierThread &other) = delete;

  public:
    NotifierThread();

    void run() override;

    void stop();

    void send_worm_info(ClientHandler* client, size_t id, size_t life_points,\
                      double x, double y, int angle, bool is_facing_right,\
                      int team, int movement_state, bool is_the_selected_worm);
    void send_worm_death_notif(ClientHandler* client, size_t id, int team);
    void send_stage_info(ClientHandler* client, size_t width, size_t height,\
                        std::string background);
    void send_beam_info(ClientHandler* client, double x, double y, \
                        int length, int width, int angle);
    void send_dynamite_info(ClientHandler* client, double x, double y,\
                            int time_to_explosion);
    void send_dynamite_explosion_info(ClientHandler* client);
    void send_radiocontrolled_info(ClientHandler* client, size_t id,\
                                   double x, double y);
    void send_radiocontrolled_explosion_info(ClientHandler* client, size_t id);
    void send_munitions_info(ClientHandler* client, int dynamite_m,\
                             int radiocontrolled_m, int teletransportation_m);
    void send_turn_time_info(ClientHandler* client, int turn_chrono);
    void send_start_turn_notif(ClientHandler* client);
    void send_end_turn_notif(ClientHandler* client);
    void send_you_win_notif(ClientHandler* client);
    void send_you_lose_notif(ClientHandler* client);
    void send_closed_connection_notif(ClientHandler* client);
};


#endif
