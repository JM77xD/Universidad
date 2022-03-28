"""

-*- coding:utf-8 -*-

Requirements:
    - Scikit-learn
    - Matplotlib
    - Numpy
    - Pandas
    - Math
    - Cmath


Author: José María Ramírez González


"""

import math
from cmath import cos, sinh, tanh, sin
from sklearn.datasets import load_iris
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
from matplotlib import cm
import numpy as np
import pandas as pd

# First exercise

iris = load_iris()    # We load the Iris dataset from sklearn (no need to download anything), then we separate the actual data from the target values

iris_data = iris.data

filtered_iris_data = np.array([data[:3:2] for data in iris_data])    # We only take the first and third characteristics using list comprehension

iris_target = iris.target

scatter_colors = ["red", "green", "blue"]                   # We create a list to change the color depending on the 3 unique value types of iris_target

groups_dict = {0:"Setosa", 1:"Versicolor", 2:"Virginica"}  # We set the different labels by group

for group in np.unique(iris_target):
    condition_to_draw = np.where(iris_target == group)
    plt.scatter(filtered_iris_data[condition_to_draw, 0], filtered_iris_data[condition_to_draw, 1], c=scatter_colors[group], label=groups_dict[group])
    # To get the plotting right, we divide by groups (iris_target) and based on https://stackoverflow.com/questions/47006268/matplotlib-scatter-plot-with-color-label-and-legend-specified-by-c-option
    # we can get the right colors and legend.

plt.xlabel("sepal length(cm)")
plt.ylabel("petal length(cm)")
plt.title("Ejercicio 1")
plt.legend()
plt.show()


# Second exercise

# For the implementation of this part of the code, we are getting our inspiration from https://stackoverflow.com/questions/47202182/train-test-split-without-using-scikit-learn
# The implementation inserts the data into a Pandas DataFrame to use the class methods

shuffled_data = pd.DataFrame(data=filtered_iris_data, columns=iris.feature_names[:3:2]) # Creating the dataframe

shuffled_data['target'] = iris_target

shuffled_data = shuffled_data.sample(frac=1)    # We shuffle the data, including the target

train_size = int(0.8 * len(filtered_iris_data))  # Defining the train size compared to the whole dataset, which is 80%

train_set = shuffled_data[:train_size]  # As we have shuffled the data, we should be able to get a correct proportion of elements from all groups just by selecting the first 80% and the last 20%
test_set = shuffled_data[train_size:]

for group in np.unique(iris_target):
    print("--- Clase {} ---".format(groups_dict[group]))
    print("Elements in train: {}".format(train_set['target'].value_counts()[int(group)]))   # We filter the set by target and then count the occurences of the current group
    print("Elements in test: {}".format(test_set['target'].value_counts()[int(group)]))

print("Clase de los ejemplos de entrenamiento:\n{}".format(train_set['target'].tolist()))
print("Clase de los ejemplos de prueba:\n{}".format(test_set['target'].tolist()))


# Third exercise

values = [(x/99)*4*math.pi for x in range(100)] # We create the values using range and normalize between 0 and 4PI using list comprehension

functions_names = ["10e-5 * sinh(x)", "cos(x)", "tanh( 2*sin(x) - 4*cos(x) )"]  # We define the strings and colors for the plotting
functions_colors = ["g--", "k--", "r--"]

results = [[10**(-5)*sinh(x) for x in values], [cos(x) for x in values], [tanh(2*sin(x) - 4*cos(x)) for x in values]] # We create a list of lists with the results

for i in range(3):
    plt.plot(values, results[i], functions_colors[i], label="y = {}".format(functions_names[i]))    # We plot the values from the different functions

plt.title("Ejercicio 3")
plt.legend()
plt.show()


# Fourth exercise

# For the implementation we are getting help from the link provided in the exercise's document: https://matplotlib.org/stable/gallery/mplot3d/subplot3d.html
# and from https://betterprogramming.pub/plot-3d-functions-with-matplotlib-and-numpy-9ab0879d23b2

fig = plt.figure(figsize=plt.figaspect(0.5))    # We create a figure, twice as wide as it is tall

ax = fig.add_subplot(1, 2, 1, projection='3d', title="Pirámide")  # First subplot

ax.xaxis.set_major_formatter(FormatStrFormatter('%.2f'))    # We format the axis to use float instead of int
ax.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.2f'))

X1_points = np.linspace(-6.0, 6.0)  # We create the x and y points
Y1_points = np.linspace(-6.0, 6.0)

X1, Y1 = np.meshgrid(X1_points, Y1_points)  # Use a meshgrid to correlate those points to each other

func1 = lambda x, y : 1-abs(x+y)-abs(y-x)   # Define the function

vectorized_func1 = np.vectorize(func1)      # Vectorize it

Z1 = vectorized_func1(X1,Y1)    # And set the Z-axis points

ax.plot_surface(X1, Y1, Z1, rstride=1, cstride=1, cmap=cm.coolwarm, linewidth=0, antialiased=False) # We then plot it to look as we want to

plt.rcParams['text.usetex'] = True  # Allow Latex in our labels

ax = fig.add_subplot(1, 2, 2, projection='3d', title=r'$x \cdot y \cdot e^{(x^{2} - y^{2})}$')  # Second subplot

ax.xaxis.set_major_formatter(FormatStrFormatter('%.2f')) # We format the axis to use float instead of int
ax.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.2f'))

X2_points = np.linspace(-2-0, 2.0)  # We create the x and y points
Y2_points = np.linspace(-2.0, 2.0)

X2, Y2 = np.meshgrid(X2_points, Y2_points)  # Use a meshgrid to correlate those points to each other

func2 = lambda x, y : x*y*math.e**(- x**2 - y**2)   # Define the function

vectorized_func2 = np.vectorize(func2)              # Vectorize

Z2 = vectorized_func2(X2, Y2)                       # And get the Z-axis points

ax.plot_surface(X2, Y2, Z2, rstride=1, cstride=1, linewidth=0, antialiased=True, cmap=cm.viridis)   # We plot it antialiased and with the viridis ColorMap


plt.show()
