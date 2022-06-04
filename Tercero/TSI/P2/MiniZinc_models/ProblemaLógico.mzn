% Problema lógico

include "globals.mzn";

% Variables

array [1..5] of int : casas = [1, 2, 3, 4, 5];  % 1 es la casa de la izquierda, 5 la de la derecha
array [1..5] of int : coloresCasas = [1, 2, 3, 4, 5];  % roja, blanca, verde, amarilla, azul
array [1..5] of int : profesiones = [1, 2, 3, 4, 5];  % pintor, escultor, diplomatico, violinista, medico
array [1..5] of int : animal = [1, 2, 3, 4, 5];  % perro, cebra, caracoles, zorro, caballo
array [1..5] of int : bebida = [1, 2, 3, 4, 5];  % te, leche, agua, zumo, cafe

set of int : procedencias = 1..5;  % Siguiente orden: vasco, catalan, gallego, navarro, andaluz, tal que 1 es vasco y 5 andaluz
set of int : datos = 1..5; % Siguiente orden: casa, colorCasa, profesion, animal, bebida
array [procedencias, datos] of var int : personas;  % Matriz con los datos de cada persona, tal que cada fila es una procedencia y cada columna sus datos

% Restricciones

constraint personas[1, 2] = 1;   % El vasco vive en la casa roja
constraint personas[2, 4] = 1;  % El catalan tiene un perro
constraint personas[3, 3] = 1;  % El gallego es pintor
constraint personas[4, 5] = 1;  % El navarro bebe te
constraint personas[5, 1] = 1;  % El andaluz vive en la casa de la izquierda
constraint forall( i in datos) (alldifferent([personas[j, i] | j in procedencias ]));  % Todos los elementos de una columna son distintos, asegurando las condiciones del problema

constraint forall(i in procedencias)(if personas[i, 2] == 3 then personas[i, 5] = 5 endif); % Casa verde bebe cafe
constraint forall(i in procedencias)(if personas[i, 2] == 3 then ( forall(j in procedencias)( if personas[j,2] == 2 then personas[i, 1] = personas[j, 1] + 1 endif) ) endif); % Casa verde al lado de la blanca y a su derecha
constraint forall(i in procedencias)(if personas[i, 3] == 2 then personas[i, 4] = 3 endif); % escultor cria caracoles
constraint forall(i in procedencias)(if personas[i, 2] == 4 then personas[i, 3] = 3 endif); % diplomatico vive en la casa amarilla
constraint forall(i in procedencias)(if personas[i, 1] == 3 then personas[i, 5] = 2 endif); % casa 3 se bebe leche
constraint forall(i in procedencias)(if personas[i, 2] == 5 then (personas[i, 1] = 2) endif) ; % casa andaluz está al lado de la azul, por tanto la casa azul es la 2
constraint forall(i in procedencias)(if personas[i, 3] == 4 then personas[i, 5] = 4 endif); % violinista bebe zumo
constraint forall(i in procedencias)(if personas[i, 4] == 4 then ( forall(j in procedencias)( if personas[j,3] == 5 then (personas[i, 1] = personas[j, 1] + 1 \/ personas[i, 1] = personas[j, 1] - 1 ) endif ) ) endif ); % zorro esta en una casa al lado de la del medico
constraint forall(i in procedencias)(if personas[i, 4] == 5 then ( forall(j in procedencias)( if personas[j,3] == 3 then (personas[i, 1] = personas[j, 1] + 1 \/ personas[i, 1] = personas[j, 1] - 1 ) endif) ) endif ); % caballo en una casa de al lado del diplomatico


constraint forall(i in procedencias, j in datos)( personas[i,j] > 0 /\ personas[i, j] < 6);  % Todos los valores están en el rango correcto, y ya sabemos que son diferentes y se cumplen las restricciones anteriores

solve satisfy;

output [
  "Valor cebra: 2\nValor agua: 3\n\nprocedencia casa colorCasa profesion animal bebida", "\nVasco: ", show(personas[1,1..5]), "\nCatalan: ", show(personas[2, 1..5]), "\nGallego: ", show(personas[3, 1..5]), "\nNavarro: ", show(personas[4, 1..5]), "\nAndaluz: ", show(personas[5, 1..5]), "\n"
]
