
n = input()
base_a = int(input())
base_b = int(input())

n_base_10 = 0
for i in range(len(n)):
	n_base_10 += int(n[-(i + 1)]) * base_a ** i

result = ''
while n_base_10 > 0:
	result = str(n_base_10 % base_b) + result
	n_base_10 //= base_b

print(result)
