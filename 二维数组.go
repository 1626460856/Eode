package main

import "fmt"

func main() {
	x := 4
	y := 4
	a := make([][]int, y)
	for i := 0; i < y; i++ {
		a[i] = make([]int, x)
		for j := 0; j < x; j++ {
			a[i][j] = j + 1 + (i+1)*10
		}
	}
	for i := 0; i < y; i++ {

		fmt.Println(a[i])

	}

}
