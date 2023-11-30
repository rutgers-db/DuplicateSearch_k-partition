import os
from pygnuplot import gnuplot
import pandas as pd

g = gnuplot.Gnuplot()
g.set(terminal='postscript eps color "Times-Roman" 25 enhanced')
g.set(size='1,0.65')
g.set(style='data histogram')
g.set(style='histogram cluster gap 2')
g.set(style='fill solid border')
g.set(style='fill pattern')
g.set(boxwidth='1')
g.unset('mytics')
# g.set(logscale='y')
# g.set(format='y "10^{%L}"')
g.set(xtics='font "Times-Roman,25"')
g.set(key='autotitle columnheader')
g.set(key='top horizontal center')
g.set(key='height -0.3')


def getfile(method, dataset, k, theta):
    for file_name in os.listdir('ExpResults/Exp_CW_query/'):
        if 'longest' not in method:
            if 'longest' in file_name:
                continue
        if method in file_name and dataset in file_name and \
           ('k'+str(k)+'_' in file_name or 'k'+str(k)+'.' in file_name) and \
           ('t'+str(theta)+'_' in file_name or 't'+str(theta)+'.' in file_name):
            return 'ExpResults/' + file_name
        
n = 10
ktics = [16, 32, 64, 128, 256]
thetatics = [0.5, 0.6, 0.7, 0.8, 0.9, 1]
# Query time vs k, n = 10
for dataset in 'openwebtext', 'PAN11', 'pile':
    for theta in thetatics:
        data = []
        for k in ktics:
            tmp = [k]
            file_name = getfile('OPH', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    sumtime += querytime
                    sumnum += 1
                tmp.append(sumtime / sumnum)
                
            file_name = getfile('OPH_longest', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    sumtime += querytime
                    sumnum += 1
                tmp.append(sumtime / sumnum)
            
            data.append(tmp)
        g.set(output='"' + f'Figures/test/{dataset}_querytime_vs_k_theta{theta}.eps' + '"')
        df = pd.DataFrame(data)
        g.plot_data(df, 'using 3:xtic(2) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 7', 'using 4 with lp title "OPHlongest" lc rgb "black" lt 2 dt 2 lw 7')

# Query Time vs theta
for dataset in 'openwebtext', 'PAN11', 'pile':
    for k in ktics:
        data = []
        for theta in thetatics:
            tmp = [theta]
            file_name = getfile('OPH', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    sumtime += querytime
                    sumnum += 1
                tmp.append(sumtime / sumnum)
                
            file_name = getfile('OPH_longest', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    sumtime += querytime
                    sumnum += 1
                tmp.append(sumtime / sumnum)
            
            data.append(tmp)
        g.set(output='"' + f'Figures/test/{dataset}_querytime_vs_theta_k{k}.eps' + '"')
        df = pd.DataFrame(data)
        g.plot_data(df, 'using 3:xtic(2) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 7', 'using 4 with lp title "OPHlongest" lc rgb "black" lt 2 dt 2 lw 7')
           
# Query time vs m, n = 10
for dataset in 'openwebtext', 'PAN11', 'pile':
    for theta in thetatics:
        for k in ktics:
            dataOPH = {}
            dataOPH_longest = {}
            dataKMINS = {}
            file_name = getfile('OPH', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    if collided in dataOPH:
                        dataOPH[collided].append(querytime)
                    else:
                        dataOPH[collided] = [querytime]
            
            file_name = getfile('OPH_longest', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    if collided in dataOPH_longest:
                        dataOPH_longest[collided].append(querytime)
                    else:
                        dataOPH_longest[collided] = [querytime]

            tmp = []
            for key in sorted(dataOPH.keys()):
                tmp.append([key, sum(dataOPH[key])/len(dataOPH[key])])
            dataOPH = tmp
            
            tmp = []
            for key in sorted(dataOPH_longest.keys()):
                tmp.append([key, sum(dataOPH_longest[key])/len(dataOPH_longest[key])])
            dataOPH_longest = tmp
            
            data = []
            for i in range(max(len(dataOPH), len(dataOPH_longest))):
                tmp = []
                if i < len(dataOPH):
                    tmp.append(dataOPH[i][0])
                    tmp.append(dataOPH[i][1])
                if i < len(dataOPH_longest):
                    tmp.append(dataOPH_longest[i][0])
                    tmp.append(dataOPH_longest[i][1])
                data.append(tmp)
            
            g.set(output='"' + f'Figures/test/{dataset}_querytime_vs_m_k{k}_theta{theta}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 2:3 with lp title "OPH" lc rgb "black" lt -1 dt 1 lw 1', 'using 4:5 with lp title "OPHlongest" lc rgb "red" lt -1 dt 1 lw 1')

# Query time vs results, n = 10
for dataset in 'openwebtext', 'PAN11', 'pile':
    for theta in thetatics:
        for k in ktics:
            dataOPH = {}
            dataKMINS = {}
            dataOPH_longest = {}
            file_name = getfile('OPH', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    if results in dataOPH:
                        dataOPH[results].append(querytime)
                    else:
                        dataOPH[results] = [querytime]
                        
            file_name = getfile('OPH_longest', dataset, k, theta)
            with open(file_name, 'r') as f:
                f.readline()
                f.readline()
                f.readline()
                f.readline()
                sumnum = 0
                sumtime = 0
                while True:
                    collided = f.readline()
                    if collided == '':
                        break
                    collided = int(collided)
                    results = int(f.readline())
                    querytime = float(f.readline())
                    if results in dataOPH_longest:
                        dataOPH_longest[results].append(querytime)
                    else:
                        dataOPH_longest[results] = [querytime]


            tmp = []
            for key in sorted(dataOPH.keys()):
                tmp.append([key, sum(dataOPH[key])/len(dataOPH[key])])
            dataOPH = tmp
            
            tmp = []
            for key in sorted(dataOPH_longest.keys()):
                tmp.append([key, sum(dataOPH_longest[key])/len(dataOPH_longest[key])])
            dataOPH_longest = tmp
            
            data = []
            for i in range(max(len(dataOPH), len(dataOPH_longest))):
                tmp = []
                if i < len(dataOPH):
                    tmp.append(dataOPH[i][0])
                    tmp.append(dataOPH[i][1])
                if i < len(dataOPH_longest):
                    tmp.append(dataOPH_longest[i][0])
                    tmp.append(dataOPH_longest[i][1])
                data.append(tmp)
            
            g.set(output='"' + f'Figures/test/{dataset}_querytime_vs_res_k{k}_theta{theta}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 2:3 with lp title "OPH" lc rgb "black" lt -1 dt 1 lw 1', 'using 4:5 with lp title "OPHlongest" lc rgb "red" lt -1 dt 1 lw 1')