import random
import numpy as np
from . import Conjunto

class Genetico(Conjunto.Conjunto):

    def __init__(self, TamPobl, Pmutacion, pCruce, archivoDatos):
        Conjunto.Conjunto._leer_datos(self, archivoDatos)
        self.ProbMut = Pmutacion
        self.TamPobl = TamPobl
        self.p_cruce = pCruce
    
    def reemplazar(self, pob, nueva_pob, costes, solucion, elit):
        # A implementar en cada tipo de AG
        pass
    
    def cruce_uniforme(self, padre1, padre2, alet):
        hijo = np.zeros(self.n, dtype=int)
        indices_padre1 = self.get_indices(padre1)
        indices_padre2 = self.get_indices(padre2)
        indices_hijo = [i for i in indices_padre1 if i in indices_padre2]
        hijo[indices_hijo] = 1

        pos_distintas = [i for i in indices_padre1 if not i in indices_hijo]
        pos_distintas.extend([i for i in indices_padre2 if not i in indices_hijo])

        se_pone = np.random.choice(alet, size=len(pos_distintas))

        for indice, poner in zip(pos_distintas, se_pone):
            if poner == 1:
                hijo[indice] = 1


        self.reparar_solucion(hijo)
        return hijo
    
    def cruce_segmento(self, padre1, padre2, alet):
        hijo = np.zeros(self.n, dtype=int)
        indices_padres = [i for i in range(self.n) if padre1[i] == 1 and padre2[i] == 1]
        hijo[indices_padres] = 1
        indices_hijo = self.get_indices(hijo)

        por_asignar = self.m - len(indices_hijo)

        indices_disponibles = [i for i in range(self.n) if not i in indices_hijo]

        indices_sel = np.random.choice(indices_disponibles, size=por_asignar)
        hijo[indices_sel] = 1

        self.reparar_solucion(hijo)
        return hijo
    
    def mutar(self, poblacion):     # Mutación de la población
        mutaciones = self.ProbMut * len(poblacion)  # Seleccionamos cuantos individuos vamos a mutar en función de la probabilidad de mutación
        individuos_a_mutar = np.random.choice([i for i in range(self.TamPobl)], size=int(mutaciones))   # Seleccionamos los individuos a mutar
        for indice in individuos_a_mutar: # De cada individuo a mutar cambiamos valores de 1 posicion a otra, mutándolo
            indices_usados = self.get_indices(poblacion[indice])
            indices_disponibles = [i for i in range(self.n) if not i in indices_usados]
            indice_cambio_a0 = np.random.choice(indices_usados, size=1, replace=False)
            indice_cambio_a1 = np.random.choice(indices_disponibles, size=1, replace=False)

            poblacion[indice][indice_cambio_a0] = 0
            poblacion[indice][indice_cambio_a1] = 1
    
    def seleccion(self, poblacion, costes, num_selecciones):
        padres = []
        
        for _ in range(num_selecciones):
            indice1, indice2 = random.randrange(0, len(poblacion)), random.randrange(0, len(poblacion)) #Dos indices
            padres.append(poblacion[indice1 if costes[indice1] < costes[indice2] else indice2]) # Seleccionamos el mejor
        
        return padres

    def cruzar(self, poblacion, cruce):
        aleatorio = [random.randint(0,1) for i in range(self.n)]
        for i in range(0, int(self.p_cruce*len(poblacion)/2), 2):
            hijo1 = cruce(poblacion[i], poblacion[i+1], aleatorio)
            hijo2 = cruce(poblacion[i], poblacion[i+1], aleatorio)
            poblacion[i] = hijo1
            poblacion[i+1] = hijo2
    
    def ejecutar_alg(self, max_evals, tam_sel, cruce, elit):

        self.it = 0
        evolucion = [] # Vamos a ir guardando el recorrido de la población para convertirlo en una gráfica
        if cruce == 'unif':
            cruce = self.cruce_uniforme
        elif cruce == 'seg':
            cruce = self.cruce_segmento
        else:
            return None
        
        # Inicializamos poblacion
        poblacion = []
        for _ in range(self.TamPobl):
            poblacion.append(self.generar_Sol())
        
        pesos_poblacion = [self.calcular_disp(individuo) for individuo in poblacion]

        mejor_ind = np.argmin(pesos_poblacion)
        solucion = poblacion[mejor_ind].copy()
        disp_act = pesos_poblacion[mejor_ind]

        while self.it < max_evals:

            nueva_poblacion = self.seleccion(poblacion, pesos_poblacion, tam_sel)
            self.cruzar(nueva_poblacion, cruce)
            self.mutar(nueva_poblacion)
            poblacion, pesos_poblacion = self.reemplazar(poblacion, nueva_poblacion, pesos_poblacion, solucion, elit)

            mejor_ind = np.argmin(pesos_poblacion)
            evolucion.append((self.it, pesos_poblacion[mejor_ind]))
            if pesos_poblacion[mejor_ind] < disp_act:
                solucion = poblacion[mejor_ind].copy()
                disp_act = pesos_poblacion[mejor_ind]

        result = {
            "evolucion" : evolucion,
            "iteraciones" : self.it,
            "dispersion" : disp_act
        }

        return solucion, result


class AGG(Genetico):

    def reemplazar(self, pob, nueva_pob, costes, solucion, elit):
        if elit:
            nueva_pob[-1] = solucion.copy()
        nuevos_pesos = [self.calcular_disp(ind) for ind in nueva_pob]
        self.it += len(nueva_pob)
        return nueva_pob, nuevos_pesos
    
class AGE(Genetico):
    
    def reemplazar(self, pob, nueva_pob, costes, solucion, elit):
        peor_indice = np.argmax(costes)
        peor = costes[peor_indice]
        costes[peor_indice] = 0
        segundo_peor_indice = np.argmax(costes)
        costes[peor_indice] = peor

        elegidos = [(pob[peor_indice], costes[peor_indice]), (pob[segundo_peor_indice], costes[segundo_peor_indice])]
        for individuo in nueva_pob:
            self.it += 1
            elegidos.append((individuo, self.calcular_disp(individuo)))
        
        elegidos.sort(key=lambda elegido : elegido[1])
        pob[peor_indice] = elegidos[0][0].copy()
        costes[peor_indice] = elegidos[0][1]
        pob[segundo_peor_indice] = elegidos[1][0].copy()
        costes[segundo_peor_indice] = elegidos[1][1]
        return pob, costes
