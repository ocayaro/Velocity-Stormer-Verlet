// define the simulation constants
#define eps			1				// an energy parameter
#define lat_const	3.61					// lattice constant of copper, in angstrom
#define cn			39.432					// density of state constant
#define nint		9						// potential function steepness					
#define mint		6						// potential function range

// define macros for index mapping of cells in 3 dimensions
#define index(ic,nc) ((ic)[0] + (nc)[0]*((ic)[1] + (nc)[1]*(ic)[2]))
