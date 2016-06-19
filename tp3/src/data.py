import fileManagment as fm
import filterEmpresa as fe
from filterEmpresa import *
import numpy
import csv

anio =2008
cant = 0
final = anio+cant
airport = "JFK"
empresa = "DL"
for i in range(0,cant+1):
    print "Procesando archivo: "+ str(anio)
    ofile  = str(anio)+ '-' + str(empresa) + '.csv'
    data = fe.getDataByEmpresa(anio,empresa,airport)
    numpy.savetxt(ofile, data, fmt="%d" ,delimiter=",")
    anio +=1
