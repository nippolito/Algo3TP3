# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import random
import math


def expFuerzaBruta():
	Completo = pd.read_csv('HeatMapGraspIter250.csv')
	
	
	
	xdata = Completo['IteracionesFijas']
	ydataNipo = Completo['IteracionesReales']


	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label="Iteraciones Realizadas")		# alpha = opacidad
	
	plt.ylabel('Iteraciones Reales')
	plt.xlabel('Iteraciones Permitidas')

	z = np.polyfit(xdata, ydataNipo, 1)
	p = np.poly1d(z)
	tendencia = "y =%.6fx+(%.6f)"%(z[0],z[1])
	plt.plot(xdata, p(xdata), "r-", alpha = 0.5, label= tendencia)

	plt.legend()
	plt.show()

def rectaTiempos():
	Completo = pd.read_csv('RectaTiempo.csv')
	
	
	
	xdata = Completo['cantNod']
	ydataNipo = Completo['Tiempo']

	curvaX = range(1,500)
	curvaY = []

	for x in curvaX:
		curvaY.append(x*x*1/1000)


	plt.plot(xdata, ydataNipo, "b-", alpha = 0.5, label="Ciclo Grasp")		# alpha = opacidad
	plt.plot(curvaX, curvaY, "g-", alpha = 0.5, label= "O(n³)")

	plt.ylabel('Cantidad de Nodos')
	plt.xlabel('Tiempo en ms')

	
	plt.legend()
	plt.show()


expFuerzaBruta()