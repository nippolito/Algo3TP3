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

def expComplejNipo():
	df1 = pd.read_csv('ExpComplej.csv')

	enes = range(1, 351)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurNipo = df1[df1['Tipo'] == 'CompletoHeurNipo']
	HeurNipo_count = HeurNipo.groupby('cantNod')
	List1 = HeurNipo_count.Tiempo_ms.tolist()

	EneCuarta = df1[df1['Tipo'] == 'FuncionEneCuarta']
	EneCuarta_count = EneCuarta.groupby('cantNod') * 15/28
	List4 = EneCuarta_count.Tiempo_ms.tolist()

	dataf1 = pd.DataFrame({'MFCGM': List1, 'O(n^4)': List4, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--b', '--r'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def expComplejEmi():
	df1 = pd.read_csv('ExpComplej.csv')

	enes = range(1, 351)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'CompletoHeurEmi' and df1['cantNod'] < 351]
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Tiempo_ms.tolist()

	EneCubo = df1[df1['Tipo'] == 'FuncionEneCubo']
	EneCubo_count = EneCubo.groupby('cantNod').mean() * 12.5
	List3 = EneCubo_count.Tiempo_ms.tolist()

	dataf1 = pd.DataFrame({'MCMF': List2, 'O(n^3)': List3, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--', '--'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()	

def GrafosMalosNipo():
	df1 = pd.read_csv('ExpGrafosMalosHeurNipo2.csv')
	df2 = pd.read_csv('ResultadosGrafoMaloNipo.csv')

	enes = range(14, 501)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'GrafoMaloNipoHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Res.tolist()

	HeurNipo = df1[df1['Tipo'] == 'GrafoMaloNipoHeurNipo']
	HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	List3 = HeurNipo_count.Res.tolist()

	ResultadosPosta = df2[df2['Tipo'] == 'Resultado']
	Res_count = ResultadosPosta.groupby('cantNod').mean()
	List4 = Res_count.Res.tolist()

	dataf1 = pd.DataFrame({'MFCGM': List3, 'Máxima frontera': List4, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--r', '--b'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def GrafosMalosEmi():
	df1 = pd.read_csv('peorcasoemi.csv')
	df2 = pd.read_csv('resCompletos.csv')

	enes = range(1, 501)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'peorCasoEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean() + 1
	List2 = HeurEmi_count.Res.tolist()

	ResultadosPosta = df2[df2['Tipo'] == 'resCompleto']
	Res_count = ResultadosPosta.groupby('cantNod').mean()
	List4 = Res_count.Res.tolist()

	dataf1 = pd.DataFrame({'MCMF': List2, 'Máxima frontera': List4, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['.g', '.c'], logy=True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()	

def TodosvsTodosEne35Res():
	df1 = pd.read_csv('ExpTodosContraTodosAzar.csv')

	enes = range(1, 36)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Res.tolist()

	print HeurEmi_count

	# HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	# HeurNipo_count = HeurNipo.groupby('cantNod')
	# List3 = HeurNipo_count.Res

	# ResultadosPosta = df1[df1['Tipo'] == 'Exacto']
	# Res_count = ResultadosPosta.groupby('cantNod')
	# List4 = Res_count.Res

	# dataf1 = pd.DataFrame({'MCMF': List2, 'MFCGM': List3, 'Exacto': List4, 'CantVertices': enes})
	# dataf1.astype(float)
	# dataf1.plot(title='', x='CantVertices', style=['--r', '--c', '.b'])
	# # dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	# plt.ylabel('Frontera devuelta')
	# plt.xlabel('Cantidad de nodos entrada')

	# plt.show()

def TodosvsTodosEne35Tiempo():
	df1 = pd.read_csv('ExpTodosContraTodosAzar.csv')

	enes = range(1, 36)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Tiempo_ms.tolist()

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	List3 = HeurNipo_count.Tiempo_ms.tolist()

	ResultadosPosta = df1[df1['Tipo'] == 'Exacto']
	Res_count = ResultadosPosta.groupby('cantNod').mean()
	List4 = Res_count.Tiempo_ms.tolist()

	dataf1 = pd.DataFrame({'MCMF': List2, 'MFCGM': List3, 'Exacto': List4, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--r', '--c', '--b'], logy=True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()	

def RandomHasta378Res():
	df1 = pd.read_csv('ExpGrafosRandomN250.csv')

	enes = range(1, 379)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Res.tolist()

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	# HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	# List3 = HeurNipo_count.Res.tolist()

	xdata = HeurNipo['cantNod']
	ydata = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']

	plt.plot(xdata, ydata, "r.", alpha = 0.1)		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "b.", alpha=0.1)


	# dataf1 = pd.DataFrame({'MCMF': List2, 'MFCGM': List3, 'CantVertices': enes})
	# dataf1.astype(float)
	# dataf1.plot(title='', x='CantVertices', style=['--y', '--m'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def RandomHasta378Tiempo():
	df1 = pd.read_csv('ExpGrafosRandomN250.csv')

	enes = range(1, 379)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	HeurEmi = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Tiempo_ms.tolist()

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	List3 = HeurNipo_count.Tiempo_ms.tolist()

	dataf1 = pd.DataFrame({'MCMF': List2, 'MFCGM': List3, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--y', '--m'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempos en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def densidadHeurEmi():
	df1 = pd.read_csv('ExpGrafosDensidadVariable.csv')

	enes = range(1, 251)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	densidad = np.arange(0.1, 1.0, 0.1)

	HeurEmi = df1[df1['Tipo'] == 'GrafoRandomDVarHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantDens').mean()
	List2 = HeurEmi_count.Res.tolist()

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDVarExacto']
	HeurNipo_count = HeurNipo.groupby('cantDens').mean()
	List3 = HeurNipo_count.Res.tolist()

	dataf1 = pd.DataFrame({'MCMF': List2, 'Exacto': List3, 'Densidad': densidad})
	dataf1.astype(float)
	dataf1.plot(title='', x='Densidad', style=['--r', '--b'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Resultado')
	plt.xlabel('Densidad')

	plt.show()


# expComplejNipo()
# expComplejEmi()
# GrafosMalosNipo()
# GrafosMalosEmi()
# TodosvsTodosEne35Res()
# TodosvsTodosEne35Tiempo()
# densidadHeurEmi()
RandomHasta378Res()
# RandomHasta378Tiempo()









# df = pd.read_csv('ruta/archivo.csv') > lee el archivo
# df.head(n) > muestras los primeros n
# df > muestra todo el archivo
# df['LongEntrada'] > muestra los elementos de la columna LongEntrada. Podés seleccionar más columnas también
# df['LongEntrada'][:5] > muestra los elementos de la column LongEntrada hasta el 5
# df[10:15] > muestra los elementos del 10 al 15
# contador = df['LongEntrada'].value_counts() > define a la variable contador como el conteo de cuántos hay según cada LongEntrada
# var.plot(kind='bar') > te crea el plot en var, el tipo es una barra
# plt.show() > te muestra el último plot que creaste
# nes20 = df[df['Longitud_Entrada'] == 20] > cree una variable nes20 donde tengo solo los de long 20

"""	tiempoMasQue40 = df["Tiempo_en_ms"] > 40
	TMas40 = df[tiempoMasQue40]
	print TMas40['Longitud_Entrada'].value_counts()"""   # me muestra cuántos tienen tiempo mayor que 40 según cada n
""" a = TMas40['Longitud_Entrada'].value_counts()
	print a
	todo = df['Longitud_Entrada'].value_counts()
	asd = a / todo.astype(float)
	print asd"""

# df.groupby('Longitud_Entrada').mean() > devuelve la mediana de todos los valores con long_entrada == 1, == 2 ....