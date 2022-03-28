# -*- coding: utf-8 -*-
"""
TRABAJO 1. 
Nombre Estudiante: José María Ramírez González
"""

from math import e, pi, sin, cos
import numpy as np
import matplotlib.pyplot as plt
import random

np.random.seed(1)

'''
Esta función muestra una figura 3D con la función a optimizar junto con el 
óptimo encontrado y la ruta seguida durante la optimización. Esta función, al igual
que las otras incluidas en este documento, sirven solamente como referencia y
apoyo a los estudiantes. No es obligatorio emplearlas, y pueden ser modificadas
como se prefiera. 
    rng_val: rango de valores a muestrear en np.linspace()
    fun: función a optimizar y mostrar
    ws: conjunto de pesos (pares de valores [x,y] que va recorriendo el optimizador
                           en su búsqueda iterativa del óptimo)
    colormap: mapa de color empleado en la visualización
    title_fig: título superior de la figura
    
Ejemplo de uso: display_figure(2, E, ws, 'plasma','Ejercicio 1.2. Función sobre la que se calcula el descenso de gradiente')
'''
def display_figure(rng_val, fun, ws, colormap, title_fig):
    # https://jakevdp.github.io/PythonDataScienceHandbook/04.12-three-dimensional-plotting.html
    from mpl_toolkits.mplot3d import Axes3D
    x = np.linspace(-rng_val, rng_val, 50)
    y = np.linspace(-rng_val, rng_val, 50)
    X, Y = np.meshgrid(x, y)
    myFun = np.vectorize(fun, excluded=['X', 'Y'])
    Z = myFun(X,Y)
    fig = plt.figure()
    ax = Axes3D(fig,auto_add_to_figure=False)
    fig.add_axes(ax)
    ax.plot_surface(X, Y, Z, edgecolor='none', rstride=1,
                            cstride=1, cmap=colormap, alpha=.6)
    if len(ws)>0:
        ws = np.asarray(ws)
        min_point = np.array([ws[-1,0],ws[-1,1]])
        min_point_ = min_point[:, np.newaxis]
        ax.plot(ws[:-1,0], ws[:-1,1], myFun(ws[:-1,0], ws[:-1,1]), 'r*', markersize=5)
        ax.plot(min_point_[0], min_point_[1], myFun(min_point_[0], min_point_[1]), 'r*', markersize=10)
    if len(title_fig)>0:
        fig.suptitle(title_fig, fontsize=16)
    ax.set_xlabel('u')
    ax.set_ylabel('v')
    ax.set_zlabel('F(u,v)')

print('EJERCICIO SOBRE LA BUSQUEDA ITERATIVA DE OPTIMOS\n')
print('Ejercicio 1\n')

def E(u,v):
    return pow(u*v*pow(e, -pow(u,2)-pow(v,2)),2)  # Función objetivo

#Derivada parcial de E con respecto a u
def dEu(u,v):
    return (2*(u*v*pow(e, -pow(u,2)-pow(v,2)))*v*pow(e, -pow(u,2)-pow(v,2))+u*v*pow(e, -pow(u,2)-pow(v,2))*(-2*u))
    
#Derivada parcial de E con respecto a v
def dEv(u,v):
    return (2*(u*v*pow(e, -pow(u,2)-pow(v,2)))*u*pow(e, -pow(u,2)-pow(v,2))+u*v*pow(e, -pow(u,2)-pow(v,2))*(-2*v))

#Gradiente de E
def gradE(u,v):
    return np.array([dEu(u,v), dEv(u,v)])

def gradient_descent(w_ini, lr, grad_fun, fun, epsilon, max_iters):
    iterations = 0  # Fijamos numero de iteraciones actuales a 0, error actual al valor de la función en el punto inicial y declaramos w como la inicial
    w = w_ini
    cost = fun(w[0],w[1])   # Coste inicial a None, para que en la primera iteración no considere el cálculo del error
    while iterations < max_iters and cost > epsilon:  # Hasta que no superemos las máximas iteraciones o no avance lo suficiente
        w = w - lr*(grad_fun(w[0],w[1])/np.linalg.norm(grad_fun(w[0],w[1])))   # Actualizamos la w con el gradiente, normalizando
        cost = fun(w[0],w[1])
        iterations+=1

    return w, iterations 

