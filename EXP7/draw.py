import os
import pandas as pd

path = '/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/index0/'

def getfile(method, dataset, k, l):
    for file_name in os.listdir(path):
        if method in file_name and dataset in file_name and \
           ('k'+str(k)+'_' in file_name or 'k'+str(k)+'.' in file_name) and \
           ('l'+str(l)+'_' in file_name or 'l'+str(l)+'.' in file_name):
            return path + file_name

def t_vs_k(datasets, ltics, ktics):
    for dataset in datasets:
        for l in ltics:
            data = []
            for k in ktics:
                tmp = [k]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / 100)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / 100)
                data.append(tmp)
            df = pd.DataFrame(data)
            print(dataset, 't_vs_k')
            print(df)

def ncws_vs_k(datasets, ltics, ktics):
    for dataset in datasets:
        for l in ltics:
            data = []
            for k in ktics:
                tmp = [k]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / 100 + int(f.readline().strip()) / 100)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / 100)
                data.append(tmp)
            df = pd.DataFrame(data)
            print(dataset, 'ncws_vs_k')
            print(df)

def t_vs_l(datasets, ltics, ktics):
    for dataset in datasets:
        for k in ktics:
            data = []
            for l in ltics:
                tmp = [l]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / 100)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    tmp.append(float(f.readline().strip()) / 100)
                data.append(tmp)
            df = pd.DataFrame(data)
            print(dataset, 't_vs_l')
            print(df)

def ncws_vs_l(datasets, ltics, ktics):
    for dataset in datasets:
        for k in ktics:
            data = []
            for l in ltics:
                tmp = [l]
                file_name = getfile('OPH', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / 100 + int(f.readline().strip()) / 100)
                file_name = getfile('KMINS', dataset, k, l)
                with open(file_name, 'r') as f:
                    f.readline()
                    tmp.append(int(f.readline().strip()) / 100)
                data.append(tmp)
            df = pd.DataFrame(data)
            print(dataset, 'ncws_vs_l')
            print(df)


# ktics = [16, 32, 64, 128, 256]
# ltics = [100, 1000, 10000, 100000]
t_vs_k(['openwebtext', 'PAN11', 'wiki'], [10000], [16, 32, 64, 128, 256])
ncws_vs_k(['openwebtext', 'PAN11', 'wiki'], [10000], [16, 32, 64, 128, 256])
t_vs_l(['openwebtext', 'PAN11', 'wiki'], [100, 1000, 10000, 100000], [64])
ncws_vs_l(['openwebtext', 'PAN11', 'wiki'], [100, 1000, 10000, 100000], [64])