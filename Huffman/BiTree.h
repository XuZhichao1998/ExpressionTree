#include <bits/stdc++.h> 
using namespace std;
typedef struct BiTNode
{
	char data;
	struct BiTNode * Lchild;
	struct BiTNode * Rchild;	
}BiTNode,*BiTree;
char str[1000]; 
typedef enum{Visit,Travel} TaskType; //访问 和 遍历 
struct Node
{
	BiTree ptr;
	TaskType task;
};
void creatTree(BiTree &T)
{
	char ch;
	cin>>ch;
	if(ch=='#') T = nullptr;
	else 
	{
		T = new BiTNode;
		T->data = ch;
		creatTree(T->Lchild);
		creatTree(T->Rchild);	
	} 
} 
//函数都写成void的好处是函数原型可以统一，调用过的时候可以函数指针实现 
void PreOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	visit(T);
	PreOrder(T->Lchild,visit);
	PreOrder(T->Rchild,visit);
}
void InOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	InOrder(T->Lchild,visit);
	visit(T);
	InOrder(T->Rchild,visit);
}
void SubsequentOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	SubsequentOrder(T->Lchild,visit);
	SubsequentOrder(T->Rchild,visit);
	visit(T);
}
void visit(BiTree T)
{
	if(T)
		cout<<T->data;
}
void pre_order(BiTree T,void(*visit)(BiTree))
{
	/*if(!T) 
	{
		cout<<"The Tree is empty!"<<endl; 
		return;	
	}*/
	stack<BiTree> S;
	BiTree p = T;
	while(p||!S.empty())
	{
		if(p) visit(p),S.push(p->Rchild),p = p->Lchild;
		else p = S.top(),S.pop();
	}
} 
void in_order(BiTree T,void(*visit)(BiTree))
{
	stack<Node> S;
	if(T) S.push({T,Travel});
	TaskType task;
	BiTree p;
	while(!S.empty())
	{
		p = S.top().ptr;
		task = S.top().task;
		S.pop();
		if(task==Visit) 
		{
			visit(p);
		}
		else      //(task==Travel)
		{
			if(p)
				S.push({p->Rchild,Travel}), //最不迫切的任务 遍历右子树 
				S.push({p,Visit}),          //访问根节点 
				S.push({p->Lchild,Travel}); //遍历左子树 
		}
	}
} 
void subsequent_order(BiTree T,void(*visit)(BiTree))
{
	stack<Node> S;
	if(T) S.push({T,Travel});
	TaskType task;
	BiTree p;
	while(!S.empty())
	{
		p = S.top().ptr;
		task = S.top().task;
		S.pop();
		if(task==Visit) 
		{
			visit(p);
		}
		else      //(task==Travel)
		{
			if(p)
				S.push({p,Visit}),  //访问根节点 
				S.push({p->Rchild,Travel}), //最不迫切的任务 遍历右子树 
				S.push({p->Lchild,Travel}); //遍历左子树 
				        
		}
	}
} 
