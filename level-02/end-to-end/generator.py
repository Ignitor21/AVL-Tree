import random
import os

requests = []
req_set = set()

N = int(input("Enter number of requests: "))
size = 0

all_files = os.listdir()
max_test_number = 0
for file in all_files:
    if file.endswith('.in'):
        test_number = int(file[:-3])
        if (test_number > max_test_number):
            max_test_number = test_number

for i in range(N):
    j = random.randint(-N, N)

    if j % 3 == 0 or size <= 0.2*N:
        requests.append('k')
        num = random.randint(-N, N)
        requests.append(str(num))
        if not(num in req_set):
            size += 1
            req_set.add(num)
    if (j % 3 == 1) and (size > 0.2*N):
        requests.append('m')
        num1 = str(random.randint(1, size))
        print("Число:", num1)
        print("Размер дерева:", size)
        requests.append(num1)
    if (j % 3 == 2) and (size > 0.2*N):
        requests.append('n')
        requests.append(str(random.randint(-1* int(1.1*N), int(1.1*N))))

with open(str(max_test_number + 1).zfill(3) + ".in", "w") as f:
    f.write(" ".join(requests))
