#Import dash packages
import dash
from dash.dependencies import Output, Input, State
from dash.exceptions import PreventUpdate
import dash_core_components as dcc
import dash_html_components as html

#Import plotly packages
import plotly
import plotly.graph_objs as go
import plotly.express as px

#Import other packages
from time import sleep
import pandas as pd

#Import other python functions
import data_output as cpp
import user_input as uip

#Example to print to real-time graph
X = cpp.start_X()
Y = cpp.start_Y()

#Start Dash app
app = dash.Dash(__name__)
server = app.server
#app.config.suppress_callback_exceptions = True

#Style of Dash app
colors = {
    'background': '#111111',
    'text': '#7FDBFF'
}

#Header of Dash app -- should include menu
def header():
    return html.Div(children = [
        html.H2(children='COVID-19 Simulation in Guelph'),
    ])

def sideBar():
    return html.Div([
        html.H3(
            "Geographical Risks",
            className = "geo_risk_label",
        ),
        html.P(
            "Social Distancing Severity",
            className = "social_distancing_label",
        ),
        dcc.RangeSlider



        html.P(
            "Incubation Period",
            className = "incubation_label",
        ),
        dcc.RangeSlider(
            id = "incubation_slider",
            min = 2,
            max = 14,
            className = "dcc_control",
        ),
        html.P(
            "Time Between Incubation and Hospital",
            className = "incubation_hospital_label",
        ),
        dcc.RangeSlider(
            id = "incubation_hospital_slider",
            min = 1,
            max = 7,
            className = "dcc_control",
        ),
        html.P(
            "Time Between Hospital and ICU",
            className = ""
        ),

        html.P(
            "Time Between ICU and Death",
            className = ""
        ),

        html.P(
            "Time Between Incubation and Hospital",
            className = ""
        ),


    ])

def graph():
    return html.Div([
        dcc.Graph(id = 'live-graph', animate = True),
        dcc.Interval(
            id = 'graph-update',
            interval = 1000 #update every 1 second
        )
    ])

#Layout of Dash app
app.layout = html.Div(
    children = [

        header(),
        graph(),
    ]
)

#Interactive elements of Dash app
@app.callback(Output('live-graph', 'figure'),
             [Input('graph-update', 'n_intervals')]
)
def update_graph_scatter(input_data):
    global X
    global Y
    X.append(cpp.get_X(X[-1]))
    Y.append(cpp.get_Y(Y[-1]))
    #Y.append(Y[-1]+Y[-1]*random.uniform(-0.1,0.1))

    data = go.Scatter(
        x = list(X),
        y = list(Y),
        name='Scatter',
        mode='lines+markers'
    )

    return {'data':[data], 'layout': go.Layout(xaxis=dict(range=[min(X), max(X)]),
                                               yaxis=dict(range=[min(Y), max(Y)]))}

#Start Dash app
if __name__ == "__main__":
    app.run_server(debug=True)
