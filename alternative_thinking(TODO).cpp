//PSEUDOCODE
total_alternating_bit = 1;	//one cause it's the minimum, like an array 11111111
for i in range(1, len(a)-1)
	if(a[i] != a[i-1])
		total_alternating_bit++
max(n, total_alternating_bit+2)

//correctess:
we have 3 cases: 
1) A has no equal adjacent bit, 
	total_alternating_bit (TAB) = n, we can flip the
	whole string and have result = n
2) A has 1 pair of equal adjacent bit. This pair defines a split point
	if the pair hase indexes (i, i+1), by flipping the prefix A[0, i]
	we obtain result = n
3) A has 2 or more pairs of equal adjacent bit. if we have a pair in (i, i+1)
	and (j, j+1), by flipping the segment A[i+1, j], we obtain result = TAB+2