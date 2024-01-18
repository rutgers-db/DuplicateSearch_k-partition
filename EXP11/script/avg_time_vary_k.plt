set terminal postscript eps color enhanced "Helvetica" 32
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -3.2 "Avg. Alignment Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",30"
set offsets 0.2, 0.2, 0.2, 0.2

# Arbitrarily VS by Position
set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4) font "Helvetica, 36"
set ytics 100 font "Helvetica, 36"
set logscale y
set format y "10^{%L}"

set yrange[0.001:5000]
set output "../figure/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.eps"
plot "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-pos",\
     "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

set yrange[0.00005:10]
set output "../figure/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.eps"
plot "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-pos",\
     "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

set yrange[0.00001:10]
set output "../figure/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.eps"
plot "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-pos",\
     "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

# All VS Longest
set ytics 1
set format y
unset logscale y

set yrange[0:2]
set output "../figure/pan_avg_time_vary_k_All_VS_Longest.eps"
plot "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-lst",\
     "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

set ytics 0.001
set yrange[0:0.006]
set output "../figure/wiki_avg_time_vary_k_All_VS_Longest.eps"
plot "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-lst",\
     "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

set yrange[0:0.004]
set output "../figure/owt_avg_time_vary_k_All_VS_Longest.eps"
plot "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-lst",\
     "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

# Interval scan VS Segment tree
set ytics 10
set logscale y
set format y "10^{%L}"

set yrange[0.001:10]
set output "../figure/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-Seg",\
     "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-Seg",\

set yrange[0.00005:0.1]
set output "../figure/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-Seg",\
     "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-Seg",\

set ytics 100
set yrange[0.00005:500]
set output "../figure/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-Seg",\
     "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-Seg",\

# Filter
set x2label offset -4.7 "Avg. Query Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"
set ytics 10
set yrange[0.1:50]
set output "../figure/pan_avg_time_vary_k_filter.eps"
plot "../data/pan_avg_time_vary_k_filter.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "None",\
     "../data/pan_avg_time_vary_k_filter.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "WFilter",\
     "../data/pan_avg_time_vary_k_filter.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "WFilter+RFilter",\

set ytics 100
set yrange[0.0000001:500]
set output "../figure/wiki_avg_time_vary_k_filter.eps"
plot "../data/wiki_avg_time_vary_k_filter.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "None",\
     "../data/wiki_avg_time_vary_k_filter.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "WFilter",\
     "../data/wiki_avg_time_vary_k_filter.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "WFilter+RFilter",\

set output "../figure/owt_avg_time_vary_k_filter.eps"
plot "../data/owt_avg_time_vary_k_filter.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "None",\
     "../data/owt_avg_time_vary_k_filter.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "WFilter",\
     "../data/owt_avg_time_vary_k_filter.txt" every ::1 u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "WFilter+RFilter",\
