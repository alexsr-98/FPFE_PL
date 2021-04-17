# My first Geant4 application
This contains the code of the lab sessions of FPFE.

To get the code:  
`git clone git@github.com:alexsr-98/FPFE_PL.git MyFirstApplication`

# How to build this application

1. Create the build folder

`cd MyFirstApplication`

`mkdir build`

`cd build`

2. Compile the code

`cmake3 -DGeant4_DIR=/Where/Your/Geant4/installation/is/lib/Geant4-10.6.0/  ../`

`make`

# How to run this application

1. Interactive mode

To run the application in the interactive mode, move to the build folder an execute

`./main`

2. Use macros

You can use macros to set up the simulation automaticaly.
To display the visual simulation execute

`./main ../vis.mac`

A simple simulation without visual representation is implemented in the run2.mac

`./main ../run2.mac`

3. Perform the Meroli experiment

To reproduce the results from the Meroli experiment 

`./main ../experiment/Meroli_exp.mac`

This will produce a rootfile in the build folder called `Histograms.root`

To plot this information together with the experimental data from `experiment/exp_Meroli_100MeV_electron_5p6um_Si.dat`, move to `MyFirstApplication` and execute

`python experiment/plotter.py`

This will create a folder `plots_ExpMeroli` with the plots.

4. Study different materials, thickness, energy and particles.

Move to `MyFirstApplication` and execute

`python executer.py`

`python plotter.py`

This will create a folder `plots` with all the histograms configured in `executer.py`.
