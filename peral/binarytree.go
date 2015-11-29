package main

import (
	"fmt"
)

type Node struct {
	V     byte
	Left  *Node
	Right *Node
}

type Stack struct {
	arr []*Node
	top int
}

func NewStack(cap int) *Stack {
	ret := &Stack{
		arr: make([]*Node, cap),
	}
	return ret
}

func (s *Stack) Top() *Node {
	return s.arr[s.top-1]
}

func (s *Stack) Push(n *Node) {
	s.arr[s.top] = n
	s.top++
}

func (s *Stack) Pop() *Node {
	s.top--
	return s.arr[s.top]
}

func (s *Stack) Empty() bool {
	return s.top <= 0
}

func PreOrderNaive(tree *Node) {
	if tree == nil {
		return
	}

	fmt.Printf("%c", tree.V)
	PreOrderNaive(tree.Left)
	PreOrderNaive(tree.Right)
}

func PreOrder(tree *Node) {
	if tree == nil {
		return
	}

	s := NewStack(20)
	s.Push(tree)

	for !s.Empty() {
		n := s.Pop()
		fmt.Printf("%c", n.V)

		if n.Right != nil {
			s.Push(n.Right)
		}

		if n.Left != nil {
			s.Push(n.Left)
		}
	}
}

func MidOrder(root *Node) {
	s := NewStack(20)

	for ; root != nil; root = root.Left {
		s.Push(root)
	}

	for !s.Empty() {
		n := s.Pop()
		fmt.Printf("%c", n.V)

		for n = n.Right; n != nil; n = n.Left {
			s.Push(n)
		}
	}
}

type Queue struct {
	arr []*Node
	tail int
	front int
}

func NewQueue(cap int) *Queue {
	return &Queue{
		arr: make([]*Node, cap),
	}
}

func (q *Queue) Empty() bool {
	return q.front == q.tail
}

func (q *Queue) Push(n *Node) {
	q.arr[q.tail] = n
	q.tail = (q.tail + 1) % len(q.arr)
	return
}

func (q *Queue) Pop() *Node {
	ret := q.arr[q.front]
	q.front = (q.front + 1) % len(q.arr)
	return ret
}

func LevelOrder(root *Node) {
	q := NewQueue(20)
	q.Push(root)
	last := root
	
	for !q.Empty() {
		n := q.Pop()
		fmt.Printf("%c", n.V)
		
		if last == n {
			fmt.Println()
			if n.Right != nil {
				last = n.Right
			} else {
				last = n.Left
			}
		}
		
		if n.Left != nil {
			q.Push(n.Left)
		}
		if n.Right != nil {
			q.Push(n.Right)
		}
	}
}

func PostOrder(root *Node) {
	p := root
	var lastVisit *Node
	s := NewStack(20)

	for p != nil || !s.Empty() {
		if p != nil {
			s.Push(p)
			p = p.Left
		} else {
			p = s.Top()
			if p.Right == nil || p.Right == lastVisit {
				s.Pop()
				fmt.Printf("%c", p.V)
				lastVisit = p
				p = nil
				continue
			}
			p = p.Right
		}
	}
}

func main() {
	a := &Node{V: 'a'}
	b := &Node{V: 'b'}
	c := &Node{V: 'c'}
	d := &Node{V: 'd'}
	e := &Node{V: 'e'}
	f := &Node{V: 'f'}
	g := &Node{V: 'g'}

	a.Left = b
	a.Right = c
	b.Left = d
	b.Right = e
	e.Right = f
	c.Left = g

	LevelOrder(a)
}
