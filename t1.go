package main

import(
	"fmt"
)

func main() {
	a := 10.000
	b := 1.2
	c := 1 + 2.12i
	d := "this is so random!"
	e := 'x'

	a = a + b
	a = a - b
	a = a * b
	a = a / b


	m := make(map[int]int)
	m[1] = 2
	m[2] = 4

	m[3] = m[2] % m[1]
	m[3] += m[2]
	m[3] -= m[2]
	m[3] *= m[2]
	m[3] /= m[2]
	m[3] %= m[2]
	m[3] << 1
	var ck1, ck2 bool
	ck1 = true
	ck2 = false

	ck1 = ck2 && ck1
	ck2 = ck1 || ck2
	ck2 |= ck1

	ck1 &= ck2

	fmt.Println(a, b, c)
	fmt.Println(d, e)
}
