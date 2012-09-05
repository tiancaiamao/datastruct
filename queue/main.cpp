#include <iostream>
using namespace std;
#define maxsize 10
template <class T>
class Queue    //队列的操作有初始化,清空,析构,插入,删除,为空,长度,取元素,遍历
{
private:
	T *base;
	int front;
	int rear;
public:
	Queue();
	~Queue();
	void Insert(T e);
	void Delete(T &e);
	void Clear();
	bool IsEmpty();
	int Length();
	void GetFront(T &e);
	void Travel();
};
template <class T>
Queue<T>::Queue()
{
	base=new T[maxsize];
	front=rear=0;
}
template <class T>
void Queue<T>::Clear()
{
	front=rear;
}
template <class T>
Queue<T>::~Queue()
{
	delete [] base;
}
template <class T>
void Queue<T>::Insert(T e)
{
	rear=(rear+1)%maxsize;
	if(rear==front) return;   //队列满了,插入失败
	*(base+rear)=e;
}
template <class T>
void Queue<T>::Delete(T &e)
{
	if(front==rear) return;   //队空不能删除
	front=(front+1)%maxsize;
}
template <class T>
bool Queue<T>::IsEmpty()
{
	return front==rear;
}
template <class T>
int Queue<T>::Length()
{
	return (rear+maxsize-front)%maxsize;
}
template <class T>
void Queue<T>::GetFront(T &e)
{
	e=*(base+front+1);
}
template <class T>
void Queue<T>::Travel()
{
	if(front<rear)
	{
		for(int i=front+1;i<=rear;i++)
			cout<<*(base+i)<<' ';
	}
	else if(front>rear)
	{
		for(int i=front+1;i<=rear+maxsize;i++)
			cout<<*(base+i%maxsize)<<' ';
	}
}
/*int main()
{
	Queue <char> q;
	q.Insert('d');
	char c;
	q.GetFront(c);
	cout<<c<<q.Length()<<endl;
	return 0;
}*/