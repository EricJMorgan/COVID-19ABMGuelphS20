import dash
from dash.dependencies import Output, Input, State
from dash.exceptions import PreventUpdate
import dash_core_components as dcc
import dash_html_components as html
import plotly
import random
import plotly.graph_objs as go
import plotly.express as px

import pandas as pd

app = dash.Dash(__name__)
server = app.server
#app.config.suppress_callback_exceptions = True

text_style = {
    'color': "#FCDE9C",
    'font-family': 'Open Sans'
}

def header():
    return html.Div(
        [
            #include a logo?
            html.H2("COVID-19 Simulation in Guelph"),
        ],
        className = "header__title",

    )

#Dash App Layout
app.layout = html.Div(
    children = [
        header(),
    ]
)

if __name__ == "__main__":
    app.run_server(debug=True)
