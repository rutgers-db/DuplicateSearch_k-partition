set terminal postscript eps color "Times-Roman" 25 enhanced
set size 2, 1.3
set style data histogram
set style histogram cluster gap 2
set style fill solid border
set style fill pattern
set boxwidth 1
unset mytics
unset mxtics
set xtics font "Times-Roman25"

set output "test.eps"

plot './EXP9/data2/openwebtext_querytime_vs_theta_k64.txt' using 2:xtic(1) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 5, \
     '' using 3 with lp title "KMINS" lc rgb "black" lt 2 dt 2 lw 5, \
     '' using 4 with lp title "OPH interval scan" lc rgb "black" lt 3 dt 3 lw 5, \
     '' using 5 with lp title "KMINS interval scan" lc rgb "black" lt 4 dt 4 lw 5, \
     '' using 6 with lp title "OPH longest" lc rgb "black" lt 5 dt 5 lw 5, \
     '' using 7 with lp title "KMINS longest" lc rgb "black" lt 6 dt 6 lw 5, \
     '' using 8 with lp title "OPH interval scan longest" lc rgb "black" lt 7 dt 7 lw 5, \
     '' using 9 with lp title "KMINS interval scan longest" lc rgb "black" lt 8 dt 8 lw 5

# set logscale y
# set format y "10^{%L}"
# plot './EXP9/data2/openwebtext_querytime_vs_k_theta0.7.txt' using 2:xtic(1) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 5, \
#      '' using 3 with lp title "KMINS" lc rgb "black" lt 2 dt 2 lw 5, \
#      '' using 4 with lp title "OPH interval scan" lc rgb "black" lt 3 dt 3 lw 5, \
#      '' using 5 with lp title "KMINS interval scan" lc rgb "black" lt 4 dt 4 lw 5, \
#      '' using 6 with lp title "OPH longest" lc rgb "black" lt 5 dt 5 lw 5, \
#      '' using 7 with lp title "KMINS longest" lc rgb "black" lt 6 dt 6 lw 5, \
#      '' using 8 with lp title "OPH interval scan longest" lc rgb "black" lt 7 dt 7 lw 5, \
#      '' using 9 with lp title "KMINS interval scan longest" lc rgb "black" lt 8 dt 8 lw 5