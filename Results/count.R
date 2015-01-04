

info_file = "create-plot.txt"
algorithm = "tree-time-complexity"
pdf = FALSE

################################################################ CREATE SUMMARIES MATRIX 
files_to_process = readLines(info_file)

sm = matrix(NA,length(files_to_process), 4)

#Writing command argument to passe argument with source
myCommandArgs = function() "hello bitch" 

i = 1
for(e in files_to_process){
  myCommandArgs = function() e
  source("import_data.R")
  sm[i,] = summary
  i = i + 1
}

plot(sm[,4], sm[,1])
