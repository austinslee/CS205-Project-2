import pandas as pd

dataset = pd.read_csv('WineQT.csv')

columns_to_normalize = ['fixed acidity', 'volatile acidity','citric acid', 'residual sugar', 'chlorides', 'free sulfur dioxide', 'total sulfur dioxide', 'density', 'pH', 'sulphates', 'alcohol']

for column in columns_to_normalize:
	mean = dataset[column].mean()
	std = dataset[column].std()

	dataset[column] = (dataset[column] - mean) / std

dataset.to_csv('normalized.csv', index=False)
