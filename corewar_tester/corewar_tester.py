import os
import sys
import re

def remove_cor_files(folder):
	files = os.listdir(folder)
	for file in files:
		m = re.match("^(.+)\.cor$", file)
		if m != None:
			os.unlink(os.path.join(folder, file))

def verify_corewar_functionality(cor_file_path_list, corewar):
	cor_file_string = ""
	for cor_file_path in cor_file_path_list:
		cor_file_string += " " + cor_file_path
	print("File: " + cor_file_string.ljust(132) + "Count cycles")
	command = "bash CountCycles.sh ./corewar " + cor_file_string
	result = os.system(command)
	filehandler = open("cycles.log", "r")
	cycles = int(filehandler.readlines()[0].strip()) - 1
	filehandler.close()
	if cycles > 0:
		print("File: " + cor_file_string.ljust(130) + "  Cycles:" + str(cycles))
		result = os.system("bash compare.sh " + corewar + " " + str(cycles) + " " + cor_file_string)
	else:
		command = "bash CountCycles.sh " + corewar + " " + cor_file_string
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

def usage():
	print(" ")
	print("python3 corewar_tester.py 4 ../asm_dir/asm ../vm_dir/corewar \"42.cor,barriere.cor,Car.cor,ultima.cor\"")
	print(" ")
	print("   4                                          --> Number of champions (1-4)")
	print("   ../asm                                     --> asm")
	print("   ../corewar                                 --> corewar")
	print("   42.cor,barriere.cor,Car.cor,ultima.cor     --> Champions to exclude. Useful in case of a long execution time")
	print(" ")
	print(" ")
	print(" ")
	print("A script for comparing corewar output to 42-corewar output with specific champion file(s) and number of cycles")
	print("    bash compare.sh ../corewar 2000 cor_files/fluttershy.cor")
	print(" ")
	print("       2000                                       --> Number of cycles")
	print("       cor_files/fluttershy.cor                   --> Champion files(s)")
	print(" ")

if __name__ == "__main__":
	num_of_params = len(sys.argv)
	if num_of_params < 4:
		usage()
		sys.exit()
	program_folder = os.path.dirname(sys.argv[0])
	max_number_of_files = int(sys.argv[1])
	asm = sys.argv[2]
	corewar = sys.argv[3]
	if num_of_params == 5:
		exclude_list = sys.argv[4].split(",")
	else:
		exclude_list = []
	cor_file_folder = os.path.join(program_folder, "cor_files")
	remove_cor_files(cor_file_folder)
	files = os.listdir(cor_file_folder)
	file_counter = 0
	cor_file_path_list = []
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
					file_counter += 1
					cor_file_path_list.append(cor_file_path)
					if file_counter == max_number_of_files:
						verify_corewar_functionality(cor_file_path_list, corewar)
						cor_file_path_list = []
						file_counter = 0
	if file_counter > 0:
		verify_corewar_functionality(cor_file_path_list, corewar)
		cor_file_path_list = []
		file_counter = 0
