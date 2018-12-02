
n = int(input())
arr = input().split()
arr = [int(i) for i in arr]
k = int(input())

arr.sort()
print(arr[k - 1])
