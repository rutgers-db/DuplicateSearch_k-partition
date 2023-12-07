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
g.set(logscale='y')
g.set(format='y "10^{%L}"')
g.set(xtics='font "Times-Roman,25"')
g.set(key='autotitle columnheader')
g.set(key='top horizontal center')
g.set(key='height -0.3')

Exp_path = 'ExpResults/EXP1/'
Out_path = 'Figures/EXP1F/'

def getfile(method, dataset, k, l):
    for file_name in os.listdir(Exp_path):
        if method in file_name and dataset in file_name and \
           ('k'+str(k)+'_' in file_name or 'k'+str(k)+'.' in file_name) and \
           ('l'+str(l)+'_' in file_name or 'l'+str(l)+'.' in file_name):
            return Exp_path + file_name

# generation time vs k
def t_vs_k(datasets, ktics, ltics, n):
    g.set(x2label='offset -12.5 "Generation Time (s)" font "Times-Roman, 30"')
    g.set(xlabel='"k, # of Hash Functions or Bins" font "Times-Roman, 30"')
    for dataset in datasets:
        for l in ltics:
            data = []
            for k in ktics:
                tmp = [k]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / n)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / n)
                data.append(tmp)
            g.set(output='"' + f'{Out_path}{dataset}_t_vs_k_l{l}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

# number of compact windows vs k
def ncws_vs_k(datasets, ktics, ltics, n):
    g.set(x2label='offset -12.5 "Number of Compact Windows" font "Times-Roman, 30"')
    g.set(xlabel='"k, # of Hash Functions or Bins" font "Times-Roman, 30"')
    for dataset in datasets:
        for l in ltics:
            data = []
            for k in ktics:
                tmp = [k]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / n)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / n)
                data.append(tmp)
            g.set(output='"' + f'{Out_path}{dataset}_ncws_vs_k_l{l}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

# generation time vs l
def t_vs_l(datasets, ktics, ltics, n):
    g.set(x2label='offset -12.5 "Generation Time (s)" font "Times-Roman, 30"')
    g.set(xlabel='"n, # Length of Sequence" font "Times-Roman, 30"')
    for dataset in datasets:
        for k in ktics:
            data = []
            for l in ltics:
                tmp = [l]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / n)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / n)
                data.append(tmp)
            g.set(output='"' + f'{Out_path}{dataset}_t_vs_l_k{k}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

# number of compact windows vs l
def ncws_vs_l(datasets, ktics, ltics, n):
    g.set(x2label='offset -12.5 "Number of Compact Windows" font "Times-Roman, 30"')
    g.set(xlabel='"n, # Length of Sequence" font "Times-Roman, 30"')
    for dataset in datasets:
        for k in ktics:
            data = []
            for l in ltics:
                tmp = [l]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / n)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / n)
                data.append(tmp)
            g.set(output='"' + f'{Out_path}{dataset}_ncws_vs_l_k{k}.eps' + '"')
            df = pd.DataFrame(data)
            g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

if __name__ == '__main__':
    ktics = [16, 32, 64, 128, 256]
    ltics = [100, 1000, 10000, 100000]
    n = 100

    t_vs_k(datasets=['openwebtext', 'PAN11', 'pile'], ktics=ktics, ltics=ltics, n=n)
    ncws_vs_k(datasets=['openwebtext', 'PAN11', 'pile'], ktics=ktics, ltics=ltics, n=n)
    t_vs_l(datasets=['openwebtext', 'PAN11', 'pile'], ktics=ktics, ltics=ltics, n=n)
    ncws_vs_l(datasets=['openwebtext', 'PAN11', 'pile'], ktics=ktics, ltics=ltics, n=n)