import os
import sys
import re

files = os.listdir(sys.argv[1])

for file in files:
	if re.match("^\._.+$", file):
		continue
	if re.match("^.+\.s$", file):
		m = re.match("^(.+)\.s$", file)
		cor_file_path = sys.argv[1] + "/" + m.group(1) + ".cor"
		if os.path.isfile(cor_file_path):
			continue
		else:
			command = "../../jhakala/asm_dir/asm " + sys.argv[1] + "/" + file
			print(command)
			result = os.system(command)
	else:
		cor_file_path = sys.argv[1] + "/" + file
	if re.match("^.+\.cor$", cor_file_path):
		print(file)
		command = "bash CountCycles.sh " + cor_file_path
		print(command)
		result = os.system(command)
		if result == 0:
			filehandler = open("cycles.log", "r")
			cycles = filehandler.readlines()[0].strip()
			filehandler.close()
			print("Cycles:" + cycles)
			result = os.system("bash ../../jhakala/test_dir/mod_compare.sh " + cycles + " " + cor_file_path)
			result = os.system("diff we.log ref.log")
			print(result)

