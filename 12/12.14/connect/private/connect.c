#include "connect_private.h"
#include <stdlib.h>
#include <string.h>

static bool commit(connectionptr conn, char operation);

connectionptr connect(const struct destination *dest) {
    connectionptr ret = malloc(sizeof(*ret));
    ret->dest = *dest;
    ret->connected = true;
    strcpy(ret->buff_recv, "");
    ret->recv_utilised = true;
    strcpy(ret->buff_send, "");
    ret->send_utilised = true;

    if (!commit(ret, 'c')) {
        free(ret);
        ret = NULL;
    }

    return ret;
}

bool disconnect(connectionptr conn) {
    bool ret = send(conn, false, "");
    free(conn);

    return ret;
}

bool send(connectionptr conn, bool connectivity, const char *msg) {
    if ((conn->connected = connectivity)) {
        strncpy(conn->buff_send, msg, MSG_MAX - 1);
        conn->buff_send[MSG_MAX - 1] = '\0';
        conn->send_utilised = false;
        return commit(conn, 's');
    }

    return commit(conn, 'd');
}

bool receive(connectionptr conn, char *msg) {
    strncpy(msg, conn->buff_recv, MSG_MAX - 1);
    msg[MSG_MAX - 1] = '\0';
    conn->recv_utilised = true;

    return commit(conn, 'r');
}

static bool commit(connectionptr conn, char operation) {
    // make a connection with self
    switch (operation) {
        case 's':
            strncpy(conn->buff_recv, conn->buff_send, MSG_MAX - 1);
            conn->buff_recv[MSG_MAX - 1] = '\0';
            conn->recv_utilised = false;
            break;
        case 'r':
            conn->send_utilised = true;
            break;
        case 'c':
        case 'd':
        default:
            break;
    }
    return true;
}
