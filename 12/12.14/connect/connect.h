#ifndef C_PRIMER_5TH_CONNECT_H
#define C_PRIMER_5TH_CONNECT_H

#include <stdint.h>
#include <stdbool.h>

struct destination {
    uint32_t ipv4;
    uint16_t port;
};

struct connection;

typedef struct connection *connectionptr;

connectionptr connect(const struct destination *dest);

bool disconnect(connectionptr conn);

bool send(connectionptr conn, bool connectivity, const char *msg);

// responsibility of user to make sure msg can store 256 bytes
bool receive(connectionptr conn, char *msg);

#endif //C_PRIMER_5TH_CONNECT_H
