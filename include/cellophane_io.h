#ifndef _CELLOPHANE_IO_H_
#define _CELLOPHANE_IO_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#include "payload.h";

typedef void (*on_event_callback)(char *);

enum socket_io_type{

    TYPE_DISCONNECT   = 0,
    TYPE_CONNECT      = 1,
    TYPE_HEARTBEAT    = 2,
    TYPE_MESSAGE      = 3,
    TYPE_JSON_MESSAGE = 4,
    TYPE_EVENT        = 5,
    TYPE_ACK          = 6,
    TYPE_ERROR        = 7,
    TYPE_NOOP         = 8,
};


typedef struct _wsevent{
    char * event_name;
    on_event_callback callback_func;

}wsevent_type;

typedef wsevent_type WsEvent;

typedef struct _wssession{

    char * sid;
    int connection_timeout;
    int heartbeat_timeout;
    char** supported_transports;

} wssession_type;

typedef wssession_type WsSession;


typedef struct _wshandler{

    char * socketIOUrl;
    char * serverPath;
    char * serverHost;
    int serverPort;
    WsSession session;
    int fd;
    int fd_alive;
    char buffer[256];
    int lastId;
    int read;
    int checkSslPeer;
    int debug;
    int handshakeTimeout;
    time_t heartbeatStamp;

    WsEvent events[128];

} wshandler_type;

typedef wshandler_type WsHandler;

void cellophane_new(WsHandler * ws_handler, char * tcp_protocol , char * address, int port, char * path, int protocol, int read, int  checkSslPeer, int debug);
void cellophane_io(WsHandler * ws_handler, char * tcp_protocol, char * address, int port );
void cellophane_init(WsHandler * ws_handler, int keepalive);
int cellophane_handshake(WsHandler * ws_handler);
int cellophane_connect(WsHandler * ws_handler);
char * cellophane_generateKey(int length);
char * cellophane_read(WsHandler * ws_handler);
void cellophane_send(WsHandler * ws_handler, enum socket_io_type io_type, char * id, char * endpoint, char * message);
void  cellophane_emit(WsHandler * ws_handler, char * event, char * args, char * endpoint);
void  cellophane_close(WsHandler * ws_handler);
void cellophane_keepAlive(WsHandler * ws_handler);
void cellophane_event_handler(WsHandler * ws_handler);


#endif //_CELLOPHANE_IO_H_

