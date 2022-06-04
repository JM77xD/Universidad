import os
import time
import sys
from fuentes import ES, BMB, ILS

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


max_evals_es = 100000
max_evals = 10000
iters_per_alg = 10

data_dir = sys.argv[1]
data_filenames = os.listdir(data_dir)

data_filenames.sort(key=sortingKey)

for filename in data_filenames: # Para cada archivo de datos

    es = ES.ES(data_dir+filename, 0.3, 0.3, 10e-3)
    bmb = BMB.BMB(data_dir+filename)
    ils = ILS.ILS(data_dir+filename, 0.3, 0.3, 10e-3)

    start_es = time.process_time()
    evaluaciones_es, disp_es = es.ejecutar_alg(max_evals_es)
    end_es = time.process_time()

    start_bmb = time.process_time()
    disp_bmb = bmb.ejecutar_alg(iters_per_alg, max_evals)
    end_bmb = time.process_time()

    start_ils_es = time.process_time()
    disp_ils_es = ils.ejecutar_alg(iters_per_alg, max_evals, "es")
    end_ils_es = time.process_time()

    start_ils_bl = time.process_time()
    disp_ils_bl = ils.ejecutar_alg(iters_per_alg, max_evals, "bl")
    end_ils_bl = time.process_time()
    
    time_es = end_es - start_es
    time_bmb = end_bmb - start_bmb
    time_ils_es = end_ils_es - start_ils_es
    time_ils_bl = end_ils_bl - start_ils_bl

    print("\n\n--------------------------Valores medios {}--------------------------\nTiempo, valor:".format(filename))
    print("\tES: {}, {}".format(time_es, disp_es))
    print("\tBMB: {}, {}".format(time_bmb, disp_bmb))
    print("\tILS-ES: {}, {}".format(time_ils_es, disp_ils_es))
    print("\tILS-BL: {}, {}".format(time_ils_bl, disp_ils_bl))
    
    
    file_es = open("data/es", "a")
    file_bmb = open("data/bmb", "a")
    file_ils_es = open("data/ils_es", "a")
    file_ils_bl = open("data/ils_bl", "a")
    
    
    file_es.write("{}\t{}, {}\n".format(filename, time_es, disp_es))
    file_bmb.write("{}\t{}, {}\n".format(filename, time_bmb, disp_bmb))
    file_ils_es.write("{}\t{}, {}\n".format(filename, time_ils_es, disp_ils_es))
    file_ils_bl.write("{}\t{}, {}\n".format(filename, time_ils_bl, disp_ils_bl))

    
    
    file_es.close()
    file_bmb.close()
    file_ils_es.close()
    file_ils_bl.close()
    
