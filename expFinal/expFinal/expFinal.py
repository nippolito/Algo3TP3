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

def expFinalDensAltaRes():
	df1 = pd.read_csv('ExpFinalSinGraspDensidadAlta.csv')
	df2 = pd.read_csv('ExpGrafosRandomGRASP50Alta.csv')

	HeurNipo = df1[df1['Tipo'] == 'HeurNipo']
	HeurEmi = df1[df1['Tipo'] == 'HeurEmi']
	BLLEmi = df1[df1['Tipo'] == 'BusquedaLocalLinealEmi']
	BLCEmi = df1[df1['Tipo'] == 'BusquedaLocalCuadraticaEmi']
	Grasp = df2[df2['Tipo'] == 'GrafoRandomDAltaGRASP']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']
	ydataBLLEmi = BLLEmi['Res']
	ydataBLCEmi = BLCEmi['Res']
	ydataGrasp = Grasp['Res']

	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	plt.plot(xdata, ydataEmi, "b.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataBLLEmi, "g.", alpha = 0.5, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCEmi, "y.", alpha = 0.5, label='BL Cuadratica sobre MCMF')
	plt.plot(xdata, ydataGrasp, "k." , alpha=0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Frontera devuelta')

	plt.legend()
	plt.show()

def expFinalDensAltaTiempo():
	df1 = pd.read_csv('ExpFinalSinGraspDensidadAlta.csv')
	df2 = pd.read_csv('ExpGrafosRandomGRASP50Alta.csv')

	HeurNipo = df1[df1['Tipo'] == 'HeurNipo']
	HeurEmi = df1[df1['Tipo'] == 'HeurEmi']
	BLLEmi = df1[df1['Tipo'] == 'BusquedaLocalLinealEmi']
	BLCEmi = df1[df1['Tipo'] == 'BusquedaLocalCuadraticaEmi']
	Grasp = df2[df2['Tipo'] == 'GrafoRandomDAltaGRASP']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']
	ydataBLLEmi = BLLEmi['Tiempo']
	ydataBLCEmi = BLCEmi['Tiempo']
	ydataGrasp = Grasp['Tiempo']

	plt.plot(xdata, ydataEmi, "b.", alpha = 0.8, label='Heuristica MCMF')
	plt.plot(xdata, ydataBLLEmi, "g.", alpha = 0.8, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCEmi, "y.", alpha = 0.8, label='BL Cuadratica sobre MCMF')
	plt.plot(xdata, ydataNipo, "r.", alpha = 0.8, label='Heuristica MFCGM')
	plt.plot(xdata, ydataGrasp, "k." , alpha=0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Tiempo en ms')
	plt.yscale('log')

	plt.legend()
	plt.show()	

def expFinalDensMediaRes():
	df1 = pd.read_csv('ExpFinalSinGraspDensidadMedia.csv')
	df2 = pd.read_csv('ExpGrafosRandomGRASP50Media.csv')

	HeurNipo = df1[df1['Tipo'] == 'HeurNipo']
	HeurEmi = df1[df1['Tipo'] == 'HeurEmi']
	BLLEmi = df1[df1['Tipo'] == 'BusquedaLocalLinealEmi']
	BLCEmi = df1[df1['Tipo'] == 'BusquedaLocalCuadraticaEmi']
	Grasp = df2[df2['Tipo'] == 'GrafoRandomDMediaGRASP']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']
	ydataBLLEmi = BLLEmi['Res']
	ydataBLCEmi = BLCEmi['Res']
	ydataGrasp = Grasp['Res']

	plt.plot(xdata, ydataEmi, "b.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataBLLEmi, "g.", alpha = 0.5, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCEmi, "y.", alpha = 0.5, label='BL Cuadratica sobre MCMF')
	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	plt.plot(xdata, ydataGrasp, "k." , alpha=0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Frontera devuelta')

	plt.legend()
	plt.show()

def expFinalDensMediaTiempo():
	df1 = pd.read_csv('ExpFinalSinGraspDensidadMedia.csv')
	df2 = pd.read_csv('ExpGrafosRandomGRASP50Media.csv')

	HeurNipo = df1[df1['Tipo'] == 'HeurNipo']
	HeurEmi = df1[df1['Tipo'] == 'HeurEmi']
	BLLEmi = df1[df1['Tipo'] == 'BusquedaLocalLinealEmi']
	BLCEmi = df1[df1['Tipo'] == 'BusquedaLocalCuadraticaEmi']
	Grasp = df2[df2['Tipo'] == 'GrafoRandomDMediaGRASP']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']
	ydataBLLEmi = BLLEmi['Tiempo']
	ydataBLCEmi = BLCEmi['Tiempo']
	ydataGrasp = Grasp['Tiempo']

	plt.plot(xdata, ydataEmi, "b.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataBLLEmi, "g.", alpha = 0.5, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCEmi, "y.", alpha = 0.5, label='BL Cuadratica sobre MCMF')
	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	plt.plot(xdata, ydataGrasp, "k." , alpha=0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Tiempo en ms')
	plt.yscale('log')

	plt.legend()
	plt.show()	

def expFinalDensBajaRes():
	df1 = pd.read_csv('ExpFinalSinGraspDensidadBaja.csv')
	df2 = pd.read_csv('ExpGrafosRandomGRASP50Baja.csv')

	HeurNipo = df1[df1['Tipo'] == 'HeurNipo']
	HeurEmi = df1[df1['Tipo'] == 'HeurEmi']
	BLLEmi = df1[df1['Tipo'] == 'BusquedaLocalLinealEmi']
	BLCEmi = df1[df1['Tipo'] == 'BusquedaLocalCuadraticaEmi']
	Grasp = df2[df2['Tipo'] == 'GrafoRandomDBajaGRASP']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Res']
	ydataEmi = HeurEmi['Res']
	ydataBLLEmi = BLLEmi['Res']
	ydataBLCEmi = BLCEmi['Res']
	ydataGrasp = Grasp['Res']

	plt.plot(xdata, ydataEmi, "b.", alpha = 0.5, label='Heuristica MCMF')
	plt.plot(xdata, ydataBLLEmi, "g.", alpha = 0.8, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCEmi, "y.", alpha = 0.5, label='BL Cuadratica sobre MCMF')
	plt.plot(xdata, ydataNipo, "r.", alpha = 0.5, label='Heuristica MFCGM')
	plt.plot(xdata, ydataGrasp, "k." , alpha=0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Frontera devuelta')

	plt.legend()
	plt.show()

def expFinalDensBajaTiempo():
	df1 = pd.read_csv('ExpFinalSinGraspDensidadBaja.csv')
	df2 = pd.read_csv('ExpGrafosRandomGRASP50Baja.csv')

	HeurNipo = df1[df1['Tipo'] == 'HeurNipo']
	HeurEmi = df1[df1['Tipo'] == 'HeurEmi']
	BLLEmi = df1[df1['Tipo'] == 'BusquedaLocalLinealEmi']
	BLCEmi = df1[df1['Tipo'] == 'BusquedaLocalCuadraticaEmi']
	Grasp = df2[df2['Tipo'] == 'GrafoRandomDBajaGRASP']

	xdata  = HeurNipo['cantNod']

	ydataNipo = HeurNipo['Tiempo']
	ydataEmi = HeurEmi['Tiempo']
	ydataBLLEmi = BLLEmi['Tiempo']
	ydataBLCEmi = BLCEmi['Tiempo']
	ydataGrasp = Grasp['Res']

	plt.plot(xdata, ydataEmi, "b.", alpha = 0.8, label='Heuristica MCMF')
	plt.plot(xdata, ydataBLLEmi, "g.", alpha = 0.8, label='BL Lineal sobre MCMF')
	plt.plot(xdata, ydataBLCEmi, "y.", alpha = 0.8, label='BL Cuadratica sobre MCMF')
	plt.plot(xdata, ydataNipo, "r.", alpha = 0.8, label='Heuristica MFCGM')
	plt.plot(xdata, ydataGrasp, "k." , alpha=0.5, label='Grasp')

	plt.xlabel('Cantidad de nodos entrada')
	plt.ylabel('Tiempo en ms')
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
expFinalDensAltaRes()
expFinalDensAltaTiempo()
expFinalDensMediaRes()
expFinalDensMediaTiempo()
expFinalDensBajaRes()
expFinalDensBajaTiempo()









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