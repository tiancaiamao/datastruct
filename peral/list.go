package main

import (
	"fmt"
)

type Node struct {
	v    int
	next *Node
}

func insert(n **Node, v int) *Node {
	p := &Node{
		v: v,
	}

	if n == nil {
		return p
	}
	if *n == nil {
		*n = p
		return p
	}

	p.next = (*n).next
	(*n).next = p
	return p
}

func merge(h1, h2 *Node) *Node {
	if h1 == nil {
		return h2
	}
	if h2 == nil {
		return h1
	}

	var ret *Node
	if h1.v > h2.v {
		ret = h1
		h1 = h1.next
	} else {
		ret = h2
		h2 = h2.next
	}

	p := ret
	for h1 != nil && h2 != nil {
		if h1.v > h2.v {
			p.next = h1
			p = h1
			h1 = h1.next
		} else {
			p.next = h2
			p = h2
			h2 = h2.next
		}
	}
	if h1 == nil {
		p.next = h2
	} else {
		p.next = h1
	}

	return ret
}

func main() {
	var head *Node
	p := insert(&head, 6)
	p = insert(&p, 5)
	p = insert(&p, 4)
	p = insert(&p, 3)
	p = insert(&p, 2)
	p = insert(&p, 1)
	for p := head; p != nil; p = p.next {
		fmt.Printf("%d ", p.v)
	}

	var h2 *Node
	p = insert(&h2, 22)
	p = insert(&p, 18)
	p = insert(&p, 13)
	p = insert(&p, 12)
	p = insert(&p, 8)
	p = insert(&p, 4)
	p = insert(&p, 3)
	for p := h2; p != nil; p = p.next {
		fmt.Printf("%d ", p.v)
	}

	fmt.Println()
	c := merge(h2, head)
	for p := c; p != nil; p = p.next {
		fmt.Printf("%d ", p.v)
	}
}
