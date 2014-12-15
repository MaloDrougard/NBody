#!bash


method="tree-parallel"
infile="tab8096"
num_particles="0"
num_slots="30"
delta_t="0.01"
num_thread="1"
accuracy="0.2"
create_files="$method-create-files-countparticle.txt"

touch "$create_files"

outfile="r.txt"
num_particles="253"
while [ $num_particles -le 8096 ]
do
        echo "NBody with $num_thread is lauch"
        outfile="r-$method-$infile-p$num_particles-s$num_slots-a$accuracy-t$num_thread.txt"
        ./NBodyTreeParallelSmallCountParticles.exe $infile $outfile $num_thread $num_slots $delta_t $accuracy $num_particles
        echo $outfile >> $create_files
	num_particles=$[$num_particles+253] 

done


