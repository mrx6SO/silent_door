#include "main.h"
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

void daemonize() {
    // No Windows, podemos simplesmente ocultar a janela do console.
    // O programa rodará em segundo plano, mas não será um serviço real.
    FreeConsole();
}

#else // Implementação para Linux/Unix
#include <unistd.h>
#include <signal.h>

void daemonize()
{
    pid_t pid;

    // 1. Primeiro fork para se desvincular do processo pai.
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS); // Processo pai termina.

    // 2. Cria uma nova sessão. O processo se torna líder da sessão.
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    // 3. Ignora sinais específicos.
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // 4. Segundo fork para garantir que o daemon não possa adquirir um terminal de controle.
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // 5. Muda o diretório de trabalho para a raiz.
    chdir("/");

    // 6. Fecha todos os descritores de arquivo abertos.
    for (int i = sysconf(_SC_OPEN_MAX); i >= 0; i--)
    {
        close(i);
    }
}

#endif