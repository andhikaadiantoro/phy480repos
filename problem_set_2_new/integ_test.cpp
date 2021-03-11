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
#include <gsl/gsl_integration.h>

double my_integrand (double x);

double my_new_integrand (double x, void *params);

const double ME = 2.7182818284590452354E0;	// Euler's number 

//************************************************************************

int
main (void)
{
  // set up the integration specifiction
  const int max_intervals = 501;	// maximum number of intervals
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = 1. - 1. / ME;	// the "exact" answer for the test 
  double result = 0;  // approximate answer
  double new_result = 0;

  gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (1000);

  double abs_error = 1.0e-8;	/* to avoid round-off problems */
  double rel_error = 1.0e-8;	/* the result will usually be much better */
  //double result;		/* the result from the integration */
  double error;			/* the estimated error from the integration */
  //double alpha = 1.0;		// parameter in integrand
  double expected = -4.0;
  

  gsl_function My_function;
  //void *params_ptr = &alpha;

  My_function.function = &my_new_integrand;
  //My_function.params = params_ptr;

  // open the output file stream
  ofstream integ_out ("integ_new.dat");	// save data in integ.dat
  integ_out << "#  N   Simpon's     Milne     Qags_GSL" << endl;
  integ_out << "#-----------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals  
  for (int i = 5; i <= max_intervals; i += 4)
  { integ_out.precision (30);
    integ_out << setw(30) << log10(i);

    result = simpsons_rule (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs((result - answer)/answer));

    result = milne (i, lower, upper, &my_integrand);
    integ_out << "  " << scientific << log10(fabs((result - answer)/answer));

    gsl_integration_qags (&My_function, lower, upper, abs_error, rel_error, 1000, work_ptr, &new_result, &error);
    integ_out << "  " << scientific << log10(fabs((new_result - expected)/expected));

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

double
my_new_integrand (double x, void *params)
{
  // Mathematica form:  Log[alpha*x]/Sqrt[x]

  // The next line recovers alpha from the passed params pointer
  double alpha = *(double *) params;

  return (log (alpha * x) / sqrt (x));
}
