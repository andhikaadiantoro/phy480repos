#  file: derivative_test.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
# 
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'log10 time vs. log10 dimension'
set xlabel 'log10 dimension'
set ylabel 'log10 time'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [2.3:2.6]
set yrange [1.5:3]

# fit the curve
f1(x) = a1*x + b1
fit [2.3:2.6] f1(x) "eigen_test_new.dat" using ($1):($2) via a1,b1 
#fit_title = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "eigen_test_new.dat" using ($1):($2), a1*x+b1 

# output the plot to the file derivative_test_plt.ps   
set out "eigen_test_new_plt.ps"
set term postscript color enhanced
replot
