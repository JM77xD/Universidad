import random
from . import Conjunto

class BMB(Conjunto.Conjunto):

    def __init__(self, archivo_datos):
        super().__init__(archivo_datos)
    
    def busqueda_local(self, sol, max_neighbours):
        changing = True
        evaluations = 0
        sol_weights = self.calcular_pesos(sol)
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

                    if self.calcular_disp(newSol, newSol_costs) < self.calcular_disp(sol, sol_weights):
                        changing = True
                        sol_weights = newSol_costs.copy()
                        sol = newSol.copy()
                        break
        return sol
    
    def ejecutar_alg(self, iters, max_evals_ls):
        self.iters = iters
        self.ls_limit = max_evals_ls

        sols = []
        for _ in range(self.iters):
            sols.append(self.generar_Sol())

        upgraded_sols = []
        for sol in sols:
            upgraded_sols.append(self.busqueda_local(sol, self.ls_limit))

        upgraded_sols.sort(key=lambda sol: self.calcular_disp(sol))

        best_sol = upgraded_sols[0].copy()

        return self.calcular_disp(best_sol)
