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
set output "./figure/KMS_withK.eps"
# Set graph titles and labels
# set title 'Probability P(X ≥ m) as a Function of J(A, B) for Various k and m'
set xlabel "J_{T,S}" font "Helvetica, 52"
set ylabel "Pr(~J{0.45\\^}_{T,S} {/Symbol \263} 0.5)" font "Helvetica ,52"

# Remove grid

# Set style for border and labels
# set border linewidth 0.01
# set style fill transparent solid 0.5 border
# Set the xtics at specific intervals
set xtics ("0" 0, "0.25" 0.25, "0.5" 0.5, "0.75" 0.75, "1.0" 1.0)

# Define the x=0.5 vertical line
set arrow from 0.5, graph 0 to 0.5, graph 1 nohead lc rgb "black" linewidth 6

# Add labels for "False Positive" and "False Negative" areas
set label "False\nPositive" at 0.1, graph 0.38
set label "False\nNegative" at 0.6, graph 0.65
# Draw line segments to labels
set arrow from 0.37, 0.1 to 0.25, graph 0.17 nohead lc rgb "black" linewidth 2 front
set arrow from 0.65, 0.73 to 0.56, graph 0.83 nohead lc rgb "black" linewidth 2 front
# # Additional xtic at x=0.5
# set xtics add ("0.5" 0.5)

# Define colors for each line and corresponding filled curves
set style line 1 lc rgb "red" lw 6
set style line 2 lc rgb "blue" lw 6
set style line 3 lc rgb "green" lw 6

# Plot commands
plot  './data/data_k16_m8.dat' using 1:($1 <= 0.5 ? $2 : 1/0) with filledcurves x1 fs transparent solid 0.1 noborder lc rgb "red" notitle, \
      './data/data_k16_m8.dat' using 1:($1 > 0.5 ? $2 : 1/0) with filledcurves above x2 fs transparent solid 0.1 noborder lc rgb "red" notitle, \
      './data/data_k64_m32.dat' using 1:($1 <= 0.5 ? $2 : 1/0) with filledcurves x1 fs transparent solid 0.1 noborder lc rgb "blue" notitle, \
      './data/data_k64_m32.dat' using 1:($1 > 0.5 ? $2 : 1/0) with filledcurves above x2 fs transparent solid 0.1 noborder lc rgb "blue" notitle, \
      './data/data_k256_m128.dat' using 1:($1 <= 0.5 ? $2 : 1/0) with filledcurves x1 fs transparent solid 0.1 noborder lc rgb "green" notitle, \
      './data/data_k256_m128.dat' using 1:($1 > 0.5 ? $2 : 1/0) with filledcurves above x2 fs transparent solid 0.1 noborder lc rgb "green" notitle, \
      './data/data_k16_m8.dat' using 1:2 with lines ls 1 title 'k=16', \
      './data/data_k64_m32.dat' using 1:2 with lines ls 2 title 'k=64', \
      './data/data_k256_m128.dat' using 1:2 with lines ls 3 title 'k=256'
