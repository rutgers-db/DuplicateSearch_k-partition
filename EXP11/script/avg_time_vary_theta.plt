set terminal postscript eps color enhanced "Helvetica" 32
set key top right width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "Theta"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -1.7 "Avg. Query Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",24"

set xtics ("0.2" 0, "0.3" 1, "0.4" 2, "0.5" 3, "0.6" 4, "0.7" 5, "0.8" 6, "0.9" 7)
set ytics 10
set logscale y
set format y "10^{%L}"

set yrange[0.001:500]
set output "../figure/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.eps"
plot "../data/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-Arb",\
     "../data/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-Arb",\
     "../data/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Pos",\
     "../data/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Pos",\

set yrange[0.00001:0.5]
set output "../figure/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.eps"
plot "../data/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-Arb",\
     "../data/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-Arb",\
     "../data/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Pos",\
     "../data/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Pos",\

set yrange[0.00001:10]
set output "../figure/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.eps"
plot "../data/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-Arb",\
     "../data/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-Arb",\
     "../data/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Pos",\
     "../data/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Pos",\


set xtics ("0.1" 0, "0.2" 1, "0.3" 2, "0.4" 3, "0.5" 4, "0.6" 5, "0.7" 6, "0.8" 7, "0.9" 8)
set ytics 0.1
set format y
unset logscale y

set yrange[0.001:0.3]
set output "../figure/pan_avg_time_vary_theta_All_VS_Longest.eps"
plot "../data/pan_avg_time_vary_theta_All_VS_Longest.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-All",\
     "../data/pan_avg_time_vary_theta_All_VS_Longest.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-All",\
     "../data/pan_avg_time_vary_theta_All_VS_Longest.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Longest",\
     "../data/pan_avg_time_vary_theta_All_VS_Longest.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Longest",\

set ytics 0.01
set yrange[0.00001:0.02]
set output "../figure/wiki_avg_time_vary_theta_All_VS_Longest.eps"
plot "../data/wiki_avg_time_vary_theta_All_VS_Longest.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-All",\
     "../data/wiki_avg_time_vary_theta_All_VS_Longest.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-All",\
     "../data/wiki_avg_time_vary_theta_All_VS_Longest.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Longest",\
     "../data/wiki_avg_time_vary_theta_All_VS_Longest.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Longest",\

set yrange[0.00001:0.03]
set output "../figure/owt_avg_time_vary_theta_All_VS_Longest.eps"
plot "../data/owt_avg_time_vary_theta_All_VS_Longest.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-All",\
     "../data/owt_avg_time_vary_theta_All_VS_Longest.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-All",\
     "../data/owt_avg_time_vary_theta_All_VS_Longest.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Longest",\
     "../data/owt_avg_time_vary_theta_All_VS_Longest.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Longest",\


set xtics ("0.2" 0, "0.3" 1, "0.4" 2, "0.5" 3, "0.6" 4, "0.7" 5, "0.8" 6, "0.9" 7)
set ytics 10
set logscale y
set format y "10^{%L}"

set yrange[0.001:10]
set output "../figure/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-Int",\
     "../data/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-Int",\
     "../data/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Seg",\
     "../data/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Seg",\

set yrange[0.00001:0.05]
set output "../figure/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-Int",\
     "../data/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-Int",\
     "../data/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Seg",\
     "../data/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Seg",\

set output "../figure/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "KMS-Int",\
     "../data/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "OPH-Int",\
     "../data/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "KMS-Seg",\
     "../data/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt" u 1:6 w linespoints pt 4 ps 2 lw 3  t "OPH-Seg",\


set xtics ("0.2" 0, "0.4" 1, "0.6" 2, "0.8" 3)
set yrange[1:200]
set output "../figure/pan_avg_time_vary_theta_filter.eps"
plot "../data/pan_avg_time_vary_theta_filter.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "None",\
     "../data/pan_avg_time_vary_theta_filter.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "Filter 1",\
     "../data/pan_avg_time_vary_theta_filter.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "Filter 1+2",\

set yrange[0.0000001:50]
set output "../figure/wiki_avg_time_vary_theta_filter.eps"
plot "../data/wiki_avg_time_vary_theta_filter.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "None",\
     "../data/wiki_avg_time_vary_theta_filter.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "Filter 1",\
     "../data/wiki_avg_time_vary_theta_filter.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "Filter 1+2",\

set output "../figure/owt_avg_time_vary_theta_filter.eps"
plot "../data/owt_avg_time_vary_theta_filter.txt" u 1:3 w linespoints pt 1 ps 2 lw 3  t "None",\
     "../data/owt_avg_time_vary_theta_filter.txt" u 1:4 w linespoints pt 2 ps 2 lw 3  t "Filter 1",\
     "../data/owt_avg_time_vary_theta_filter.txt" u 1:5 w linespoints pt 3 ps 2 lw 3  t "Filter 1+2",\