# plot file for diffeq_test_exp_back
set timestamp

set xlabel 't'
set ylabel 'y(t)'

set title 'Comparing Differential Equation Algorithms'


plot \
  "diffeq_test.dat" using (log10($1)):(log10(abs(($2-$4)/$4))) title 'Euler', \
  "diffeq_test.dat" using (log10($1)):(log10(abs(($3-$4)/$4)))  title '4th order Runge-Kutta', \
  "diffeq_test.dat" using (log10($1)):(log10(abs(($4-$4)/$4))) title 'exact'
