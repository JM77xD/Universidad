import random
import numpy as np
from. import Conjunto

class Memetico(Conjunto.Conjunto):

    def __init__(self, TamPobl, Pmutacion, pCruce, archivoDatos):
        Conjunto.Conjunto._leer_datos(self, archivoDatos)
        self.ProbMut = Pmutacion
        self.TamPobl = TamPobl
        self.p_cruce = pCruce

    def cruzar(self, pob, cruce):
        aleatorio = [random.randint(0,1) for i in range(self.n)]
        for i in range(0, int(self.p_cruce*len(pob)/2), 2):
            hijo1 = cruce(pob[i], pob[i+1], aleatorio)
            hijo2 = cruce(pob[i], pob[i+1], aleatorio)
            pob[i] = hijo1
            pob[i+1] = hijo2
    
    def reemplazar(self, pob, nueva_pob, costes, solucion, elit):
        if elit:
            nueva_pob[-1] = solucion.copy()
        nuevos_pesos = [self.calcular_disp(ind) for ind in nueva_pob]
        self.it += len(nueva_pob)
        return nueva_pob, nuevos_pesos
    
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

    def busqueda_local(self, sol, max_neighbours):
        changing = True
        evaluations = 0
        sol_weights = self.calcular_pesos(sol)
        self.it += 1
        sol_weights.sort()

        while changing and evaluations < max_neighbours:
            changing = False
            sol_index = self.get_indices(sol)
            options = [i for i in range(self.n) if not i in sol_index]

            random.shuffle(options)

            for u in sol_index:
                for v in options:

                    evaluations += 1

                    if evaluations >= max_neighbours:
                        break

                    newSol, newSol_costs = self.Int(sol, sol_weights, u, v)
                    newSol_costs.sort()

                    if (newSol_costs[-1] - newSol_costs[0]) < (sol_weights[-1] - sol_weights[0]):
                        changing = True
                        sol_weights = newSol_costs.copy()
                        sol = newSol.copy()
                        break
                        


    def busqueda_local_generacional(self, pob, gen_to_bl, prob, mej, failures):
        if self.gen % gen_to_bl == 0:
            if mej:
                dispersiones = [[self.calcular_disp(ind), index] for ind, index in zip(pob,range(len(pob)))]
                self.it += len(pob)
                dispersiones.sort(key=lambda valores : valores[0])
                seleccion = [ind[1] for ind in dispersiones[:int(len(pob)*prob)]]
            else:
                seleccion = random.sample(range(0, len(pob)), int(len(pob)*prob))
            
            for i in seleccion:
                self.busqueda_local(pob[i], failures)
    

    def ejecutar_alg(self, max_evals, tam_sel, cruce, elit, gen_to_bl, prob_bl, mej_bl, failures_bl):

        self.it = 0
        self.gen = 1
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
            self.busqueda_local_generacional(nueva_poblacion, gen_to_bl, prob_bl, mej_bl, failures_bl)
            poblacion, pesos_poblacion = self.reemplazar(poblacion, nueva_poblacion, pesos_poblacion, solucion, elit)

            mejor_ind = np.argmin(pesos_poblacion)
            evolucion.append((self.it, pesos_poblacion[mejor_ind]))
            if pesos_poblacion[mejor_ind] < disp_act:
                solucion = poblacion[mejor_ind].copy()
                disp_act = pesos_poblacion[mejor_ind]
            
            self.gen += 1

        result = {
            "evolucion" : evolucion,
            "iteraciones" : self.it,
            "dispersion" : disp_act,
            "generaciones" : self.gen
        }

        return solucion, result
