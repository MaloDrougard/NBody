# import the data from an output file from a result file of the NBody software
# and construct the approptiate time table



# i for index, s for start, e for end, n for name

name = "r-basic-parallel-tab8096-p253-s30-t1.txt"
clear = FALSE #clean or not the value and data at the end of the script

# uncomment this to bound this with the plot.R
# myCommandArgs = function() NULL

args <- myCommandArgs()
if ( length(args) == 1){
  name = args[1]
  clear = TRUE
}

text = readLines(name)
file_header = read.table(text = text[1])
num_threads = file_header[1,4]
num_slots = file_header[1,8]
num_particles = file_header[1,6]


#table name:
total_start_n = "TOTALTIME_TABLE_START"
total_end_n = "TOTALTIME_TABLE_END"
para_start_n = "PARALLELTIME_START"
para_end_n = "PARALLELTIME_END"
solo_part1_start_n = "SOLOTIME_START_PART1"
solo_part1_end_n = "SOLOTIME_END_PART1"
solo_part2_start_n = "SOLOTIME_START_PART2"
solo_part2_end_n = "SOLOTIME_END_PART2"
summary_n = "SUMMARY"

getLineNum <- function(table_name){
  grep(table_name ,text, ignore.case = TRUE) + 1
}

getTable <- function(table_name){
  i = getLineNum(table_name)
  read.table(text= text[  i : (i + num_threads)], header=TRUE, row.names = 1)
}


total_s = getTable(total_start_n)
total_e = getTable(total_end_n)
para_s = getTable(para_start_n)
para_e = getTable(para_end_n)
solo_part1_s = getTable(solo_part1_start_n)
solo_part1_e = getTable(solo_part1_end_n)
solo_part2_s =getTable(solo_part2_start_n)
solo_part2_e = getTable(solo_part2_end_n)


################ GET THE EFFECTIVE TIME #######################
para = sapply(para_e, max) - sapply(para_s, min)
# we take allways the max because only one thread is active during a part
solo = (sapply(solo_part1_e, max) - sapply(solo_part1_s, max)) +
              (sapply(solo_part2_e, max) - sapply(solo_part2_s, max) )

################# TOTAL TIME ##################################
total_t = max(total_e) -  min(total_s)
time_slots = para + solo
mean_time_per_slot = mean(time_slots)
sum = sum(para) + sum(solo)


################### FRACTIONS #################################
f_solo = solo/ (solo + para) 
f_mean_solo =  mean(f_solo)
mean_solo = mean(solo)

################# DIFFERENCE BETWEEN THE THREADS ##############
dif_para = sapply( para_e, max ) - sapply( para_e, min)
dif_mean = mean(dif_para)

#################### SUMMARY ##################################
# sequntial_time is the time where the code is executec by only one threads
# wait_time is  the time that the thread whos has finisch first wait on the others

summary = matrix(NA, 1, 5)

colnames(summary) = c("TIME_PER_SLOT", "SEQUENTIAL_TIME", "WAIT_TIME", "NUM_PARTICLES", "SOLO_TIME_PART2")
summary[1,1] = mean_time_per_slot
summary[1,2] = mean_solo
summary[1,3] = dif_mean
summary[1,4] = num_particles
summary[1,5] = mean(sapply(solo_part2_e, max) - sapply(solo_part2_s, max))

if(length(grep(summary_n, text, ignore.case = TRUE)) == 0){
  write("\n" , name, append = TRUE)
  write(summary_n , name, append = TRUE)
  write.table(summary, name,  append = TRUE, col.names = TRUE)
}


################ PLOTS #######################################

#pdf= TRUE
#if(pdf){
#  pdf(paste(name, "slots-times.pdf", sep=""), width=6, heigh=4)
#  plot(time_slots, xlab="slot", ylab="time", ylim = c(0,3.5))
#  dev.off()
#}



#################### END AND CLEAR ############################
if(clear){
  rm(solo_part1_s, solo_part1_e, solo_part2_s, solo_part2_e, total_s, total_e, para_s, para_e, file_header)
  rm(solo, para, total_t)
  rm(solo_part1_end_n, solo_part1_start_n, solo_part2_end_n, solo_part2_start_n,
     total_end_n, total_start_n, para_end_n, para_start_n)
  rm(args, clear, dif_mean, dif_para, f_mean_solo,f_solo,getLineNum,getTable, 
     mean_time_per_slot, name, num_slots, num_threads,sum, summary_n, text, time_slots)   
  rm(mean_solo, num_particles)
}






