import os
import time
import sys
from fuentes import CS, M_CS

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

if len(sys.argv) != 2:
    raise ValueError('Por favor introduzca el directorio donde se encuentran los archivos a leer')


max_evals_cs = 500
nests = 50
pa = 0.2
gen_to_bl = 5
prob_bl = 0.1
mej_bl = True
limit_bl = 1000

data_dir = sys.argv[1]
data_filenames = os.listdir(data_dir)

data_filenames.sort(key=sortingKey)

for filename in data_filenames: # Para cada archivo de datos

    #cs = CS.CuckooSearch(data_dir+filename, nests, pa)


    #start_cs = time.process_time()
    #disp_cs = cs.ejecutar_alg(max_evals_cs)
    #end_cs = time.process_time()

    

    m_cs = M_CS.Memetico(data_dir+filename, nests, pa)


    start_m_cs = time.process_time()
    disp_m_cs = m_cs.ejecutar_alg(max_evals_cs, gen_to_bl, prob_bl, mej_bl, limit_bl)
    end_m_cs = time.process_time()

    
    #time_cs = end_cs - start_cs
    time_m_cs = end_m_cs - start_m_cs


    print("\n\n--------------------------Valores medios {}--------------------------\nTiempo, valor:".format(filename))
    #print("\tCS: {}, {}".format(time_cs, disp_cs))
    print("\tMemetico_CS_mej: {}, {}".format(time_m_cs, disp_m_cs))
    
    
    #file_cs = open("data/cs", "a")
    file_m_cs = open("data/m_cs", "a")
    
    
    #file_cs.write("{}\t{}, {}\n".format(filename, time_cs, disp_cs))
    file_m_cs.write("{}\t{}, {}\n".format(filename, time_m_cs, disp_m_cs))

    
    
    #file_cs.close()
    file_m_cs.close()

