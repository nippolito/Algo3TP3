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
	df3 = pd.read_csv('FuncionesNCuboNCuarta.csv')

	HeurNipo = df1[df1['Tipo'] == 'CompletoHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'CompletoHeurEmi']
	EneCubo = df3[df3['Tipo'] == 'FuncionEneCubo']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']
	ydataComplej = EneCubo['Tiempo']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.3)		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "b.", alpha=0.3)
	plt.plot(xdata, ydataComplej, "g.", alpha=0.3)

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

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5)		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5)

	plt.ylabel('Diferencia entre exacto y heurísticas')
	plt.xlabel('Cantidad de nodos entrada')

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

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5)		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5)
	plt.plot(xdata, ydataExacto, "b.", alpha=0.5)

	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')
	plt.yscale('log')

	plt.show()

def RandomHasta400Res():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5)		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5)

	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def RandomHasta400Tiempo():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']

	xdata = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5)		# alpha = opacidad
	plt.plot(xdata, ydataEmi, "g.", alpha=0.5)

	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')
	# plt.yscale('log')

	plt.show()


# expComplejNipoYEmi()
# TodosvsTodosEne35Res()
# TodosvsTodosEne35Tiempo()
# RandomHasta400Res()
# RandomHasta400Tiempo()









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