import dash
import dash_bootstrap_components as dbc
import dash_html_components as html
import dash_core_components as dcc
from dash.dependencies import Input, Output, State
import element
import os
import math

#Import plotly packages
import plotly
import plotly.graph_objs as go
import plotly.express as px

import pandas as pd
# import geopandas as gpd
import matplotlib.pyplot as plt
from plotly.tools import mpl_to_plotly

############################################################

import cffi

ffi = cffi.FFI()
ffi.cdef('''
    typedef struct _Simulation Simulation;
    Simulation* Simulation_new();
    void simTimeStep(Simulation* sim);
    int newlyInfected(Simulation* sim);
    int infectedCurrent(Simulation* sim);
    int infectedTotal(Simulation* sim);
    int deceasedTotal(Simulation* sim);
    int recoveredTotal(Simulation* sim);
    int hospitalTotal(Simulation* sim);
    int hospitalCurrent(Simulation* sim);
    int ICUtotal(Simulation* sim);
    int ICUCurrent(Simulation* sim);
    void socialDistanceServeritySetter(Simulation* sim, int val);
    void maskComplianceSetter(Simulation* sim, double val);
    void hygieneMaintainenceSetter(Simulation* sim, double val);
    void genStoreRiskSetter(Simulation* sim, double val);
    void transportRiskSetter(Simulation* sim, double val);
    void schoolRiskSetter(Simulation* sim, double val);
    void parkRiskSetter(Simulation* sim, double val);
    void entertainmentRiskSetter(Simulation* sim, double val);
    void healthPlaceRiskSetter(Simulation* sim, double val);
    void placeOfWorshipRiskSetter(Simulation* sim, double val);
    void residentialRiskSetter(Simulation* sim, double val);
    void quarantineSeverity(Simulation* sim, double val);
''')

lib = ffi.dlopen('./libProject.so')

class Simulation(object):
    def __init__(self):
        self.obj = lib.Simulation_new()

    def timeStep(self):
        lib.simTimeStep(self.obj)
    
    def newlyInfected(self):
        return lib.newlyInfected(self.obj)

    def infectedCurrent(self):
        return lib.infectedCurrent(self.obj)

    def infectedTotal(self):
        return lib.infectedTotal(self.obj)

    def deceasedTotal(self):
        return lib.deceasedTotal(self.obj)

    def recoveredTotal(self):
        return lib.recoveredTotal(self.obj)
        
    def hospitalTotal(self):
        return lib.hospitalTotal(self.obj)

    def hospitalCurrent(self):
        return lib.hospitalCurrent(self.obj)
    
    def ICUtotal(self):
        return lib.ICUtotal(self.obj)

    def ICUCurrent(self):
        return lib.ICUCurrent(self.obj)

    def setSocialDistanceServerity(self, val):
        lib.socialDistanceServeritySetter(self.obj, val)

    def setmaskCompliance(self, val):
        lib.maskComplianceSetter(self.obj, val)

    def setHygieneMaintainence(self, val):
        lib.hygieneMaintainenceSetter(self.obj, val)

    def setGenStoreRisk(self, val):
        lib.genStoreRiskSetter(self.obj, val)

    def setTransportRisk(self, val):
        lib.transportRiskSetter(self.obj, val)

    def setSchoolRisk(self, val):
        lib.schoolRiskSetter(self.obj, val)

    def setParkRisk(self, val):
        lib.parkRiskSetter(self.obj, val)

    def setEntertainmentRisk(self, val):
        lib.entertainmentRiskSetter(self.obj, val)

    def setHealthPlaceRisk(self, val):
        lib.healthPlaceRiskSetter(self.obj, val)

    def setPlaceOfWorshipRisk(self, val):
        lib.placeOfWorshipRiskSetter(self.obj, val)

    def setResidentialRisk(self, val):
        lib.residentialRiskSetter(self.obj, val)
    
    def quarantineSeverity(self, val):
        lib.quarantineSeverity(self.obj, val)

#Initialize times and values
sim = Simulation()
time = element.start_time()
infectedC = sim.infectedCurrent()
infectedN = sim.newlyInfected()
infectedT = sim.infectedTotal()
deceasedT = sim.deceasedTotal()
recoveredT = sim.recoveredTotal()
hospitalC = sim.hospitalCurrent()
hospitalT = sim.hospitalTotal()
icuC = sim.ICUCurrent()
icuT = sim.ICUtotal()
totalBedCount = 130
icuBedCount = 22

############################################################

app = dash.Dash(external_stylesheets=[dbc.themes.FLATLY])

