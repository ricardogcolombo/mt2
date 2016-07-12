class empresa:
    ventas = []
    name = ""

    def setName(self,name):
        self.name=name
        self.ventas = []

    def getName(self):
        return self.name

    def addVenta(self,venta):
        self.ventas.append(venta)

    def getVentasXMes(self):
        result = []
        anioActual= 0
        mesActual = 0
        for v in self.ventas:
            if v[0] != anioActual or v[1]!=mesActual:
                result.append(1)
                anioActual= v[0]
                mesActual = v[1]
            else:
                result[len(result)-1]+=1

        return result
