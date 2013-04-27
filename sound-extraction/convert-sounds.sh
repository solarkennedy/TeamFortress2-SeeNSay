# Gets files into the right format
# Populates the sdcard

THREADS=8
cd gcf-extract/picked/
for class in pyro demoman medic spy engineer soldier scout sniper heavy
do
	mkdir -p ../../sdcard/$class 2>/dev/null
	find . -iname ${class}\* | xargs -P $THREADS -I {} cp {} ../../sdcard/$class/{}
	# Aparently the stock sounds need no conversion? 
        #find . -iname ${class}\* | xargs -P $THREADS -I {} sox -G {} -t wav --endian little -c 1 -r 22050 ../../sdcard/$class/{}
done

mkdir sdcard/preludes
cd preludes 
find  | xargs -P $THREADS -I {} sox -G {} -t wav --endian little -c 1 -r 22050 ../sdcard/preludes/{}