infectedGraph = element.graph_linear('infectedGraph', 1000, 1)
idrGraph = element.graph_linear('idrGraph', 1000, 2)
hospitalGraph = element.graph_linear('hospitalGraph', 1000, 3)
icuGraph = element.graph_linear('icuGraph', 1000, 4)


infectedGraph = dbc.Card([
    dbc.CardBody([
        html.Div([infectedGraph]),
        html.Div([idrGraph]),
    ],
    id="i_tab")
])

hospitalGraph = dbc.Card([
    dbc.CardBody([
        html.Div([hospitalGraph]),
        html.Div([icuGraph]),
    ],
    id="h_tab")
])

graphTabs = dbc.Tabs([
    dbc.Tab(infectedGraph, label="COVID-19 Cases", tab_id="i_tab"),
    dbc.Tab(hospitalGraph, label="Hospital & ICU Cases", tab_id="h_tab"),
],
id="graph_tabs",
active_tab="i_tab",
)

app.layout = html.Div([
    element.navigator,
    dbc.Row(dbc.Col(html.Div(element.buttons))),
    dbc.Row([
        dbc.Col(html.Div(element.tabs), width=4),
        dbc.Col(html.Div(graphTabs), width=8),
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

##################################################
list_elements = ['Q_slider', 'SD_slider', 'MC_slider', 'HM_slider', 'gs_slider',
                't_slider', 'sch_slider', 'pnr_slider', 'serv_slider',
                'ent_slider', 'health_slider', 'poworship_slider', 'res_slider',]

@app.callback(
    Output(list_elements[0]+'_value', 'children'),
    [Input(list_elements[0], 'value')])
def update_output_Q(value):
    sim.quarantineSeverity(value/100)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[1]+'_value', 'children'),
    [Input(list_elements[1], 'value')])
def update_output_SD(value):
    sim.setSocialDistanceServerity(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[2]+'_value', 'children'),
    [Input(list_elements[2], 'value')])
def update_output_MC(value):
    sim.setmaskCompliance(value/100)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[3]+'_value', 'children'),
    [Input(list_elements[3], 'value')])
def update_output_HM(value):
    sim.setHygieneMaintainence(value/100)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[4]+'_value', 'children'),
    [Input(list_elements[4], 'value')])
def update_output_gs(value):
    sim.setGenStoreRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[5]+'_value', 'children'),
    [Input(list_elements[5], 'value')])
def update_output_t(value):
    sim.setTransportRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[6]+'_value', 'children'),
    [Input(list_elements[6], 'value')])
def update_output_sch(value):
    sim.setSchoolRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[7]+'_value', 'children'),
    [Input(list_elements[7], 'value')])
def update_output_pnr(value):
    sim.setParkRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[8]+'_value', 'children'),
    [Input(list_elements[8], 'value')])
def update_output_serv(value):
    #RETURN VALUE
    return '{}'.format(value)

@app.callback(
    Output(list_elements[9]+'_value', 'children'),
    [Input(list_elements[9], 'value')])
def update_output_ent(value):
    sim.setEntertainmentRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[10]+'_value', 'children'),
    [Input(list_elements[10], 'value')])
def update_output_health(value):
    sim.setEntertainmentRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[11]+'_value', 'children'),
    [Input(list_elements[11], 'value')])
def update_output_poworship(value):
    sim.setPlaceOfWorshipRisk(value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[12]+'_value', 'children'),
    [Input(list_elements[12], 'value')])
def update_output_res(value):
    sim.setResidentialRisk(value)
    return '{}'.format(value)
###########################################################

list_graphs  = ['infectedGraph', 'idrGraph', 'hospitalGraph', 'icuGraph']
list_outputs = [[infectedC], [infectedT], [deceasedT], [recoveredT], [hospitalC], [hospitalT], [icuC], [icuT], [infectedN]]
limitHospital = [totalBedCount]
limitICU = [icuBedCount]
graph1 = False
graph2 = False
graph3 = False
graph4 = False

#Infected Graph
@app.callback(Output('infectedGraph', 'figure'),
             [Input('linear-update1', 'n_intervals')]
)
def update_infectedGraph(input_data):
    time.append(element.next_timestep(time[-1]))
    list_outputs[0].append(sim.infectedCurrent())
    list_outputs[1].append(sim.infectedTotal())
    list_outputs[8].append(sim.newlyInfected())
    converted_time = [val/24 for val in time]
    converted_time = [round(val,2) for val in converted_time]

    data1 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[0]),
        name = 'Current Infected Cases',
        mode = 'lines+markers',
        marker_color = '#F5CB5C',
    )

    data2 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[1]),
        name = 'Total Infected Cases',
        mode = 'lines+markers',
        marker_color = '#F71735',
    )

    data3 = go.Bar(
        x = list(converted_time),
        y = list(list_outputs[8]),
        name = 'Newly Infected Cases',
        marker_color = '#76B041',
    )

    global graph1
    graph1 = True

    return {'data':[data1,data2,data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[0]),max(list_outputs[1]))/100.0)*100)], title='Number of Cases', side='left'),
                                                title='Infected Cases Over Time',
                                                showlegend=True,
                                                )}

