
echo "hello we gonna start the script"
$method="basic"
$infile="t"
$outfile="l.txt"
$num_slots=100
$num_threads=0
$delta_time=0.01
$accuracy=0


for($num_threads=1; $num_threads -le 3; $num_threads++){
 echo "Couputation with $num_threads starts"
 $outfile="r-$method-s$num_slots-acc$accuracy-t$num_threads.txt"
 C:\Users\malo\Documents\"Visual Studio 2013"\Projects\NBody\Release\NBody.exe $infile $outfile $num_threads $num_slots $delta_time $accuracy
}

echo "All the computation is done"


