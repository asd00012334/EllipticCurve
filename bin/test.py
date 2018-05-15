#!/usr/bin/env python3
try:
	while 1:
		print(">>> ", end='')
		inp = input()
		print(inp, "=", eval(inp))
except EOFError:
	print()
	pass
