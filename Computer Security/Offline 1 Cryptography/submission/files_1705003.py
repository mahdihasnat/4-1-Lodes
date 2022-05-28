import os
def file_path(relative_path):
	file = os.path.join(os.path.dirname(__file__), relative_path)
	# create directory if not exists
	if not os.path.exists(os.path.dirname(file)):
		os.makedirs(os.path.dirname(file))
	return file
