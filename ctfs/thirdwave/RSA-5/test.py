from Crypto.Util.number import long_to_bytes, bytes_to_long, getPrime, inverse
import decimal

flag= b'test123123123123123123123asdlolquestoeunmessaggio molto lungo giu'

p,q = getPrime(512), getPrime(512)
n = p*q

decimal.getcontext().prec = n.bit_length()

e = 65537
m = bytes_to_long(flag)

k = 2

req = pow(m,e,n)
req2 = pow(m,e,n) ** k

phi = (p-1)*(q-1)
d = inverse(e,phi)
dec = pow(int(req),d,n)
dec2 = pow(int(req2),d,n)
#assert dec != m
print(f"dec = {dec}")
print(f"dec2 = {dec2}")

root  = decimal.Decimal(dec2) ** (decimal.Decimal(1.0) / decimal.Decimal(2) ) 
print(f"dec2-k = {int(root)}")

print(long_to_bytes(dec).decode())
print(long_to_bytes(int(root)).decode())