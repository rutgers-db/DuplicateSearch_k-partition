set terminal postscript eps monochrome enhanced "Helvetica" 32
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -1.7 "Avg. Query Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",24"

set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4)

set yrange[0.001:500]
set ytics 10
set logscale y
set format y "10^{%L}"
set xtics ("0.2" 0, "0.3" 1, "0.4" 2, "0.5" 3, "0.6" 4, "0.7" 5, "0.8" 6, "0.9" 7)

set output "../figure/pan_avg_time_vary_theta(Arbitrarily_VS_by_Position).eps"
plot "../data/pan_avg_time_vary_theta(Arbitrarily_VS_by_Position).txt" u 1:3 w lines lw 3  t "KMS-Arb",\
     "../data/pan_avg_time_vary_theta(Arbitrarily_VS_by_Position).txt" u 1:4 w lines lw 3  t "OPH-Arb",\
     "../data/pan_avg_time_vary_theta(Arbitrarily_VS_by_Position).txt" u 1:5 w lines lw 3  t "KMS-Pos",\
     "../data/pan_avg_time_vary_theta(Arbitrarily_VS_by_Position).txt" u 1:6 w lines lw 3  t "OPH-Pos",\

set yrange[0.001:0.4]
set ytics auto
set format y
unset logscale y
set xtics ("0.1" 0, "0.2" 1, "0.3" 2, "0.4" 3, "0.5" 4, "0.6" 5, "0.7" 6, "0.8" 7, "0.9" 8)

set output "../figure/pan_avg_time_vary_theta(All_VS_Longest).eps"
plot "../data/pan_avg_time_vary_theta(All_VS_Longest).txt" u 1:3 w lines lw 3  t "KMS-All",\
     "../data/pan_avg_time_vary_theta(All_VS_Longest).txt" u 1:4 w lines lw 3  t "OPH-All",\
     "../data/pan_avg_time_vary_theta(All_VS_Longest).txt" u 1:5 w lines lw 3  t "KMS-Longest",\
     "../data/pan_avg_time_vary_theta(All_VS_Longest).txt" u 1:6 w lines lw 3  t "OPH-Longest",\

set yrange[0.001:10]
set ytics 10
set logscale y
set format y "10^{%L}"
set xtics ("0.2" 0, "0.3" 1, "0.4" 2, "0.5" 3, "0.6" 4, "0.7" 5, "0.8" 6, "0.9" 7)
set output "../figure/pan_avg_time_vary_theta(Interval_Scan_VS_Segment_Tree).eps"
plot "../data/pan_avg_time_vary_theta(Interval_Scan_VS_Segment_Tree).txt" u 1:3 w lines lw 3  t "KMS-Int",\
     "../data/pan_avg_time_vary_theta(Interval_Scan_VS_Segment_Tree).txt" u 1:4 w lines lw 3  t "OPH-Int",\
     "../data/pan_avg_time_vary_theta(Interval_Scan_VS_Segment_Tree).txt" u 1:5 w lines lw 3  t "KMS-Seg",\
     "../data/pan_avg_time_vary_theta(Interval_Scan_VS_Segment_Tree).txt" u 1:6 w lines lw 3  t "OPH-Seg",\