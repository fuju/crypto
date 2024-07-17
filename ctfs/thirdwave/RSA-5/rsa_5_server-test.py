from Crypto.Util.number import long_to_bytes, bytes_to_long, getPrime, inverse
import decimal

e = 3

def transform(k):
    return k**2

def inverse_transform(k):
    return decimal.Decimal(k) ** (decimal.Decimal(1.0) / decimal.Decimal(2) )

flag= b'test123123123123123123123asdlolquestoeunmessaggio molto lungo gi'

p,q = getPrime(512), getPrime(512)
n = p*q

decimal.getcontext().prec = n.bit_length()
m = bytes_to_long(flag)

k = 2

req = pow(m,e,n)
req2 = transform(pow(m,e,n))

phi = (p-1)*(q-1)
d = inverse(e,phi)
dec = pow(int(req),d,n)
dec2 = pow(int(req2),d,n)
#assert dec != m
print(f"dec = {dec}")
print(f"dec2 = {dec2}")

root  = inverse_transform(dec2)
print(f"dec2-inverse = {int(root)}")

print(long_to_bytes(dec).decode())
print(long_to_bytes(int(root)).decode())