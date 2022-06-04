% Problema de coloración de aristas de un grafo

include "globals.mzn";

% Variables

int : NUM_NODES;    % Número de nodos
int : NUM_SIDES;    % Número de aristas

array[1..NUM_SIDES,1..2] of int : sides;    % Vector con tantas entradas como aristas cuyas entradas son una tupla de la forma [n1,n2] simbolizando que la arista i une los nodos n1 y n2.

array[1..NUM_SIDES] of var 1..NUM_SIDES : colores;  % Número de colores que tendremos que usar, tal que el máximo será tantos colores como nodos.

% Restricciones

    % Las aristas similares (aquellas que comparten ambos nodos) tendrán el mismo color
constraint forall(i,j in 1..NUM_SIDES where i < j)(if (sides[i,1] == sides[j,1] /\ sides[i,2] == sides[j,2]) \/ (sides[i,2] == sides[j,1] /\ sides[i,1] == sides[j,2]) then colores[i] == colores[j] endif);

    % Las aristas que compartan 1 solo nodo, tendrán colores distintos
constraint forall(i,j in 1..NUM_SIDES where i < j)(if (sides[i,1] != sides[j,1] /\ sides[i,2] == sides[j,2]) \/ (sides[i,2] != sides[j,1] /\ sides[i,1] == sides[j,2]) \/ (sides[i,1] == sides[j,1] /\ sides[i,2] != sides[j,2]) \/ (sides[i,2] == sides[j,1] /\ sides[i,1] != sides[j,2])then colores[i] != colores[j] endif);

solve minimize max(colores);    % Queremos minimizar el número de colores, para ello buscamos el valor máximo del array de colores a asignar y buscamos que sea mínimo.

output [
    "Colores necesarios: " ++ show(max(colores))
]
