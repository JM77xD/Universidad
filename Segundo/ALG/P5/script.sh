#!/bin/bash

echo "" >> BotesPintura.dat
i=5
b=5
c=6
while [ $i -le 4000 ]
do
    ./BotesPintura $i $b $c>> BotesPintura.dat
    ((i=i+5))
    ((b=b+5))
done
