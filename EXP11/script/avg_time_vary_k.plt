set terminal postscript eps color enhanced "Helvetica" 32
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -1.7 "Avg. Query Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",28"

set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4)

set yrange[0.001:5000]
set ytics 10
set logscale y
set format y "10^{%L}"

# set output "owt_avg_time_vary_k.eps"
# plot "owt_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "owt_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "../figure/pan_avg_time_vary_k(Arbitrarily_VS_by_Position).eps"
plot "../data/pan_avg_time_vary_k.txt" u 1:3 w linespoints pt 1 lw 3  t "KMS-Arb",\
     "../data/pan_avg_time_vary_k.txt" u 1:4 w linespoints pt 2 lw 3  t "OPH-Arb",\
     "../data/pan_avg_time_vary_k.txt" u 1:5 w linespoints pt 3 lw 3  t "KMS-Pos",\
     "../data/pan_avg_time_vary_k.txt" u 1:6 w linespoints pt 4 lw 3  t "OPH-Pos",\

# set output "wiki_avg_time_vary_k.eps"
# plot "wiki_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "wiki_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set yrange[0.001:4]
set ytics auto
set format y
unset logscale y
set output "../figure/pan_avg_time_vary_k(All_VS_Longest).eps"
plot "../data/pan_avg_time_vary_k.txt" u 1:7 w linespoints pt 1 lw 3  t "KMS-All",\
     "../data/pan_avg_time_vary_k.txt" u 1:8 w linespoints pt 2 lw 3  t "OPH-All",\
     "../data/pan_avg_time_vary_k.txt" u 1:9 w linespoints pt 3 lw 3  t "KMS-Longest",\
     "../data/pan_avg_time_vary_k.txt" u 1:10 w linespoints pt 4 lw 3  t "OPH-Longest",\

set yrange[0.001:10]
set ytics 10
set logscale y
set format y "10^{%L}"
set output "../figure/pan_avg_time_vary_k(Interval_Scan_VS_Segment_Tree).eps"
plot "../data/pan_avg_time_vary_k.txt" u 1:5 w linespoints pt 1 lw 3  t "KMS-Int",\
     "../data/pan_avg_time_vary_k.txt" u 1:6 w linespoints pt 2 lw 3  t "OPH-Int",\
     "../data/pan_avg_time_vary_k.txt" u 1:11 w linespoints pt 3 lw 3  t "KMS-Seg",\
     "../data/pan_avg_time_vary_k.txt" u 1:12 w linespoints pt 4 lw 3  t "OPH-Seg",\