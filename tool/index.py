#Import packages
import dash
import dash_bootstrap_components as dbc
import dash_html_components as html
import dash_core_components as dcc
from dash.dependencies import Input, Output, State
from dash import no_update
import cffi
import element
import math

#Import Plotly packages
import plotly
import plotly.graph_objs as go
import plotly.express as px
from plotly.tools import mpl_to_plotly
import matplotlib.pyplot as plt

#Create library of C++ functions
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
    void setAgentMitagationChance(Simulation* sim, int ageGroup, int strategy, double value);
    double getAgentMitagationChance(Simulation *sim, int ageGroup, int strategy);
    void setMitagationEffectivness(Simulation *sim, int strategy, double value);
    double getMitagationEffectivness(Simulation *sim, int strategy);
    void setLocationRisk(Simulation *sim, int location, double value);
    double getLocationRisk(Simulation *sim, int location);
    void setAgentRecoveryTime(Simulation* sim, int ageRange, int val);
    int getAgentRecoveryTime(Simulation *sim, int ageRange);
    void setAgentDeathChance(Simulation* sim, int ageRange, double val);
    double getAgentDeathChance(Simulation* sim, int ageRange);
    void setAgentChanceOfMovment(Simulation* sim, int ageGroup, int day, int time, int location, double value);
    double getAgentChanceOfMovment(Simulation* sim, int ageGroup, int day, int time, int location);
    void setAgentNeedsHospital(Simulation *sim, int ageGroup, double chance);
    double getAgentNeedsHospital(Simulation *sim, int ageGroup);
    void setAgentChanceOfICU(Simulation *sim, int ageGroup, double value);
    double getAgentChanceOfICU(Simulation *sim, int ageGroup);
    void setAgentIncubationTime(Simulation *sim, int ageGroup, int value);
    int getAgentIncubationTime(Simulation *sim, int ageGroup);
    void simDayTimeStep(Simulation *sim);
    void setPresets(Simulation *sim, int preset);
    int saveCurrentPreset(Simulation *sim, int fileNum);
