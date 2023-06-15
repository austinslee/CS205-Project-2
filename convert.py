import csv


csv_file = 'normalized.csv'
txt_file = 'realWorld.txt'

with open(csv_file, 'r') as file:
	csv_reader = csv.reader(file)
	# skipping the description row
	next(csv_reader)
	with open(txt_file, 'w') as txt_output:
		for row in csv_reader:
			# putting 'quality' column in front and dropping 'id' column
			last_col = row[-2]
			new_row = [last_col] + row[:-2]
			line = ' '.join(new_row)
			txt_output.write(line + '\n')

