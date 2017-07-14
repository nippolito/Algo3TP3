# -*- coding: utf-8 -*-

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import random
import math
import numpy as np

# from pylab import *
# rcParams['figure.figsize'] = 15,5



# Always display all the columns
# pd.set_option('display.width', 5000)
# pd.set_option('display.max_columns', 60)

def expComplejNipoYEmi():
	df1 = pd.read_csv('ExpComplejHeurNipoNuevo.csv')
	df2 = pd.read_csv('ExpComplejHeurEmiNuevo.csv')
	df3 = pd.read_csv('FuncionEneCubo.csv')

	enes = range(1, 351)

	HeurNipo = df1[df1['Tipo'] == 'CompletoHeurNipo']
	HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	List1 = HeurNipo_count.Tiempo.tolist()

	HeurEmi = df2[df2['Tipo'] == 'CompletoHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Tiempo.tolist()

	EneCubo = df3[df3['Tipo'] == 'FuncionEneCubo']
	EneCubo_count = EneCubo.groupby('cantNod').mean()
	List3 = EneCubo_count.Tiempo.tolist()

	dataf1 = pd.DataFrame({'MFCGM': List1, 'MCMF': List2, 'O(n^3)': List3, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--b', '--r', '--g'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def HeurEmiBLinealDBajaL():
	df1 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	DLineal = df1[df1['Tipo'] == 'DiferenciaHeurEmiConLineal']

	xdata = DLineal['cantNod']

	ydataLineal = DLineal['Res']
	
	plt.plot(xdata, ydataLineal, "r.", alpha = 0.5, label= 'BLineal - MCMF')		# alpha = opacidad
	
	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiBLinealDBajaC():
	df1 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	DCuad = df1[df1['Tipo'] == 'DiferenciaHeurEmiConCuadratica']

	xdata = DCuad['cantNod']

	ydataCuadr = DCuad['Res']

	plt.plot(xdata, ydataCuadr, "g.", alpha=0.5, label = 'BCuadratica - MCMF')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiBLinealDMediaL():
	df1 = pd.read_csv('HeurEmioConLinealDMedia.csv')

	DLineal = df1[df1['Tipo'] == 'DiferenciaHeurEmiConLineal']
	
	xdata = DLineal['cantNod']

	ydataLineal = DLineal['Res']
	
	plt.plot(xdata, ydataLineal, "r.", alpha = 0.5, label= 'BLineal - MCMF')		# alpha = opacidad
	
	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiBLinealDMediaC():
	df1 = pd.read_csv('HeurEmioConLinealDMedia.csv')

	DCuad = df1[df1['Tipo'] == 'DiferenciaHeurEmiConCuadratica']

	xdata = DCuad['cantNod']

	ydataCuadr = DCuad['Res']

	plt.plot(xdata, ydataCuadr, "g.", alpha=0.5, label = 'BCuadratica - MCMF')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()


def HeurEmiBLinealDAltaL():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')

	DLineal = df1[df1['Tipo'] == 'DiferenciaHeurEmiConLineal']
	
	xdata = DLineal['cantNod']

	ydataLineal = DLineal['Res']
	
	plt.plot(xdata, ydataLineal, "r.", alpha = 0.5, label= 'BLineal - MCMF')		# alpha = opacidad
	
	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiBLinealDAltaC():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')

	DCuad = df1[df1['Tipo'] == 'DiferenciaHeurEmiConCuadratica']

	xdata = DCuad['cantNod']

	ydataCuadr = DCuad['Res']

	plt.plot(xdata, ydataCuadr, "g.", alpha=0.5, label = 'BCuadratica - MCMF')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiDifCuadLinealDBaja():
	df1 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	Dif = df1[df1['Tipo'] == 'DiferenciasLocales']



	xdata = Dif['cantNod']
	ydataCuadr = Dif['Res']

	plt.plot(xdata, ydataCuadr, "b.", alpha=0.5, label = 'BCuadratica - Blineal')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiDifCuadLinealDMedia():
	df1 = pd.read_csv('HeurEmioConLinealDMedia.csv')

	Dif = df1[df1['Tipo'] == 'DiferenciasLocales']


	xdata = Dif['cantNod']
	ydataCuadr = Dif['Res']

	plt.plot(xdata, ydataCuadr, "b.", alpha=0.5, label = 'BCuadratica - Blineal')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def HeurEmiDifCuadLinealDAlta():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')

	Dif = df1[df1['Tipo'] == 'DiferenciasLocales']



	xdata = Dif['cantNod']
	ydataCuadr = Dif['Res']

	plt.plot(xdata, ydataCuadr, "b.", alpha=0.5, label = 'BCuadratica - Blineal')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def TiemposLC():
	df1 = pd.read_csv('HeurEmioConLinealDBaja.csv')


	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Lineal_count = Lineal.groupby('cantNod').mean()
	List1 = Lineal_count.Tiempo.tolist()

	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']
	Cuadr_count = Cuadr.groupby('cantNod').mean()
	List2 = Cuadr_count.Tiempo.tolist()

	xrow = len(List1)


	dataf1 = pd.DataFrame({'Busqueda Lineal': List1, 'Busqueda Cuadratica': List2})
	dataf1.astype(float)
	dataf1.plot(title='', x=xrow , style=['--b', '--r', '--g'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()




# expComplejNipoYEmi()
# TodosvsTodosEne35Res()
# TodosvsTodosEne35Tiempo()
# RandomHasta400Res()
# RandomHasta400Tiempo()

#HeurEmiBLinealDBajaL()
#HeurEmiBLinealDBajaC()
#HeurEmiBLinealDMediaL()
#HeurEmiBLinealDMediaC()
#HeurEmiBLinealDAltaL()
#HeurEmiBLinealDAltaC()
#HeurEmiDifCuadLinealDBaja()
#HeurEmiDifCuadLinealDMedia()
#HeurEmiDifCuadLinealDAlta()
TiemposLC()
