# coil_winder



MPLAB project



The circuit consists of 

1x PIC18F2550 microcontroller, 

2x L293D motor drivers, 

1x MAX232 serial port chip, 

2x nema 17 stepper motors



One motor is winding the coil while the other one is moving a guider forth and back along the width of the core
to aid laying the wire side by side on the core.



The microcontroller receives the coil parameters on serial port from a windows program 
that provides the user interface for the circuit. https://github.com/akosbrachna/coil_winder_interface



![Alt text](eagleCAD/circuit_schematic.png?raw=true "Circuit schematic") 