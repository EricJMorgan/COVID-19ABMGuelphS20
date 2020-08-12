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

#Things to print to real-time graph
time1 = element.start_time()
time2 = element.start_time()
time3 = element.start_time()
infectedC = element.start_value(5)
infectedT = element.start_value(5)
deceasedT = element.start_value(1)
recoveredT = element.start_value(1)
hospitalC = element.start_value(1)
hospitalT = element.start_value(1)
icuC = element.start_value(1)
icuT = element.start_value(1)

############################################################



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

def toggle_navbar_collapse(n, is_open):
    if n:
        return not is_open
    return is_open

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
    time1.append(element.next_timestep(time1[-1]))
    infectedC.append(element.get_randomY(infectedC[-1]))

    data1 = go.Scatter(
        x = list(time1),
        y = list(infectedC),
        name = 'Scatter',
        mode = 'lines+markers'
    )

    return {'data':[data1], 'layout': go.Layout(xaxis=dict(range=[min(time1), max(time1)]),
                                                yaxis=dict(range=[min(infectedC), max(infectedC)]))}


if __name__ == "__main__":
    app.run_server(debug=True, use_reloader=True)