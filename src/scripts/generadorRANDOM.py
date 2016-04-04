#!/usr/bin/env python

from random import randint
for teams in [50,200,100,300,500,700,1000]:
    for matches in [10,50,100,200,500,700,1000]:
        outputFile= open("../tests/random/testRANDOM" + str(teams) + str(matches)+".in", "a+")
        lineaInicial = str(teams) + " " + str(matches)
        outputFile.write(lineaInicial +"\n")
        for total in range(0,matches):
            team1 = randint(1,teams)
            team2 = randint(1,teams)
            while team1==team2:
                team2 = randint(1,teams)
            goals1 = randint(0,130)
            goals2 = randint(0,130)
            while goals1==goals2:
                goals2 = randint(0,130)
            linea = "1 "+ str(team1) + " " + str(goals1) + " " +str(team2)+ " "+str(goals2)
            outputFile.write(linea +"\n")
        outputFile.close()
