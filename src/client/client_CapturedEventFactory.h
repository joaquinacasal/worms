#ifndef __CAPTUREDEVENTFACTORY__
#define __CAPTUREDEVENTFACTORY__

#include "client_ICapturedEvent.h"
#include "../common/common_BlockingQueue.h"
#include "client_DynamiteCapturedEvent.h"
#include "client_TeletransportationCapturedEvent.h"
#include "client_RadiocontrolledCapturedEvent.h"
#include "client_MoveRightCapturedEvent.h"
#include "client_MoveLeftCapturedEvent.h"
#include "client_StopMovingCapturedEvent.h"
#include "client_JumpForwardCapturedEvent.h"
#include "client_JumpBackwardCapturedEvent.h"
#include "client_ClosedConnectionCapturedEvent.h"


class CapturedEventFactory {
private:
    SocketProtocol& socket_protocol;
    BlockingQueue<ICapturedEvent*>& blocking_queue;

    CapturedEventFactory(const CapturedEventFactory&) = delete;
    CapturedEventFactory& operator=(const CapturedEventFactory&) = delete;
public:
    CapturedEventFactory(SocketProtocol& _socket_protocol, \
                    BlockingQueue<ICapturedEvent*>& _blocking_queue);

    void create_move_right_event();
    void create_move_left_event();
    void create_stop_moving_event();
    void create_jump_forward_event();
    void create_jump_backward_event();
    void create_closed_connection_event();
    void create_dynamite_event();
    void create_radiocontrolled_event(int x, int y);
    void create_teletransportation_event(int x, int y);

    ~CapturedEventFactory();
};


#endif //__CAPTUREDEVENTFACTORY__