def gradient_descent_to_draw(w_ini, lr, grad_fun, fun, epsilon, max_iters): # Igual a la función anterior, solo que devuelve también todos los estados por los que ha pasado w
    iterations = 0
    w = w_ini
    all_w = [w]
    cost = fun(w[0],w[1])   # Coste inicial a None, para que en la primera iteración no considere el cálculo del error
    while iterations < max_iters and cost > epsilon:  # Hasta que no superemos las máximas iteraciones o no avance lo suficiente
        w = w - lr*(grad_fun(w[0],w[1])/np.linalg.norm(grad_fun(w[0],w[1])))   # Actualizamos la w con el gradiente, normalizando
        cost = fun(w[0],w[1])
        all_w.append(w)
        iterations+=1

    return tuple((w, iterations, all_w))


eta = 0.1 
maxIter = 10000000000
error2get = 1e-8
initial_point_e = np.array([0.5,-0.5])
w_e, it_e, all_w_e = gradient_descent_to_draw(initial_point_e, eta, gradE, E, error2get, maxIter)

display_figure(2, E, all_w_e, 'plasma', 'Función E')
plt.show()


print ('Numero de iteraciones: ', it_e)
print('Coste asociado: ', E(w_e[0],w_e[1]))
print ('Coordenadas obtenidas: (', w_e[0], ', ', w_e[1],')')

input("\n--- Pulsar tecla para continuar ---\n")


print('EJERCICIO SOBRE LA BUSQUEDA ITERATIVA DE OPTIMOS\n')
print('Ejercicio 3a\n')


def F(u,v):
    return (pow(u,2) + 2*pow(v,2) + 2*sin(2*pi*u)*sin(pi*v))  # Función objetivo

#Derivada parcial de F con respecto a u
def dFu(u,v):
    return (2*u+2*cos(2*pi*u)*sin(pi*v)*2*pi)
    
#Derivada parcial de F con respecto a v
def dFv(u,v):
    return (4*v + 2*sin(2*pi*u)*cos(pi*v)*pi)

#Gradiente de F
def gradF(u,v):
    return np.array([dFu(u,v), dFv(u,v)])

eta_1 = 0.01    # Establecemos los lr para las 2 pruebas a realizar, al igual que las máximas iteraciones
eta_2 = 0.1
maxIter = 50
error2get = -100000
initial_point_f = np.array([-1,1])  # Punto inicial

(w_f1, it_f1, all_w_f1) = gradient_descent_to_draw(initial_point_f, eta_1, gradF, F, error2get, maxIter)
print ('Numero de iteraciones con lr de 0.01: ', it_f1)
print ('Coordenadas obtenidas con lr de 0.01: (', w_f1[0], ', ', w_f1[1],')')


(w_f2, it_f2, all_w_f2) = gradient_descent_to_draw(initial_point_f, eta_2, gradF, F, error2get, maxIter)
print ('Numero de iteraciones con lr de 0.1: ', it_f2)
print ('Coordenadas obtenidas con lr de 0.1: (', w_f2[0], ', ', w_f2[1],')')

display_figure(2, F, all_w_f1, 'plasma','$\eta = 0.01$')
display_figure(2, F, all_w_f2, 'plasma','$\eta = 0.1$')
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")


print('EJERCICIO SOBRE LA BUSQUEDA ITERATIVA DE OPTIMOS\n')
print('Ejercicio 1.3b\n')

initial_points = [ [-0.5, -0.5], [1, 1], [2.1, -2.1], [-3, 3], [-2, 2]]
etas = [0.01, 0.1]

for point in initial_points:
    for eta in etas:
        w, it = gradient_descent(point, eta, gradF, F, error2get, maxIter)

        print ('Numero de iteraciones con lr de {} y punto inicial {}: {}'.format(eta, point, it))
        print('Valor asociado: ', F(w[0],w[1]))
        print ('Coordenadas obtenidas con lr de {} y punto inicial {}: ({},{})'.format(eta, point, w[0], w[1]))
        
        

input("\n--- Pulsar tecla para continuar ---\n")

###############################################################################
###############################################################################
###############################################################################
###############################################################################
print('EJERCICIO SOBRE REGRESION LINEAL\n')
print('Ejercicio 1\n')

label5 = 1
label1 = -1

# Funcion para leer los datos
def readData(file_x, file_y):
	# Leemos los ficheros	
	datax = np.load(file_x)
	datay = np.load(file_y)
	y = []
	x = []	
	# Solo guardamos los datos cuya clase sea la 1 o la 5
	for i in range(0,datay.size):
		if datay[i] == 5 or datay[i] == 1:
			if datay[i] == 5:
				y.append(label5)
			else:
				y.append(label1)
			x.append(np.array([1, datax[i][0], datax[i][1]]))
			
	x = np.array(x, np.float64)
	y = np.array(y, np.float64)
	
	return x, y

