#include <cstdlib>
#include <iostream>
using namespace std;

template <class T> class BSTree;
template <class T>
class Node
{
    public:
        friend class BSTree<T>;
        Node():lchild(NULL),rchild(NULL){}
    private:
        T data;
        Node<T>* lchild;
        Node<T>* rchild;
};
template <class T>
class BSTree
{
    private:
        Node<T>* root;
        void Clear(Node<T>* p);
        void Insert(const T& k,Node<T>* &p);
        void Show(Node<T>* p);
        void Delete(Node<T>* &p);
    public:
        BSTree():root(NULL){};
        ~BSTree();
        Node<T>* Find(const T& k);
        void Insert(const T& k);
        void Delete(const T& k);
        void Show(){Show(root);};
};
template <class T>
Node<T>* BSTree<T>::Find(const T& k)       //非递归实现 
{
    Node<T>* temp=root;
    while(temp!=NULL)
    {
        if(temp->data<k)
            temp=temp->lchild;
        else if(temp->data>k)
            temp=temp->rchild;
        else
            {
                return temp;
            }
    }
    return NULL;
}
template <class T>
void BSTree<T>::Show(Node<T>* p)
{
    if(p!=NULL)
    {
        Show(p->lchild);
        cout<<p->data<<' ';
        Show(p->rchild);
    }
}
template <class T>
void BSTree<T>::Insert(const T& k)
{
    Insert(k,root);
}
template <class T>
BSTree<T>::~BSTree()
{
    Clear(root);
}
template <class T>
void BSTree<T>::Clear(Node<T>* p)
{
    if(p!=NULL)
    {
        if(p->lchild!=NULL)
            Clear(p->lchild);
        if(p->rchild!=NULL)
            Clear(p->rchild);
        delete p;
    }
}
template <class T>
void BSTree<T>::Insert(const T& k,Node<T>* &p)
{
    if(p==NULL)
    {
        p=new Node<T>;
        p->data=k;
        p->lchild=NULL;
        p->rchild=NULL;
    }   
    else if(k<p->data)
        Insert(k,p->lchild);
    else if(k>p->data)
        Insert(k,p->rchild);
    else
        return;
}
template <class T>
void BSTree<T>::Delete(const T& k)
{
    Node<T>* p=Find(k);
    if(p==NULL)
        return;
    else
        Delete(p);
}
template <class T>
void BSTree<T>::Delete(Node<T>* &p)
{
    Node<T>* temp,*temp2;
    if(p->lchild!=NULL&&p->rchild!=NULL)        //p的左右都有孩子 
    {
        temp=p->rchild;
        while(temp->lchild!=NULL)
        {
            temp2=temp;
            temp=temp->lchild;
        }
        p->data=temp->data;
        Delete(temp2->lchild);
    }
    else if(p->rchild!=NULL)            //p只有右孩子 
    {
        temp=p;
        p=p->rchild;
        delete p;
    }
    else            //右孩子或无孩子 
    {
        temp=p;
        p=p->lchild;
        delete p;       
    }
}
int main(int argc, char *argv[])
{
    BSTree<int> tree;
    tree.Insert(5);
    tree.Insert(10);
    tree.Insert(12);
    tree.Insert(17);
    tree.Insert(9);
    tree.Insert(2);
    tree.Delete(5);
    tree.Insert(5);
    tree.Show();
    system("PAUSE");
    return EXIT_SUCCESS;
}
