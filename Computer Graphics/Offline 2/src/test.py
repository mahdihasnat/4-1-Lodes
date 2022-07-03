#!/bin/python
import os

os.system("make")
os.system("make main.out")
for i in range(1,5):
	dir = '../resource/Test Cases (Updated)/'+str(i)
	os.system("./main.out '"+dir+"/scene.txt'"+" '"+dir+"/config.txt'")
	for j in range(1,4):
		file = "/stage"+str(j)+".txt"
		os.system("diff -bB ."+file+" '"+dir+file+"'")
	# os.system("diff ")