package rbtree

import "fmt"
const (
	COLOR_R = iota
	COLOR_B
)
type color_t byte
type Interface interface {
	Less(Interface) bool
	Equal(Interface) bool
}
type Node struct {
	left,right,parent *Node
	color color_t
	Value Interface
}
type Rbtree struct {
	root *Node
	current *Node
}

func newNode(v Interface) *Node {
	return &Node{
	color:COLOR_R,
	Value:v,
	}
}
func New() *Rbtree {
	return &Rbtree{}
}
func (this *Rbtree) Insert(v Interface) {
	if this.root == nil {
		this.root = &Node{color:COLOR_B,Value:v}
		this.current = this.root
		return
	}else{
		p := this.current.parent
		for ;this.current != nil; {
			if this.current.Value.Less(v) {
				p = this.current
				this.current = this.current.right
			} else if this.current.Value.Equal(v) {
				this.root = this.current
				return
			} else {
				p = this.current
				this.current = this.current.left
			}
		}
		node := newNode(v)
		if this.current == p.left {
			p.left = node
		}else{
			p.right = node
		}
		node.parent = p
		this.current = node
//		this.adjust()
	}
}
func (this *Rbtree) Dump() {
	dump(this.root,0)
}
func dump(n *Node,tab int) {
	if n != nil {
		dump(n.right,tab+1)
		for i:=0; i<tab; i++ {
			fmt.Print("\t")
		}
		var color string
		if(n.color == COLOR_R) {
			color = "r"
		}else{
			color = "b"
		}
		fmt.Printf("%v(%s)\n",n.Value,color)
		dump(n.left,tab+1)
	}
}
func (this *Rbtree) adjust() {
	n := this.current
	p := n.parent
	if p.color == COLOR_B {//pb
		this.current = this.root
		return
	}else{
		u := uncle(this.current)
		if u==nil || u.color==COLOR_R {//prur
			p.color = COLOR_B
			if u!=nil {
				u.color = COLOR_B
			}
			this.current = p.parent
			this.adjust()
		}else{//prub
			
		}
	}
}
func uncle(n *Node) (ret *Node) {
	p := n.parent
	g := p.parent
	if g.left == p {
		ret = g.right
	}else{
		ret = g.left
	}
	return
}
func (n *Rbtree) Find(v Interface) bool {
	return false
}

func (n *Rbtree) Delete(v Interface) {
} 