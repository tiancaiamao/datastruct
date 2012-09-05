#include <cstdlib>
#include <iostream>
#include <stack>
#include <iomanip>
using namespace std;

const int Max=20;
template <class T>        //T是结点类型
class MGraph
{
private:
    T nodelist[Max];      //结点表 
    int arc[Max][Max];      //边表 
    int arcnum;         //当前边数 
    int nodenum;        //当前结点数 
public:
    MGraph();
    bool InsertNode(const T& v);             //在结点表最后插入结点v 
    bool InsertArc(int v1,int v2,int weight);      //在v1 v2之间插入一条弧 
    bool DeleteArc(int v1,int v2);
    bool MGraph<T>::DeleteNode(int v);      //删除结点表中第v个结点及相关的弧 
    void PrintNode();
    void PrintArc();
    void Dijsktra(int v,int* &cost,int* &path);            //迪杰斯特拉 最短路径算法 
    void Floyd(int** &cost,int** &path);                              //弗洛伊德  最短路径算法 
    void Prim(int v);                              //Prim最小生成树算法 
    void DFS();                            //深度优先遍历,非递归实现 
    int NodeNum();
    int ArcNum();
};
template <class T> 
MGraph<T>::MGraph()
{
    arcnum=0;
    nodenum=0;
    int i,j;
    for(i=0;i<Max;i++)
        for(j=0;j<Max;j++)
            arc[i][j]=9999;         //权值9999表示无边 
}
template <class T> 
bool MGraph<T>::InsertNode(const T& v)
{
    if(nodenum>=Max)
        return false;
    nodenum++;
    nodelist[nodenum-1]=v;
    return true;
}
template <class T> 
bool MGraph<T>::InsertArc(int v1,int v2,int weight)
{
    if(v1<0||v1>=nodenum||v2<0||v2>=nodenum)
        return false;
    arc[v1][v2]=weight;
    arcnum++;
    return true;
}
template <class T> 
bool MGraph<T>::DeleteArc(int v1,int v2)
{
    if(v1<0||v1>=nodenum||v2<0||v2>=nodenum||arcnum<=0)
        return false;
    arc[v1][v2]=0;
    arcnum--;
    return true;
}
template <class T>
bool MGraph<T>::DeleteNode(int v)       
{
    if(v<0||v>=nodenum)
        return false;
    int i,j;
    for(i=v+1;i<nodenum;i++)
    {
        nodelist[i]=nodelist[i-1];
    }
    nodenum--;
    for(i=0;i<nodenum;i++)
    {
        if(arc[i][v]!=0)    arcnum--;
        if(arc[v][i]!=0)    arcnum--;
        for(j=v+1;j<nodenum;j++)
        {
            arc[i][j]=arc[i][j-1];
            arc[j][i]=arc[j][i-1];
        }
    } 
    return true;
}
template <class T> 
void MGraph<T>::PrintArc()
{
    int i,j;
    for(i=0;i<nodenum;i++)
    {
        for(j=0;j<nodenum;j++)
        { 
            cout<<setw(5)<<arc[i][j];
        }
        cout<<endl;
    }
}
template <class T>
void MGraph<T>::PrintNode()
{
    for(int i=0;i<nodenum;i++)
    {
        cout<<nodelist[i];
    }
    cout<<endl;
}
template <class T>
void MGraph<T>::Dijsktra(int v,int* &cost,int* &path)       //第一个参数是结点号,第二个是记录最短路径的值的数组,第三个记录路径 
{                                                     //修改数组的值...用引用方式把结果传出去  
    bool* final=new bool[nodenum];
    cost=new int[nodenum];
    path=new int[nodenum];
    int i;
    for(i=0;i<nodenum;i++)           //初始化 
    {
        final[i]=false;
        cost[i]=arc[v][i];
        if(i!=v&&arc[v][i]!=9999)
        {
            path[i]=v;
        }
        else 
            path[i]=-1;
    }
    final[v]=true;              //放入结点v到集合 
    for(i=0;i<nodenum-1;i++)                //放其它结点到集合,进行n-1次全部放完 
    {
        int min=cost[v],u=v;
        for(int j=0;j<nodenum;j++)
        {
            if(!final[j]&&cost[j]<min)
            {
                min=cost[j];
                u=j;
            }
        }
        final[u]=true;      //把最小的中的一个结点放入集合
        for(int j=0;j<nodenum;j++)
        {
            if(!final[j]&&cost[u]+arc[u][j]<cost[j])
            {
                cost[j]=cost[u]+arc[u][j];
                path[j]=u;
            }
        } 
    }
}
template <class T>
void MGraph<T>::Floyd(int** &cost,int** &path)
{
    cost=new int*[nodenum];             //先为指针声明空间,让cost(二维指针)指向这些指针 
    path=new int*[nodenum];
    int i,j,k;
    for(i=0;i<nodenum;i++)              //为指针声明空间 
    {
        cost[i]=new int[nodenum];
        path[i]=new int[nodenum];
    }
    for(i=0;i<nodenum;i++)          //初始化
    {
        for(j=0;j<nodenum;j++)
        {
            cost[i][j]=arc[i][j];           
            if(i!=j&&cost[i][j]!=9999)
            {
                path[i][j]=i;
            }
            else
                path[i][j]=-1;
        }
    } 
    for(k=0;k<nodenum;k++)      
    {
        for(i=0;i<nodenum;i++)
        {
            for(j=0;j<nodenum;j++)
            {
                if(cost[i][k]+cost[k][j]<cost[i][j])
                {
                    cost[i][j]=cost[i][k]+cost[k][j];
                    path[i][j]=path[k][j];
                }
            }
        }
    }
}
template <class T>
void MGraph<T>::Prim(int v)
{
    int* path=new int[nodenum];
    int* cost=new int[nodenum];  
    int i;  
    for(i=0;i<nodenum;i++)
    { 
        cost[i]=arc[v][i];
        if(arc[v][i]!=9999)
        {

            path[i]=v;
        }
        else
            path[i]=-1;
    }
    cost[v]=0;
    for(i=0;i<nodenum-1;i++)
    {
        int min=9999,u;
        for(int j=0;j<nodenum;j++)
        {
            if(cost[j]!=0&&cost[j]<min)
            {
                min=cost[j];
                u=j;
            }
        }
        cout<<nodelist[path[u]]<<"->"<<nodelist[u]<<endl;
        for(int j=0;j<nodenum;j++)
        {
            if(cost[j]!=0&&arc[u][j]<cost[j])
            {
                cost[j]=arc[u][j];
                path[j]=u;
            }
        }
    }
}
template <class T>
void MGraph<T>::DFS()
{
    bool* visited=new bool[nodenum];
    int i;
    for(i=0;i<nodenum;i++)
    {
        stack<int> q;
        int temp;
        if(!visited[i])
        {
            
            cout<<nodelist[i];
            visited[i]=true;
            q.push(i);
            while(!q.empty())
            {
                temp=q.top();
                for(int j=0;j<nodenum;j++)
                {
                    if(!visited[j]&&arc[temp][j]!=9999)
                    {
                        cout<<nodelist[j];
                        visited[j]=true;
                        q.push(j);
                    }
                    
                }
                q.pop();
                
            }
        }
    }
}
template <class T>
int MGraph<T>::NodeNum()
{
    return nodenum;
}
template <class T>
int MGraph<T>::ArcNum()
{
    return arcnum;
}
int main(int argc, char *argv[])
{
    MGraph<char> m;
    m.InsertNode('A');
    m.InsertNode('B');
    m.InsertNode('C');
    m.InsertNode('D');
    m.InsertArc(0,1,54);
    m.InsertArc(0,2,19);
    m.InsertArc(0,3,12);
    m.InsertArc(1,2,18);
    m.InsertArc(2,0,15);
    m.InsertArc(3,0,23);
    m.InsertArc(3,1,6);
    m.InsertArc(3,2,42);    
    cout<<"结点表"<<endl;
    m.PrintNode();
    cout<<"邻接矩阵"<<endl;
	m.PrintArc();
	
	int** path;
	int** cost;
	m.Floyd(cost,path);
	cout<<'\n'<<"cost表"<<endl;
	for(int k=0;k<m.NodeNum();k++)
	{
        for(int s=0;s<m.NodeNum();s++)
        {
            cout<<setw(5)<<*(cost[k]+s);
        }
        cout<<endl;
    }
    cout<<'\n'<<"path表"<<endl;
	for(int k=0;k<m.NodeNum();k++)
	{
        for(int s=0;s<m.NodeNum();s++)
        {
            cout<<setw(5)<<path[k][s];
        }
        cout<<endl;
    }
    m.Prim(0);
    cout<<'\n'<<"m的深度遍历"<<endl;
    m.DFS();
    system("PAUSE");
    return EXIT_SUCCESS;
}
