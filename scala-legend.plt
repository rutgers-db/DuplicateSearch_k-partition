reset
set terminal postscript eps color "Times-Roman" 28 enhanced
set size 1.5,0.08

set style data histogram
set style histogram cluster gap 2
set style fill solid border 
set style fill pattern
set boxwidth 1
unset key
set key top horizontal center outside
# set key spacing 0.2  # Adjust this value to control the spacing between legend entries

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
set key maxrows 1
# set key height -0.3
# set key width -1
# set lmargin -30


# set output 'index_legend.eps' 
# plot 	'./legends.txt' using 2:xtic(1) w boxes fs pattern 7   t "OPH",\
# 	'' using 3 w boxes fs pattern 9   t "KMS"

# set output './Legend/arb_bypos_legend.eps' 
# plot 	'./legends.txt' using 2:xtic(1) w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
#      '' using 3 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
#      '' using 4 w linespoints pt 6 ps 3.5 lw 5  t "KMS-pos",\
#      '' using 5 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

# set output './Legend/pos_lst_legend.eps' 
# plot 	'./legends.txt' using 2:xtic(1) w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
#      '' using 3 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
#      '' using 4 w linespoints pt 6 ps 3.5 lw 5  t "KMS-lst",\
#      '' using 5 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\


# set output './Legend/seg_lst_legend.eps' 
# plot 	'./legends.txt' using 2:xtic(1) w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
#      '' using 3 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
#      '' using 4 w linespoints pt 6 ps 3.5 lw 5  t "KMS-seg",\
# 
# plot 	'./legends.txt' using 2:xtic(1) w linespoints pt 1 ps 3.5 lw 5  t "KMS-vanilla",\
#      '' using 3 w linespoints pt 2 ps 3.5 lw 5  t "OPH-seg",\

set key height -0.3
set key width -1
set lmargin -30

set output './Legend/scalability_legend.eps' 
plot 	'./legends.txt' using 2:xtic(1) w linespoints pt 1 ps 3.5 lw 5  t "OPH",\
     '' using 3 w linespoints pt 2 ps 3.5 lw 5  t "OPH-seg",\