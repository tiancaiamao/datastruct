package main

import (
	"fmt"
)

type Edge struct {
	vertex int
	next   *Edge
}

type Graph struct {
	edges []*Edge
	vNum  int
}

func NewGraph(numVertex int) *Graph {
	ret := new(Graph)
	ret.vNum = numVertex
	ret.edges = make([]*Edge, numVertex)
	return ret
}

func (g *Graph) AddEdge(from, to int) {
	head := g.edges[from]
	e := &Edge{
		vertex: to,
	}
	if head == nil {
		g.edges[from] = e
	} else {
		e.next = head.next
		head.next = e
	}
}

func DFS(g *Graph) {
	visited := make([]bool, g.vNum)
	
	dfs(g, 0, visited)
}

func dfs(g *Graph, v int, visited []bool) {
	if visited[v] {
		return
	}
	
	fmt.Println(v)
	visited[v] = true	
	
	for e := g.edges[v]; e != nil; e = e.next {
		dfs(g, e.vertex, visited)
	}
}

func main() {
	// 0->1 0->2
	// 1->2 1->3
	// 2->3
	// 3->0

	g := NewGraph(4)
	g.AddEdge(0, 1)
	g.AddEdge(0, 2)
	g.AddEdge(1, 2)
	g.AddEdge(1, 3)
	g.AddEdge(2, 3)
	g.AddEdge(3, 0)

	DFS(g)
}
