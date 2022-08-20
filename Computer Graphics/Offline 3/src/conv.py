import os
import sys

import os, fnmatch
def findReplace(directory, find, replace, filePattern):
    for path, dirs, files in os.walk(os.path.abspath(directory)):
        for filename in fnmatch.filter(files, filePattern):
            filepath = os.path.join(path, filename)
            with open(filepath) as f:
                s = f.read()
            s = s.replace(find, replace)
            with open(filepath, "w") as f:
                f.write(s)

# get output of ls command
output = os.popen('ls *.h').read()
output = output.split('\n')
for file in output:
	print(file)
	if len(file)==0:
		continue
	findReplace('./',file,"1705003_"+file,"*.h")
	findReplace('./',file,"1705003_"+file,"*.cpp")
	os.rename(file, "1705003_"+file)