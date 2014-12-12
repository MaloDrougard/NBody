
#Set-ExecutionPolicy RemoteSigned to allowing runing script

echo "hello we gonna start the script"
$method="bp"
$infile="tab8096"
$outfile="l.txt"
$created_file="info_file_8096.txt" #contains the file name who was create
$num_slots=100
$num_threads=0
$max_num_threads=64
$delta_time=0.01
$accuracy=0

ni $created_file -type file 

for($num_threads=1; $num_threads -le $max_num_threads; $num_threads++){
 echo "Couputation with $num_threads starts"
 $outfile="r-$method-$infile-s$num_slots-acc$accuracy-t$num_threads.txt"
 C:\Users\malo\Documents\"Visual Studio 2013"\Projects\NBody\Release\NBody.exe $infile $outfile $num_threads $num_slots $delta_time $accuracy
  "$outfile" | out-file $created_file -encoding ascii -Append
}

echo "All the computation is done"


