#!/bin/bash
out_file='/home/vagrant/share/data.csv'

echo 'Link delay,Window size,Bandwidth' > data.csv

status_path='/home/vagrant/dce/source/ns-3-dce/files-1/var/log/*/status'
stdout_path='/home/vagrant/dce/source/ns-3-dce/files-1/var/log/*/stdout'

max_progress=$((61 * 206))
progress=0

echo "Perfomance test started. Progress:"
for ld in {1..301..5}
do
	for ws in {1..1026..5}
	do
		(cd /home/vagrant/dce/source/ns-3-dce; ./waf --run "dce-iperf --window-size=${ws}K --link-delay=${ld}ms") > /dev/null 2>/dev/null
		status=`cat $status_path | tail -n1 | awk -F "--> " '{print $2}'`
		bw="Nan"
		case $status in
			"Exit (0)"*)
				bw=`cat $stdout_path | tail -n1 | awk '{print $7}'`
				;;
			"Never ended."*) 
				;;
			*) 
				echo "Unknown exit status on data ld=$ld ws=$ws" >> error.log
				;;
		esac
		echo "${ld},${ws},${bw}" >> data.csv
		
		(( ++progress ))
		percent=$(( (100 * $progress) / $max_progress ))
		count_hash=$(($percent / 2))
		count_space=$((50 - $count_hash))
		count_dots=$((progress % 4))
		count_dot_space=$((3 - count_dots))
		hashes=`printf %${count_hash}s |tr ' ' '#'`
		space=`printf %${count_space}s`
		dots=`printf %${count_dots}s |tr ' ' '.'`
		dot_space=`printf %${count_space}s`
		
		echo -ne "[${hashes}${space}] (${percent}%) ${dots}${dot_space}\r"
		
	done
done

echo -ne "[${hashes}${space}] (${percent}%) ${dots}${dot_space}\r"

echo "Test done. Aborting."

mv data.csv $out_file
