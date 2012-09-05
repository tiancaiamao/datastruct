package main

import (
	"rbtree"
	"fmt"
	"os"
)

type Int int
func (v1 Int) Less(v2 rbtree.Interface) bool{
	tv2,ok := v2.(Int)
	if !ok {
		fmt.Fprintf(os.Stderr,"Fatal error:can't use Less between Int and Non Int")
		os.Exit(-1)
	}
	return v1<tv2
}
func (v1 Int) Equal(v2 rbtree.Interface) bool{
	tv2,ok := v2.(Int)
	if !ok {
		fmt.Fprintf(os.Stderr,"Fatal error:can't use Less between Int and Non Int")
		os.Exit(-1)
	}
	return v1==tv2
}

func main() {
	tree := rbtree.New()
	 tree.Insert(Int(12))
	 tree.Insert(Int(1))
	 tree.Insert(Int(9))
	 tree.Insert(Int(2))
	 tree.Insert(Int(0))
	 tree.Insert(Int(11))
	 tree.Insert(Int(7))
	 tree.Insert(Int(19))
	 tree.Insert(Int(4))
	 tree.Insert(Int(15))
	 tree.Insert(Int(18))
	 tree.Insert(Int(5))
	 tree.Insert(Int(14))
	 tree.Insert(Int(13))
tree.Insert(Int(10))
tree.Insert(Int(16))
tree.Insert(Int(6))
tree.Insert(Int(3))
tree.Insert(Int(8))
tree.Insert(Int(17))
	tree.Dump()
}