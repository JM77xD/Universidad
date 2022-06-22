import random
import numpy as np
from. import CS

class Memetico(CS.CuckooSearch):

    def __init__(self, archivoDatos, nests, pa):
        super().__init__(archivoDatos, nests, pa)

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

                    if (newSol_costs[-1] - newSol_costs[0]) < (sol_weights[-1] - sol_weights[0]):
                        changing = True
                        sol_weights = newSol_costs.copy()
                        sol = newSol.copy()
                        break
                        


    def busqueda_local_generacional(self, nests, gen_to_bl, prob, mej, failures):
        if self.iters % gen_to_bl == 0:
            if mej:
                dispersiones = [[self.calcular_disp(ind), index] for ind, index in zip(nests,range(len(nests)))]
                dispersiones.sort(key=lambda valores : valores[0])
                seleccion = [ind[1] for ind in dispersiones[:int(len(nests)*prob)]]
            else:
                seleccion = random.sample(range(0, len(nests)), int(len(nests)*prob))
            
            for i in seleccion:
                self.busqueda_local(nests[i], failures)
    

    def ejecutar_alg(self, max_iters, gen_to_bl, prob_bl, mej_bl, failures_bl):
        
        self.iters = 0

        for i in range(self.numNests):
            sol = self.generar_Sol()
            self.nests.append(sol)
        
        best_nest = self.nests[0].copy()
        best_nest_disp = self.calcular_disp(best_nest)

        while self.iters < max_iters and best_nest_disp != 0:
            
            self.iters+=1

            np.random.shuffle(self.nests)     
            nest = self.get(np.random.randint(0, self.numNests))

            alet = np.random.randint(0, self.numNests)

            if self.calcular_disp(nest) < self.calcular_disp(self.nests[alet]):
                self.nests[alet] = nest

            self.busqueda_local_generacional(self.nests, gen_to_bl, prob_bl, mej_bl, failures_bl)

            self.nests.sort(key= lambda sol : self.calcular_disp(sol), reverse=True)

            disp_mejor_actual = self.calcular_disp(self.nests[-1])
            if disp_mejor_actual < best_nest_disp:
                best_nest = self.nests[-1].copy()
                best_nest_disp = disp_mejor_actual

            for i in range(self.toAbandon):
                self.nests[i] = self.generar_Sol()
                if self.calcular_disp(self.nests[i]) < best_nest_disp:
                    best_nest = self.nests[i].copy()
                    best_nest_disp = disp_mejor_actual

            

        return best_nest_disp
