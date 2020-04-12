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
		echo "$message"
	fi

}

trap 'sigintHandler' 2

getCorrectFileName

fileSize=`wc * | tr -s ' ' | grep -e $filename | cut -f 4 -d ' '`
totalSize=`wc * | tr -s ' ' | grep -e total | cut -f 4 -d ' '`

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
