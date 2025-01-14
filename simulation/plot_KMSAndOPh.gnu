# Set the output format and size
# set terminal png size 800,600
# set output 'jaccard_similarity.png'
set terminal postscript eps color enhanced "Helvetica" 40
set size 1.2, 1
unset mytics
unset mxtics
set ytics font "Helvetica, 44"
set xtics font "Helvetica, 44"
set key font ",36" right bottom
set output "./figure/KMSAndOPH.eps"
# Set graph titles and labels
# set title 'Probability P(X ≥ m) as a Function of J(A, B) for Various k and m'

# Set the xtics at specific intervals
set xtics ("0" 0, "0.25" 0.25, "0.5" 0.5, "0.75" 0.75, "1.0" 1.0)

set xlabel "J_{T,S}" font "Helvetica, 52"
set ylabel "Pr(~J{0.45\\^}_{T,S} {/Symbol \263} 0.5)" font "Helvetica ,52"
set yrange[0:1]
# Remove grid

# Set style for border and labels
# set border linewidth 0.01
# set style fill transparent solid 0.5 border

# # Additional xtic at x=0.5
# set xtics add ("0.5" 0.5)

# Define colors for each line and corresponding filled curves
set style line 1 lc rgb "red" lw 6
set style line 2 lc rgb "blue" lw 6
# set style line 3 lc rgb "green" lw 6

# Plot commands
plot  './data/data_k64_m32.dat' using 1:2 with lines ls 1 title 'k-mins', \
      './data/oph_k64.dat' using 1:2 with lines ls 2 title 'OPH'
