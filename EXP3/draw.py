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
# g.set(yrange='[0:0.9]')
# g.set(logscale='y')
# g.set(format='y "10^{%L}"')
g.set(xtics='font "Times-Roman,25"')
g.set(key='autotitle columnheader')
g.set(key='top horizontal center')
g.set(key='height -0.3')

Exp_path = '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/results/EXP3/'
Out_path = './EXP3/Figures/'

def getfile(method, dataset, k, theta, m):
    for file_name in os.listdir(Exp_path):
        if method in file_name and dataset in file_name and \
           ('k'+str(k)+'_' in file_name or 'k'+str(k)+'.' in file_name) and \
           ('t'+str(theta)+'_' in file_name or 't'+str(theta)+'.' in file_name) and \
           ('m'+str(m)+'_' in file_name or 'm'+str(m)+'.' in file_name):
            return Exp_path + file_name
        
def skip_start(file_name, f):
    if 'OPH' in file_name:
        f.readline()
        f.readline()
        f.readline()
    else:
        f.readline()

def get_data(f):
    collided = f.readline()
    if collided == '':
        return None, None, None
    collided = int(collided)
    results = int(f.readline())
    querytime = float(f.readline())
    return collided, results, querytime

def get_avg_t(file_name):
    f = open(file_name, 'r')
    skip_start(file_name, f)
    sumnum = 0
    sumtime = 0
    while True:
        collided, results, querytime = get_data(f)
        if collided == None:
            break
        sumtime += querytime
        sumnum += 1
    return sumtime / sumnum
        

