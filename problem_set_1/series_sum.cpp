#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

int main()
{
	int N;
    cin>>N;
    
    ofstream out ("sum.dat");
    
    
    // main for loop
	 for (N = 100; N <= 100000000; N *= 10) 
    {   // summing up
        float sum_up;
        int i;
        for (i = 1; i <= N; i++){

             sum_up = sum_up + 1.0/i;

        }
        // summing down
        float sum_down;
        for (i = N; i <= 1; i--){

             sum_down = sum_down + 1.0/i;

        }

     //difference
     float diff = (fabs(sum_up - sum_down)/((0.5)*(fabs(sum_up)+fabs(sum_down))));

    out << fixed << N << " "
	<< sum_up << " "
	<< sum_down << " "
    << diff << " "
    << endl;

    }
    
  out.close ();
  return (0);
    
}