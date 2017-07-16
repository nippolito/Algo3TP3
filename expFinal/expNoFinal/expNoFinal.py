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

def expNoFinal():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')
	df3 = pd.read_csv('ExpGrafosRandomGRASP60.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi'] 
	Grasp = df3[df3['Tipo'] == 'Grasp']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']
	ydataGrasp = Grasp['Res']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	plt.plot(xdata, ydataEmi, "b.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataGrasp, "g.", alpha = 0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Frontera devuelta')

	plt.legend()
	plt.show()
	
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

def expComplejEmi():
	df2 = pd.read_csv('ExpComplejHeurEmiNuevo.csv')
	df3 = pd.read_csv('FuncionEneCubo.csv')

	enes = range(1, 351)

	HeurEmi = df2[df2['Tipo'] == 'CompletoHeurEmi']
	HeurEmi_count = HeurEmi.groupby('cantNod').mean()
	List2 = HeurEmi_count.Tiempo.tolist()

	EneCubo = df3[df3['Tipo'] == 'FuncionEneCubo']
	EneCubo_count = EneCubo.groupby('cantNod').mean() * 7
	List3 = EneCubo_count.Tiempo.tolist()

	dataf1 = pd.DataFrame({'MCMF': List2, 'O(n^3)': List3, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--r', '--g'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def expComplejNipo():
	df1 = pd.read_csv('ExpComplejHeurNipoNuevo.csv')
	df3 = pd.read_csv('FuncionEneCubo.csv')

	enes = range(1, 351)

	HeurNipo = df1[df1['Tipo'] == 'CompletoHeurNipo']
	HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	List1 = HeurNipo_count.Tiempo.tolist()

	EneCubo = df3[df3['Tipo'] == 'FuncionEneCubo']
	EneCubo_count = EneCubo.groupby('cantNod').mean() * 4
	List3 = EneCubo_count.Tiempo.tolist()

	dataf1 = pd.DataFrame({'MFCGM': List1, 'O(n^3)': List3, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--b', '--g'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def TodosvsTodosEne35Res():
	df1 = pd.read_csv('Test3TodosvsTodosHeurNipoNuevo.csv')
	df2 = pd.read_csv('Test3TodosvsTodosHeurEmiNuevo.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label="Heurística MFCGM")		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5, label="Heurística MCMF")

	plt.ylabel('Diferencia entre exacto y heurísticas')
	plt.xlabel('Cantidad de nodos entrada')

	plt.legend()
	plt.show()

def TodosvsTodosEne35Tiempo():
	df1 = pd.read_csv('Test3TodosvsTodosHeurNipoNuevo.csv')
	df2 = pd.read_csv('Test3TodosvsTodosHeurEmiNuevo.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	Exacto = df1[df1['Tipo'] == 'Exacto']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']
	ydataExacto = Exacto['Tiempo']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label="Heurística MFCGM")		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5, label="Heurística MCMF")
	plt.plot(xdata, ydataExacto, "b.", alpha=0.5, label="Exacto")

	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')
	plt.yscale('log')

	plt.legend()
	plt.show()

def RandomHasta400Res():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label="Heurística MFCGM")		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5, label="Heurística MCMF")

	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.legend()
	plt.show()

def RandomHasta400Tiempo():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label="Heurística MFCGM")		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5, label="Heurística MCMF")

	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.legend()
	plt.show()


# expComplejNipoYEmi()
# TodosvsTodosEne35Res()
# TodosvsTodosEne35Tiempo()
# RandomHasta400Res()
# RandomHasta400Tiempo()
# expComplejEmi()
# expComplejNipo()
expNoFinal()









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