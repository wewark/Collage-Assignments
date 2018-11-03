
a = input()
b = input()

while len(a) < len(b):
	a = '0' + a
while len(a) > len(b):
	b = '0' + b

result = ''
carry = 0
for i in range(len(a) - 1, -1, -1):
	digit = int(a[i]) + int(b[i]) + carry
	carry = 0
	if digit > 9:
		digit = (digit + 6) % 16
		carry = 1
	result = str(digit) + result
if carry > 0:
	result = '1' + result

print(result)
