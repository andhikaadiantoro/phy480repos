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

double breit_wigner(double x);
inline double sqr (double z) {return z*z;}  // inline function for z^2

int
main (void)
{
  //const int NMAX = 300;   // maximum number of array points 
  //double x_values[NMAX], y_values[NMAX];


  // Test: interpolate y = sin(x^2) from xmin to xmax with npts points 
  // double xmin = 1.;
  // double xmax = 3.;
  int npts = 9;
  double x_values[npts] = {0.,25.,50.,75.,100.,125.,150.,175.,200.};
  double y_values[npts] = {9.34,17.9,41.5,83.5,51.5,21.5,10.8,6.29,4.09}; 
  //double deltax = (xmax - xmin)/double(npts-1);
  // for (int i = 0; i < npts; i++)
  // {
  //   double x_temp = xmin + double(i) * deltax;   // grid of x points
  //   x_values[i] = x_temp;
  //   y_values[i] = sin (x_temp * x_temp);
  // }

  // Make the spline object
  string type = "cubic";
  Spline my_cubic_spline (x_values, y_values, npts, type);
  string type2 = "polynomial";
  Spline my_poly_spline (x_values, y_values, npts, type2);

  // double x;
  // cout << "Enter x: ";
  // cin >> x;    // test point
  ofstream spline_out ("spline.dat");
  
  
  // Evaluate the spline and derivatives
  //double y = my_cubic_spline.y (x);
  // double y_deriv = my_cubic_spline.yp (x);
  // double y_deriv2 = my_cubic_spline.ypp (x);
  spline_out << "    x    exact    cubic    polynomial   " <<endl;

  for(int i = 0; i<200; i+=5){
    //double x_sq = sqr(x);
    double sigma_th = breit_wigner(i);
    double y = my_cubic_spline.y (i);
    double z = my_poly_spline.y (i);
    spline_out << fixed << setprecision(6) 
        << i << "  " << sigma_th << "  " <<  y << "  " << z << "  "
        //  <<  2.*x*cos(x_sq) << "  " << y_deriv << "  "
        //  <<  -4.*x_sq* sin(x_sq) + 2.*cos(x_sq) << " " <<  y_deriv2 << "  " <<  sigma_th 
        << endl;

  }
  
  // cout << "    x     y_exact   y_spline   y'_exact  y'_spline";
  // cout << "  y''_exact  y''_spline" << endl;
  // cout << fixed << setprecision(6) 
  //      << x << "  " << sin(x_sq) << "  " <<  y << "  "
  //      <<  2.*x*cos(x_sq) << "  " << y_deriv << "  "
  //      <<  -4.*x_sq* sin(x_sq) + 2.*cos(x_sq) << "  " <<  y_deriv2
  //      << endl;
  
  cout << "data stored in spline.dat\n";
  spline_out.close ();
  return (0);      // successful completion 
}

double breit_wigner(double x){
  double y = (63900.)/(pow((x-78.),2)+(pow(55.,2)/4));
  return y;
}