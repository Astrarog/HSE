import numpy as np
import argparse

def generate_matrix(m, p):
    matrix = []
    for i in range(m+1):
        zeros = np.full(i,0)
        values = np.random.randint(p, size=m+1-i)
        string = np.concatenate([zeros, values])
        matrix += [string]
    matrix = np.array(matrix)
    return matrix + np.tril(matrix.T, k=-1)   

def get_secret(matrix, r_i, p):
    secret = np.matmul(matrix, [(r_i**j % p) for j in range(len(matrix))])
    return secret % p
    
def secret_to_string(secret):
    monoms = []
    for i,g_i  in enumerate(secret):
        if g_i == 0:
            continue
        
        mon = (str(g_i))
        
        if i > 1:
            mon += (f" x^{i}")
        elif i == 1:
            mon += (" x")
            
        monoms += [mon]
    return " + ".join(monoms)    

parser = argparse.ArgumentParser(
    description="Blom's key exchange scheme.")  
parser.add_argument('p', type=int)
parser.add_argument('m', type=int)
parser.add_argument('n', type=int)

args = parser.parse_args()
 
p = args.p
m = args.m
n = args.n
r = [i for i in range(1,n+1)]

matrix = generate_matrix(m, p)
print(matrix)

for i,r_i in enumerate(r):
    secret = get_secret(matrix, r_i, p)
    to_print = f"g_{i+1}(x) = " + secret_to_string(secret)
    print(to_print)