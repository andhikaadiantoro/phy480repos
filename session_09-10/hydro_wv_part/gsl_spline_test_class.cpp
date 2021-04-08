//  file: gsl_spline_test_class.cpp
// 
//  Test program for the gsl spline routines using the Spline class
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02/10/09 -- created from gsl_cubic_spline_test.cpp
//
//  Notes:
//   * uses the GSL interpolation functions (see online documentation) 
//
//*****************************************************************
// include files
#include <iostream>    // cout and cin
#include <iomanip>     // manipulators like setprecision
#include <cmath>
#include <string>     // C++ strings
#include <fstream>                                   
using namespace std;    
#include "GslSpline.h"  // Header file for the GSL Spline class
#include <gsl/gsl_integration.h>

double hydrogen(double x);
//inline double sqr (double z) {return z*z;}  // inline function for z^2

int
main (void)
{

  int npts = 200;
  double x_values[npts];
  double y_values[npts];
  
  for (int i = 0; i < npts; i++)
    {
      double x_temp = double(i) / 50.;
      x_values[i] = x_temp;
      y_values[i] = 2*pow(x_temp,(-1*x_temp));      
    }

    gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (1000);

  double lower_limit = 0;	/* lower limit a */
  double upper_limit = 1;	/* upper limit b */
  double abs_error = 1.0e-8;	/* to avoid round-off problems */
  double rel_error = 1.0e-8;	/* the result will usually be much better */
  double result;		/* the result from the integration */
  double error;			/* the estimated error from the integration */

  gsl_function My_function;
 

  My_function.function = &hydrogen;
  My_function.params = params_ptr; 


  // Make the spline object
  string type = "cubic";
  Spline my_cubic_spline (x_values, y_values, npts, type);

  ofstream hydro_out ("hydro.dat");
  hydro_out << "    x    absolute  " <<endl;
  // Evaluate the spline and derivatives
  for(int i = 0; i<200; i++){
    double hydro = hydrogen(i);
    double y = my_cubic_spline.y (i);
    double y_deriv = my_cubic_spline.yp (i);
    double integ = gsl_integration_qags (&My_function, lower_limit, upper_limit,
			abs_error, rel_error, 1000, work_ptr, &result,
			&error);
    hydro_out << fixed << setprecision(6) 
        << i << "  " << y << "  " << log10 (fabs (y_deriv- hydro)) <<  "  "  << integ << "  "
        << endl;
  }

  cout << "data stored in hydro.dat\n";
  hydro_out.close ();
  return (0);      // successful completion 
}

double hydrogen(double x) {
  double y = 2*pow(x,-x);
  return y;
}