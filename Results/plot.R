
info_file = "info_file.txt"

files_to_process = readLines(info_file)

source("summary_function.R")
sm = matrix(NA,length(files_to_process), 3)

#Writing command argument to passe argument with source
myCommandArgs = function() "hello bitch" 

i = 1
for(e in files_to_process){
  myCommandArgs = function() e
  source("import_data.R")
  sm[i,] = summary
  i = i + 1
}