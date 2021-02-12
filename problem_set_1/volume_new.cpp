
#include <iostream>	     
using namespace std;     



const double pi = 3.1415926535897932385;   

int
main ()
{
  double radius;    

  cout << "Enter the radius of a circle: ";	
  cin >> radius;

  double volume = (4/3) * pi * radius * radius * radius;	

  cout << "radius = " << radius << ",  volume = " << volume;

  return 0;			
}

