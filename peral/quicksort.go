package main

import (
	"fmt"
	"math/rand"
	"time"
)

// sort [low, high)
func QuickSort(array []int, low int, high int) {
	if high <= low {
		return
	}

	povit := low + rand.Intn(high-low)
	swap(array, povit, high-1)
	small := low
	for i := low; i < high-1; i++ {
		if array[i] < array[high-1] {
			swap(array, small, i)
			small++
		}
	}
	swap(array, high-1, small)

	QuickSort(array, low, small)
	QuickSort(array, small+1, high)
}

func QuickSort1(array []int, low int, high int) {
	if high <= low {
		return
	}

	povit := low + rand.Intn(high-low)
	save := array[povit]
	array[povit] = array[high-1]

	i := low
	j := high - 1
	for i < j {
		for i < j && array[i] <= save {
			i++
		}
		if i < j {
			array[j] = array[i]
			j--
		}

		for i < j && array[j] >= save {
			j--
		}
		if i < j {
			array[i] = array[j]
			i++
		}
	}
	array[i-1] = save

	QuickSort(array, low, i-1)
	QuickSort(array, i, high)
}

func swap(array []int, a int, b int) {
	tmp := array[a]
	array[a] = array[b]
	array[b] = tmp
	return
}

func main() {
	rand.Seed(time.Now().Unix())
	arr := make([]int, 100)
	for i := 0; i < len(arr); i++ {
		arr[i] = rand.Intn(200)
	}

	QuickSort1(arr, 0, len(arr))
	fmt.Println(arr)
	
	fmt.Println(BinSearch([]int{1, 2, 4, 9, 11, 23, 27, 31, 48}, 23))
	return
}

func BinSearch(array []int, value int) int {
	low := 0
	high := len(array)-1
	
	for low <= high {
		mid := (low + high) / 2
		switch {
		case array[mid] > value:
			high = mid - 1
		case array[mid] < value:
			low = mid + 1
		case array[mid] == value:
			return mid
		}
	}
	return -1
}
