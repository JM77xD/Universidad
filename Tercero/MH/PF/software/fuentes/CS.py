from . import Conjunto
import math
import numpy as np

class CuckooSearch(Conjunto.Conjunto):

    def __init__(self, archivoDatos, nests, pa):
        super().__init__(archivoDatos)
        self.Levy = 1.5
        self.StepSize = 0.1
        self.numNests = nests
        self.toAbandon = int(pa*self.numNests) if int(pa*self.numNests) > 0 else 1
        self.nests = []

    
    def levy_flight(self):
        sigma1 = np.power((math.gamma(1 + self.Levy) * np.sin((np.pi * self.Levy) / 2)) \
                        / math.gamma((1 + self.Levy) / 2) * np.power(2, (self.Levy - 1) / 2), 1 / self.Levy)
        sigma2 = 1
        u = np.random.normal(0, sigma1, size=self.n)
        v = np.random.normal(0, sigma2, size=self.n)
        step = u / np.power(np.fabs(v), 1 / self.Levy)

        return step
    
    def get(self, i):
        step = self.StepSize * self.levy_flight()
        max_step = np.argmax(step)
        lower_bound, upper_bound = -(max_step*0.1), (max_step*0.1)
        
        indices = np.array([i for i in range(self.n) if step[i] < upper_bound and step[i] > lower_bound])
        new_nest = self.nests[i].copy()
        if len(indices) != 0:
            new_nest[indices] = 1
            self.reparar_solucion(new_nest)

        return new_nest
    

    def ejecutar_alg(self, max_iters):
        
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
        

