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
#import geopandas

#Import other python functions
import data_output as cpp
import user_input as uip

#Example to print to real-time graph
X1 = cpp.start_X()
X2 = cpp.start_X()
Y = cpp.start_Y()
Z = cpp.start_Y()

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
    return html.Div([
        html.Div([
            html.H2(
                "COVID-19 Simulation in Guelph",
            ),
        ],
        id = "title",
        className = "one-half column",
        ),
#        html.Div([
#            html.A(
#                html.Button("Extra", id = "extra"),
#                #insert href here
#            ),
#            html.A(
#                html.Button("Learn More", id = "learn-more"),
#                #insert href here
#            ),
#        ],
#        className = "one-half column",
#        id = "menu-buttons",
#        style = {"width": "66%", "display": "inline-block"},
#        )
    ],
    id = "header",
    className = "row flex-display",
    )

def buttons():
    return html.Div([
        html.Button("Start Simulation", id = "start"),
        html.Button("Pause", id = "pause"),
        html.Button("Reset", id = "reset"),
    ],
    id = "buttons",
    className = "mini_container",
    )

def sideBar():
    return html.Div([
        #GEOGRAPHICAL RISK SECTION
        html.H3(
            "Geographical Risks",
            className = "control_label",
        ),
        html.P(
            "Social Distancing Severity",
            className = "control_label",
        ),
        dcc.Slider(
            id = "social_distancing_slider",
            min = 1,
            max = 10,
            value = 5,
            marks = {
                1: '1',
                2: '2',
                3: '3',
                4: '4',
                5: '5',
                6: '6',
                7: '7',
                8: '8',
                9: '9',
                10: '10',
            },
            className = "dcc_control",
        ),
        html.P(
            "Mask Compliance",
            className = "control_label",
        ),
        dcc.Slider(
            id = "mask_compliance_slider",
            min = 1,
            max = 10,
            value = 6,
            marks = {
                1: '1',
                2: '2',
                3: '3',
                4: '4',
                5: '5',
                6: '6',
                7: '7',
                8: '8',
                9: '9',
                10: '10',
            },
            className = "dcc_control",
        ),
        html.P(
            "Maintenance in Hygiene",
            className = "control_label",
        ),
        dcc.Slider(
            id = "maint_hygiene_slider",
            min = 1,
            max = 10,
            value = 7,
            marks = {
                1: '1',
                2: '2',
                3: '3',
                4: '4',
                5: '5',
                6: '6',
                7: '7',
                8: '8',
                9: '9',
                10: '10',
            },
            className = "dcc_control",
        ),
        #SIR INPUTS
        html.H3(
            "Simulation Factors",
            className = "control_label",
        ),
        html.P(
            "Incubation Period",
            className = "control_label",
        ),
        dcc.Slider(
            id = "incubation_slider",
            min = 2,
            max = 14,
            value = 7,
            marks = {
                2: '2',
                3: '3',
                4: '4',
                5: '5',
                6: '6',
                7: '7',
                8: '8',
                9: '9',
                10: '10',
                11: '11',
                12: '12',
                13: '13',
                14: '14',
            },
            className = "dcc_control",
        ),
        html.P(
            "Recovery Period",
            className = "control_label",
        ),
        dcc.Slider(
            id = "recovery_period_slider",
            min = 7,
            max = 14,
            value = 7,
            marks = {
                7: '7',
                8: '8',
                9: '9',
                10: '10',
                11: '11',
                12: '12',
                13: '13',
                14: '14',
            },
            className = "dcc_control",
        ),
        html.P(
            "Time Between Incubation and Hospital",
            className = "control_label",
        ),
        dcc.Slider(
            id = "incubation_hospital_slider",
            min = 1,
            max = 7,
            value = 6,
            marks = {
                1: '1',
                2: '2',
                3: '3',
                4: '4',
                5: '5',
                6: '6',
                7: '7',
            },
            className = "dcc_control",
        ),
        html.P(
            "Time Between Hospital and ICU",
            className = "control_label",
        ),
        dcc.Slider(
            id = "hospital_icu_slider",
            min = 1,
            max = 3,
            value = 2,
            marks = {
                1: '1',
                2: '2',
                3: '3',
            },
            className = "dcc_control",
        ),
        html.P(
            "Time Between ICU and Death",
            className = "control_label",
        ),
        dcc.Slider(
            id = "icu_death_slider",
            min = 1,
            max = 6,
            value = 5,
            marks = {
                1: '1',
                2: '2',
                3: '3',
                4: '4',
                5: '5',
                6: '6',
            },
            className = "dcc_control",
        ),
    ],
    className = "mini_container",
    id = "user-options",
    )

def graph_linear():
    return html.Div([
        dcc.Graph(id = 'linear-graph', animate = True),
        dcc.Interval(
            id = 'linear-update',
            interval = 1000 #update every 1 second
        )
    ],
    className = "mini_container",
    id = "graph1",
    )

def graph_random():
    return html.Div([
        dcc.Graph(id = 'random-graph', animate = True),
        dcc.Interval(
            id = 'random-update',
            interval = 1000 #update every 1 second
        )
    ],
    className = "mini_container",
    id = "graph2",
    )

#Layout of Dash app
app.layout = html.Div(
    children = [
        header(),
        html.Div([
            html.Div([
                buttons(),
                sideBar(),
            ],
            style = {"width": "25%", "display": "inline-block"},
            ),
            html.Div([
                graph_linear(),
                graph_random(),
            ],
            style = {"width": "75%", "display": "inline-block"},
            ),
        ],
        className = "row flex-display",
        )
    ]
)

#Interactive elements of Dash app
@app.callback(Output('linear-graph', 'figure'),
             [Input('linear-update', 'n_intervals')]
)
def update_linear_scatter(input_data):
    global X1
    global Y
    X1.append(cpp.get_X(X1[-1]))
    Y.append(cpp.get_randomY(Y[-1]))

    data1 = go.Scatter(
        x = list(X1),
        y = list(Y),
        name = 'Scatter',
        mode = 'lines+markers'
    )

    return {'data':[data1], 'layout': go.Layout(xaxis=dict(range=[min(X1), max(X1)]),
                                               yaxis=dict(range=[min(Y), max(Y)]))}

#Interactive elements of Dash app
@app.callback(Output('random-graph', 'figure'),
             [Input('random-update', 'n_intervals')]
)
def update_random_scatter(input_data):
    global X2
    global Z
    X2.append(cpp.get_X(X2[-1]))
    Z.append(cpp.get_randomY(Z[-1]))

    data2 = go.Scatter(
        x = list(X2),
        y = list(Z),
        name='Scatter',
        mode='lines+markers'
    )

    return {'data':[data2], 'layout': go.Layout(xaxis=dict(range=[min(X2), max(X2)]),
                                               yaxis=dict(range=[min(Z), max(Z)]))}

#Start Dash app
if __name__ == "__main__":
    app.run_server(debug=True)
