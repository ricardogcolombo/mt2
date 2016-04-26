#!/usr/bin/env python

from random import randint
for teams in [300]:
    for matches in [1000]:
        outputFile= open("../tests/test1000partidosRandomCholesky.in", "a+")
        lineaInicial = str(teams) + " " + str(matches)
        outputFile.write(lineaInicial +"\n")
        for total in range(0,matches):
            team1 = randint(1,teams)
            team2 = randint(1,teams)
            while team1==team2:
                team2 = randint(1,teams)
            goals1 = goals2 = 0
            linea = "1 "+ str(team1) + " " + str(goals1) + " " +str(team2)+ " "+str(goals2)
            outputFile.write(linea +"\n")
        outputFile.close()
