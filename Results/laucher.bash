#!bash

method="basic-parallel"
infile="tab8096"
num_slots="100"
delta_t="0.01"
accuracy="0"
create_files="$method-create-files.txt"

touch "$create_files"

outfile="r.txt"
for num_thread in $(seq 28 64)
do
	echo "NBody with $num_thread is lauch" 
	outfile="r-$method-$infile-s$num_slots-a$accuracy-t$num_thread.txt"	
	./NBodyBasicParallel.exe $infile $outfile $num_thread $num_slots $delta_t $accuracy
	echo $outfile >> $create_files

	 
done


 


 
