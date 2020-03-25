#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <algorithm>
//#define LOCAL 1 
using namespace std;
typedef struct
{
    int weight;
    int Lchild,Rchild;
}HTNode;
typedef struct
{
    HTNode * HTree;
    int root;
}HuffmanTree;
struct Node1{
    //int weight,id;
    int first,second; ///weight,id
    bool operator < (const Node1& t)const{
        if(first!=t.first) return first>t.first;
        return second>t.second;
    }
    Node1(int x=0,int y=0):first(x),second(y){}
};
typedef struct Node1 Node1;
void buildHuffmanTree(HuffmanTree &HT,int * w,int n) ///构建一棵有n个叶子节点的赫夫曼树HT，节点的值为w[0]to w[n-1]
{
    int m = 2*n-1; ///n个叶子节点的二叉树有2*n-1个节点
    HT.HTree = new HTNode[m];
    for(int i=0;i<n;i++) ///初始化
    {
       HT.HTree[i].Lchild = HT.HTree[i].Rchild = -1;
       HT.HTree[i].weight = w[i];
    }
    for(int i=n;i<m;i++)
    {
        HT.HTree[i].Lchild = HT.HTree[i].Rchild = -1;
        HT.HTree[i].weight = 0;
    }
    //priority_queue<  pair<int,int> , vector<pair<int,int> >,   greater<pair<int,int>  > > Q;
    priority_queue<Node1> Q;
    for(int i=0;i<n;i++)
    {
        Q.push({w[i],i});
    }
    //pair<int,int> tmp1,tmp2;
    Node1 tmp1,tmp2;
    for(int i=n;i<m;i++)
    {
        //assert(!Q.empty());
        tmp1 = Q.top();Q.pop();
        //assert(!Q.empty());
        tmp2 = Q.top();Q.pop();
        //cout<<tmp1.first<<" "<<tmp2.first<<"\t";
        //cout<<tmp1.second<<" "<<tmp2.second<<endl;
        HT.HTree[i].weight = tmp1.first+tmp2.first;
        HT.HTree[i].Lchild = tmp1.second;
        HT.HTree[i].Rchild = tmp2.second;
        //tmp1.first = HT.HTree[i].weight;
       // tmp1.second = i;
        //Q.push(/*make_*/pair<int,int>(HT.HTree[i].weight,i));
        Q.push(Node1(HT.HTree[i].weight,i) );
       // Q.push(tmp1);
    }
    HT.root = m-1;
}

/*
5: 0001
29: 10
7: 1110
8: 1111
14: 110
23: 01
3: 0000
11: 001


*/
int w[1000];
///init: cnt = 0
void dfs(HuffmanTree &T,int now,char * record,int cnt,char **&Hc) ///record记录路径，cnt是当前record中的个数+1
{
    if(cnt>0&&T.HTree[now].Lchild == -1&&T.HTree[now].Rchild == -1)
    {
        Hc[now] = new char[cnt+1];
        for(int i=0;i<cnt;i++)
        {
            Hc[now][i] = record[i];
        }
        Hc[now][cnt] = '\0';
    }

    if(T.HTree[now].Lchild!=-1)
    {
        record[cnt++] = '0';
        dfs(T,T.HTree[now].Lchild,record,cnt,Hc);
        cnt--;
    }
    if(T.HTree[now].Rchild!=-1)
    {
        record[cnt++] = '1';
        dfs(T,T.HTree[now].Rchild,record,cnt,Hc);
        cnt--;
    }
}
void showTree(HuffmanTree Htree)
{
    for(int i=0;i<Htree.root;i++)
    {
        cout<<i<<":"<<Htree.HTree[i].weight<<" "<<Htree.HTree[i].Lchild<<" "<<Htree.HTree[i].Rchild<<endl;
    }
}
int main()
{
	#ifdef LOCAL
    freopen("in.txt","r",stdin);
    #endif
    int n;
    #ifndef LOCAL
    cout<<"请输入节点个数n： ";
	#endif 
    cin>>n;
    #ifndef LOCAL
    cout<<"请输入"<<n<<"个节点的权值："<<endl;
	#endif 
    for(int i=0;i<n;i++)
        cin>>w[i];
    HuffmanTree Htree;
    buildHuffmanTree(Htree,w,n);

    char * record = new char[n];
    char **Hc;
    Hc = new char * [n];
    dfs(Htree,Htree.root,record,0,Hc);
    cout<<"赫夫曼树各节点的前缀码如下："<<endl; 
    for(int i=0;i<n;i++)
    {
        cout<<w[i]<<": ";
        cout<<Hc[i]<<endl;
    }
    for(int i=0;i<n;i++)
        delete Hc[i];
    delete Hc;
    delete []Htree.HTree;

    return 0;
}
