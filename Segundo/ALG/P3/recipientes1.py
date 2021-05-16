lista = [0.1 ,0.6, 0.3, 0.7, 0.6, 0.05, 0.8, 0.3, 0.2, 0.14]

R = 1

lista.sort(reverse=True)

num_rec = 0

reparto = list()

while (lista):
    front = lista.pop(0)
    
    reparto.append([front])
    num_rec +=1
    
    lista_menores = list(lista)
    lista_menores.reverse()
    
    for i in lista_menores:
        if (sum(reparto[num_rec-1]) + i) <= R:
            reparto[len(reparto)-1].append(i)
            lista.remove(i)

print(reparto)
print(len(reparto))