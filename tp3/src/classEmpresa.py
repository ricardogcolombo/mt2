import numpy as np
class empresa:
    ventasXMes = []
    ventas= []
    name = ""
    anioInicial=0000
    cantAnios = 0

    def setName(self,name,anioInicial,anios):
        self.name=name
        self.anioInicial=int(anioInicial)
        self.cantAnios=int(anios)
        self.ventas = []


    def getName(self):
        return self.name

    def addVenta(self,venta):
        self.ventas.append(venta)

    def getVentasXMes(self):
        result = np.zeros((int(self.cantAnios)+1)*12, dtype=np.int)

        anioActual= 0
        mesActual = 0
        for v in self.ventas:
            anio = int(v[0])-int(self.anioInicial)
            result[int(v[1])+(12*anio)-1]+=1
            #  if v[0] != anioActual or v[1]!=mesActual:
                #  result.append(1)
                #  anioActual= v[0]
                #  mesActual = v[1]
            #  else:
                #  result[len(result)-1]+=1

        return result