# Funcion para calcular el error
def Err(x,y,w = 0):
    error = 0
    for value, result in zip(x,y):
        error += pow((np.dot(w,value) - result),2)
    error /= len(x)
    return error

# Gradiente Descendente Estocastico
# Fuente: https://medium.com/@nikhilparmar9/simple-sgd-implementation-in-python-for-linear-regression-on-boston-housing-data-f63fcaaecfb1
def sgd(train_data, lr, y, epsilon, max_iter, batch_size):

    w = np.zeros(len(train_data[0]))   # Vector de 0s para los pesos al inicio
    iterations = 0
    Ein = Err(train_data,y,w)       # El error se calcula en función de los pesos y train
    all_Ein = [Ein]
    curr_batch = 0

    merged = list(zip(train_data, y))     # Juntamos las x e y para desordenarlas y luego las volvemos a separar para usarlas por separado
    random.shuffle(merged)
    shuffled_train = [item[0] for item in merged]
    shuffled_y = [item[1] for item in merged]

    while Ein > epsilon and iterations < max_iter:

        if((curr_batch+batch_size) >= len(train_data)): # Si es necesario, barajamos los datos para crear nuevos minibatches
            merged = list(zip(train_data, y))   # Importante juntar los datos con los resultados para poder calcularlo todo correctamente
            random.shuffle(merged)
            shuffled_train = [item[0] for item in merged]
            shuffled_y = [item[1] for item in merged]
            curr_batch = 0


        gradiente_w = np.zeros(len(train_data[0]))  # Inicializamos los gradientes del peso a 0
            
        for k in range(batch_size):     # Calculamos el gradiente para el minibatch
            prediccion = np.dot(w, shuffled_train[k+curr_batch])
            gradiente_w = gradiente_w + 2*np.dot(shuffled_train[k+curr_batch],(prediccion - shuffled_y[k+curr_batch]))


            
        gradiente_w /= batch_size

        w = w - lr*gradiente_w
            
        Ein = Err(train_data,y,w)   # Calculamos el error de nuevo

        all_Ein.append(Ein)

        if Ein < epsilon:   # Si cumplimos el requisito, salimos
            break

        iterations+=1

        curr_batch += batch_size


    
    return w    # Tan solo devolvemos los pesos

# Pseudoinversa	
def pseudoinverse(x,y):
    x_t = np.matrix.transpose(x)
    U_x, D_x, V_t_x = np.linalg.svd(x)  # Importante, la matriz diagonal D_x nos viene en forma de array, pasar a matriz con np.diag()
    VDDVt = np.dot(np.dot(np.dot(V_t_x.T,np.diag(D_x)),np.diag(D_x)),V_t_x)
    w = np.dot(np.dot(np.linalg.inv(VDDVt),x_t),y)
    return w


# Lectura de los datos de entrenamiento
x, y = readData('datos/X_train.npy', 'datos/y_train.npy')
# Lectura de los datos para el test
x_test, y_test = readData('datos/X_test.npy', 'datos/y_test.npy')



w_s = sgd(x, 0.02, y, 1e-4, 200, 32)
print ('Bondad del resultado para grad. descendente estocastico:\n')
print ("Ein: ", Err(x,y,w_s))
print ("Eout: ", Err(x_test, y_test, w_s))

w_p = pseudoinverse(x,y)      # Calculamos también con la pseudoinversa
print ('\nBondad del resultado para pseudoinversa:\n')
print ("Ein: ", Err(x,y,w_p))
print ("Eout: ", Err(x_test, y_test, w_p))


fig = plt.figure(figsize=plt.figaspect(0.5))    # Mostramos por pantalla figuras

ax = fig.add_subplot(1, 2, 1, title="Datos proporcionados en train")    # Con los datos que nos proporcionan en train y test y la línea que define al sgd y la pseudoinversa
plt.scatter(x[np.where(y == -1), 1], x[np.where(y == -1), 2], c="red", label="label -1")
plt.scatter(x[np.where(y == 1), 1], x[np.where(y == 1), 2], c="blue", label="label 1")

t_train = np.arange(0,np.amax(x),0.5)
plt.plot(t_train, -w_s[0]/w_s[2]-w_s[1]/w_s[2]*t_train, 'black', label="clasificador del sgd")
plt.plot(t_train, -w_p[0]/w_p[2]-w_p[1]/w_p[2]*t_train, 'purple', label="clasificador de la pseudoinversa")
plt.legend()

