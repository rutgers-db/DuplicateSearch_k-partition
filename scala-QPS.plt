reset
set terminal postscript eps color "Times-Roman" 45 enhanced
set size 0.8,0.8

set style data histogram
set style histogram cluster gap 2
set style fill solid border 
set style fill pattern
set boxwidth 1
unset key
#set key top horizontal center outside
#set key height 1
#set key width 5


unset mytics


unset xlabel
#set ylabel "Trainning Time (minutes)" offset 0.5 font "Times-Roman,18"
# set x2label offset -4 "QPS" font "Times-Roman, 45"  
set ylabel offset 2.25 "QPS" font "Times-Roman, 45"  
set xlabel offset 0,0.5 "# of points ({/Symbol \264}10\^6)" font "Times-Roman, 45"  

#set logscale y
#set format y "10^{%L}

#set ytics ('10^{0}' 1, '10^{1}' 10, '10^{2}' 100, '10^{3}' 1000, '10^{4}' 10000,'10^{5}' 100000, 'OM' 384000)
#set xtics rotate by -30 font "Times-Roman,25"

set xtics font "Times-Roman,45"

set xrange [-0.2:4.2]
set yrange [0:2000]
set ytic 500

# set arrow 1 from 3.8, 0 to 3.6, 7 nohead lc rgb "black" lw 2
# set label 1 "OOM" at 3.6, 9 center

# set arrow 2 from 4.0, 14 to 3.8, 14 nohead lc rgb "black" lw 2
# set label 2 "50.1" at 3.6, 14 center



set output 'scala-QPS.eps' 
plot 	'legneds.txt' using 2:xtic(1) with lp title 'ASAP' lc rgb "black" lt 1 dt 1 lw 7 ps 2.5 pt 6,\
	'' using 3 with lp title 'EdgePool' lc rgb "black" lt 2 dt 2 lw 7 ps 2.5 pt 4

#set terminal x11
#replot
