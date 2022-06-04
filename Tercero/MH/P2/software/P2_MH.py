import os
import time
import sys
import numpy as np
from random import randint, shuffle, seed
from fuentes import Genetico,Memetico

def sortingKey(e):
    first_digit = int(e[6])
    second_digit = -1
    if e[7] != '_':
        second_digit = int(e[7])

    key = 0
    
    if (second_digit != -1):
        key = first_digit*10 + second_digit
    else:
        key = first_digit
    
    return key

def greedy(possible_options, data_matrix):
    first_element = possible_options[randint(0,n-1)]
    result_elements = [first_element[0], first_element[1]]

    while len(result_elements) != m:
        min_value = float('inf')
        curr_index = None

        delta_values = []

        for element in result_elements:
            delta_value = 0

            for other_elem in result_elements:
                delta_value += data_matrix[element, other_elem]
                        
            delta_values.append(delta_value)

        for k in range(n):
            if k not in result_elements:

                possible_result = result_elements.copy()

                possible_result.append(k)

                possible_delta = delta_values.copy()

                for values, element in zip(possible_delta,result_elements):
                    values += data_matrix[k,element]
                    
                delta_value = 0

                for element in possible_result:
                    delta_value += data_matrix[k,element]

                possible_delta.append(delta_value)

                possible_delta.sort()

                actual_dif = possible_delta[-1] - possible_delta[0]

                if actual_dif < min_value:
                    min_value = actual_dif
                    curr_index = k
            
        result_elements.append(curr_index)

    delta_values = []

    for element in result_elements:
        delta_value = 0
        for other_elem in result_elements:
            if other_elem != element:
                delta_value += data_matrix[element, other_elem]
        delta_values.append(delta_value)
    
    delta_values.sort()
    
    return delta_values
    
def Int(Sel, Sel_costs, u, v):
    index = Sel.index(u)
    newSel = Sel.copy()
    newSel[index] = v

    newSel_costs = [elem - data_matrix[u, item] + data_matrix[v, item] for elem, item in zip(Sel_costs, Sel)]
    newSel_costs.pop(index)
    value = 0
    for elem in newSel:
        value += data_matrix[v, elem]
    
    newSel_costs.insert(index, value)

    return newSel, newSel_costs

def BL(possible_options, data_matrix):
    shuffle(possible_options)

    Sel = possible_options[0:m].copy()
    Sel_costs = []

    for element in Sel:
        cost = 0
        for other_elem in Sel:
            cost += data_matrix[element, other_elem]
        Sel_costs.append(cost)
        possible_options.remove(element)

    changing = True

    evaluations = 0

    merged = list(zip(Sel, Sel_costs))
    merged = sorted(merged, key=lambda e : e[1])
    Sel = [element[0] for element in merged]
    Sel_costs = [element[1] for element in merged]

    while changing and evaluations < 100000:
        changing = False
        
        shuffle(possible_options)

        for u in Sel:
            for v in possible_options:
                newSel, newSel_costs = Int(Sel, Sel_costs, u, v)


                new_merged = list(zip(newSel, newSel_costs))
                new_merged = sorted(new_merged, key=lambda e : e[1])
                newSel = [element[0] for element in new_merged]
                newSel_costs = [element[1] for element in new_merged]

                if (newSel_costs[-1] - newSel_costs[0]) < (Sel_costs[-1] - Sel_costs[0]):
                    possible_options.append(u)
                    possible_options.remove(v)
                    changing = True
                    Sel = newSel.copy()
                    Sel_costs = newSel_costs.copy()
                    break

                evaluations += 1

                if evaluations >= 100000:
                    break
                
            if changing or evaluations >= 100000:
                break
    
    return Sel_costs

if len(sys.argv) != 2:
    raise ValueError('Por favor introduzca el directorio donde se encuentran los archivos a leer')

# Probabilidades para el AGG y AGE
P_cruce_AGG = 0.7
P_cruce_AGE = 1
TamPoblacionAG = 50
TamPoblacionAM = 50
P_mutacion = 0.1
max_evals = 100000


data_dir = sys.argv[1]
data_filenames = os.listdir(data_dir)

data_filenames.sort(key=sortingKey)
seeds = [19102001,20102001,19112001,19102002,21112001]

