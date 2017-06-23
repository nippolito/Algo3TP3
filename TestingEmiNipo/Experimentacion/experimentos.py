# -*- coding: utf-8 -*-

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import random
import math

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
	HeurNipo_count = HeurNipo.groupby('cantNod').mean()
	List1 = HeurNipo_count.Tiempo_ms.tolist()

	EneCuarta = df1[df1['Tipo'] == 'FuncionEneCuarta']
	EneCuarta_count = EneCuarta.groupby('cantNod').mean() * 15/28
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

	HeurEmi = df1[df1['Tipo'] == 'CompletoHeurEmi']
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

	dataf1 = pd.DataFrame({'MCMF': List2, 'MFCGM': List3, 'Máxima frontera': List4, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['-.r', '--b', '--g'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

def GrafosMalosEmi():
	df1 = pd.read_csv('ExpGrafosMalosHeurEmi2.csv')
	df2 = pd.read_csv('ResultadosGrafoMaloEmi.csv')

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

	dataf1 = pd.DataFrame({'MCMF': List2, 'MFCGM': List3, 'Máxima frontera': List4, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', style=['--r', '--b', '--g'])
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Frontera devuelta')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()	

# def expC():
# 	df1 = pd.read_csv('ExpMinC.csv')
# 	df2 = pd.read_csv('ExpMedC.csv')
# 	df3 = pd.read_csv('ExpMaxC.csv')

# 	enes = range(2, 451)

# 	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

# 	NigualM = df1[df1['Tipo'] == 'MinC']
# 	NigualM_count = NigualM.groupby('cantNod').mean()
# 	List1 = NigualM_count.Tiempo_ms.tolist()

# 	Completo = df3[df3['Tipo'] == 'MaxC']
# 	Completo_count = Completo.groupby('cantNod').mean()
# 	List2 = Completo_count.Tiempo_ms.tolist()

# 	mitadAristas = df2[df2['Tipo'] == 'MedC']
# 	mitadAristas_count = mitadAristas.groupby('cantNod').mean()
# 	List3 = mitadAristas_count.Tiempo_ms.tolist()

# 	dataf1 = pd.DataFrame({'T1': List1, 'T3': List2, 'T2': List3, 'CantVertices': enes})
# 	dataf1.astype(float)
# 	dataf1.plot(title='', x='CantVertices')
# 	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
# 	plt.ylabel('Tiempo en ms')
# 	plt.xlabel('Maximo peso de arista')

# 	plt.show()	

# expComplejNipo()
# expComplejEmi()
GrafosMalosNipo()








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