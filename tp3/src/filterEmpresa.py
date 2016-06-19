import csv
import numpy as np

def getDataByEmpresa(anioInicial,empresa,airport):
    result= []
    filename = anioInicial
    ifile  = open("../data/"+str(filename)+".csv", "rb")
    reader = csv.reader(ifile)

    for row in reader:
	if row[8]==empresa and row[16]==airport:
		result.append(list(row))
    ifile.close()
 
    datosFiles= np.zeros(12, dtype=np.int)
    for item in result:
        datosFiles[int(item[1])-1]+=1

    return datosFiles


