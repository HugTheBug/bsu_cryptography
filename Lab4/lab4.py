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


def phi(p, q):
    return (p - 1) * (q - 1)


def get_d(p, q, e):
    return inverse(e, phi(p, q))


def encrypt(x, e, n):
    return pow(x, e, n)


def decrypt(y, d, n):
    return pow(y, d, n)


def main():
    p = 684391453787369
    q = 938396705691661
    e = 245372344253915653531369256899

    d = get_d(p, q, e)
    n = p * q

    x1 = 184712154522842417799563173273
    y1 = 447204864183801463638208868116

    print('d : {0} \nEncrypted : {1} \nDecrypted : {2}'.format(d, encrypt(x1, e, n), decrypt(y1, d, n)))


main()

