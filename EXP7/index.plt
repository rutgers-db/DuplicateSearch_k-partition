set terminal postscript eps color enhanced "Helvetica" 40
set key top left width 0

#set ylabel "average time (s)" offset 1 font "Helvetica, 40"
#set xlabel "k, sketch size" offset 0 font "Helvetica, 40"
set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -1.7 "Avg. Generation Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",36"

set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4)
set xrange[-0.6:4.6]

set yrange[0.0001:1]
set ytics 10
set logscale y
set format y "10^{%L}"
set output "owt_avg_time_vary_k.eps"
plot "owt_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "owt_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "pan_avg_time_vary_k.eps"
plot "pan_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "pan_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "wiki_avg_time_vary_k.eps"
plot "wiki_avg_time_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "wiki_avg_time_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"


set xtics ("100" 0, "1000" 1, "10000" 2, "100000" 3)
set xrange[-0.6:3.6]
set xlabel "n, Sequence Length"  font "Helvetica, 40" #font "Times-Roman, 32"
set yrange[0.00001:1]
set output "owt_avg_time_vary_n.eps"
plot "owt_avg_time_vary_n.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "owt_avg_time_vary_n.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "pan_avg_time_vary_n.eps"
plot "pan_avg_time_vary_n.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "pan_avg_time_vary_n.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "wiki_avg_time_vary_n.eps"
plot "wiki_avg_time_vary_n.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "wiki_avg_time_vary_n.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"


set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
set x2label offset -1 "Avg. \# of Compact Windows"  font "Helvetica, 40" #font "Times-Roman, 32"

set key font ",36"

set xtics ("16" 0, "32" 1, "64" 2, "128" 3, "256" 4)
set xrange[-0.6:4.6]

set yrange[10000:10000000]
set ytics 10
set logscale y
set format y "10^{%L}"
set output "owt_avg_num_vary_k.eps"
plot "owt_avg_num_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "owt_avg_num_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "pan_avg_num_vary_k.eps"
plot "pan_avg_num_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "pan_avg_num_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "wiki_avg_num_vary_k.eps"
plot "wiki_avg_num_vary_k.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "wiki_avg_num_vary_k.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"


set xtics ("100" 0, "1000" 1, "10000" 2, "100000" 3)
set xrange[-0.6:3.6]
set xlabel "n, Sequence Length"  font "Helvetica, 40" #font "Times-Roman, 32"
set yrange[100:10000000]
set output "owt_avg_num_vary_n.eps"
plot "owt_avg_num_vary_n.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "owt_avg_num_vary_n.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "pan_avg_num_vary_n.eps"
plot "pan_avg_num_vary_n.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "pan_avg_num_vary_n.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

set output "wiki_avg_num_vary_n.eps"
plot "wiki_avg_num_vary_n.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
     "wiki_avg_num_vary_n.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"





# set xlabel "k, Sketch Size"  font "Helvetica, 40" #font "Times-Roman, 32"
# set x2label offset -6 "Index Time (s)"  font "Helvetica, 40" #font "Times-Roman, 32"

# set key font ",36"

# set xtics ("4" 0, "8" 1, "16" 2, "32" 3, "64" 4)
# set xrange[-0.6:4.6]

# set yrange[100:10000]
# set ytics 10
# set logscale y
# set format y "10^{%L}"
# set output "owt_index_time.eps"
# plot "owt_index_time.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "owt_index_time.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

# set output "pan_index_time.eps"
# plot "pan_index_time.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "pan_index_time.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

# set output "wiki_index_time.eps"
# plot "wiki_index_time.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "wiki_index_time.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"




# set x2label offset -5.2 "Index Size (GB)"  font "Helvetica, 40" #font "Times-Roman, 32"
# set yrange[10:1000]
# set output "owt_index_size.eps"
# plot "owt_index_size.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "owt_index_size.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

# set output "pan_index_size.eps"
# plot "pan_index_size.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "pan_index_size.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"

# set output "wiki_index_size.eps"
# plot "wiki_index_size.txt" u ($1-0.15):($3):(0.3)  w boxes fs pattern 7   t "OPH",\
#      "wiki_index_size.txt" u ($1+0.15):($4):(0.3) w boxes fs pattern 9   t "KMS"



