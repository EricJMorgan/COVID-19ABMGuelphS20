import dash
import dash_bootstrap_components as dbc
import dash_html_components as html
import dash_core_components as dcc
from dash.dependencies import Input, Output, State
import element
import os

#Import plotly packages
import plotly
import plotly.graph_objs as go
import plotly.express as px

import pandas as pd
import geopandas as gpd
import matplotlib.pyplot as plt
from plotly.tools import mpl_to_plotly

#Example to print to real-time graph
X1 = element.start_X()
X2 = element.start_X()
Y = element.start_Y()
Z = element.start_Y()

############################################################

app = dash.Dash(external_stylesheets=[dbc.themes.FLATLY])

app.layout = html.Div([
    element.navigator,
    dbc.Row(dbc.Col(html.Div(element.buttons))),
    dbc.Row([
        dbc.Col(html.Div(element.tabs), width=4),
        dbc.Col(html.Div(element.graph_linear('graph', 1000, 'Infected Cases Over Time')), width=8),
    ]),
])

# we use a callback to toggle the collapse on small screens
def toggle_navbar_collapse(n, is_open):
    if n:
        return not is_open
    return is_open

# the same function (toggle_navbar_collapse) is used in all three callbacks
app.callback(
    Output("navbar-collapse", "is_open"),
    [Input("navbar-toggler", "n_clicks")],
    [State("navbar-collapse", "is_open")],
)(toggle_navbar_collapse)

list_elements = ['Q_slider', 'SD_slider', 'MC_slider', 'HM_slider', 'gs_slider',
                't_slider', 'sch_slider', 'pnr_slider', 'serv_slider',
                'ent_slider', 'health_slider', 'poworship_slider', 'res_slider',]

for i in range(len(list_elements)):
    @app.callback(
        Output(list_elements[i]+'_value', 'children'),
        [Input(list_elements[i], 'value')])
    def update_output_SD(value):
        return '{}'.format(value)

#Interactive elements of Dash app
@app.callback(Output('graph', 'figure'),
             [Input('linear-update', 'n_intervals')]
)
def update_linear_scatter(input_data):
    global X1
    global Y
    X1.append(element.get_X(X1[-1]))
    Y.append(element.get_randomY(Y[-1]))

    data1 = go.Scatter(
        x = list(X1),
        y = list(Y),
        name = 'Scatter',
        mode = 'lines+markers'
    )

    return {'data':[data1], 'layout': go.Layout(xaxis=dict(range=[min(X1), max(X1)]),
                                                yaxis=dict(range=[min(Y), max(Y)]))}


if __name__ == "__main__":
    app.run_server(debug=True, use_reloader=True)