set terminal postscript eps color enhanced "Helvetica" 32
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -1.7 "Avg. Query Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",24"

set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4)

set yrange[0.001:5000]
set ytics 10
set logscale y
set format y "10^{%L}"
# set output "owt_avg_time_vary_k.eps"
# plot "owt_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "owt_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "pan_avg_time_vary_k(Arbitrarily VS by Position).eps"
plot "pan_avg_time_vary_k.txt" u 1:3 w lines lw 5  t "KMS Arbitrarily",\
     "pan_avg_time_vary_k.txt" u 1:4 w lines lw 5  t "OPH Arbitrarily",\
     "pan_avg_time_vary_k.txt" u 1:5 w lines lw 5  t "KMS by Position",\
     "pan_avg_time_vary_k.txt" u 1:6 w lines lw 5  t "OPH by Position",\

# set output "wiki_avg_time_vary_k.eps"
# plot "wiki_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "wiki_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set yrange[0.001:10]
set output "pan_avg_time_vary_k(All VS Longest).eps"
plot "pan_avg_time_vary_k.txt" u 1:7 w lines lw 5  t "KMS All",\
     "pan_avg_time_vary_k.txt" u 1:8 w lines lw 5  t "OPH All",\
     "pan_avg_time_vary_k.txt" u 1:9 w lines lw 5  t "KMS Longest",\
     "pan_avg_time_vary_k.txt" u 1:10 w lines lw 5  t "OPH Longest",\

set output "pan_avg_time_vary_k(Interval Scan VS Segment Tree).eps"
plot "pan_avg_time_vary_k.txt" u 1:5 w lines lw 5  t "KMS Interval Scan",\
     "pan_avg_time_vary_k.txt" u 1:6 w lines lw 5  t "OPH Interval Scan",\
     "pan_avg_time_vary_k.txt" u 1:11 w lines lw 5  t "KMS Segment Tree",\
     "pan_avg_time_vary_k.txt" u 1:12 w lines lw 5  t "OPH Segment Tree",\

set yrange[0.001:500]
set xtics ("0.2" 0, "0.3" 1, "0.4" 2, "0.5" 3, "0.6" 4, "0.7" 5, "0.8" 6, "0.9" 7)

set output "pan_avg_time_vary_theta(Arbitrarily VS by Position).eps"
plot "pan_avg_time_vary_theta(Arbitrarily VS by Position).txt" u 1:3 w lines lw 5  t "KMS Arbitrarily",\
     "pan_avg_time_vary_theta(Arbitrarily VS by Position).txt" u 1:4 w lines lw 5  t "OPH Arbitrarily",\
     "pan_avg_time_vary_theta(Arbitrarily VS by Position).txt" u 1:5 w lines lw 5  t "KMS by Position",\
     "pan_avg_time_vary_theta(Arbitrarily VS by Position).txt" u 1:6 w lines lw 5  t "OPH by Position",\

set yrange[0.001:10]
set xtics ("0.1" 0, "0.2" 1, "0.3" 2, "0.4" 3, "0.5" 4, "0.6" 5, "0.7" 6, "0.8" 7, "0.9" 8)

set output "pan_avg_time_vary_theta(All VS Longest).eps"
plot "pan_avg_time_vary_theta(All VS Longest).txt" u 1:3 w lines lw 5  t "KMS All",\
     "pan_avg_time_vary_theta(All VS Longest).txt" u 1:4 w lines lw 5  t "OPH All",\
     "pan_avg_time_vary_theta(All VS Longest).txt" u 1:5 w lines lw 5  t "KMS Longest",\
     "pan_avg_time_vary_theta(All VS Longest).txt" u 1:6 w lines lw 5  t "OPH Longest",\

set xtics ("0.2" 0, "0.3" 1, "0.4" 2, "0.5" 3, "0.6" 4, "0.7" 5, "0.8" 6, "0.9" 7)

set output "pan_avg_time_vary_theta(Interval Scan VS Segment Tree).eps"
plot "pan_avg_time_vary_theta(Interval Scan VS Segment Tree).txt" u 1:3 w lines lw 5  t "KMS Interval Scan",\
     "pan_avg_time_vary_theta(Interval Scan VS Segment Tree).txt" u 1:4 w lines lw 5  t "OPH Interval Scan",\
     "pan_avg_time_vary_theta(Interval Scan VS Segment Tree).txt" u 1:5 w lines lw 5  t "KMS Segment Tree",\
     "pan_avg_time_vary_theta(Interval Scan VS Segment Tree).txt" u 1:6 w lines lw 5  t "OPH Segment Tree",\