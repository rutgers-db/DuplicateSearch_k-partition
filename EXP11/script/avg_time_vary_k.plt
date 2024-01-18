set terminal postscript eps color enhanced "Helvetica" 32
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "k, Sketch Size"  font "Helvetica, 52" #font "Times-Roman, 32"
set x2label offset 0 "Avg. Alignment Time (s)"  font "Helvetica, 52" #font "Times-Roman, 32"

set key font ",30"
set offsets 0.2, 0.2, 0, 0

# Arbitrarily VS by Position
set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4) font "Helvetica, 44"
set ytics 100 font "Helvetica, 44"
set logscale y
set format y "10^{%L}"

set ytics 0.001, 100
set yrange[0.001:5000]
set output "../figure/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.eps"
plot "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-pos",\
     "../data/pan_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

set ytics 0.00001, 100
set yrange[0.00001:10]
set output "../figure/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.eps"
plot "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-pos",\
     "../data/wiki_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

set ytics 0.00001, 100
set yrange[0.00001:10]
set output "../figure/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.eps"
plot "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-pos",\
     "../data/owt_avg_time_vary_k_Arbitrarily_VS_by_Position.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

# All VS Longest
set x2label offset 0 "Avg. # of near-duplicates"  font "Helvetica, 52" #font "Times-Roman, 32"
set ytics 10
# set format y
# unset logscale y

set yrange[100:1000000]
set output "../figure/pan_avg_time_vary_k_All_VS_Longest.eps"
plot "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-lst",\
     "../data/pan_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

set ytics 10
set yrange[10:10000]
set output "../figure/wiki_avg_time_vary_k_All_VS_Longest.eps"
plot "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-lst",\
     "../data/wiki_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

set ytics 10
set yrange[0.1:10000]
set output "../figure/owt_avg_time_vary_k_All_VS_Longest.eps"
plot "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-lst",\
     "../data/owt_avg_time_vary_k_All_VS_Longest.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

# Interval scan VS Segment tree
set x2label offset 0 "Avg. Alignment Time (s)"  font "Helvetica, 52" #font "Times-Roman, 32"
set ytics 10
set logscale y
set format y "10^{%L}"

set yrange[0.001:10]
set output "../figure/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-seg",\
     "../data/pan_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-seg",\

set yrange[0.00001:0.1]
set output "../figure/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-seg",\
     "../data/wiki_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-seg",\

set ytics 0.00001, 100
set yrange[0.00001:1000]
set output "../figure/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.eps"
plot "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "KMS-seg",\
     "../data/owt_avg_time_vary_k_Interval_Scan_VS_Segment_Tree.txt" every ::1 u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-seg",\

# Filter
set x2label offset -2 "Avg. Query Time (s)"  font "Helvetica, 52" #font "Times-Roman, 32"
set xtics ("8" 0, "16" 1, "32" 2, "64" 3) font "Helvetica, 44"
set ytics 100
set yrange[1:10000000]
set output "../figure/pan_avg_time_vary_k_filter.eps"
plot "../data/pan_avg_time_vary_k_filter.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-vanilla",\
     "../data/pan_avg_time_vary_k_filter.txt" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-seg",\
     "../data/pan_avg_time_vary_k_filter.txt" u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "OPH-filter",\

set ytics 0.1, 100
set yrange[0.1:1000000]
set output "../figure/wiki_avg_time_vary_k_filter.eps"
plot "../data/wiki_avg_time_vary_k_filter.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-vanilla",\
     "../data/wiki_avg_time_vary_k_filter.txt" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-seg",\
     "../data/wiki_avg_time_vary_k_filter.txt" u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "OPH-filter",\

set ytics 0.1, 100
set yrange[0.1:1000000]
set output "../figure/owt_avg_time_vary_k_filter.eps"
plot "../data/owt_avg_time_vary_k_filter.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-vanilla",\
     "../data/owt_avg_time_vary_k_filter.txt" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-seg",\
     "../data/owt_avg_time_vary_k_filter.txt" u 1:5 w linespoints pt 6 ps 3.5 lw 5  t "OPH-filter",\
