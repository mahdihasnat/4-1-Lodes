import os
import sys

# get output of ls command
output = os.popen('ls *.h').read()
output = output.split('\n')
for file in output:
	print(file)
	if len(file)==0:
		continue
	file = file.split('.')[0]+'\.h'
	s = "grep -l '{}' ./ | xargs sed -i 's/{}/1705003_{}/g'".format(file,file,file)
	print(s)
	os.popen(s)