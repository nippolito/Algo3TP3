# -*- coding: utf-8 -*-

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import random
import math


def expFuerzaBruta():
	df1 = pd.read_csv('ExpCompleto.csv')
	df2 = pd.read_csv('ExpNIgualM.csv')
	df3 = pd.read_csv('ExpMitadAristas.csv')
	# dfcomplej = pd.read_csv('FuncionComplej.csv')

	enes = range(2, 25)

	# consumo = [(math.pow(n, 3) * math.log(100, 2)) for n in enes]

	NigualM = df2[df2['Tipo'] == 'NigualM']
	NigualM_count = NigualM.groupby('cantNod').mean()
	List1 = NigualM_count.Tiempo_ms.tolist()

	Completo = df1[df1['Tipo'] == 'Completo']
	Completo_count = Completo.groupby('cantNod').mean()
	List2 = Completo_count.Tiempo_ms.tolist()

	mitadAristas = df3[df3['Tipo'] == 'MitadAristas']
	mitadAristas_count = mitadAristas.groupby('cantNod').mean()
	List3 = mitadAristas_count.Tiempo_ms.tolist()

	# complej = dfcomplej[dfcomplej['Tipo'] == 'FuncionComplej']
	# complej_count = complej.groupby('cantNod').mean() * 18
	# List4 = complej_count.Tiempo_ms.tolist()

	dataf1 = pd.DataFrame({'T1': List1, 'T3': List2, 'T2': List3, 'CantVertices': enes})
	dataf1.astype(float)
	dataf1.plot(title='', x='CantVertices', logy=True)
	# dataf1.plot(title='', x='CantVertices', logy=True, kind='scatter', colorbar=True)
	plt.ylabel('Tiempo en ms')
	plt.xlabel('Cantidad de nodos entrada')

	plt.show()

expFuerzaBruta()