% Problema de asignaión de tareas

include "globals.mzn";

% Variables
enum numeroTareas = {A, B, C, D, E, F, G, H ,I};  % Las tareas a realizar
enum trabajadores = { primero, segundo, tercero};  % Los tres trabajdores
array [1..9] of var trabajadores : tareas;  % Asignación de tareas
array [numeroTareas, trabajadores] of int : duracionTareasPorT = [| 4, 7, 10  % Duración de cada tarea al ser realizada por cada trabajador
                                                                     | 3, 5, 7
                                                                     | 3, 1, 4
                                                                     | 2, 5, 8
                                                                     | 4, 2, 6
                                                                     | 3, 2, 1
                                                                     | 1, 2, 3
                                                                     | 1, 3, 5
                                                                     | 2, 3, 4 |];
int : tiempoMax = sum(i in numeroTareas, j in trabajadores)(duracionTareasPorT[i,j]);  % El tiempo máximo es la suma de todos los tiempos, por convenio
array [numeroTareas, 1..2] of var 0.. tiempoMax : tiempos;  % Tiempos de inicio y final para cada tarea
var 0..tiempoMax : tiempoTotal;  % El tiempo total está entre 0 y el tiempo máximo

% Restricciones

    % Aseguramos que una tarea no empieza hasta que no han acabado sus dependencias y que acaba cuando la realiza el trabajador correspondiente desde que empezó
constraint tiempos[A,1] = 0 /\ tiempos[A,2] = tiempos[A,1] + duracionTareasPorT[A,tareas[1]];
constraint tiempos[B,1] >= tiempos[A,2] /\ tiempos[B,2] = tiempos[B,1] + duracionTareasPorT[B,tareas[2]];
constraint tiempos[C,1] >= tiempos[B,2] /\ tiempos[C,2] = tiempos[C,1] + duracionTareasPorT[C,tareas[3]];
constraint tiempos[D,1] >= tiempos[A,2] /\ tiempos[D,2] = tiempos[D,1] + duracionTareasPorT[D,tareas[4]];
constraint tiempos[E,1] >= max(tiempos[C,2], tiempos[D,2]) /\ tiempos[E,2] = tiempos[E,1] + duracionTareasPorT[E,tareas[5]];
constraint tiempos[F,1] >= max(tiempos[C,2], tiempos[D,2]) /\ tiempos[F,2] = tiempos[F,1] + duracionTareasPorT[F,tareas[6]];
constraint tiempos[G,1] >= max(tiempos[C,2], tiempos[D,2]) /\ tiempos[G,2] = tiempos[G,1] + duracionTareasPorT[G,tareas[7]];
constraint tiempos[H,1] >= tiempos[A,2] /\ tiempos[H,2] = tiempos[H,1] + duracionTareasPorT[H,tareas[8]];
constraint tiempos[I,1] >= max(tiempos[F,2], tiempos[H,2]) /\ tiempos[I,2] = tiempos[I,1] + duracionTareasPorT[I,tareas[9]];

    % No puede haber un mismo trabajador en 2 tareas a la vez
constraint forall(i,j in 1..9 where i != j)(if tareas[i] == tareas[j] then (tiempos[to_enum(numeroTareas,i),1] >= tiempos[to_enum(numeroTareas,j),2] \/ tiempos[to_enum(numeroTareas,j),1] >= tiempos[to_enum(numeroTareas,i),2]) endif);


tiempoTotal = max(tiempos[numeroTareas,2]); % El tiempo total es el tiempo en el que han acabado todas las tareas

solve minimize tiempoTotal;


output ["tiempoTotal = \(tiempoTotal)\nTareas: "] ++
    [ show_int(1,tareas[i]) ++ " " | i in 1..9
    ] ++ ["\nTiempos inicio y fin:\n"] ++
    [show(i) ++ " " ++ show(tiempos[i,1]) ++ " " ++ show(tiempos[i,2]) ++ "\n" | i in numeroTareas]
