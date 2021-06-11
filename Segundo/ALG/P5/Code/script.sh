#!/bin/bash

echo "" >> ../data/BotesPintura.dat
i=5
b=5
c=6
while [ $i -le 4000 ]
do
    ./BotesPintura $i $b $c>> ../data/BotesPintura.dat
    ((i=i+5))
    ((b=b+5))
done
