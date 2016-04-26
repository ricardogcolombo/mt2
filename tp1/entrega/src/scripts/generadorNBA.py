#!/usr/bin/env python

import csv
with open('../tests/nba/modified_nba_2016_scores.csv', 'rb') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        for teams in [5,10,15,20,30]:
            files = open("../tests/nba/testNBA" + str(teams) +".in", "a+")
            lineaString=  "1," + ', '.join(row);
            linea= lineaString.split(",")
            if int(linea[1])<=teams and int(linea[3])<=teams:
                #  print linea[1] + " - " +linea[3] + " teams " + str(teams)
                #  print int(linea[1])<=teams
                #  print int(linea[3])<=teams
                files.write(lineaString.replace(","," ")+"\n")
            files.close()