for filename in data_filenames: # Para cada archivo de datos

    #mean_time_greedy = 0
    #mean_time_bl = 0
    #mean_value_greedy = 0
    #mean_value_bl = 0
    #best_time_greedy = float('inf')
    #best_time_bl = float('inf')
    #best_value_greedy = float('inf')
    #best_value_bl = float('inf')
    #worst_time_greedy = float('-inf')
    #worst_time_bl = float('-inf')
    #worst_value_greedy = float('-inf')
    #worst_value_bl = float('-inf')
     
    """
    for l in range(5):
        seed(seeds[l])
        file = open(data_dir+filename)


        first_line = file.readline().split(' ')

        n, m = int(first_line[0]), int(first_line[1])   # Leemos numero de elementos y objetivo

        data_matrix = np.zeros((n,n))   # Creamos la matriz de entradas
        possible_options = []

        for line in file:
            line = line.strip('\n').split(' ')
            possible_options.append([int(line[0]), int(line[1])])
            data_matrix[int(line[0]), int(line[1])] = float(line[2])
            data_matrix[int(line[1]), int(line[0])] = float(line[2])
        
        file.close()

        start_time_greedy = time.process_time()

        delta_values = greedy(possible_options, data_matrix)    

        end_time_greedy = time.process_time()

        mean_time_greedy += (end_time_greedy-start_time_greedy)/5
        mean_value_greedy += (delta_values[-1]-delta_values[0])/5

        if end_time_greedy-start_time_greedy > worst_time_greedy:
            worst_time_greedy = end_time_greedy-start_time_greedy
        
        if end_time_greedy-start_time_greedy < best_time_greedy:
            best_time_greedy = end_time_greedy-start_time_greedy
        
        if best_value_greedy > delta_values[-1]-delta_values[0]:
            best_value_greedy = delta_values[-1]-delta_values[0]
        
        if worst_value_greedy < delta_values[-1]-delta_values[0]:
            worst_value_greedy = delta_values[-1]-delta_values[0]


        possible_options = [i for i in range(n)]

        start_time_BL = time.process_time()

        Sel_costs = BL(possible_options, data_matrix)
            
        end_time_BL = time.process_time()

        mean_time_bl += (end_time_BL-start_time_BL)/5
        mean_value_bl += (Sel_costs[-1]-Sel_costs[0])/5

        if end_time_BL-start_time_BL > worst_time_bl:
            worst_time_bl = end_time_BL-start_time_BL
        
        if end_time_BL-start_time_BL < best_time_bl:
            best_time_bl = end_time_BL-start_time_BL
        
        if best_value_bl > Sel_costs[-1]-Sel_costs[0]:
            best_value_bl = Sel_costs[-1]-Sel_costs[0]
        
        if worst_value_bl < Sel_costs[-1]-Sel_costs[0]:
            worst_value_bl = Sel_costs[-1]-Sel_costs[0]
    """
    
    agg = Genetico.AGG(TamPoblacionAG, P_mutacion, P_cruce_AGG, data_dir+filename)
    age = Genetico.AGE(TamPoblacionAG, P_mutacion, P_cruce_AGE, data_dir+filename)
    
    am = Memetico.Memetico(TamPoblacionAM, P_mutacion, P_cruce_AGG, data_dir+filename)

    start_agg_unif = time.process_time()
    solucion_agg_unif, evolucion_agg_unif = agg.ejecutar_alg(max_evals, TamPoblacionAG, 'unif', True)
    end_agg_unif = time.process_time()

    start_agg_seg = time.process_time()
    solucion_agg_seg, evolucion_agg_seg = agg.ejecutar_alg(max_evals, TamPoblacionAG, 'seg', True)
    end_agg_seg = time.process_time()

    start_age_unif = time.process_time()
    solucion_age_unif, evolucion_age_unif = age.ejecutar_alg(max_evals, 2, 'unif', True)
    end_age_unif = time.process_time()

    start_age_seg = time.process_time()
    solucion_age_seg, evolucion_age_seg = age.ejecutar_alg(max_evals, 2, 'seg', True)
    end_age_seg = time.process_time()

    start_am_10_1 = time.process_time()
    solucion_am_10_1, evolucion_am_10_1 = am.ejecutar_alg(max_evals, TamPoblacionAM, 'unif', True, 10, 1, False, 400)
    end_am_10_1 = time.process_time()

    start_am_10_01 = time.process_time()
    solucion_am_10_01, evolucion_am_10_01 = am.ejecutar_alg(max_evals, TamPoblacionAM, 'unif', True, 10, 0.1, False, 400)
    end_am_10_01 = time.process_time()

    start_am_10_01mej = time.process_time()
    solucion_am_10_01mej, evolucion_am_10_01mej = am.ejecutar_alg(max_evals, TamPoblacionAM, 'unif', True, 10, 0.1, True, 400)
    end_am_10_01mej = time.process_time()

    time_agg_unif = end_agg_unif - start_agg_unif
    time_agg_seg = end_agg_seg - start_agg_seg
    time_age_unif = end_age_unif - start_age_unif
    time_age_seg = end_age_seg - start_age_seg
    time_am_10_1 = end_am_10_1 - start_am_10_1
    time_am_10_01 = end_am_10_01 - start_am_10_01
    time_am_10_01mej = end_am_10_01mej - start_am_10_01mej
    

    print("\n\n--------------------------Valores medios {}--------------------------\nTiempo, valor:".format(filename))
    #print("\tGreedy: {}, {}".format(mean_time_greedy, mean_value_greedy))
    #print("\tBL: {}, {}".format(mean_time_bl, mean_value_bl))
    print("\tAGG_unif: {}, {}".format(time_agg_unif, evolucion_agg_unif["dispersion"]))
    print("\tAGG_seg: {}, {}".format(time_agg_seg, evolucion_agg_seg["dispersion"]))
    print("\tAGE_unif: {}, {}".format(time_age_unif, evolucion_age_unif["dispersion"]))
    print("\tAGE_seg: {}, {}".format(time_age_seg, evolucion_age_seg["dispersion"]))
    print("\tAM_10_1: {}, {}".format(time_am_10_1, evolucion_am_10_1["dispersion"]))
    print("\tAM_10_01: {}, {}".format(time_am_10_01, evolucion_am_10_01["dispersion"]))
    print("\tAM_10_01mej: {}, {}".format(time_am_10_01mej, evolucion_am_10_01mej["dispersion"]))

    graphics_bl = open("data/bl/{}.dat".format(filename), "a")
    graphics_greedy = open("data/greedy/{}.dat".format(filename), "a")
    graphics_agg_unif = open("data/agg_unif/{}.dat".format(filename), "a")
    graphics_agg_seg = open("data/agg_seg/{}.dat".format(filename), "a")
    graphics_age_unif = open("data/age_unif/{}.dat".format(filename), "a")
    graphics_age_seg = open("data/age_seg/{}.dat".format(filename), "a")
    graphics_am_10_1 = open("data/am_10_1/{}.dat".format(filename), "a")
    graphics_am_10_01 = open("data/am_10_01/{}.dat".format(filename), "a")
    graphics_am_10_01mej = open("data/am_10_01mej/{}.dat".format(filename), "a")

    """
    graphics_bl.write("Mean disp\tMean time\t\tBest disp\tBest time\t\tWorst disp\tWorst time\n")
    graphics_bl.write("{}\t{}\t\t{}\t{}\t\t{}\t{}\n".format(mean_value_bl, mean_time_bl, best_value_bl, best_time_bl, worst_value_bl, worst_time_bl))

    graphics_greedy.write("Mean disp\tMean time\t\tBest disp\tBest time\t\tWorst disp\tWorst time\n")
    graphics_greedy.write("{}\t{}\t\t{}\t{}\t\t{}\t{}\n".format(mean_value_greedy, mean_time_greedy, best_value_greedy, best_time_greedy, worst_value_greedy, worst_time_greedy))
    """
    
    for it, disp in evolucion_agg_unif["evolucion"]:
        graphics_agg_unif.write("{}\t{}\n".format(it, disp))

    for it, disp in evolucion_agg_seg["evolucion"]:
        graphics_agg_seg.write("{}\t{}\n".format(it, disp))

    for it, disp in evolucion_age_unif["evolucion"]:
        graphics_age_unif.write("{}\t{}\n".format(it, disp))

    for it, disp in evolucion_age_seg["evolucion"]:
        graphics_age_seg.write("{}\t{}\n".format(it, disp))

    for it, disp in evolucion_am_10_1["evolucion"]:
        graphics_am_10_1.write("{}\t{}\n".format(it, disp))
    
    for it, disp in evolucion_am_10_01["evolucion"]:
        graphics_am_10_01.write("{}\t{}\n".format(it, disp))
    
    for it, disp in evolucion_am_10_01mej["evolucion"]:
        graphics_am_10_01mej.write("{}\t{}\n".format(it, disp))
    
    graphics_bl.close()
    graphics_greedy.close()
    graphics_agg_unif.close()
    graphics_agg_seg.close()
    graphics_age_unif.close()
    graphics_age_seg.close()
    graphics_am_10_1.close()
    graphics_am_10_01.close()
    graphics_am_10_01mej.close()
    
