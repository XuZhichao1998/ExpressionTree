#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <cstdlib>
#include <string>
using namespace std;
const int maxn = 1e5 + 100;
typedef char ElemType;
typedef struct BiTNode
{
	ElemType data;
	struct BiTNode * Lchild;
	struct BiTNode * Rchild;
}BiTNode,*BiTree;
void InitBiTree(BiTree & T)
{
	T = nullptr;
}
typedef enum{TRAV=1,VIS=0} TaskType;
typedef struct SElemType{
    BiTree ptr;
    TaskType task; ///TRAV:是遍历， VIS是访问
    SElemType(BiTree p,TaskType t):ptr(p),task(t){}
}SElemType;
char str[1000];
int cnt;
void CreatBiTree(BiTree & T)
{
	ElemType ch;
	ch = str[cnt++];
	if(ch=='#') T = nullptr;
	else
	{
		T = new BiTNode;
		if(T==nullptr)
        {
            cout<<"内存不足！"<<endl;
            exit(-1);
        }
		T->data = ch;
		CreatBiTree(T->Lchild);
		CreatBiTree(T->Rchild);
	}
}
void Visit(BiTree T)
{
	if(T)
    {
        cout<<T->data<<" ";
    }

}
void InOrderVisit(BiTree T,void(*Visit)(BiTree))
{
	if(T==nullptr) return;
	InOrderVisit(T->Lchild,Visit);
	Visit(T);
	InOrderVisit(T->Rchild,Visit);
}
void PreOrderVisit(BiTree T,void(*Visit)(BiTree))
{
	if(!T) return;
	Visit(T);
	PreOrderVisit(T->Lchild,Visit);
	PreOrderVisit(T->Rchild,Visit);
}
void LastOrderVisit(BiTree T,void(*Visit)(BiTree))
{
    if(!T) return;
    LastOrderVisit(T->Lchild,Visit);
    LastOrderVisit(T->Rchild,Visit);
    Visit(T);
}
void PreVisit(BiTree T,void(*Visit)(BiTree))
{
    //while(!S.empty()) S.pop();
    stack<BiTree> S1;
    BiTree p = T;
    while(p||!S1.empty())
    {
        if(p)
        {
            Visit(p);
            if(p->Rchild)
                S1.push(p->Rchild);
            p = p->Lchild;
        }
        else p = S1.top(),S1.pop();
    }
    cout<<endl;
}
void InVisit(BiTree T,void(*Visit)(BiTree))
{
    stack<SElemType> S;
    BiTree p;
    TaskType task;
    S.push({T,TRAV});  ///<-> S.push(SElemType(T,TRAV))
    while(!S.empty())
    {
        p = S.top().ptr;
        task = S.top().task;
        S.pop();
        if(task==VIS) Visit(p);
        else ///task==TRAV
        {
            if(p)
            {
                S.push({p->Rchild,TRAV});
                S.push({p,VIS});
                S.push({p->Lchild,TRAV});
            }
        }
    }
    cout<<endl;
}
void LastVisit(BiTree T,void(*Visit)(BiTree))
{
    stack<SElemType> S;
    BiTree p;
    TaskType task;
    S.push({T,TRAV});  ///<-> S.push(SElemType(T,TRAV))
    while(!S.empty())
    {
        p = S.top().ptr;
        task = S.top().task;
        S.pop();
        if(task==VIS) Visit(p);
        else ///task==TRAV
        {
            if(p)
            {
                S.push({p,VIS});
                S.push({p->Rchild,TRAV});
                S.push({p->Lchild,TRAV});
            }
        }
    }
    cout<<endl;
}
void BiTreeDepth(BiTree T,int h,int & depth)
{
	if(T)
	{
		if(h>depth) depth = h;
		BiTreeDepth(T->Lchild,h+1,depth);
		BiTreeDepth(T->Rchild,h+1,depth);
	}
}
BiTree GetTreeNode(ElemType elem,BiTree Lptr,BiTree Rptr) //计算仅由一位数组成的表达式树 
{
	BiTree newT = new BiTNode;
	newT->data = elem;
	newT->Lchild = Lptr;
	newT->Rchild = Rptr;
	return newT;
}
BiTree CopyTree(BiTree T) //以T为根节点的数，返回复制后的树的根指针 
{
	if(!T) return nullptr;
	BiTree newLptr=nullptr,newRptr = nullptr;
	if(T->Lchild) newLptr = CopyTree(T->Lchild);
	if(T->Rchild) newRptr = CopyTree(T->Rchild); 
	BiTree newNode = GetTreeNode(T->data,newLptr,newRptr);
	return newNode;
}
bool isOperator(char ch)
{
	return ch=='+'||ch=='-'||ch=='*'||ch=='/';
}
double getAns(BiTree T)
{
	if(!T) return 0.0;
	double Loperand = getAns(T->Lchild);
	double Roperand = getAns(T->Rchild);
	if(!T->Lchild && !T->Rchild) return T->data -'0'; 
	else
	{
		switch(T->data)
		{
			case '+': return Loperand+Roperand;
			case '-': return Loperand-Roperand;
			case '*': return Loperand*Roperand;
			case '/': if(Roperand==0) 
			{
				cout<<"devide by 0!"; exit(-1);
			}
			return Loperand/Roperand;
			default: cout<<"invalid Operator!"<<T->data<<endl;
				exit(-1); 
		}
	}
		
} 
int getDepth(BiTree T)
{
	if(!T) return 0;
	int L = getDepth(T->Lchild);
	int R = getDepth(T->Rchild);
	return max(L,R)+1;	
} 
int getNumOfLeave(BiTree T)
{
	if(!T) return 0;
	if(T->Lchild==nullptr&&T->Rchild==nullptr)
	{
		cout<<"叶子节点为："<<T->data<<endl; 
		return 1;	
	} 
	return getNumOfLeave(T->Lchild) + getNumOfLeave(T->Rchild);	
} 
int getdepth(BiTree T)
{
	if(!T) return 0;
	if(!T->Lchild&&!T->Rchild) return 1;
	return 1 + max(getdepth(T->Lchild) , getdepth(T->Rchild));
}
int main()
{
	freopen("in1.txt","r",stdin);
	BiTree T;
	cin>>str;
	cout<<"str = "<<str<<endl;
	cnt = 0;
	CreatBiTree(T);
	cout<<"前序遍历：";
	PreOrderVisit(T,Visit);
	cout<<endl;
    cout<<"中序遍历：";
	InOrderVisit(T,Visit);
	cout<<endl;
	cout<<"后续遍历：";
	LastOrderVisit(T,Visit);
	cout<<endl;
    cout<<"非递归前序遍历：";
    PreVisit(T,Visit);
    cout<<"非递归中序遍历：";
    InVisit(T,Visit);
    cout<<"非递归后序遍历：";
    LastVisit(T,Visit);
	int depth = 0;
	BiTreeDepth(T,1,depth); //前序遍历求树深 
	cout<<"树深为："<<depth<<endl;
	cout<<"树深为："<<getDepth(T)<<endl;
	cout<<"树深为："<<getdepth(T)<<endl;
	BiTree newT = CopyTree(T);
	cout<<"复制后的树为(前)："; 
	PreVisit(newT,Visit);
	cout<<"复制后的树为(中)："; 
	InVisit(newT,Visit);
	cout<<"复制后的树为(后)：";
	LastVisit(newT,Visit);
	cout<<getAns(T)<<endl;
	cout<<"叶子节点的个数为："<<getNumOfLeave(T)<<endl;

	return 0;
}
