TF2CONTENT="/backups/Steam/SteamApps/Team Fortress 2 Content.gcf"
EXTRACT=LD_PRELOAD=work/HLLib/libhl.so.2.3.0 work/HLExtract/hlextract
#TF2CONTENT="~/Steam/SteamApps/Team Fortress 2 Content.gcf"

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

extract:
	$(EXTRACT) -p $(TF2CONTENT) -d gcf-extract -m -e root/tf/sound/vo/

pick:
	./pick-sounds.sh
convert:
	./convert-sounds.sh

all: work/HLExtract/hlextract


#all
#LD_PRELOAD=work/HLLib/libhl.so.2.3.0 work/HLExtract/hlextract -p "/backups/Steam/SteamApps/Team Fortress 2 Content.gcf" -d /archive/tf2/ -m -e root/tf/sound/vo/

