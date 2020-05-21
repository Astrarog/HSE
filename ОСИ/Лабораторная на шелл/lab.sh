counter=0
filename=''
message=''

getCorrectFileName(){
	while true
	do

		read -p "Filename: " filename

		if [ ! -f "$filename" ]; then
			echo "File $filename not found"
		else
			break
		fi
	done
}


sigintHandler(){

	counter=`expr $counter + 1`
	ost=`expr $counter % 5`
	if [ $ost -eq 0 ]
	then
		if [ ! "$filename" = '' ]; then
			fs = `du $filename | tail -n 1 | cut -f 1 -d$'\t'`
			sigMess = `echo "File \"$filename\" consists of $fileSize blocks"`
			echo "$sigMess"
		fi
	fi

}

trap 'sigintHandler' 2

getCorrectFileName

fileSize=`du $filename | tail -n 1 | cut -f 1 -d$'\t'`
totalSize=`du --summarize | cut -f 1 -d$'\t'`
message=`echo "There are $fileSize block in file $filename"; echo "Totaly, there are $totalSize blocks in current directory"`
echo "$message"


sleep 5
sleep 5
sleep 5
sleep 5
sleep 5
sleep 5
sleep 5
sleep 5
