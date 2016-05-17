/* --------------------------------------------------------------------------------------------------------
   Filename:		velocity-stormer-verlet_method_02.c
   Needs:			#include "velocity-stormer-verlet_02.h"

   Application:		Calculates particle parameters i.e. position, velocity, kinetic energy, potential
					energy and forces in a particle system. The time-evolution of parameters such as
					position are calculated using the technique of Velocity-Stormer-Verlet integration.

   Particle format:	The particles are specified in a text file according to the format:

							mass xpos ypos zpos xvelocity yvelocity zvelocity

					All these parameters except the particle mass can be taken as initial values. 
					For a static system i.e. only potential energies are required, the initial 
					velocity components can be taken as zero.

   Author:			R.O. Ocaya		
   Copyright:		(c) 2015 University of the Free State (UFS).
   Last modified:	Wednesday 05 August 2015.
   ---------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "velocity-stormer-verlet_02.h"

int main(){
	int N = 0, pcount=0;
	int j, d ;				// index for counting particles and dimensions
	float delta_t, t_end;
	float mass_0=0, x_0=0, y_0=0, z_0=0, v_x0=0, v_y0=0, v_z0=0;  // initial values from file
	double total_pot_energy=0, ParticleForce = 0, netForce = 0;

	Particle *p;
	FILE *particleFile;
	
	// find #particles in system to allocate memory dynamically
	if ((particleFile = fopen("data.txt", "r")) == NULL){
		printf("Error: cannot open file for reading...\n");
		exit (0);
	}
	else {
		while(fscanf(particleFile, "%f %f %f %f %f %f %f", &mass_0, &x_0, &y_0, &z_0, &v_x0, &v_y0, &v_z0) != EOF)
			pcount++;
		N = pcount;		
	}
	rewind(particleFile);	// reset file read ptr to start of file
	pcount = 0;

	(Particle *)p = (Particle *)malloc(N*sizeof(*p));
	
	// greeting
	printf("This program uses the Sutton-Chen Embedded Atom Method \n");
	printf("to calculate potential energies in a particle system.\n\n");

	// Memory usage statistics
	printf("Found %d particles and used %d bytes of total memory.\n", N, N*sizeof(*p));

	/* uncomment the following 4 lines of code for console data input
	printf("\ndelta_t = ");
	scanf_s("%f", &delta_t);
	   
	printf("t_end = ");
	scanf_s("%f", &t_end);
	*/ 

	// populate memory array with particle data
	while(fscanf(particleFile, "%f %f %f %f %f %f %f", &mass_0, &x_0, &y_0, &z_0, &v_x0, &v_y0, &v_z0) != EOF){
		p[pcount].m = mass_0;
		p[pcount].x[0] = lat_const*x_0;
		p[pcount].x[1] = lat_const*y_0;
		p[pcount].x[2] = lat_const*z_0;
		p[pcount].v[0] = v_x0;
		p[pcount].v[1] = v_y0;
		p[pcount].v[2] = v_z0;
		p[pcount].F_old[0] = 0;		// reset all forces
		p[pcount].F_old[1] = 0;
		p[pcount].F_old[2] = 0;
		p[pcount].F[0] = 0;
		p[pcount].F[1] = 0;
		p[pcount].F[2] = 0;
		pcount++;
	}  
	particleFileContent(p, pcount);

	/* Call either:
	       timeIntegration_basis(), which uses the naive force()
						or 
		   timeIntegration2_basis(), which uses the modified force2()
    */
	
	// timeIntegration2_basis (0, delta_t, t_end, p, N); // this modifies the structure coordinates

	// Calculate total potential energy of the particle system

	/* uncomment next two lines for total potential energy of the system

	total_pot_energy = Utot(p, pcount);	
 	printf("\n\nTotal potential energy = %.4f (eV)\n\n", total_pot_energy);

	*/ 
	
    for (j=0; j<N; j++){					
		F_i(p, j, pcount);
		netForce = 0;		// net force on particle j

		for (d=0; d<DIM; d++)
			netForce += pow(p[j].F[d], 2);			// vector sum of force components
		netForce = pow(netForce,0.5);		// in micro Newtons
	 	printf("\nForce (uN) on particle %d = (%.4f, %.4f, %.4f), Net force = %.4f", j+1, p[j].F[0], p[j].F[1], p[j].F[2], netForce);

	}

	printf("\nDone!\n\nPress a key to exit....");
	getch();
	 
	// free the allocated memory
	free(p);
	fclose(particleFile);
	return (0);
}