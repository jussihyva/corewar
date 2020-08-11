import os
import sys
import re

def remove_cor_files(folder):
	files = os.listdir(folder)
	for file in files:
		m = re.match("^(.+)\.cor$", file)
		if m != None:
			os.unlink(os.path.join(folder, file))

def verify_corewar_functionality(cor_file_path, corewar):
	print("File: " + cor_file_path.ljust(42) + "Count cycles")
	command = "bash CountCycles.sh ./corewar " + cor_file_path
	result = os.system(command)
	filehandler = open("cycles.log", "r")
	cycles = int(filehandler.readlines()[0].strip()) - 1
	filehandler.close()
	if cycles > 0:
		print("File: " + cor_file_path.ljust(40) + "  Cycles:" + str(cycles))
		result = os.system("bash compare.sh " + corewar + " " + str(cycles) + " " + cor_file_path)
	else:
		command = "bash CountCycles.sh " + corewar + " " + cor_file_path
		print(command)
		result = os.system(command)
		print("Prog: " + str(result))

def create_cor_file(s_file_path, cor_file_path):
	command = asm + " " + s_file_path + " > asm_result.log"
	result = os.system(command)
	if os.path.isfile(cor_file_path) == True:
		return (True)
	else:
		command = "./asm " + s_file_path + " > asm_result.log"
		result = os.system(command)
		if os.path.isfile(cor_file_path) == True:
			print("ASM Error: " + s_file_path)
			return (True)
		else:
			return (False)

if __name__ == "__main__":
	num_of_params = len(sys.argv)
	program_folder = os.path.dirname(sys.argv[0])
	asm = sys.argv[1]
	corewar = sys.argv[2]
	if num_of_params == 4:
		exclude_list = sys.argv[3].split(",")
	else:
		exclude_list = []
	cor_file_folder = os.path.join(program_folder, "cor_files")
	remove_cor_files(cor_file_folder)
	files = os.listdir(cor_file_folder)
	for file in files:
		m = re.match("^(.+)\.s$", file)
		if m != None:
			s_file_path = os.path.join(cor_file_folder, file)
			cor_file = m.group(1) + ".cor"
			if (file in exclude_list) or (cor_file in exclude_list):
				print("Excluded: " + file)
			else:
				cor_file_path = os.path.join(cor_file_folder, cor_file)
				result = create_cor_file(s_file_path, cor_file_path)
				if result == True:
					verify_corewar_functionality(cor_file_path, corewar)
