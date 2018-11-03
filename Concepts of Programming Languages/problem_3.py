
def armstrong(x):
    digits = str(x)
    num_digits = len(digits)

    result = 0
    for digit in digits:
        result += int(digit) ** num_digits

    return result == x


start, end = input().split()
start = int(start)
end = int(end)

for i in range(start, end + 1):
	if armstrong(i):
		print(i)