ax = fig.add_subplot(1, 2, 2, title="Datos proporcionados en test")
plt.scatter(x_test[np.where(y_test == -1), 1], x_test[np.where(y_test == -1), 2], c="orange", label="label -1")
plt.scatter(x_test[np.where(y_test == 1), 1], x_test[np.where(y_test == 1), 2], c="cyan", label="label 1")

t_test = np.arange(0,np.amax(x_test),0.5)
plt.plot(t_test, -w_s[0]/w_s[2]-w_s[1]/w_s[2]*t_test, 'black', label="clasificador del sgd")
plt.plot(t_test, -w_p[0]/w_p[2]-w_p[1]/w_p[2]*t_test, 'purple', label="clasificador de la pseudoinversa")
plt.legend()


plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print('Ejercicio 2\n')

# Simula datos en un cuadrado [-size,size]x[-size,size]
def simula_unif(N, d, size):
	return np.random.uniform(-size,size,(N,d))

def sign(x):
	if x >= 0:
		return 1
	return -1

def f(x1, x2):
	return sign((x1-0.2)**2+x2**2-0.6) 

f = np.vectorize(f)

AvgEin_linear = 0
AvgEout_linear = 0
for i in range(1000):

    training_sample = simula_unif(1000,2,1)     # Creamos los datos

    func_result = f(training_sample[:,0],training_sample[:,1])
    merged_training = list(zip(func_result, training_sample))   # barajamos los valores como hacíamos en el sgd
    random.shuffle(merged_training)
    func_result = [item[0] for item in merged_training]
    training_sample = [item[1] for item in merged_training]

    for result in func_result[0:int(len(func_result)/10)]:       # Invertimos el valor del 10% de ellos para introducir ruido
        if result == 1:
            result = -1
        else:
            result = 1

    merged_training = list(zip(func_result, training_sample))   # Volvemos a barajar
    random.shuffle(merged_training)
    func_result = [item[0] for item in merged_training]
    training_sample = [item[1] for item in merged_training]

    training_sample = [[1,x[0],x[1]] for x in training_sample]  # Reformateamos la lista de entrenamiento de tal forma que el primer elemento de cada objeto sea 1

    func_weights = sgd(training_sample, 0.05, func_result, 1e-4, 100, 25)

    AvgEin_linear += Err(training_sample, func_result, func_weights)/1000

    training_sample = simula_unif(1000,2,1) # Creamos nuevos datos para Eout
    training_sample = [[1,x[0],x[1]] for x in training_sample]  # Y ponemos el 1 al comienzo

    AvgEout_linear += Err(training_sample, func_result, func_weights)/1000

AvgEin_nonLineal = 0
AvgEout_nonLineal = 0
for i in range(1000):

    training_sample = simula_unif(1000,2,1)     # Creamos los datos

    func_result = f(training_sample[:,0],training_sample[:,1])
    merged_training = list(zip(func_result, training_sample))   # barajamos los valores como hacíamos en el sgd
    random.shuffle(merged_training)
    func_result = [item[0] for item in merged_training]
    training_sample = [item[1] for item in merged_training]

    for result in func_result[0:int(len(func_result)/10)]:       # Invertimos el valor del 10% de ellos para introducir ruido
        if result == 1:
            result = -1
        else:
            result = 1

    merged_training = list(zip(func_result, training_sample))   # Volvemos a barajar
    random.shuffle(merged_training)
    func_result = [item[0] for item in merged_training]
    training_sample = [item[1] for item in merged_training]

    training_sample = [[1,x[0],x[1],x[0]*x[1],x[0]*x[0],x[1]*x[1]] for x in training_sample]  # Reformateamos la lista de entrenamiento de tal forma que el primer elemento de cada objeto sea 1

    func_weights = sgd(training_sample, 0.05, func_result, 1e-4, 100, 25)

    AvgEin_nonLineal += Err(training_sample, func_result, func_weights)/1000

    training_sample = simula_unif(1000,2,1) # Creamos nuevos datos para Eout
    training_sample = [[1,x[0],x[1],x[0]*x[1],x[0]*x[0],x[1]*x[1]] for x in training_sample]  # Y ponemos el 1 al comienzo

    AvgEout_nonLineal += Err(training_sample, func_result, func_weights)/1000

print("Con características lineales:\n")
print("Ein medio en 1000 muestras: {}\n".format(AvgEin_linear))
print("Eout medio en 1000 muestras: {}\n".format(AvgEout_linear))

print("Con características no lineales:\n")
print("Ein medio en 1000 muestras: {}\n".format(AvgEin_nonLineal))
print("Eout medio en 1000 muestras: {}\n".format(AvgEout_nonLineal))

