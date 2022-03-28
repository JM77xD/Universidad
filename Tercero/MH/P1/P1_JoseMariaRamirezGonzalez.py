import os
import time
import numpy as np
from random import randint, shuffle

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

    
def sortingKey_Sel(e):    
    return e[1]


data_dir = 'datos/'
data_filenames = os.listdir(data_dir)

data_filenames.sort(key=sortingKey)

for filename in data_filenames: # Para cada archivo de datos
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

    start_time_greedy = time.process_time()
    
    first_element = possible_options[randint(0,n-1)]
    result_elements = [first_element[0], first_element[1]]

    for i in range(m-2):
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

    end_time_greedy = time.process_time()

    print("-------------------------------------GREEDY--------------------------------------")
    print("Coste de la solución de {}: {}\nTiempo de ejecución: {}\n\n".format(filename, delta_values[-1]-delta_values[0], end_time_greedy-start_time_greedy))

    possible_options = [i for i in range(n)]
    start_time_BL = time.process_time()

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

    while changing and evaluations < 100000:
        changing = False

        merged = list(zip(Sel, Sel_costs))
        merged = sorted(merged, key=sortingKey_Sel)
        Sel = [element[0] for element in merged]
        Sel_costs = [element[1] for element in merged]


        for u in Sel:
            for v in possible_options:
                index = Sel.index(u)
                newSel = Sel.copy()
                newSel[index] = v

                newSel_costs = [elem - data_matrix[u, item] + data_matrix[v, item] for elem, item in zip(Sel_costs, Sel)]
                newSel_costs.
                value = 0
                for elem in newSel:
                    value += data_matrix[v, elem]
                
                newSel_costs.insert(index, value)


                new_merged = list(zip(newSel, newSel_costs))
                new_merged = sorted(new_merged, key=sortingKey_Sel)
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
    

    merged = list(zip(Sel, Sel_costs))
    merged = sorted(merged, key=sortingKey_Sel)
    Sel = [element[0] for element in merged]
    Sel_costs = [element[1] for element in merged]
    
    end_time_BL = time.process_time()
        
    
    print("--------------------------------------BL----------------------------------------")
    print("Coste de la solución de {}: {}\nTiempo de ejecución: {}\nEvaluaciones: {}\n\n".format(filename, Sel_costs[-1]-Sel_costs[0], end_time_BL-start_time_BL, evaluations))




