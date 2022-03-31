# -*- coding: utf-8 -*-

from math import e, pi, sin, cos
import numpy as np
import matplotlib.pyplot as plt


def display_figure(rng_val, fun, ws, colormap, title_fig):
    # https://jakevdp.github.io/PythonDataScienceHandbook/04.12-three-dimensional-plotting.html
    from mpl_toolkits.mplot3d import Axes3D
    x = np.linspace(-rng_val, rng_val, 50)
    y = np.linspace(-rng_val, rng_val, 50)
    X, Y = np.meshgrid(x, y)
    myFun = np.vectorize(fun, excluded=['X', 'Y'])
    Z = myFun(X,Y)
    fig = plt.figure()
    ax = Axes3D(fig)
    fig.add_axes()
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


def simula_unif(N, d, size):
	return np.random.uniform(-size,size,(N,d))

def gradient_descent(w_ini, lr, grad_fun, fun, epsilon, max_iters):
    iterations = 0  # Fijamos numero de iteraciones actuales a 0, error actual al valor de la función en el punto inicial y declaramos w como la inicial
    w = w_ini
    cost = fun(w[0],w[1])   # Coste inicial al valor de la función
    while iterations < max_iters and cost > epsilon:  # Hasta que no superemos las máximas iteraciones o no lleguemos al valor esperado
        w = w - lr*(grad_fun(w[0],w[1])/np.linalg.norm(grad_fun(w[0],w[1])))   # Actualizamos la w con el gradiente, normalizando
        cost = fun(w[0],w[1])
        iterations+=1

    return w, iterations 

# Igual a la función anterior, solo que devuelve también todos los estados por los que ha pasado w
def gradient_descent_to_draw(w_ini, lr, grad_fun, fun, epsilon, max_iters):
    iterations = 0
    w = w_ini
    all_w = [w]
    cost = fun(w[0],w[1])
    while iterations < max_iters and cost > epsilon:
        w = w - lr*(grad_fun(w[0],w[1])/np.linalg.norm(grad_fun(w[0],w[1])))
        cost = fun(w[0],w[1])
        all_w.append(w)
        iterations+=1

    return tuple((w, iterations, all_w))


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


eta = 0.1 
maxIter = 10000000000
error2get = 1e-8
initial_point_e = np.array([0.5,-0.5])
w_e, it_e, all_w_e = gradient_descent_to_draw(initial_point_e, eta, gradE, E, error2get, maxIter)

display_figure(2, E, all_w_e, 'plasma', 'Función E')
plt.show()


print ('Numero de iteraciones: ', it_e)
print('Punto asociado: ', E(w_e[0],w_e[1]))
print ('Coordenadas obtenidas: (', w_e[0], ', ', w_e[1],')')


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

initial_points = [ [-0.5, -0.5], [1, 1], [2.1, -2.1], [-3, 3], [-2, 2]]
etas = [0.01, 0.1]

for point in initial_points:
    for eta in etas:
        w, it = gradient_descent(point, eta, gradF, F, error2get, maxIter)

        print ('lr de {} y punto inicial {}'.format(eta, point))
        print('Valor asociado: ', F(w[0],w[1]))
        print ('Coordenadas obtenidas con lr de {} y punto inicial {}: ({},{})'.format(eta, point, w[0], w[1]))
        print()

# Funcion para calcular el error
def Err(x,y,w):
    error = np.sum((y - (x @ w))**2, axis=0)/len(x)
    return error

# Gradiente Descendente Estocastico
# Fuentes: https://medium.com/@nikhilparmar9/simple-sgd-implementation-in-python-for-linear-regression-on-boston-housing-data-f63fcaaecfb1
# https://stackoverflow.com/questions/63518634/stochastic-gradient-descent-implementation-in-python-from-scratch-is-the-implem
def sgd(train_data, lr, y, epsilon, max_iter, batch_size):

    w = np.random.normal(size=len(train_data[0])) # Muestras aleatorias en una distribución Gaussiana para los pesos al inicio
    iterations = 0
    Ein = Err(train_data,y,w)       # El error se calcula en función de los pesos, train e y

    while Ein > epsilon and iterations < max_iter:

        indices = np.random.choice(np.arange(len(y)), size=batch_size, replace=False)
        shuffled_train, shuffled_y = train_data[indices], y[indices]
        

        prediccion = shuffled_train @ w

        gradiente_w = (2/batch_size)*np.sum((prediccion- shuffled_y).reshape(-1,1) * shuffled_train, axis=0)

        w -= lr*gradiente_w
            
        Ein = Err(train_data,y,w)   # Calculamos el error de nuevo

        if Ein < epsilon:   # Si cumplimos el requisito, salimos
            break

        iterations+=1

    
    return w    # Tan solo devolvemos los pesos

