#!/bin/bash
mkdir gcf-extract/picked/

for class in pyro demoman medic spy engineer soldier scout sniper heavy
do
	find gcf-extract/vo/ -iname ${class}_* -size +100k | grep -v cloakedspy  | \
        grep -v falling | grep -v pain | grep -v mp3 | grep -v cart | xargs -I {} cp {} gcf-extract/picked/
done

