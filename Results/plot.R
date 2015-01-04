
info_file = "basic-parallel-create-files.txt"
algorithm = "basic-parallel"
pdf = TRUE

################################################################ CREATE SUMMARIES MATRIX 
files_to_process = readLines(info_file)

sm = matrix(NA,length(files_to_process), 5)

#Writing command argument to passe argument with source
myCommandArgs = function() "hello bitch" 

i = 1
for(e in files_to_process){
  myCommandArgs = function() e
  source("import_data.R")
  sm[i,] = summary
  i = i + 1
}


################################################################## MAKE GRAPHS
max_threads=length(sm[,1])
f_solo = mean(sm[,2])/sm[1,1] #we take the mean and don't just the first one because we see that solo time grows
amdhal = rep(1,max_threads)/(f_solo + ((rep(1,max_threads)-f_solo)/seq(1,max_threads)))

par(bg = colors()[1])
if(pdf) {pdf(paste(algorithm,"-speedup.pdf", sep=""), width=6, heigh=4)}
plot(sm[1,1]/sm[,1], xlab="number of threads", ylab="speed up", ylim=c(0,amdhal[max_threads]+1))
lines(seq(1,max_threads), amdhal, col="green")
if(pdf){dev.off()}

if(pdf){pdf(paste(algorithm,"-sequantial-time.pdf", sep=""), width=6, heigh=4)}
plot(sm[,2], xlab="number of threads", ylab="sequantial time")
if(pdf){dev.off()}

if(pdf){pdf(paste(algorithm,"-wait-time.pdf", sep=""), width=6, heigh=4)}
plot(sm[,3]/(sm[,1]-sm[,2]), xlab="number of thread", ylab="parallel section wait time in percent")
if (pdf){dev.off()}

if(pdf){pdf(paste(algorithm,"-adapte-speedup.pdf", sep=""), width=6, heigh=4)}
#ploting speedup when substract waitng time
plot(sm[1,1]/(sm[,1]-sm[,3]), xlab="number of threads", ylab="speed up", ylim=c(0,amdhal[max_threads]+1))
lines(seq(1,max_threads), amdhal, col="green")
if(pdf){dev.off()}

################################################################## KEEP SM
 

