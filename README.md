# Velocity-Stormer-Verlet
Calculates particle parameters i.e. position, velocity, kinetic energy, potential energy and forces in a particle system. The time-evolution of parameters such as position are calculated using the technique of Velocity-Stormer-Verlet integration.

The main program relies on a C-style header file called velocity-stormer-verlet_02.h that defines extensive function implementations of various molecular-dynamics processes such as VSV integration, potential energy calculations and memory declarations and management for large bodies of particles. The library is invoked through the directive:

            #include "velocity-stormer-verlet_02.h"contains functions to implement 
            
Note: in the program, the function C-function printf() is not called except at the final output because it consumes a lot of simulation time if included. It is included in actual calculation functions only during program development and commented out during the actual executing stage.
