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
    return html.Div([
        html.Div([
            html.H2(
                "COVID-19 Simulation in Guelph",
            ),
        ],
        className = "one-half column",
        id = "title",
        style = {"width": "33%", "display": "inline-block"},
        ),
        html.Div([
            html.A(
                html.Button("Extra", id = "extra"),
                #insert href here
            ),
            html.A(
                html.Button("Learn More", id = "learn-more"),
                #insert href here
            ),
        ],
        className = "one-half column",
        id = "menu-buttons",
        style = {"width": "66%", "display": "inline-block"},
        )
    ],
    id = "header",
    className = "row flex-display",
    )

def buttons():
    return html.Div([
        html.Button("Start Simulation", id = "start"),
        html.Button("Pause", id = "pause"),
        html.Button("Reset", id = "reset"),
    ])

def sideBar():
    return html.Div([
        #GEOGRAPHICAL RISK SECTION
        html.H3(
            "Geographical Risks",
            className = "geo_risk_label",
        ),
        html.P(
            "Social Distancing Severity",
            className = "social_distancing_label",
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
            className = "mask_compliance_label",
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
            className = "maint_hygiene_label",
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
            className = "simulation_factors_label",
        ),
        html.P(
            "Incubation Period",
            className = "incubation_label",
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
            "Time Between Incubation and Hospital",
            className = "incubation_hospital_label",
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
    ],
    className = "pretty_container four columns",
    id = "user-options",
    )

def graph():
    return html.Div([
        dcc.Graph(id = 'live-graph', animate = True),
        dcc.Interval(
            id = 'graph-update',
            interval = 1000 #update every 1 second
        )
    ],
    className = "pretty_container",
    id = "graph",
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
                graph(),
            ],
            style = {"width": "50%", "display": "inline-block"},
            ),
        ])
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
