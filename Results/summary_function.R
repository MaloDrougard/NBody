


summary <- function(name_file){
  
  summary_n = "SUMMARY"
  text = readLines(name_file)
  file_header = read.table(text = text[1])
  num_threads = file_header[1,4]

  
  getLineNum <- function(table_name){
    grep(table_name ,text, ignore.case = TRUE) + 1
  }
  
  getTable <- function(table_name){
    i = getLineNum(table_name)
    read.table(text= text[  i : (i + num_threads)], header=TRUE, row.names = 1)
  }
  
  summary = getTable(summary_n)
  
  return(summary)
  
}