#!/bin/csh -vx

echo "" >> divide_venceras_busqueda.dat
@ i = 10000
while ( $i < 7000000 )
./divide_venceras_busqueda $i >> divide_venceras_busqueda.dat
@ i += 20000
end
