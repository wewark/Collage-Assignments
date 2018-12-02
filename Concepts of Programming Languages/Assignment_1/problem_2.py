import math

n = int(input())

result = []
for i in range(1, int(math.sqrt(n)) + 1):
	if n % i == 0:
		result.append(i)
		if n // i != i:
			result.append(n // i)

result.sort()
for i in result:
	print(i)
