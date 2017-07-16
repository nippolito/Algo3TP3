import datetime
import numpy as np
import plotly
import plotly.plotly as py
import plotly.graph_objs as go
import csv

plotly.tools.set_credentials_file(username='petermattenet',api_key='pyvyKf7oH0riA58DbkGh')

programmers = ['Alex','Nicole','Sara','Etienne','Chelsea','Jody','Marianne']

base = datetime.datetime.today()
date_list = [base - datetime.timedelta(days=x) for x in range(0, 180)]
x = []
y = []
z = []

with open('HeatMapGraspAlfa.csv', 'rb') as csvfile:
    textreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    rowNo = 0
    for row in textreader:
        new_row = []
        if rowNo == 0:
            colNo = 0
            for col in row:
                if colNo != 0:
                    x.append(col)
                colNo += 1
        else:
            colNo = 0
            for col in row:
                if colNo != 0:
                    new_row.append(col)
                colNo += 1
            y.append(row[0])
            z.append(list(new_row))
        rowNo += 1
        

data = [
    go.Heatmap(
        z=z,
        x=x,
        y=y,
        colorscale='Viridis',
    )
]

layout = go.Layout(
    title= '',
    xaxis = dict(title = 'Alfa',ticks='', nticks=36),
    yaxis = dict(title = 'Nodos',ticks='' )
)

fig = go.Figure(data=data, layout=layout)
py.plot(fig, filename='HeatMapGraspAlfa')
