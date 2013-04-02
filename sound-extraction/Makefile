work/hllib244.zip:
	wget -O work/hllib244.zip http://nemesis.thewavelength.net/files/files/hllib244.zip

work/HLLib/: work/HLLib/libhl.so.2.3.0
	cd work
	unzip -f hllib244.zip 

work/HLLib/libhl.so.2.3.0:
	cd work/HLLib/
	make
	sudo make install

work/HLExtract/hlextract:
	cd work/
	gcc -O2 -g HLExtract/Main.c -o HLExtract/hlextract -lhl

#LD_PRELOAD=work/HLLib/libhl.so.2.3.0 work/HLExtract/hlextract
#LD_PRELOAD=work/HLLib/libhl.so.2.3.0 work/HLExtract/hlextract  -p ~/Steam/SteamApps/Team Fortress 2 Content.gcf

all: work/HLExtract/hlextract

