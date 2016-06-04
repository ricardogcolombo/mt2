#!/bin/bash
# Sumar la cantidad de cancelaciones filtrando por par origen - destino usando awk.

# Definimos algunas variables. Ojo que a bash no le gustan los espacios cerca del "=".
infile="../data/2008.csv"
outfile="../data/group-column.csv"

orig_ap="IND" 
dest_ap="PHX"

# Columna 17 aeropuerto origen, columna 18 aeropuerto destino
# Ojo con la secuencia de " y ' al filtrar por &&. 
awk -F, '{if ($17 == "'"$orig_ap"'" && $18 == "'"$dest_ap"'") {s+=$22}} END {print s}' $infile > $outfile 
