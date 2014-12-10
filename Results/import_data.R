# i for index, s for start, e for end, n for name

name = "r-1024-tp-acc2-1.txt"
text = readLines(name)
file_header = read.table(text = text[1])
num_threads = file_header[1,4]
num_slots = file_header[1,8]
  
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
mean_time_per_slot = total_t / num_slots
time_slots = para + solo
sum = sum(para) + sum(solo)


################### FRACTIONS #################################
f_solo = solo / (solo + para) 
f_mean_solo =  mean(f_solo)

################# DIFFERENCE BETWEEN THE THREADS ##############
dif_para = sapply( (para_e - para_s) , max ) - sapply( (para_e - para_s), min)
dif_mean = mean(dif_para)

#################### SUMMARY ##################################

summary = matrix(NA, 1, 3)
colnames(summary) = c("TIME_PER_SLOT", "NONE_PARALLEL_FRACTION", "DIFFERENCE_PARALLEL_SECTION")
summary[1,1] = mean_time_per_slot
summary[1,2] = f_mean_solo
summary[1,3] = dif_mean

if(length(grep(summary_n, text, ignore.case = TRUE)) == 0){
  write("\n" , name, append = TRUE)
  write(summary_n , name, append = TRUE)
  write.table(summary, name,  append = TRUE, col.names = TRUE)
}


#################### END AND CLEAR ############################







