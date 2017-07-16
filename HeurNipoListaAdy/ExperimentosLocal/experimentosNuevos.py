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

def IteracionesBaja():
	df1 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']


	xdata = Lineal['cantNod']
	ydataLineal = Lineal['Iteraciones']
	ydataCuadr = Cuadr ['Iteraciones']

	plt.plot(xdata, ydataLineal, "r*", alpha=0.5, label = 'IteracionesLineal')

	plt.plot(xdata, ydataCuadr, "g.", alpha=0.5, label = 'IteracionesCuadratica')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def IteracionesMedia():
	df1 = pd.read_csv('HeurEmioConLinealDMedia.csv')

	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']


	xdata = Lineal['cantNod']
	ydataLineal = Lineal['Iteraciones']
	ydataCuadr = Cuadr ['Iteraciones']

	plt.plot(xdata, ydataLineal, "r*", alpha=0.5, label = 'IteracionesLineal')

	plt.plot(xdata, ydataCuadr, "g.", alpha=0.5, label = 'IteracionesCuadratica')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def IteracionesAlta():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')

	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']


	xdata = Lineal['cantNod']
	ydataLineal = Lineal['Iteraciones']
	ydataCuadr = Cuadr ['Iteraciones']

	plt.plot(xdata, ydataLineal, "r*", alpha=0.5, label = 'IteracionesLineal')

	plt.plot(xdata, ydataCuadr, "g.", alpha=0.5, label = 'IteracionesCuadratica')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def TiemposBaja():
	df1 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	enes = [5,10,15,20,25,0,5,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175]

	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Lineal_count = Lineal.groupby('cantNod').mean()
	List1 = Lineal_count.Tiempo.tolist()

	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']
	Cuadr_count = Cuadr.groupby('cantNod').mean()
	List2 = Cuadr_count.Tiempo.tolist()

	print List1



	dataf1 = pd.DataFrame({'Busqueda Lineal': List1, 'Busqueda Cuadratica': List2, 'CantVertices':enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices' , style=['--b', '--r', '--g'], logy = True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def TiemposMedia():
	df1 = pd.read_csv('HeurEmioConLinealDMedia.csv')

	enes = [5,10,15,20,25,0,5,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175]

	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Lineal_count = Lineal.groupby('cantNod').mean()
	List1 = Lineal_count.Tiempo.tolist()

	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']
	Cuadr_count = Cuadr.groupby('cantNod').mean()
	List2 = Cuadr_count.Tiempo.tolist()

	print List1



	dataf1 = pd.DataFrame({'Busqueda Lineal': List1, 'Busqueda Cuadratica': List2, 'CantVertices':enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices' , style=['--b', '--r', '--g'], logy= True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def TiemposAlta():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')

	enes = [5,10,15,20,25,0,5,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175]

	Lineal = df1[df1['Tipo'] == 'BLinealHeurEmi']
	Lineal_count = Lineal.groupby('cantNod').mean()
	List1 = Lineal_count.Tiempo.tolist()

	Cuadr = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']
	Cuadr_count = Cuadr.groupby('cantNod').mean()
	List2 = Cuadr_count.Tiempo.tolist()

	print List1



	dataf1 = pd.DataFrame({'Busqueda Lineal': List1, 'Busqueda Cuadratica': List2, 'CantVertices':enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices' , style=['--b', '--r', '--g'], logy= True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def TiemposTodos():

	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')
	df2 = pd.read_csv('HeurEmioConLinealDMedia.csv')
	df3 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	enes = [5,10,15,20,25,0,5,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175]

	LinealA = df1[df1['Tipo'] == 'BLinealHeurEmi']
	LinealA_count = LinealA.groupby('cantNod').mean()
	List1 = LinealA_count.Tiempo.tolist()

	CuadrA = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']
	CuadrA_count = CuadrA.groupby('cantNod').mean()
	List2 = CuadrA_count.Tiempo.tolist()

	LinealM = df2[df2['Tipo'] == 'BLinealHeurEmi']
	LinealM_count = LinealM.groupby('cantNod').mean()
	List3 = LinealM_count.Tiempo.tolist()

	CuadrM = df2[df2['Tipo'] == 'BCuadraticaHeurEmi']
	CuadrM_count = CuadrM.groupby('cantNod').mean()
	List4 = CuadrM_count.Tiempo.tolist()

	LinealB = df3[df3['Tipo'] == 'BLinealHeurEmi']
	LinealB_count = LinealB.groupby('cantNod').mean()
	List5 = LinealB_count.Tiempo.tolist()

	CuadrB = df3[df3['Tipo'] == 'BCuadraticaHeurEmi']
	CuadrB_count = CuadrB.groupby('cantNod').mean()
	List6 = CuadrB_count.Tiempo.tolist()






	dataf1 = pd.DataFrame({'BL Alta': List1, 'BC Alta': List2, 'BL Media': List3, 'BC Media': List4, 'BL Baja': List5, 'BC Baja': List6,  'CantVertices':enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices' , style=['--b', '--r', '--g', '--c', '--m', '--k'], logy= True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def IteracionesTodos():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')
	df2 = pd.read_csv('HeurEmioConLinealDMedia.csv')
	df3 = pd.read_csv('HeurEmioConLinealDBaja.csv')

	LinealA = df1[df1['Tipo'] == 'BLinealHeurEmi']
	CuadrA = df1[df1['Tipo'] == 'BCuadraticaHeurEmi']
	LinealM = df2[df2['Tipo'] == 'BLinealHeurEmi']
	CuadrM = df2[df2['Tipo'] == 'BCuadraticaHeurEmi']
	LinealB = df3[df3['Tipo'] == 'BLinealHeurEmi']
	CuadrB = df3[df3['Tipo'] == 'BCuadraticaHeurEmi']


	xdata = LinealA['cantNod']
	ydataLinealA = LinealA['Iteraciones']
	ydataCuadrA = CuadrA ['Iteraciones']
	ydataLinealM = LinealM['Iteraciones']
	ydataCuadrM = CuadrM ['Iteraciones']
	ydataLinealB = LinealB['Iteraciones']
	ydataCuadrB = CuadrB ['Iteraciones']

	plt.plot(xdata, ydataLinealA, "r*", alpha=0.5, label = 'IteracionesLinealA')
	plt.plot(xdata, ydataLinealM, "g*", alpha=0.5, label = 'IteracionesLinealM')
	plt.plot(xdata, ydataLinealB, "b*", alpha=0.5, label = 'IteracionesLinealB')

	plt.plot(xdata, ydataCuadrA, "m.", alpha=0.5, label = 'IteracionesCuadraticaA')
	plt.plot(xdata, ydataCuadrM, "k.", alpha=0.5, label = 'IteracionesCuadraticaM')
	plt.plot(xdata, ydataCuadrB, "c.", alpha=0.5, label = 'IteracionesCuadraticaB')

	plt.ylabel('Diferencia obtenida')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()

def NipoVsEmiBL():
	df1 = pd.read_csv('DiferenciasNipo.csv')


	DLineal = df1[df1['Tipo'] == 'DifNipoLineal']
	DCuad = df1[df1['Tipo'] == 'DifNipoCuadratica']
	
	xdata = DLineal['cantNod']

	ydataDLineal = DLineal['Res']
	ydataDCuad = DCuad['Res']
	

	
	#plt.plot(xdata, ydataLineal, "r-", alpha = 0.5, label= 'Busqueda Lineal')
	#plt.plot(xdata, ydataDCuad, "b.", alpha = 0.5, label= 'MFCGM - Busqueda Cuadratica')
	plt.plot(xdata, ydataDLineal, "m.", alpha = 0.5, label= 'MFCGM - Busqueda Lineal')
	

	plt.ylabel('Resultado obtenido')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()




def prueba():
	df1 = pd.read_csv('HeurEmioConLinealDAlta.csv')

	DLineal = df1[df1['Tipo'] == 'DiferenciaHeurEmiConLineal']
	
	xdata = DLineal['cantNod']

	ydataLineal = DLineal['Res']
	prueba = pd.Series()
	
	l = len(xdata)
	c= 2
	
	prueba = toA

	for  i in xrange(0,l):
		print prueba
		c+=6


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
#prueba()
#IteracionesBaja()
#IteracionesMedia()
#IteracionesAlta()
#TiemposBaja()
#TiemposMedia()
#TiemposAlta()
#TiemposTodos()
#IteracionesTodos()
NipoVsEmiBL()