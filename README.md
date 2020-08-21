# README
**Contributors**: Danyal Mahmood, James Busch, Joyce Li
___
## Introduction
This project entails an initial proof of concept for an environmental agent-based model (eABM) that monitors the spread of COVID-19 within a population of agents that resembles the demography of Guelph. It consists of infection and recovery/mortality rates of agents that live and travel around Guelph.
___
## Methodology
In this project, an eABM was created to simulate the spread of COVID-19. Object-oriented programming (OOP) was used to organize agents and important attributes, such as demographics and locations. Hence, C++ was selected as the backend language, as it is known for its good performance with efficient coding practices.

The agents move around the city of Guelph depending on their demography, as well as the time of the day. The simulation is executed in intervals of 4 hours. This means that the simulation will need to run 180 timesteps before hitting 30 days within the simulation.

For the frontend of the simulation model, sliders and graphs are presented to visualize the simulation. The sliders give the user the control over the agents' overall compliance in following mitigation strategies, as well as COVID-19 transmission rates for various locations, such as schools and public places. The graphs display the number of cases over time. Python was used to design the dashboard because there are many available packages to help with creating the graphs.
___
## Results & Discussion
The finished project entails a successfully working eABM that resembles Guelph. The user can play with the sliders to see how each variable impacts the spread of COVID-19. Since this simulation is agent-based, the behaviours are stochastic.

The following list consists of potential improvements to be made:
* A map of Guelph that displays the hotspots of where agents are getting infected the most
* More buttons to start, pause, and reset the simulation
* More work to be done to improve the user interface dashboard
* More work to be done to improve the "accuracy" of agent behaviours
* Flu season in the Fall, especially with students coming to campus or not

Here is a snapshot of the overall simulation functionality:
![Alt text](Screenshot.gif)
___
## Contributions
Currently, this project is made private. We will not be taking any pull requests. Stay safe!
___
## Steps to Install and Run
Firstly, clone the repository. You can do this by entering the following:
```bash
git clone https://github.com/joyglitch/COVID-19ABMGuelphS20.git
```
Then, `cd` into the directory that contains the cloned repository and enter the following command:
```bash
make library
```
Furthermore, ensure that you have installed all the necessary Python packages by running the following command:
```bash
pip install -r requirements.txt
```

## Steps to Update Documentation
For the documentation generation, we used [Doxygen](https://www.doxygen.nl/index.html) to create MD and HTML files. To learn more about the standards we used while documenting, please use the following resources:  
https://flcwiki.desy.de/How%20to%20document%20your%20code%20using%20doxygen  
https://developer.lsst.io/cpp/api-docs.html  

After [Doxygen](https://www.doxygen.nl/index.html) has been installed, run the following command:  
```bash
doxygen COVIDABMDOCCONFIG
```