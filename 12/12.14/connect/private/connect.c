#include "connect_private.h"
#include <stdlib.h>
#include <string.h>

static bool commit(connectionptr conn, char operation);

connectionptr connect(const struct destination *dest) {
    connectionptr ret = malloc(sizeof(*ret));
    if (!ret) { return ret; }

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
        strncpy(conn->buff_send, msg, MSG_MAX);
        conn->buff_send[MSG_MAX - 1] = '\0';
        conn->send_utilised = false;
        return commit(conn, 's');
    }

    return commit(conn, 'd');
}

bool receive(connectionptr conn, char *msg) {
    strncpy(msg, conn->buff_recv, MSG_MAX);
    msg[MSG_MAX - 1] = '\0';
    conn->recv_utilised = true;

    return commit(conn, 'r');
}

static bool commit(connectionptr conn, char operation) {
    // make a connection with self
    switch (operation) {
        case 's':
            if (conn->recv_utilised) {
                strncpy(conn->buff_recv, conn->buff_send, MSG_MAX);
                conn->buff_recv[MSG_MAX - 1] = '\0';
                conn->recv_utilised = false;
                return true;
            } else {
                return false;
            }
        case 'r':
            if (conn->send_utilised) {
                return false;
            } else {
                conn->send_utilised = true;
                return true;
            }
        case 'c':
        case 'd':
        default:
            return true;
    }
}
