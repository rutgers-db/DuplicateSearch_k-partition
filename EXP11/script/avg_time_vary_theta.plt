set terminal postscript eps color enhanced "Helvetica" 32
set key top right width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "{/Symbol q}, Sim Threshold"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -3.2 "Avg. Alignment Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",30"

set xtics ("0.1" 0, "0.2" 1, "0.4" 2, "0.8" 3) font "Helvetica, 36"
set ytics 100 font "Helvetica, 36"
set logscale y
set format y "10^{%L}"

set yrange[0.001:500]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/pan_avg_time_vary_theta_Arbitrarily_VS_by_Position.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-pos",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

set yrange[0.00001:5]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/wiki_avg_time_vary_theta_Arbitrarily_VS_by_Position.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-pos",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\

set yrange[0.00001:10]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/owt_avg_time_vary_theta_Arbitrarily_VS_by_Position.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-arb",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-arb",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-pos",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-pos",\


set ytics 0.1
set format y "%.1f"
unset logscale y

set yrange[0:0.3]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/pan_avg_time_vary_theta_All_VS_Longest.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/pan_avg_time_vary_theta_All_VS_Longest.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-lst",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

set format y "%.2f"
set ytics 0.01
set yrange[0:0.02]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/wiki_avg_time_vary_theta_All_VS_Longest.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/wiki_avg_time_vary_theta_All_VS_Longest.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-lst",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\

set yrange[0:0.02]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/owt_avg_time_vary_theta_All_VS_Longest.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/owt_avg_time_vary_theta_All_VS_Longest.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-pos",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-pos",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-lst",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-lst",\


set ytics 10
set logscale y
set format y "10^{%L}"

set yrange[0.001:10]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/pan_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-Seg",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-Seg",\

set yrange[0.00001:0.5]
system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/wiki_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-Seg",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-Seg",\

system("awk 'NR==1 || NR==2 || NR==4 || NR==8' ../data/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.txt > filtered_data2.txt")
system("awk '{ $1=NR-1; print }' filtered_data2.txt > filtered_data.txt")
set output "../figure/owt_avg_time_vary_theta_Interval_Scan_VS_Segment_Tree.eps"
plot "filtered_data.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "KMS-lst",\
     "" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "OPH-lst",\
     "" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "KMS-Seg",\
     "" u 1:6 w linespoints pt 4 ps 3.5 lw 5  t "OPH-Seg",\


set x2label offset -4.7 "Avg. Query Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set xtics ("0.2" 0, "0.4" 1, "0.6" 2, "0.8" 3)
set ytics 10
set yrange[1:200]
set output "../figure/pan_avg_time_vary_theta_filter.eps"
plot "../data/pan_avg_time_vary_theta_filter.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "None",\
     "../data/pan_avg_time_vary_theta_filter.txt" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "WFilter",\
     "../data/pan_avg_time_vary_theta_filter.txt" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "WFilter+RFilter",\


set ytics 100
set yrange[0.0000001:500]
set output "../figure/wiki_avg_time_vary_theta_filter.eps"
plot "../data/wiki_avg_time_vary_theta_filter.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "None",\
     "../data/wiki_avg_time_vary_theta_filter.txt" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "WFilter",\
     "../data/wiki_avg_time_vary_theta_filter.txt" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "WFilter+RFilter",\

set output "../figure/owt_avg_time_vary_theta_filter.eps"
plot "../data/owt_avg_time_vary_theta_filter.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5  t "None",\
     "../data/owt_avg_time_vary_theta_filter.txt" u 1:4 w linespoints pt 2 ps 3.5 lw 5  t "WFilter",\
     "../data/owt_avg_time_vary_theta_filter.txt" u 1:5 w linespoints pt 3 ps 3.5 lw 5  t "WFilter+RFilter",\