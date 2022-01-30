import numpy as np
import argparse

def extendedEuclideanAlgorithm(a, b):
    if abs(b) > abs(a):
        (x,y,d) = extendedEuclideanAlgorithm(b, a)
        return (y,x,d)
  
    if abs(b) == 0:
        return (1, 0, a)
  
    x1, x2, y1, y2 = 0, 1, 1, 0
    while abs(b) > 0:
        q, r = divmod(a,b)
        x = x2 - q*x1
        y = y2 - q*y1
        a, b, x2, x1, y2, y1 = b, r, x1, x, y1, y
  
    return (x2, y2, a)

def inverse(n, p):
    x,y,d = extendedEuclideanAlgorithm(n, p)
    return x % p

def generate_polinomial(t, p):
    secret = np.random.randint(p)
    coefs  = np.random.randint(p, size=t-2)
    last_coef = np.random.randint(1, p)
    polinomial = np.concatenate([[secret], coefs, [last_coef]])
    return polinomial
    
    
def print_polinomial(polinomial):
    monoms = []
    for i,g_i  in enumerate(polinomial):
        if g_i == 0:
            continue
        
        mon = (str(g_i))
        
        if i > 1:
            mon += (f" x^{i}")
        elif i == 1:
            mon += (" x")
            
        monoms += [mon]
    return " + ".join(monoms)
    
def get_secret(polinomial, r_i, p):
    x = [(r_i**j % p) for j in range(len(polinomial))]
    secret = np.dot(polinomial, x) % p
    return secret 

def get_omega(i, r, t, p):
    prod = 1
    for j in range(t):
        if i != j:
            value = (r[j] * inverse( (r[i] - r[j]) % p ,  p)) % p
            prod *= value % p
    return prod % p 

parser = argparse.ArgumentParser(
    description="Shamir's secret sharing sceme.")  
parser.add_argument('p', type=int)
parser.add_argument('t', type=int)
parser.add_argument('n', type=int)

args = parser.parse_args()
 
p = args.p
t = args.t
n = args.n
r = [i for i in range(1,n+1)]

polinomial = generate_polinomial(t, p)
print(print_polinomial(polinomial))

s = []
for i,r_i in enumerate(r):
    secret = get_secret(polinomial, r_i, p)
    to_print = f"s_{i+1} = {secret}"
    print(to_print)
    s+=[secret]
    

s = s[:t]
omegas = []
for i in range(t):
    omega_i = get_omega(i, r[:t], t, p)
    omegas += [omega_i]
    print (f"\omega_{i+1} = {omega_i}")
    
    
print(np.dot(s, omegas) % p)