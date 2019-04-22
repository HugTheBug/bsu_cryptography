import random
import hashlib


def egcd(a, b):
    """return (g, x, y) such that a*x + b*y = g = gcd(a, b)"""
    if a == 0:
        return b, 0, 1
    else:
        g, x, y = egcd(b % a, a)
        return g, y - (b // a) * x, x


def inverse(a, b):
    """return x such that (x * a) % b == 1"""
    g, x, _ = egcd(a, b)
    if g == 1:
        return x % b


def modexp(a, b, n):
  if not b:
    return 1
  if b % 2:
    return a * modexp(a ** 2 % n, (b - 1) // 2, n) % n
  return modexp(a ** 2 % n, b // 2, n) % n


def get_hash(s):
    return int(hashlib.sha256(s).hexdigest(), 16)


def gen(q):
    R = random.randrange((q + 1) * 2) * 2
    R = 4 * q
    p = q * R + 1
    while modexp(2, q * R, p) != 1 or modexp(2, R, p) == 1:
        R = random.randrange((q + 1) * 2) * 2
        # print(R)
        R -= 2
        p = q * R + 1
    x = random.randrange(p)
    g = modexp(x, R, p)
    while g == 1:
        x = random.randrange(p)
        g = modexp(x, R, p)
    d = random.randrange(q)
    e = modexp(g, d, p)
    return p, g, e, d


def sign(p, q, g, d, m):
    m = get_hash(m)
    k = random.randrange(1, q)
    r = modexp(g, k, p)
    inv_k = inverse(k, q)
    s = (inv_k * (m - d * r)) % q
    return r, s


def verify(p, q, g, e, m, r, s):
    if p > r > 0 and q > s >= 0:
        m = get_hash(m)
        return modexp(e, r, p) * modexp(r, s, p) % p == modexp(g, m, p)
    else:
        return False


def main():
    q = 139917935451086595095698262488180793987376018819267640047704411792656425400927

    with open("out.txt", "w") as file:
        p, g, e, d = gen(q)
        file.write("p = {0}\n".format(p))
        file.write("g = {0}\n".format(g))
        file.write("e = {0}\n".format(e))
        file.write("d = {0}\n".format(d))
        message = "I, Denis Belov, love MiKOZI".encode("utf-8")
        r, s = sign(p, q, g, d, message)
        file.write("r = {0}\n".format(r))
        file.write("s = {0}\n".format(s))
        print(verify(p, q, g, e, message, r, s))


main()
