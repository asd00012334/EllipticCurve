from random import randint


def geneBigInt(m):
	radix = randint(0, m)
	if randint(1, 2) == 1:
		print('-', end='')
	print(randint(1, 9), end='')
	for i in range(radix - 1):
		print(randint(0, 9), end='')
	

def gene(n, m, op):
	for _ in range(n):
		geneBigInt(m)
		print(' ' + op + ' ', end='')
		geneBigInt(m)
		print()

n, m = [int(x) for x in input().split()]
gene(n, m, '+')
gene(n, m, '-')
