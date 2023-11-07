package main

import "fmt"

func main() {
	x, y, z := 4, 3, 5

	// 创建一个 y 行，每行包含 x 个元素的切片
	a := make([][][]int, y) //有y个大的元素
	for i := 0; i < y; i++ {
		// 创建一个 x 行，每行包含 z 个元素的切片
		a[i] = make([][]int, x)
		for j := 0; j < x; j++ {
			// 创建一个长度为 z 的切片
			a[i][j] = make([]int, z)
			for k := 0; k < z; k++ {
				// 初始化每个元素
				a[i][j][k] = (i+1)*100 + (j+1)*10 + k + 1
			}
		}
	}
	for i := 0; i < y; i++ {
		fmt.Println(a[i])
	}

}
