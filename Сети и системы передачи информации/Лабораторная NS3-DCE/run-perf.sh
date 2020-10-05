#!/bin/bash
out_file='/home/vagrant/share/data.csv'

#echo 'Window Size,Link delay, Bandwidth' >> $out_file

status_path='/home/vagrant/dce/source/ns-3-dce/files-1/var/log/*/status'
stdout_path='/home/vagrant/dce/source/ns-3-dce/files-1/var/log/*/stdout'

max_progress=$((60 * 205))
progress=0

echo "Perfomance test started. Progress:"
for ld in {1..301..5}
do
	for ws in {1..1026..5}
	do
		#/home/vagrant/dce/source/ns-3-dce/waf --run "dce-runperf --window-size 128K --link-delay 301ms"
		#
		#bw=``
		#echo "${ld},${ws},${bw}" >> $out_file
		
		(( ++progress ))
		percent=$(( (100 * $progress) / $max_progress ))
		count_hash=$(($percent / 2))
		count_space=$((50 - $count_hash))
		count_dots=$((progress % 4))
		hashes=`printf %${count_hash}s |tr ' ' '#'`
		space=`printf %${count_space}s`
		dots=`printf %${count_dots}s |tr ' ' '.'`
		echo -ne "[${hashes}${space}] (${percent}%) ${dots}\r"
	done
done
