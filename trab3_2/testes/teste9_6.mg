fun main () : []int

	c : []int
	b : [][]int
	f : [][][]char

	c = new [4] int
	b = new [5][] int
	f = new [5][][] char

	f[5] = new [2][] char

	c = b[5]

	c[2] = 1

	c = f[4][9]

	return c
end
