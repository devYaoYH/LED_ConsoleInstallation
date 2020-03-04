def serialize_snake_grid(zero, dims):
	grid = [[0 for i in range(dims)] for j in range(dims)]
	odd_row = True
	c_r = 0
	c_c = 0
	for i in range(zero, dims*dims+zero):
		print(f"{c_r}, {c_c} | {odd_row}")
		grid[c_r][c_c] = i
		if ((c_c == dims-1 and odd_row) or (c_c == 0 and not odd_row)):
			c_r += 1
			c_c = dims-1 if odd_row else 0
			odd_row = not odd_row
		else:
			c_c += 1 if odd_row else -1
	return grid

if (__name__ == "__main__"):
	grid = serialize_snake_grid(1, 7)
	grid_array = ["{" + ",".join([str(i) for i in line]) + "}" for line in grid]
	print("{" + ',\n'.join(grid_array) + "}")