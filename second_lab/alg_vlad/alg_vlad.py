def get_coeffs(x: list, y: list):
	def f_n(idxs: list):
		n = len(idxs)
		if n == 1:
			return y[idxs[0]]
		res = (f_n(idxs[1:]) - f_n(idxs[:-1])) / (x[idxs[-1]] - x[idxs[-1] - n + 1])
		return res

	b = []
	for i in range(1, len(x) + 1):
		b.append(f_n(list(range(i))))
	return b


def get_coeffs2(x, y):
	n = len(y)
	m = [y]
	b = [y[0]]
	for i in range(1, n):
		m.append([])
		for j in range(n - i):
			f_n = (m[i-1][j+1] - m[i-1][j])/(x[j+i] - x[j])
			m[i].append(f_n)
		b.append(m[i][0])
	return b



x = [1, -2, 3, 0, -1]
y = [2, 17, 82, 1, 2]

print(get_coeffs(x, y))
print(get_coeffs2(x, y))