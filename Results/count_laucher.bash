#!bash


method="basic-parallel"
infile="tab65536"
num_particles="0"
num_slots="30"
delta_t="0.01"
num_thread="1"
accuracy="0.2"
create_files="$method-create-files-countparticle.txt"

touch "$create_files"

outfile="r.txt"
num_particles="8096"
while [ $num_particles -le 65536 ]
do
        echo "NBody with $num_thread is lauch"
        outfile="r-$method-$infile-p$num_particles-s$num_slots-a$accuracy-t$num_thread.txt"
        ./NBodyBasicParallelSmallCount.exe $infile $outfile $num_thread $num_slots $delta_t $accuracy $num_particles
        echo $outfile >> $create_files
	num_particles=$[$num_particles+253] 

done


