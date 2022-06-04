import random
import numpy as np

class Conjunto:

    def _leer_datos(self, archivo_datos):
        file = open(archivo_datos)

        first_line = file.readline().split(' ')
        self.n, self.m = int(first_line[0]), int(first_line[1])   # Leemos numero de elementos y objetivo

        self.datos = np.zeros((self.n,self.n))   # Creamos la matriz de entradas

        for line in file:
            line = line.strip('\n').split(' ')
            self.datos[int(line[0]), int(line[1])] = float(line[2])
            self.datos[int(line[1]), int(line[0])] = float(line[2])
        
        file.close()
    
    def __init__(self, archivo_datos):
        self._leer_datos(archivo_datos)
    
    def get_indices(self, Solucion):
        indices = [i for i in range(self.n) if Solucion[i] == 1]
        return indices
    
    def es_solucion(self, Solucion):
        return len([i for i in Solucion if i == 1]) == self.m
    
    def calcular_pesos(self, Solucion):
        pesos = []
        indices = self.get_indices(Solucion)
        for pos1 in indices:
            peso = 0
            for pos2 in indices:
                peso += self.datos[pos1, pos2]
            pesos.append(peso)

        return pesos
    
    def calcular_disp(self, Solucion, pesos=None):
        if not pesos:
            pesos = self.calcular_pesos(Solucion)
        indice_min = np.argmin(pesos)
        indice_max = np.argmax(pesos)
        return (pesos[indice_max] - pesos[indice_min])
    
    def generar_Sol(self):
        solucion = np.zeros(self.n, dtype=int)
        indices_sol = np.random.choice(range(self.n), size=self.m, replace=False)
        solucion[indices_sol] = 1
        return solucion
    
    def get_media(self, Solucion):
        media = 0
        pesos = self.calcular_pesos(Solucion)
        for peso in pesos:
            media += peso
        
        if pesos:
            media /= len(pesos)

        return media
    
    def get_media_and_pesos(self, Solucion):
        media = 0
        pesos = self.calcular_pesos(Solucion)
        for peso in pesos:
            media += peso
        
        if pesos:
            media /= len(pesos)

        return media, pesos
    
    def reparar_solucion(self, Solucion):
        if not self.es_solucion(Solucion):
            if len([i for i in Solucion if i == 1]) > self.m:
                while len([i for i in Solucion if i == 1]) > self.m:
                    media = self.get_media(Solucion)
                    index = self.get_most_impacting_element(Solucion, media)
                    Solucion[index] = 0
            else:
                while len([i for i in Solucion if i == 1]) < self.m:
                    media = self.get_media(Solucion)
                    index = self.get_least_impacting_element(Solucion, media)
                    Solucion[index] = 1
    
    def Int(self, Sol, Sol_costs, u, v):
        newSol = Sol.copy()
        newSol[v] = 1
        newSol[u] = 0
        sol_index = self.get_indices(Sol)


        u_index = sol_index.index(u)

        newSol_costs = [elem - self.datos[u, item] + self.datos[v, item] for elem, item in zip(Sol_costs, sol_index)]
        newSol_costs.pop(u_index)
        
        value = 0
        newSol_index = self.get_indices(newSol)
        v_index = newSol_index.index(v)
        for elem in newSol_index:
            value += self.datos[v, elem]
        
        newSol_costs.insert(v_index, value)

        return newSol, newSol_costs
    
    def get_most_impacting_element(self, Solucion, mean):
        selected_elements = self.get_indices(Solucion)
        maximo = float('-inf')
        mean_difference = float('-inf')

        for elem in selected_elements:
            contribution = 0
            for elem2 in [elem2 for elem2 in selected_elements if elem2 != elem]:
                contribution += self.datos[elem, elem2]
            if abs(contribution - mean) > mean_difference:
                maximo = elem
                mean_difference = abs(contribution - mean)
        
        return maximo
    
    def get_least_impacting_element(self, Solucion, mean):
        selected_elements = self.get_indices(Solucion)

        minimo = float('inf')
        mean_difference = float('inf')
        for pos in [ pos for pos in range(self.n) if not pos in selected_elements]:
            delta_for_pos = 0
            for elem in selected_elements:
                delta_for_pos += self.datos[pos, elem]
            if abs(delta_for_pos - mean) < mean_difference:
                minimo = pos
                mean_difference = abs(delta_for_pos - mean)
        
        return minimo

    def generarVecino(self, solucion, pesos):
        indices = self.get_indices(solucion)
        opciones = [ i for i in range(self.n) if not i in indices]
        meterSol = np.random.choice(opciones, size=1)
        sacarSol = np.random.choice(indices, size=1)

        return self.Int(solucion, pesos, sacarSol, meterSol)