''')

lib = ffi.dlopen('./libProject.so')

#Create Simulation class in Python
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

    def setAgentMitagationChance(self, ageGroup, strategy, value):
        lib.setAgentMitagationChance(self.obj, ageGroup, strategy, value)
    
    def getAgentMitagationChance(self, ageGroup, strategy):
        return lib.getAgentMitagationChance(self.obj, ageGroup, strategy)
    
    def setMitagationEffectivness(self, strategy, value):
        lib.setMitagationEffectivness(self.obj, strategy, value)
    
    def getMitagationEffectivness(self, strategy):
        return lib.getMitagationEffectivness(self.obj, strategy)

    def setLocationRisk(self, location, value):
        lib.setLocationRisk(self.obj, location, value)
    
    def getLocationRisk(self, location):
        return lib.getLocationRisk(self.obj, location)
    
    def setAgentRecoveryTime(self, ageRange, value):
        lib.setAgentRecoveryTime(self.obj, ageRange, value)
    
    def getAgentRecoveryTime(self, ageRange):
        return lib.getAgentRecoveryTime(self.obj, ageRange)
    
    def setAgentDeathChance(self, ageRange, value):
        lib.setAgentDeathChance(self.obj, ageRange, value)
    
    def getAgentDeathChance(self, ageRange):
        return lib.getAgentDeathChance(self.obj, ageRange)
    
    def setAgentChanceOfMovment(self, day, time, location, value):
        lib.setAgentChanceOfMovment(self.obj, day, time, location, value)
    
    def getAgentChanceOfMovment(self, ageGroup, day, time, location):
        return lib.getAgentChanceOfMovment(self.obj, ageGroup, day, time, location)
    
    def setAgentNeedsHospital(self, ageGroup, chance):
        lib.setAgentNeedsHospital(self.obj, ageGroup, chance)
    
    def getAgentNeedsHospital(self, ageGroup):
        return lib.getAgentNeedsHospital(self.obj, ageGroup)
    
    def setAgentChanceOfICU(self, ageGroup, value):
        lib.setAgentChanceOfICU(self.obj, ageGroup, value)
    
    def getAgentChanceOfICU(self, ageGroup):
        return lib.getAgentChanceOfICU(self.obj, ageGroup)
    
    def setAgentIncubationTime(self, ageGroup, value):
        lib.setAgentIncubationTime(self.obj, ageGroup, value)
    
    def getAgentIncubationTime(self, ageGroup):
        return lib.getAgentIncubationTime(self.obj, ageGroup)
    
    def simDayTimeStep(self):
        lib.simDayTimeStep(self.obj)

    def setPresets(self, preset):
        lib.setPresets(self.obj, preset)

    def saveCurrentPreset(self, fileNum):
        return lib.saveCurrentPreset(self.obj, fileNum)

#Initialize times and values
sim = Simulation()
sim.setPresets(2)
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


#Hospital and ICU variables
totalBedCount = 130
icuBedCount = 22
appStart = False

#Start Dash application
app = dash.Dash(external_stylesheets=[dbc.themes.FLATLY])

#Create graphs for Dash application
infectedGraph = element.create_graph('infectedGraph', 4000, 1)
idrGraph = element.create_graph('idrGraph', 4000, 2)
hospitalGraph = element.create_graph('hospitalGraph', 4000, 3)
icuGraph = element.create_graph('icuGraph', 4000, 4)

#COVID-19 Cases graph tab
infectedGraph = dbc.Card([
    dbc.CardBody([
        dbc.Row(
            children=[
                dbc.Col(
                    children=[
                        html.Div([infectedGraph]),
                        html.Div([idrGraph]),
                    ],
                    width= 6
                ),
                dbc.Col(
                    children=[
                        html.Div([hospitalGraph]),
                        html.Div([icuGraph]),
                    ],
                    width= 6
                )
            ]
        )
        
    ],
    id="i_tab",)
])

#Tabs of graphs
graphTabs = dbc.Tabs([
    dbc.Tab(infectedGraph, label="COVID-19 Cases", tab_id="i_tab"),
],
id="graph_tabs", persistence=True, persistence_type='session',
)

#Layout for Dash application
app.layout = html.Div([
    element.navigator,
    dbc.Tabs([
        dbc.Tab(label='Simulation', children=[
            dbc.Row(
                className='content-row',
                children=[
                dbc.Row(dbc.Col(html.Div(element.buttons))),
                dbc.Col(html.Div(graphTabs), width=12),
            ])
        ]),
        dbc.Tab(label='Global Settings', children=[
            dbc.Row(
                className='content-row',
                children=[
                dbc.Row(html.Div(id='dd-output-container')),
                dbc.Col(html.Div(element.tabs), width=12),    
            ])
        ]),
        dbc.Tab(label='Age Specific Settings', children=[
            dbc.Row(
                className='content-row',
                children=[
                dbc.Col(
                    children=[
                        html.Div(element.ageDropdown),
                        html.Div(children=[dbc.Button("Apply Changes", outline=True, color="primary", className="mr-1", id="submit-ageSliders")], className="btn-container"),
                        dbc.Row(html.Div(id='ageSettings-output-container')),
                        dbc.Row(html.Div(id='ageSettings-drop-output'))
                    ],
                    width=4),
                dbc.Col(html.Div(element.ageTabs), width=8),    
            ])
        ])
    ])
])

#Toggling Navbar
def toggle_navbar_collapse(n, is_open):
    if n:
        return not is_open
    return is_open

app.callback(
    Output("navbar-collapse", "is_open"),
    [Input("navbar-toggler", "n_clicks")],
    [State("navbar-collapse", "is_open")],
)(toggle_navbar_collapse)

#Graph Boolean variables for schedule handling
graph1 = False
graph2 = False
graph3 = False
graph4 = False
buttonPressed = False

#Callback function for the button to disable after first click
@app.callback(Output('simulationStart', 'disabled'),
             [Input('simulationStart', 'n_clicks')]
)
def disable_button(n_clicks):
    global buttonPressed
    if buttonPressed:
        return True
    if n_clicks is None:
        return False
    else:
        return True

#Callback function to save current simulation values to a CSV file
@app.callback(Output('saveSimSetup', 'disabled'),
             [Input('saveSimSetup', 'n_clicks')]
)
def saveSimulationSetup(n_clicks):
    if(n_clicks == 0):
        return
    presetPrint = sim.saveCurrentPreset(2)
    print(presetPrint)

#Callback function for the button to loop timestep after first click
@app.callback(Output('placeholderdiv', 'children'),
             [Input('simulationStart', 'n_clicks')]
)
def on_button_click(n_clicks):
    global graph1
    global graph2
    global graph3
    global graph4
    global buttonPressed
    global appStart

    if n_clicks is None:
        return
    else:
        while (1) :
            buttonPressed = True
            appStart = True
            if (graph1 & graph2 & graph3 & graph4):
                sim.timeStep()
                graph1 = False
                graph2 = False
                graph3 = False
                graph4 = False

#List of slider names
list_elements = ['Q_slider', 'SD_slider', 'MC_slider', 'HM_slider', 'gs_slider',
                't_slider', 'sch_slider', 'pnr_slider', 'serv_slider',
                'ent_slider', 'health_slider', 'poworship_slider', 'res_slider',
                'dc_slider', 'recov_slider','socialDis_slider','maskUse_slider',
                'hygieneUse_slider','isolationRate_slider','vaccineUse_slider','incubation_slider']


 # Function to get slider values for a given age range
@app.callback(
    dash.dependencies.Output('ageSettings-drop-output', 'children'),
    [dash.dependencies.Input('age-dropdown', 'value')])
def get_age_sliders(value):
    return 'Got slider values for "{}"'.format(value)


# Callback functions for sliders

# Mitigation effectiveness sliders in chronological order (refer to C++ array indexing)
@app.callback(
    Output(list_elements[0]+'_value', 'children'),
    [Input(list_elements[0], 'value')])
def update_output_Q(value):
    sim.setMitagationEffectivness(0,value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[1]+'_value', 'children'),
    [Input(list_elements[1], 'value')])
def update_output_SD(value):
    sim.setMitagationEffectivness(1,value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[2]+'_value', 'children'),
    [Input(list_elements[2], 'value')])
def update_output_MC(value):
    sim.setMitagationEffectivness(2,value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[3]+'_value', 'children'),
    [Input(list_elements[3], 'value')])
def update_output_HM(value):
    sim.setMitagationEffectivness(3,value)
    return '{}'.format(value)

# Location risk sliders
@app.callback(
    Output(list_elements[4]+'_value', 'children'),
    [Input(list_elements[4], 'value')])
def update_output_gs(value):
    sim.setLocationRisk(0, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[5]+'_value', 'children'),
    [Input(list_elements[5], 'value')])
def update_output_t(value):
    sim.setLocationRisk(1, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[6]+'_value', 'children'),
    [Input(list_elements[6], 'value')])
def update_output_sch(value):
    sim.setLocationRisk(2, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[7]+'_value', 'children'),
    [Input(list_elements[7], 'value')])
def update_output_pnr(value):
    sim.setLocationRisk(3, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[8]+'_value', 'children'),
    [Input(list_elements[8], 'value')])
def update_output_serv(value):
    sim.setLocationRisk(4, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[9]+'_value', 'children'),
    [Input(list_elements[9], 'value')])
def update_output_ent(value):
    sim.setLocationRisk(5, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[10]+'_value', 'children'),
    [Input(list_elements[10], 'value')])
def update_output_health(value):
    sim.setLocationRisk(6, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[11]+'_value', 'children'),
    [Input(list_elements[11], 'value')])
def update_output_poworship(value):
    sim.setLocationRisk(7, value)
    return '{}'.format(value)

@app.callback(
    Output(list_elements[12]+'_value', 'children'),
    [Input(list_elements[12], 'value')])
def update_output_res(value):
    sim.setLocationRisk(8, value)
    return '{}'.format(value)

# Age specific slider functions that are just used to update slider values, they do not apply any
# settings until the Apply button is pressed.

# Death Chance Slider
@app.callback(
    Output(list_elements[13]+'_value', 'children'),
    [Input(list_elements[13], 'value')])
def update_output_death(value):
    return '{}'.format(value)

# Recovery Time Slider
@app.callback(
    Output(list_elements[14]+'_value', 'children'),
    [Input(list_elements[14], 'value')])
def update_output_recovery(value):
    return '{}'.format(value)

# Social Distancing Use Age Specific Slider
@app.callback(
    Output(list_elements[15]+'_value', 'children'),
    [Input(list_elements[15], 'value')])
def update_output_SD_use(value):
    return '{}'.format(value)

# Mask Wearing Use Age Specific Slider
@app.callback(
    Output(list_elements[16]+'_value', 'children'),
    [Input(list_elements[16], 'value')])
def update_output_mask_use(value):
    return '{}'.format(value)

# Hygiene Use Age Specific Slider
@app.callback(
    Output(list_elements[17]+'_value', 'children'),
    [Input(list_elements[17], 'value')])
def update_output_hygiene_use(value):
    return '{}'.format(value)

# Isolation Age Specific Slider
@app.callback(
    Output(list_elements[18]+'_value', 'children'),
    [Input(list_elements[18], 'value')])
def update_output_isolation_use(value):
    return '{}'.format(value)

# Vaccine Age specific Slider
@app.callback(
    Output(list_elements[19]+'_value', 'children'),
    [Input(list_elements[19], 'value')])
def update_output_vaccine_use(value):
    return '{}'.format(value)

# Incubation Period Slider (Age Specific)
@app.callback(
    Output(list_elements[20]+'_value', 'children'),
    [Input(list_elements[20], 'value')])
def update_output_incubation(value):
    return '{}'.format(value)


# Function to update age-specific values in the simulation
@app.callback(
    Output('ageSettings-output-container', 'children'),
    [Input('submit-ageSliders', 'n_clicks')],
    [State('age-dropdown', 'value'),
    State('dc_slider', 'value'),
    State('recov_slider', 'value'),
    State('incubation_slider', 'value'),
    State('socialDis_slider', 'value'),
    State('maskUse_slider', 'value'),
    State('hygieneUse_slider', 'value'),
    State('isolationRate_slider', 'value'),
    State('vaccineUse_slider', 'value')])
def update_ageSpecificValues(n_clicks, age_range, deathChance, recov, incubation, socialDis, maskUse, hygiene, isolation, vaccine):
    if(n_clicks == 0 or age_range == None):
        return 'Please select an age range to apply settings.'
    
    # Set all age specific values here when the apply button has been clicked
    sim.setAgentDeathChance(age_range, deathChance)
    sim.setAgentRecoveryTime(age_range,recov)
    sim.setAgentIncubationTime(age_range, incubation)
    sim.setAgentMitagationChance(age_range, 0, socialDis)
    sim.setAgentMitagationChance(age_range, 1, maskUse)
    sim.setAgentMitagationChance(age_range, 2, hygiene)
    sim.setAgentMitagationChance(age_range, 3, isolation)
    sim.setAgentMitagationChance(age_range, 4, vaccine)

    return 'Values for the age range have been updated.'


#List of graphs names, outputs to graphs, hospital and ICU maximum capacities
list_graphs  = ['infectedGraph', 'idrGraph', 'hospitalGraph', 'icuGraph']
list_outputs = [[infectedC], [infectedT], [deceasedT], [recoveredT], [hospitalC], [hospitalT], [icuC], [icuT], [infectedN]]
limitHospital = [totalBedCount]
limitICU = [icuBedCount]

#Callback function for the infected graph
@app.callback(Output('infectedGraph', 'figure'),
             [Input('linear-update1', 'n_intervals')]
)
def update_infectedGraph(input_data):
    if (appStart == False):
        return no_update
    else:
        time.append(element.next_timestep(time[-1]))
        list_outputs[0].append(sim.infectedCurrent())
        list_outputs[1].append(sim.infectedTotal())
        list_outputs[8].append(sim.newlyInfected())
        converted_time = [val/24 for val in time]
        converted_time = [round(val,2) for val in converted_time]

        data1 = go.Scatter(x=list(converted_time), y=list(list_outputs[0]), name='Current Infected Cases', mode='lines+markers', marker_color='#F5CB5C')
        data2 = go.Scatter(x=list(converted_time), y=list(list_outputs[1]), name='Total Infected Cases', mode='lines+markers', marker_color='#F71735')
        data3 = go.Bar(x=list(converted_time), y=list(list_outputs[8]), name='Newly Infected Cases', marker_color='#76B041')

        global graph1
        graph1 = True

        return {'data':[data1,data2,data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                    yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[0]),max(list_outputs[1]))/100.0)*100)], title='Number of Cases', side='left'),
                                                    title='Infected Cases Over Time',
                                                    showlegend=True,
                                                    )}

#Callback function for the Infected-Deceased-Recovered graph
@app.callback(Output('idrGraph', 'figure'),
             [Input('linear-update2', 'n_intervals')]
)
def update_idrGraph(input_data):
    if (appStart == False):
        return no_update
    else:
        list_outputs[2].append(sim.deceasedTotal())
        list_outputs[3].append(sim.recoveredTotal())
        converted_time = [val/24 for val in time]
        converted_time = [round(val,2) for val in converted_time]

        data1 = go.Scatter(x=list(converted_time), y=list(list_outputs[1]), name='Total Infected Cases', mode='lines+markers', marker_color='#F71735')
        data2 = go.Scatter(x=list(converted_time), y=list(list_outputs[2]), name='Total Deceased Cases', mode='lines+markers', marker_color='#242423')
        data3 = go.Scatter(x=list(converted_time), y=list(list_outputs[3]), name='Total Recovered Cases', mode='lines+markers', marker_color='#00A8E8')

        global graph2
        graph2 = True

        return {'data':[data1,data2, data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                    yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[1]),max(list_outputs[2]),max(list_outputs[3]))/100.0)*100)], title='Number of Cases', side='left'),
                                                    title='Infected, Deceased and Recovered Cases Over Time',
                                                    showlegend=True,
                                                    )}

#Callback function for the hospital graph
@app.callback(Output('hospitalGraph', 'figure'),
             [Input('linear-update3', 'n_intervals')]
)
def update_hospital(input_data):
    if (appStart == False):
        return no_update
    else:
        list_outputs[4].append(sim.hospitalCurrent())
        list_outputs[5].append(sim.hospitalTotal())
        limitHospital.append(totalBedCount)
        converted_time = [val/24 for val in time]
        converted_time = [round(val,2) for val in converted_time]

        data1 = go.Scatter(x=list(converted_time), y=list(list_outputs[4]), name='Current Hospitalized Cases', mode='lines+markers', marker_color='#F3DC68')
        data2 = go.Scatter(x=list(converted_time), y=list(list_outputs[5]), name='Total Hospitalized Cases', mode='lines+markers', marker_color='#D6B50D')
        data3 = go.Scatter(x=list(converted_time), y=list(limitHospital), name='Hospital Bed Limit', mode='lines', marker_color='#11151C')

        global graph3
        graph3 = True

        return {'data':[data1,data2,data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                    yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[4]),max(list_outputs[5]),max(limitHospital))/100.0)*100)], title='Number of Cases', side='left'),
                                                    title='Hospitalized Cases Over Time',
                                                    showlegend=True,
                                                    )}

#Callback function for the ICU graph
@app.callback(Output('icuGraph', 'figure'),
             [Input('linear-update4', 'n_intervals')]
)
def update_icu(input_data):
    if (appStart == False):
        return no_update
    else:
        list_outputs[6].append(sim.ICUCurrent())
        list_outputs[7].append(sim.ICUtotal())
        limitICU.append(icuBedCount)
        converted_time = [val/24 for val in time]
        converted_time = [round(val,2) for val in converted_time]

        data1 = go.Scatter(x=list(converted_time), y=list(list_outputs[6]), name='Current ICU Cases', mode='lines+markers', marker_color='#7D1128')
        data2 = go.Scatter(x=list(converted_time), y=list(list_outputs[7]), name='Total ICU Cases', mode='lines+markers', marker_color='#3C0919')
        data3 = go.Scatter(x=list(converted_time), y=list(limitICU), name='ICU Bed Limit', mode='lines', marker_color='#11151C')

        global graph4
        graph4 = True

        return {'data':[data1,data2,data3], 'layout': go.Layout(xaxis=dict(range=[0, max(converted_time)], title='Time (Days)'),
                                                    yaxis=dict(range=[0, int(math.ceil(max(max(list_outputs[6]),max(list_outputs[7]),max(limitICU))/100.0)*100)], title='Number of Cases', side='left'),
                                                    title='ICU Cases Over Time',
                                                    showlegend=True,
                                                    )}

if __name__ == "__main__":
    app.run_server(debug=True, use_reloader=True)