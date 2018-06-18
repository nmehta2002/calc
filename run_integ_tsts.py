#!/usr/bin/python

import subprocess

cmd = './calc divider 1 2'
cmdout = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
cmdouts = cmdout.split()
result = float(cmdouts[-1])
assert(result == 0.5)

print 'Divider command line input succeeded.'

file = open('numbers1.txt', 'w')
float_numbers = '2.0 8.0'
file.write(float_numbers)
file.close()

file = open('numbers2.txt', 'w')
float_numbers = '1.0'
file.write(float_numbers)
file.close()

cmd = './calc divider numbers1 numbers2'
cmdout = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
cmdouts = cmdout.split()
result = float(cmdouts[-1])
assert(result == 0.25)
print 'Divider file input succeeded.'

cmd = './calc multiplier numbers1 numbers2'
cmdout = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
cmdouts = cmdout.split()
result = float(cmdouts[-1])
assert(result == 16)
print 'Multipliers file input succeeded.'


