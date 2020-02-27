#ifndef C_PRIMER_5TH_CONNECT_PRIVATE_H
#define C_PRIMER_5TH_CONNECT_PRIVATE_H

#include "connect.h"

#define MSG_MAX 256

struct connection {
    struct destination dest;
    bool connected;
    char buff_send[MSG_MAX];
    bool send_utilised;
    char buff_recv[MSG_MAX];
    bool recv_utilised;
};

#endif // C_PRIMER_5TH_CONNECT_PRIVATE_H
