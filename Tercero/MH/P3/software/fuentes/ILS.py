import random
from . import Conjunto
import numpy as np
import math

class ILS(Conjunto.Conjunto):

    def __init__(self, archivo_datos, mu, phi, finalT):
        super().__init__(archivo_datos)
        self.mu = mu
        self.phi = phi
        self.max_vecinos = 10 * self.n
        self.max_exitos = self.n
        self.Tfinal = finalT
        self.numMut = int(0.3*self.m) if int(0.3*self.m) > 0 else 1

    
    def mutar(self, solucion):
        indices = self.get_indices(solucion)
        options = [ i for i in range(self.n) if not i in indices]

        convert_to1 = np.random.choice(options, size=self.numMut)
        convert_to0 = np.random.choice(indices, size=self.numMut)

        solucion[convert_to0] = 0
        solucion[convert_to1] = 1

        return self.calcular_pesos(solucion)

    
    def es(self, sol_inicial, sol_weights = None):

        evaluaciones = 0

        sol = sol_inicial
        
        if sol_weights:
            sol_w = sol_weights.copy()
        else:
            sol_w = self.calcular_pesos(sol)
            
        sol_disp = self.calcular_disp(sol, sol_w)

        best_sol = sol.copy()
        best_sol_w = sol_w.copy()
        best_sol_disp = self.calcular_disp(best_sol, best_sol_w)

        self.M = self.max_evals/self.max_vecinos

        self.Tini = (self.mu * self.calcular_disp(sol, sol_w))/(-math.log(self.phi))    # Calculamos la T inicial

        self.T = self.Tini

        self.beta = (self.Tini - self.Tfinal)/(self.M * self.Tfinal * self.Tini) if self.Tini != 0 else 0

        self.decrement = lambda t : t/(1 + self.beta * t) if self.Tini != 0 else lambda t : t   # Definimos una función lambda para enfriar

        n_vecinos, n_exitos = -1, -1

        while evaluaciones <= self.max_evals and n_exitos != 0:
            n_vecinos, n_exitos = 0, 0

            while n_vecinos < self.max_vecinos and n_exitos < self.max_exitos and evaluaciones <= self.max_evals:
                new_sol, new_sol_w = self.generarVecino(sol, sol_w)
                n_vecinos += 1
                incr_f = self.calcular_disp(new_sol, new_sol_w) - sol_disp
                evaluaciones += 1

                if incr_f < 0 or ((random.uniform(0, 1) <= math.exp(-incr_f/self.T)) if self.Tini != 0 else False ):
                    n_exitos += 1
                    sol = new_sol.copy()
                    sol_w = new_sol_w.copy()
                    sol_disp = self.calcular_disp(sol, sol_w)

                    if sol_disp < best_sol_disp:
                        best_sol = sol.copy()
                        best_sol_w = sol_w.copy()
                        best_sol_disp = sol_disp
            
            self.T = self.decrement(self.T)
        

        return best_sol, best_sol_w

    
    def busqueda_local(self, sol, sol_w = None):
        changing = True
        evaluations = 0
        if sol_w:
            sol_weights = sol_w.copy()
        else:
            sol_weights = self.calcular_pesos(sol)
        sol_weights.sort()

        while changing and evaluations < self.max_evals:
            changing = False
            sol_index = self.get_indices(sol)
            options = [i for i in range(self.n) if not i in sol_index]

            random.shuffle(options)

            for u in sol_index:
                for v in options:

                    evaluations += 1

                    if evaluations >= self.max_evals:
                        break

                    newSol, newSol_costs = self.Int(sol, sol_weights, u, v)

                    if self.calcular_disp(newSol, newSol_costs) < self.calcular_disp(sol, sol_weights):
                        changing = True
                        sol_weights = newSol_costs.copy()
                        sol = newSol.copy()
                        break
        
        return sol, sol_weights

    


    def ejecutar_alg(self, iterations, max_evals, alg):
        self.max_evals = max_evals

        best_sol = self.generar_Sol()

        algoritmo = self.es if alg == "es" else self.busqueda_local

        best_sol, best_sol_w = algoritmo(best_sol)

        for _ in range(iterations-1):
            sol = best_sol.copy()

            sol_w = self.mutar(sol)

            sol, sol_w = algoritmo(sol, sol_w)

            if self.calcular_disp(sol, sol_w) < self.calcular_disp(best_sol, best_sol_w):
                best_sol = sol.copy()
                best_sol_w = sol_w.copy()
        
        return float(self.calcular_disp(best_sol, best_sol_w))




        


    
