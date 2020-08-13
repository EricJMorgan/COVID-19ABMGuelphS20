import dash_bootstrap_components as dbc
import dash_core_components as dcc
import dash_html_components as html
#########################################################################################################################################
#Navbar items
dashboard_item = dbc.NavItem(dbc.NavLink("Dashboard", href="#"))
about_item = dbc.NavItem(dbc.NavLink("About", href="#"))

#Navbar
navigator = dbc.Navbar(
    dbc.Container(
        [
            html.A(
                dbc.Row(
                    [
                        dbc.Col(dbc.NavbarBrand("COVID-19 Guelph eABM", className="ml-2")),
                    ],
                    align="center",
                ),
            ),
            dbc.NavbarToggler(id="navbar-toggler"),
            dbc.Collapse(
                dbc.Nav(
                    [dashboard_item, about_item], className="ml-auto", navbar=True
                ),
                id="navbar-collapse",
                navbar=True,
            ),
        ]
    ),
    className="mb-5",
)
#########################################################################################################################################
#Button Container
buttons = html.Div([
    dbc.Button("Play", outline=True, color="primary", className="mr-1", id="simulationStart"),
    #dbc.Button("Reset", outline=True, color="secondary", className="mr-1"),
]
)
#########################################################################################################################################
#Function to make slider
def make_slider(label, id_tag, slider_value, minimum, maximum, step_value, start_value):
    return dbc.FormGroup([
        dbc.Row([
            dbc.Label(label, html_for=id_tag+"_label"),
            html.Div(className="values", id=slider_value),
        ]),
        dcc.Slider(id=id_tag, min=minimum, max=maximum, step=step_value, value=start_value, marks={
            minimum: str(minimum),
            maximum: str(maximum),
        }),
    ])

#Geographical Risk Sliders (4)
quarantine = make_slider("Quarantine", "Q_slider", "Q_slider_value", 0, 100, 1, 75)
social_distance = make_slider("Social Distancing Severity", "SD_slider", "SD_slider_value", 0, 10, 1, 5)
mask_compliance = make_slider("Mask Compliance", "MC_slider", "MC_slider_value", 0, 100, 1, 75)
hygiene_maint = make_slider("Hygiene Maintenance", "HM_slider", "HM_slider_value", 0, 100, 1, 60)

#Geographical Tab
geo_tab = dbc.Card([
    dbc.CardBody([
        html.Div([quarantine, html.Div(id='quarantine_container')]),
        html.Div([social_distance, html.Div(id='social_distance_container')]),
        html.Div([mask_compliance, html.Div(id='mask_compliance_container')]),
        html.Div([hygiene_maint, html.Div(id='hygiene_maint_container')]),
    ],
    className="mt-1",
    id="geo_tab",
    )
])

#Location Risk Sliders (9)
genstore = make_slider("General Store", "gs_slider", "gs_slider_value", 0, 1, 0.1, 0.6)
transport = make_slider("Transportation", "t_slider", "t_slider_value", 0, 1, 0.1, 0.8)
school = make_slider("School", "sch_slider", "sch_slider_value", 0, 1, 0.1, 0.9)
parksandrec = make_slider("Parks and Recreation", "pnr_slider", "pnr_slider_value", 0, 1, 0.1, 0.2)
services = make_slider("Services", "serv_slider", "serv_slider_value", 0, 1, 0.1, 0.2)
entertainment = make_slider("Entertainment", "ent_slider", "ent_slider_value", 0, 1, 0.1, 0.8)
health = make_slider("Health", "health_slider", "health_slider_value", 0, 1, 0.1, 0.9)
placeofworship = make_slider("Place of Worship", "poworship_slider", "poworship_slider_value", 0, 1, 0.1, 0.8)
residential = make_slider("Residential Areas", "res_slider", "res_slider_value", 0, 1, 0.1, 0.5)

#Location Tab
loc_tab = dbc.Card([
    dbc.CardBody([
        html.Div([genstore, html.Div(id='genstore_container')]),
        html.Div([transport, html.Div(id='transport_container')]),
        html.Div([school, html.Div(id='school_container')]),
        html.Div([parksandrec, html.Div(id='parksandrec_container')]),
        html.Div([services, html.Div(id='services_container')]),
        html.Div([entertainment, html.Div(id='entertainment_container')]),
        html.Div([health, html.Div(id='health_container')]),
        html.Div([placeofworship, html.Div(id='placeofworship_container')]),
        html.Div([residential, html.Div(id='residential_container')]),
    ],
    className="mt-1",
    id="loc_tab",
    )
])

#Tabs
tabs = dbc.Tabs([
    dbc.Tab(geo_tab, label="Geographical Risks", tab_id="geo_tab"),
    dbc.Tab(loc_tab, label="Location Risks", tab_id="loc_tab"),
],
id="tabs",
active_tab="geo_tab",
)
#########################################################################################################################################
#Graphs
import random
from collections import deque

def graph_linear(id_tag, step, num):
    return html.Div([
        dcc.Graph(id = id_tag,
            animate = True,
        ),
        dcc.Interval(
            id = 'linear-update'+str(num),
            interval = step #update every predetermined interval
        )
    ])

def start_time():
    X = deque()
    X.append(0)
    return X

def start_value(initial):
    Y = deque()
    Y.append(initial)
    return Y

def next_timestep(value):
    return value + 4

def get_randomY(value):
    return value + (value * random.uniform(-0.1,0.1)) + 1