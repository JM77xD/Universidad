% Problema de las monedas


% Declaración de variables

  % Cantidad de cada tipo de monedas
var int : monedaCent1;
var int : monedaCent2;
var int : monedaCent5;
var int : monedaCent10;
var int : monedaCent20;
var int : monedaCent50;
var int : monedaEuro1;
var int : monedaEuro2;

  % Cantidad pedida
int : cantidadPedida;  % Introducir el valor pedido en centimos
  
  % Total de monedas que tenemos
var int : cantidadMonedas;

% Restricciones

  % La cantidad pedida ha de ser mayor o igual a 0
constraint assert(cantidadPedida >= 0, "El valor pedido ha de ser mayor o igual a 0");

  % Debemos tener como mínimo 0 monedas de las de céntimo y tantas monedas de 1 y 2 euros como necesitemos para igualar la cantidad entera
constraint monedaCent1 >= 0;
constraint monedaCent2 >= 0;
constraint monedaCent5 >= 0;
constraint monedaCent10 >= 0;
constraint monedaCent20 >= 0;
constraint monedaCent50 >= 0;
constraint monedaEuro1 = cantidadPedida div 100 - 2*(cantidadPedida div 200);
constraint monedaEuro2 = cantidadPedida div 200;

  % La cantidad pedida debe ser igual a la suma de cada moneda por su valor
constraint cantidadPedida = monedaCent1 + 2*monedaCent2 + 5*monedaCent5 + 10*monedaCent10 + 20*monedaCent20 + 50*monedaCent50 + 100*monedaEuro1 + 200*monedaEuro2;

  % El total de monedas que tengamos es la suma de todas ellas
cantidadMonedas = monedaCent1 + monedaCent2 + monedaCent5 + monedaCent10 + monedaCent20 + monedaCent50 + monedaEuro1 + monedaEuro2;

solve minimize cantidadMonedas;

output [
  "Monedas de 1 centimo: ", show(monedaCent1), "\nMonedas de 2 centimos: ", show(monedaCent2), "\nMonedas de 5 centimos: ", show(monedaCent5),
  "\nMonedas de 10 centimos: ", show(monedaCent10), "\nMonedas de 20 centimos: ", show(monedaCent20), "\nMonedas de 50 centimos: ", show(monedaCent50),
  "\nMonedas de 1 euro: ", show(monedaEuro1), "\nMonedas de 2 euros: ", show(monedaEuro2), "\n\nCantidad de monedas: ", show(cantidadMonedas)
]
