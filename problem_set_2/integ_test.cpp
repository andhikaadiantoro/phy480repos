//  file: integ_test.cpp
//
//  This is a test program for basic integration methods.               
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  changed functions to pass integrand
//      09-Jan-2011  updated functions
//
//  Notes:
//   * define with doubles to emphasize round-off error  
//   * compile with:  "g++ -Wall -c integ_test.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau                           
// 
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "integ_routines_new.h"	// prototypes for integration routines

double my_integrand (double x);

const double ME = 2.7182818284590452354E0;	// Euler's number 

//************************************************************************

int
main ()
{
  // set up the integration specifiction
  const int max_intervals = 501;	// maximum number of intervals
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = 1. - 1. / ME;	// the "exact" answer for the test 
  double result = 0.;  // approximate answer

  // open the output file stream
  ofstream integ_out ("integ_new.dat");	// save data in integ.dat
  integ_out << "#  N   Simpon's     Milne       3/8 " << endl;
  integ_out << "#-----------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals  
  for (int i = 3; i <= max_intervals; i += 4)
  {
    integ_out << setw(4) << log10(i);

    result = simpsons_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs((result - answer)/answer));

    result = milne (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs((result - answer)/answer));

    result = three_eight (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs((result - answer)/answer));

    integ_out << endl;
  }

  cout << "data stored in integ_new.dat\n";
  integ_out.close ();

  return (0);
}

//************************************************************************

// the function we want to integrate 
double
my_integrand (double x)
{
  return (exp (-x));
}
