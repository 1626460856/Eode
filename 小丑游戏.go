package main

import (
	"fmt"
	"math/rand"
)

type Clown int

func (c Clown) String() string {
	if c == 0 {
		return "小丑"
	}
	if c == 1 {
		return "深情"
	}

	{
		return fmt.Sprintf("%d", c)
	}
}
func main() {
	m1 := make(map[string]int, 8)
	m1["1"] = 2

	x, y := 4, 4
	a := make([][]int, y)
	for i := 0; i < y; i++ {
		a[i] = make([]int, x) // 为每一行分配空间
		for j := 0; j < x; j++ {
		}
	}
	var i = rand.Intn(4) // 生成一个 0~3 之间的随机整数
	var j = rand.Intn(4)
	a[i][j] = 1

	for i := 0; i < 4; i++ {
		var m, n int
		fmt.Println("你还有", (4 - i), "次机会，在4*4的坐标位点中有1个深情，15个舔狗，请依次输入1-4的两个数作为坐标尝试吧")
		fmt.Scan(&m, &n)
		k := a[m-1][n-1]
		if k == 0 || k == 1 {
			fmt.Println(Clown(k))
			a[m-1][n-1] = 3
		}
		if k == 3 {
			fmt.Println("请试试其他位置")
		}
	}
	for i := 0; i < y; i++ {

		fmt.Println(a[i])
	}

}
