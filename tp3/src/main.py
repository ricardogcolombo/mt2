import csv
import numpy as np



def getItemsForAirport(csvName,airport,mes):
    #  leo el csv
    reader=csv.reader(open(csvName,"rb"),delimiter=',')

    #  creo un array con los elementos con numpy
    x=list(reader)
    result=np.array(x)

    jfkfiltered = []
    clefiltered = np.array(1)
    for item in result:
        if item[15]!="NA" and item[16]==airport and item[25]!="NA":
            if int(item[15])>15 and item[16]==airport and int(item[25])>0:
                jfkfiltered.append(item)
        #  elif result[n][15]>15 & result[n][16]=="CLE" & result[n][26]>0:
            #  jfkfiltered.push(item)

    #  semana= np.zeros(5, dtype=np.int)

    for item in jfkfiltered:
        mes[int(item[1])-1]+=1
        np.append(mes,1)
        #  semana[item[2]-1]+=1



    return

#  print jfkfiltered

mes = np.zeros(12, dtype=np.int)
getItemsForAirport("train.csv","JFK",mes)

print mes