label5 = 1
label1 = -1

nombreCarpeta = 'data'    # Cambiar con el nombre de la carpeta donde tenemos los datos
# Lectura de los datos de entrenamiento
x, y = readData(nombreCarpeta+'/X_train.npy', nombreCarpeta+'/y_train.npy')
# Lectura de los datos para el test
x_test, y_test = readData(nombreCarpeta+'/X_test.npy', nombreCarpeta+'/y_test.npy')

def pseudoinverse(x,y):
    x_t = np.matrix.transpose(x)
    U_x, D_x, V_t_x = np.linalg.svd(x)  # Importante, la matriz diagonal D_x nos viene en forma de array, pasar a matriz con np.diag()
    VDDVt = np.dot(np.dot(np.dot(V_t_x.T,np.diag(D_x)),np.diag(D_x)),V_t_x)
    w = np.dot(np.dot(np.linalg.inv(VDDVt),x_t),y)
    return w

w_s = sgd(x, 0.02, y, 1e-4, 200, 64)
print ('Bondad del resultado para grad. descendente estocastico:\n')
print ("Ein: ", Err(x,y,w_s))
print ("Eout: ", Err(x_test, y_test, w_s))

w_p = pseudoinverse(x,y)
print ('\nBondad del resultado para pseudoinversa:\n')
print ("Ein: ", Err(x,y,w_p))
print ("Eout: ", Err(x_test, y_test, w_p))


fig = plt.figure(figsize=plt.figaspect(0.5))

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

training_sample = simula_unif(1000,2,1)

plt.scatter(training_sample[:,0], training_sample[:,1])
plt.title("Muestra aleatoria creada con simula_unif")
plt.show()

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
    training_sample = np.array([[1,x[0],x[1]] for x in training_sample])
    
    indices = np.random.choice(len(func_result), size=100, replace=False)      
    func_result[indices] = -func_result[indices]          # Invertimos el valor del 10% de ellos para introducir ruido

    func_weights = sgd(training_sample, 0.05, func_result, 1e-4, 100, 32)

    AvgEin_linear += Err(training_sample, func_result, func_weights)/1000

    training_sample = simula_unif(1000,2,1) # Creamos nuevos datos para Eout
    func_result = f(training_sample[:,0],training_sample[:,1])
    training_sample = np.array([[1,x[0],x[1]] for x in training_sample])

    AvgEout_linear += Err(training_sample, func_result, func_weights)/1000

print("Con características lineales:\n")
print("Ein medio en 1000 muestras: {}\n".format(AvgEin_linear))
print("Eout medio en 1000 muestras: {}\n".format(AvgEout_linear))

AvgEin_nonLinear = 0
AvgEout_nonLinear = 0
for i in range(1000):

    training_sample = simula_unif(1000,2,1)     # Creamos los datos

    func_result = f(training_sample[:,0],training_sample[:,1])
    training_sample = np.array([[1,x[0],x[1],x[0]*x[1],x[0]*x[0],x[1]*x[1]] for x in training_sample])  # Reformateamos la lista de entrenamiento de tal forma que el primer elemento de cada objeto sea 1
    
    indices = np.random.choice(len(func_result), size=100, replace=False)      
    func_result[indices] = -func_result[indices]          # Invertimos el valor del 10% de ellos para introducir ruido

    func_weights = sgd(training_sample, 0.05, func_result, 1e-4, 100, 25)

    AvgEin_nonLinear += Err(training_sample, func_result, func_weights)/1000

    training_sample = simula_unif(1000,2,1)
    func_result = f(training_sample[:,0], training_sample[:,1])
    training_sample = np.array([[1,x[0],x[1],x[0]*x[1],x[0]*x[0],x[1]*x[1]] for x in training_sample]) # Creamos nuevos datos para Eout

    AvgEout_nonLinear += Err(training_sample, func_result, func_weights)/1000

print("Con características no lineales:\n")
print("Ein medio en 1000 muestras: {}\n".format(AvgEin_nonLinear))
print("Eout medio en 1000 muestras: {}\n".format(AvgEout_nonLinear))


training_sample = simula_unif(1000,2,1)

results = f(training_sample[:,0], training_sample[:,1])


plt.scatter(training_sample[np.where(results == 1),0], training_sample[np.where(results == 1),1], c='b')
plt.scatter(training_sample[np.where(results == -1),0], training_sample[np.where(results == -1),1], c='r')
plt.title("Clasificación de una muestra aleatoria")
plt.show()
