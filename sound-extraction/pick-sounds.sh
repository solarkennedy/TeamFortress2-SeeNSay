#!/bin/bash
for class in pyro demoman medic spy engineer soldier scout sniper heavy
do
        mkdir -p sdcard/$class 2>/dev/null
        # We need wavs that are decently long, but not too long
	find gcf-extract/vo/ -iname ${class}_* -size +100k -size -280k | \
        grep -v cloakedspy  | grep -v falling | grep -v pain | grep -v mp3 | grep -v cart | xargs -I {} cp {} sdcard/$class/{}
	# We can use stock wavs, they are already in a compatible format 
done

# do preludes
mkdir sdcard/preludes
cd preludes
find  | xargs -P $THREADS -I {} sox -G {} -t wav --endian little -c 1 -r 22050 ../sdcard/preludes/{}

