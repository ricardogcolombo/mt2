import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
import classEmpresa
import json


anioInicial=2004
cantAnios=4
empresas =fm.getTotalMarket(anioInicial,cantAnios,"ALL")

color_sequence = ['#1f77b4', '#aec7e8', '#ff7f0e', '#ffbb78', '#2ca02c',
        '#98df8a', '#d62728', '#ff9896', '#9467bd', '#c5b0d5',
        '#8c564b', '#c49c94', '#e377c2', '#f7b6d2', '#7f7f7f',
        '#c7c7c7', '#bcbd22', '#dbdb8d', '#17becf', '#9edae5',
        '#c7c7d7', '#bcbdaa', '#dbdb8c', '#1bbecf', '#9ebae5',
        '#c7c7a7', '#c2bd22', '#dbab8d', '#17afcf', '#9afae5',
        '#c7c2d7', '#ccbd22', '#dbbb8d', '#17bfcf', '#9eaae5']
colorNumber = 0

meses = ["Ene","Feb","Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"]
#  for number,month in enumerate(meses):
labels = []

for i in range(0,12*(cantAnios+1)):
    labels.append(meses[i%12])

ejeXMeses = []
for i in range(0,((cantAnios+1)*12)):
    ejeXMeses.append(i)
#  ejeXMeses.append(meses[i%12])
fig, ax = plt.subplots(1, 1, figsize=(5, 5))

# Remove the plot frame lines. They are unnecessary here.
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
#  plt.ylim(-0.1, 1000000)
plt.xlim(-0.1, 12*(cantAnios+1))

colorNumber = 0
for rank,empresa in enumerate(empresas):
    valores= empresa.getVentasXMes()
    #  print valores
    line = plt.plot(ejeXMeses,
            valores,
            color=color_sequence[rank],
            label=empresa.getName())

    y_pos = valores[len(valores)-1]
    #  plt.text(12*(cantAnios+1)+0.5, y_pos, empresa.getName(), fontsize=9, color=color_sequence[rank])
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
plt.title('Datos Reales Market Share (2004-2008)', fontsize=11, ha='center')

ax.set_xticks(range(len(labels)))
ax.set_xticklabels(labels,rotation='vertical')
plt.ylabel("cantidad de vuelos")
plt.xlabel("meses")
fig.set_size_inches(18.5, 10.5)
plt.savefig('marketShare.png')
#  plt.show()
