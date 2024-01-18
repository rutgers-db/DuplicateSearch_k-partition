reset
set terminal postscript eps color "Times-Roman" 28 enhanced
set size 1.5,0.08

set style data histogram
set style histogram cluster gap 2
set style fill solid border 
set style fill pattern
set boxwidth 1
#unset key
set key top horizontal center outside
#set key height 1
#set key width 5


unset mytics


unset xlabel

set yrange [-0.1:-0.2]

unset xlabel
unset ylabel
unset xtics
unset ytics
unset border
unset mxtics
unset mytics
unset title
set key top horizontal center
set key height -0.3
#set key width -2
#set lmargin -10


set output 'scala-legend.eps' 
plot 	'./legends.txt' using 2:xtic(1) w boxes fs pattern 7   t "OPH",\
	'' using 3 w boxes fs pattern 9   t "KMS"
