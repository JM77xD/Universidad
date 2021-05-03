lista = [0.5,0.33,0.33,0.33,0.25,0.25]

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