#!/usr/bin/python

import subprocess

cmd = './calc divider 8 4'
cmdout = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
cmdouts = cmdout.split()
result = int(cmdouts[-1])
assert(result == 2)

print 'Divider command line input succeeded.'

file = open('numbers1.txt', 'w')
numbers = '-8 2'
file.write(numbers)
file.close()

file = open('numbers2.txt', 'w')
numbers = '1'
file.write(numbers)
file.close()

cmd = './calc divider numbers1 numbers2'
cmdout = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
print cmdout
cmdouts = cmdout.split()
result = int(cmdouts[-1])
assert(result == -4)
print 'Divider file input succeeded.'

cmd = './calc multiplier numbers1 numbers2'
cmdout = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
cmdouts = cmdout.split()
result = int(cmdouts[-1])
assert(result == -16)
print 'Multipliers file input succeeded.'


