import csv
import numpy as np


#  esta funcion obtiene los datos ya filtrados
#  anioInicial es el nombre del archivo +.csv que se agrega en la funcion para obtener los datos
#  cantAnios es la cantidad de archivos + anios que se obtienen
def getDataFromFiles(anioInicial,cantAnios,airport):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open(str(filename)+".csv", "rb")
        reader = csv.reader(ifile)

        #  ACA SE APLICA EL FILTRO SI SE QUIERE USAR OTRO FILTRO CAMBIAR EL IF DENTRO DEL FOR
        # columna 15 es Delay
        # columna 16 es el nombre del aeropuerto
        # columna 25 es Delay por causas de clima
        #  revisamos que las columnas que necesitamos cumplan:
        #  - delay y weather delay !=NA y delay > 15 minutos ademas que el delayPorClima >0
        #  los que cumplen las condiciones quedan apendeados en results
        for row in reader:
            if row[15]!="NA" and row[16]==airport and row[25]!="NA" and int(row[15])>15 and row[16]==airport and int(row[25])>0:
                result.append(list(row))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    print "termino de leer"

    datosFiles= np.zeros((cantAnios+1)*12, dtype=np.int)
    countAnios= 0

    #  tomo el anioo del primer elemento como referencia, estan ordenados por ser una lectura ordenada
    anioActual= int(result[0][0])

    #  voy guardando mes a mes segun el anio para ejecutarlo
    for item in result:
        if anioActual < int(item[0]):
            countAnios+=1
            anioActual = int(item[0])
        datosFiles[int(item[1])+(12*countAnios)-1]+=1

    return datosFiles