# Query time vs k
def t_vs_k(datasets, ktics, thetatics):
    for dataset in datasets:
        for theta in thetatics:
            data = []
            for k in ktics:
                tmp = [k]
                file_name = getfile('OPH', dataset, k, theta, 0)
                tmp.append(get_avg_t(file_name))
                file_name = getfile('OPH', dataset, k, theta, 1)
                tmp.append(get_avg_t(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 0)
                tmp.append(get_avg_t(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 1)
                tmp.append(get_avg_t(file_name))

                data.append(tmp)
                
            g.set(output='"' + f'{Out_path}{dataset}_querytime_vs_k_theta{theta}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 5', 'using 4 with lp title "OPHlongest" lc rgb "black" lt 2 dt 2 lw 5', 'using 5 with lp title "KMINS" lc rgb "black" lt 3 dt 3 lw 5', 'using 6 with lp title "KMINSintervalscan" lc rgb "black" lt 4 dt 4 lw 5')

# Query Time vs theta
def t_vs_theta(datasets, ktics, thetatics):
    for dataset in datasets:
        for k in ktics:
            data = []
            for theta in thetatics:
                tmp = [theta]
                file_name = getfile('OPH', dataset, k, theta, 0)
                tmp.append(get_avg_t(file_name))
                file_name = getfile('OPH', dataset, k, theta, 1)
                tmp.append(get_avg_t(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 0)
                tmp.append(get_avg_t(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 1)
                tmp.append(get_avg_t(file_name))
                data.append(tmp)
                
            g.set(output='"' + f'{Out_path}{dataset}_querytime_vs_theta_k{k}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 5', 'using 4 with lp title "OPHlongest" lc rgb "black" lt 2 dt 2 lw 5', 'using 5 with lp title "KMINS" lc rgb "black" lt 3 dt 3 lw 5', 'using 6 with lp title "KMINSintervalscan" lc rgb "black" lt 4 dt 4 lw 5')
            
def get_t_vs_m_data(file_name):
    data = {}
    f = open(file_name, 'r')
    skip_start(file_name, f)
    while True:
        collided, results, querytime = get_data(f)
        if collided == None:
            break
        if collided in data:
            data[collided].append(querytime)
        else:
            data[collided] = [querytime]
    tmp = []
    for key in sorted(data.keys()):
        tmp.append([key, sum(data[key])/len(data[key])])
    return tmp

def get_t_vs_res_data(file_name):
    data = {}
    f = open(file_name, 'r')
    skip_start(file_name, f)
    while True:
        collided, results, querytime = get_data(f)
        if collided == None:
            break
        if results in data:
            data[results].append(querytime)
        else:
            data[results] = [querytime]
    tmp = []
    for key in sorted(data.keys()):
        tmp.append([key, sum(data[key])/len(data[key])])
    return tmp

def merge(*args):
    data = []
    maxlen = 0
    
    for item in args:
        maxlen = max(maxlen, len(item))
    
    for i in range(maxlen):
        tmp = []
        for item in args:
            if i < len(item):
                tmp.append(item[i][0])
                tmp.append(item[i][1])
            else:
                tmp.append(item[-1][0])
                tmp.append(item[-1][1])
        data.append(tmp)
        
    return data
           
# Query time vs m
def t_vs_m(datasets, ktics, thetatics):
    for dataset in datasets:
        for theta in thetatics:
            for k in ktics:
                file_name = getfile('OPH', dataset, k, theta, 0)
                dataOPH = get_t_vs_m_data(file_name)
                file_name = getfile('OPH', dataset, k, theta, 1)
                dataOPH_longest = get_t_vs_m_data(file_name)
                file_name = getfile('KMINS', dataset, k, theta, 0)
                dataKMINS = get_t_vs_m_data(file_name)
                file_name = getfile('KMINS', dataset, k, theta, 1)
                dataKMINS_scan = get_t_vs_m_data(file_name)
            
                data = merge(dataOPH, dataOPH_longest, dataKMINS, dataKMINS_scan)
                
                g.set(output='"' + f'{Out_path}{dataset}_querytime_vs_m_k{k}_theta{theta}.eps' + '"')
                df = pd.DataFrame(data)
                g.plot_data(df, 'using 2:3 with lp title "OPH" smooth bezier lc rgb "black" lt 1 dt 1 lw 3', 'using 4:5 with lp title "OPHlongest" smooth bezier lc rgb "black" lt 2 dt 2 lw 3', 'using 6:7 with lp title "KMINS" smooth bezier lc rgb "black" lt 3 dt 3 lw 3', 'using 8:9 with lp title "KMINSintervalscan" smooth bezier lc rgb "black" lt 4 dt 4 lw 3')

# Query time vs results
def t_vs_res(datasets, ktics, thetatics):
    for dataset in datasets:
        for theta in thetatics:
            for k in ktics:
                file_name = getfile('OPH', dataset, k, theta, 0)
                dataOPH = get_t_vs_res_data(file_name)
                file_name = getfile('OPH', dataset, k, theta, 1)
                dataOPH_longest = get_t_vs_res_data(file_name)
                file_name = getfile('KMINS', dataset, k, theta, 0)
                dataKMINS = get_t_vs_res_data(file_name)
                file_name = getfile('KMINS', dataset, k, theta, 1)
                dataKMINS_scan = get_t_vs_res_data(file_name)
                
                data = merge(dataOPH, dataOPH_longest, dataKMINS, dataKMINS_scan)

                g.set(output='"' + f'{Out_path}{dataset}_querytime_vs_res_k{k}_theta{theta}.eps' + '"')
                df = pd.DataFrame(data)
                g.plot_data(df, 'using 2:3 with lp title "OPH" smooth bezier lc rgb "black" lt 1 dt 1 lw 3', 'using 4:5 with lp title "OPHlongest" smooth bezier lc rgb "black" lt 2 dt 2 lw 3')#'using 6:7 with lp title "KMINS" smooth bezier lc rgb "black" lt 3 dt 3 lw 3', 'using 8:9 with lp title "KMINSintervalscan" smooth bezier lc rgb "black" lt 4 dt 4 lw 3')
                
def get_avg_m(file_name):
    f = open(file_name, 'r')
    skip_start(file_name, f)
    sumnum = 0
    summ = 0
    while True:
        collided, results, querytime = get_data(f)
        if collided == None:
            break
        summ += collided
        sumnum += 1
    return summ / sumnum
        

# m vs k
def m_vs_k(datasets, ktics, thetatics):
    for dataset in datasets:
        for theta in thetatics:
            data = []
            for k in ktics:
                tmp = [k]
                file_name = getfile('OPH', dataset, k, theta, 0)
                tmp.append(get_avg_m(file_name))
                file_name = getfile('OPH', dataset, k, theta, 1)
                tmp.append(get_avg_m(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 0)
                tmp.append(get_avg_m(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 1)
                tmp.append(get_avg_m(file_name))

                data.append(tmp)
                
            g.set(output='"' + f'{Out_path}{dataset}_m_vs_k_theta{theta}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 5', 'using 4 with lp title "OPHlongest" lc rgb "black" lt 2 dt 2 lw 5', 'using 5 with lp title "KMINS" lc rgb "black" lt 3 dt 3 lw 5', 'using 6 with lp title "KMINSintervalscan" lc rgb "black" lt 4 dt 4 lw 5')
            
def m_vs_theta(datasets, ktics, thetatics):
    for dataset in datasets:
        for k in ktics:
            data = []
            for theta in thetatics:
                tmp = [theta]
                file_name = getfile('OPH', dataset, k, theta, 0)
                tmp.append(get_avg_m(file_name))
                file_name = getfile('OPH', dataset, k, theta, 1)
                tmp.append(get_avg_m(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 0)
                tmp.append(get_avg_m(file_name))
                file_name = getfile('KMINS', dataset, k, theta, 1)
                tmp.append(get_avg_m(file_name))
                data.append(tmp)
                
            g.set(output='"' + f'{Out_path}{dataset}_m_vs_theta_k{k}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) with lp title "OPH" lc rgb "black" lt 1 dt 1 lw 5', 'using 4 with lp title "OPHlongest" lc rgb "black" lt 2 dt 2 lw 5', 'using 5 with lp title "KMINS" lc rgb "black" lt 3 dt 3 lw 5', 'using 6 with lp title "KMINSintervalscan" lc rgb "black" lt 4 dt 4 lw 5')
            
if __name__ == '__main__':
    ktics = [16, 32, 64, 128, 256]
    thetatics = [0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    t_vs_k(datasets=['suspsource'], ktics=ktics, thetatics=thetatics)
    t_vs_theta(datasets=['suspsource'], ktics=ktics, thetatics=thetatics)
    t_vs_m(datasets=['suspsource'], ktics=ktics, thetatics=thetatics)
    t_vs_res(datasets=['suspsource'], ktics=ktics, thetatics=thetatics)
    m_vs_k(datasets=['suspsource'], ktics=ktics, thetatics=thetatics)
    m_vs_theta(datasets=['suspsource'], ktics=ktics, thetatics=thetatics)