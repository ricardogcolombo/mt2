import fileManagment
import numpy

anio =1987
cant = 21
final = anio+cant
airport = "JFK"
for i in range(0,cant+1):
    data = fileManagment.procesarData(anio,0,airport)
    print "termine numero "+ str(i)
    numpy.savetxt(str(anio)+'.csv', data, fmt="%d" ,delimiter=",")
    anio +=1
