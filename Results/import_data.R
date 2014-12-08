# i for index, s for start, e for end, n for name

name = "result.txt"
text = readLines(name)
file_header = read.table(text = text[1])
num_threads = file_header[1,4]

#table name:
total_start_n = "TOTALTIME_TABLE_START"
total_end_n = "TOTALTIME_TABLE_END"
para_start_n = "PARALLELTIME_START"
para_end_n = "PARALLELTIME_END"
solo_part1_start_n = "SOLOTIME_START_PART1"
solo_part1_end_n = "SOLOTIME_END_PART1"
solo_part2_start_n = "SOLOTIME_START_PART2"
solo_part2_end_n = "SOLOTIME_END_PART2"

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
solo_part1_e= getTable(solo_part1_end_n)
solo_part2_s = getTable(solo_part2_start_n)
solo_part2_e = getTable(solo_part2_end_n)