fun main () : []int

	c : []int
	b : [][]int
	f : [][][]char
	g : []bool

	f = new [5][][] char
	f[4] = new [2][] char
	f[5][1] = new [2] char

	g = new [1] bool

	c = f[4][9]

	b[5][5] = c[1] - 6 + 8

	return c
end