#I-D-R Graph
@app.callback(Output('idrGraph', 'figure'),
             [Input('linear-update2', 'n_intervals')]
)
def update_idrGraph(input_data):
    list_outputs[2].append(sim.deceasedTotal())
    list_outputs[3].append(sim.recoveredTotal())
    converted_time = [val/24 for val in time]
    converted_time = [round(val,2) for val in converted_time]

    data1 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[1]),
        name = 'Total Infected Cases',
        mode = 'lines+markers',
        marker_color = '#F71735',
    )

    data2 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[2]),
        name = 'Total Deceased Cases',
        mode = 'lines+markers',
        marker_color = '#242423',
    )

    data3 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[3]),
        name = 'Total Recovered Cases',
        mode = 'lines+markers',
        marker_color = '#00A8E8',
    )

    global graph2
    graph2 = True

    return {'data':[data1,data2, data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[1]),max(list_outputs[2]),max(list_outputs[3]))/100.0)*100)], title='Number of Cases', side='left'),
                                                title='Infected, Deceased and Recovered Cases Over Time',
                                                showlegend=True,
                                                )}

#Hospital Graph
@app.callback(Output('hospitalGraph', 'figure'),
             [Input('linear-update3', 'n_intervals')]
)
def update_hospital(input_data):
    list_outputs[4].append(sim.hospitalCurrent())
    list_outputs[5].append(sim.hospitalTotal())
    limitHospital.append(totalBedCount)
    converted_time = [val/24 for val in time]
    converted_time = [round(val,2) for val in converted_time]

    data1 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[4]),
        name = 'Current Hospitalized Cases',
        mode = 'lines+markers',
        marker_color = '#F3DC68',
    )

    data2 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[5]),
        name = 'Total Hospitalized Cases',
        mode = 'lines+markers',
        marker_color = '#D6B50D',
    )

    data3 = go.Scatter(
        x = list(converted_time),
        y = list(limitHospital),
        name = 'Hospital Bed Limit',
        mode = 'lines',
        marker_color = '#11151C',
    )

    global graph3
    graph3 = True

    return {'data':[data1,data2,data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[4]),max(list_outputs[5]))/100.0)*100)], title='Number of Cases', side='left'),
                                                title='Hospitalized Cases Over Time',
                                                showlegend=True,
                                                )}

#ICU Graph
@app.callback(Output('icuGraph', 'figure'),
             [Input('linear-update4', 'n_intervals')]
)
def update_icu(input_data):
    list_outputs[6].append(sim.ICUCurrent())
    list_outputs[7].append(sim.ICUtotal())
    limitICU.append(icuBedCount)
    converted_time = [val/24 for val in time]
    converted_time = [round(val,2) for val in converted_time]

    data1 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[6]),
        name = 'Current ICU Cases',
        mode = 'lines+markers',
        marker_color = '#7D1128',
    )

    data2 = go.Scatter(
        x = list(converted_time),
        y = list(list_outputs[7]),
        name = 'Total ICU Cases',
        mode = 'lines+markers',
        marker_color = '#3C0919',
    )

    data3 = go.Scatter(
        x = list(converted_time),
        y = list(limitICU),
        name = 'ICU Bed Limit',
        mode = 'lines',
        marker_color = '#11151C',
    )

    global graph4
    graph4 = True

    return {'data':[data1,data2,data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[6]),max(list_outputs[7]))/100.0)*100)], title='Number of Cases', side='left'),
                                                title='ICU Cases Over Time',
                                                showlegend=True,
                                                )}

#Button Callback
@app.callback(Output('simulationStart', 'children'),
             [Input('simulationStart', 'n_clicks')]
)
def on_button_click(n):
    global graph1
    global graph2
    global graph3
    global graph4

    if n is None:
        return
    else:
        while (1) :
            if (graph1 & graph2 & graph3 & graph4):
                sim.timeStep()
                graph1 = False
                graph2 = False
                graph3 = False
                graph4 = False

if __name__ == "__main__":
    app.run_server(debug=True, use_reloader=True)