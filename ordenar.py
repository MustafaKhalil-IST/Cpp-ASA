from random import shuffle

n = 1000

lst = list(range(1,n+1))

shuffle(lst)

print n, " ", n-1

lel = []
for i in range(n-1):
	lel.append((lst[i], lst[i+1]))

shuffle(lel)
for i in range(len(lel)):
	print lel[i][0], " ", lel[i][1]