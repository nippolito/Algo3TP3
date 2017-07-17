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

def expNoFinalRes():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')
	df3 = pd.read_csv('ExpGrafosRandomGRASP60.csv')
	df4 = pd.read_csv('ExpGrafosRandomBL.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	BLLinealEmi = df4[df4['Tipo'] == 'BLinealHeurEmi']
	BLCuadraticaEmi = df4[df4['Tipo'] == 'BCuadraticaHeurEmi'] 
	Grasp = df3[df3['Tipo'] == 'Grasp']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']
	ydataGrasp = Grasp['Res']
	ydataBLLineal = BLLinealEmi['Res']
	ydataBLCuadratica = BLCuadraticaEmi['Res']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	# plt.plot(xdata, ydataEmi, "g.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataGrasp, "b.", alpha = 0.5, label='Grasp')
	# plt.plot(xdata, ydataBLLineal, "k.", alpha = 0.5, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCuadratica, "y.", alpha = 0.5, label='BL Cuadr sobre MCMF')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Frontera devuelta')

	plt.legend()
	plt.show()

def expNoFinalTiempo():
	df1 = pd.read_csv('ExpGrafosRandomNipoNuevo.csv')
	df2 = pd.read_csv('ExpGrafosRandomEmiNuevo.csv')
	df3 = pd.read_csv('ExpGrafosRandomGRASP60.csv')
	df4 = pd.read_csv('ExpGrafosRandomBL.csv')

	HeurNipo = df1[df1['Tipo'] == 'GrafoRandomDMediaHeurNipo']
	HeurEmi = df2[df2['Tipo'] == 'GrafoRandomDMediaHeurEmi']
	BLLinealEmi = df4[df4['Tipo'] == 'BLinealHeurEmi']
	BLCuadraticaEmi = df4[df4['Tipo'] == 'BCuadraticaHeurEmi'] 
	Grasp = df3[df3['Tipo'] == 'Grasp']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']
	ydataGrasp = Grasp['Tiempo']
	ydataBLLineal = BLLinealEmi['Tiempo']
	ydataBLCuadratica = BLCuadraticaEmi['Tiempo']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	plt.plot(xdata, ydataEmi, "g.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataGrasp, "b.", alpha = 0.5, label='Grasp')
	plt.plot(xdata, ydataBLLineal, "k.", alpha = 0.5, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCuadratica, "y.", alpha = 0.5, label='BL Cuadr sobre MCMF')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Frontera devuelta')
	plt.yscale('log')

	plt.legend()
	plt.show()	


# expComplejNipoYEmi()
# TodosvsTodosEne35Res()
# TodosvsTodosEne35Tiempo()
# RandomHasta400Res()
# RandomHasta400Tiempo()
# expComplejEmi()
# expComplejNipo()
expNoFinalRes()
expNoFinalTiempo()









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