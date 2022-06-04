import random
from . import Conjunto
import math

class ES(Conjunto.Conjunto):

    def __init__(self, archivo_datos, mu, phi, finalT):
        super().__init__(archivo_datos)
        self.mu = mu
        self.phi = phi
        self.max_vecinos = 10 * self.n
        self.max_exitos = self.n
        self.Tfinal = finalT


    def ejecutar_alg(self, max_Evals, sol_inicial = None):

        self.max_evals = max_Evals
        self.evaluaciones = 0

        if not sol_inicial:
            sol = self.generar_Sol()
        else:
            sol = sol_inicial
        
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
        


        while self.evaluaciones <= self.max_evals and n_exitos != 0:
            n_vecinos, n_exitos = 0, 0

            while n_vecinos < self.max_vecinos and n_exitos < self.max_exitos and self.evaluaciones <= self.max_evals:
                new_sol, new_sol_w = self.generarVecino(sol, sol_w)
                n_vecinos += 1
                incr_f = self.calcular_disp(new_sol, new_sol_w) - sol_disp
                self.evaluaciones += 1

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
        

        return self.evaluaciones, float(best_sol_disp)

    
