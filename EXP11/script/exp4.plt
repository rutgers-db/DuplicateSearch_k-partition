set terminal postscript eps color enhanced "Helvetica" 32 
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "# of Sequences"  font "Helvetica, 52" #font "Times-Roman, 32"
set x2label offset -5 "Index Size (GB)"  font "Helvetica, 52" #font "Times-Roman, 32"

set key font ",30"
set offset 0.3, 0.3, 0, 0

set ytics 10 font "Helvetica, 44"
set logscale y
set format y "10^{%L}"

set xtics ("1M" 0, "2M" 1, "4M" 2, "8M" 3) font "Helvetica, 44"
set output "../figure2/owt_index_size_vary_docsnum.eps"
plot "../data/owt_index_size_vary_docsnum.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5 t "OPH",\


set xtics ("0.36M" 0, "0.73M" 1, "1.46M" 2, "2.92M" 3)
set output "../figure2/wiki_index_size_vary_docsnum.eps"
plot "../data/wiki_index_size_vary_docsnum.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5 t "OPH",\


set x2label offset -5.5 "Index Time (s)"  font "Helvetica, 52" #font "Times-Roman, 32"

set xtics ("1M" 0, "2M" 1, "4M" 2, "8M" 3)
set output "../figure2/owt_index_time_vary_docsnum.eps"
plot "../data/owt_index_time_vary_docsnum.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5 t "OPH",\


set xtics ("0.36M" 0, "0.73M" 1, "1.46M" 2, "2.92M" 3)
set output "../figure2/wiki_index_time_vary_docsnum.eps"
plot "../data/wiki_index_time_vary_docsnum.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5 t "OPH",\


set x2label offset -5.3 "Avg. Query Time (s)"  font "Helvetica, 52" #font "Times-Roman, 32"

set xtics ("1M" 0, "2M" 1, "4M" 2, "8M" 3)
set output "../figure2/owt_query_time_vary_docsnum.eps"
plot "../data/owt_query_time_vary_docsnum.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5 t "OPH-filter",\


set xtics ("0.36M" 0, "0.73M" 1, "1.46M" 2, "2.92M" 3)
set output "../figure2/wiki_query_time_vary_docsnum.eps"
plot "../data/wiki_query_time_vary_docsnum.txt" u 1:3 w linespoints pt 1 ps 3.5 lw 5 t "OPH-filter",\
