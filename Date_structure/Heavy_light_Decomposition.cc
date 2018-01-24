/*********************************************************
树链剖分

树链剖分是一种将树形结构转化为线性结构的算法 
通过两次树的遍历,将树剖分成一个个的[重链], 
且对每个节点进行编号,确保一条链上的节点编号连续 
这样一来,我们就能通过一个维护区间关系的数据结构来维护树上,属同一个链上的元素

在维护两个节点(u,v)的时候即:维护两个节点(u,v)间的元素, 
我么从深度大的不断向上维护,最后遍历的位置,两个节点一定在一条链上(且深度小的就是LCA(u,v))
**********************************************************/
int dep[N];   //每个节点的深度
int fa[N];    //每个节点的父节点
int sz[N];    //每个节点所有的子节点个数(包括自身)
int son[N];   //每个节点的重儿子
void dfs1(int u,int ff,int deep){
    son[u]=0;fa[u]=ff;sz[u]=1;dep[u]=deep;
    for(int i=head[u];i!=-1;i=G[i].next){
        int v=G[i].to;
        if(v==ff) continue;
        dfs1(v,u,deep+1);
        sz[u]+=sz[v];                  
        if(sz[v]>sz[son[u]]) son[u]=v; //重儿子子节点个数大
    }
}

int top[N];   //节点所在链上的【根】
int tree[N];  //节点对应在线段树/树状数组的位置
int pre[N];   //在线段树/树状数组的位置对应的节点的标号  (树状数组时一般不需要)
int cnt;      //对链上节点编号
void dfs2(int u,int ff){
    tree[u]=++cnt;pre[tree[u]]=u;top[u]=ff;
    if(son[u]) dfs2(son[u],ff); //先遍历重链   
    else return ;
    for(int i=head[u];i!=-1;i=G[i].next){
        int v=G[i].to;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

int findi(int x,int y){
    int fx=top[x],fy=top[y];
    int ans = 0;
    while(fx!=fy){
        if(dep[fx]<dep[fy]) myswap(x,y),myswap(fx,fy);
        ans+=getSum(tree[x])-getSum(tree[fx]-1);  //不断向上维护区间 
        x=fa[fx],fx=top[x];
    }
    if(dep[x]>dep[y]) myswap(x,y);
    if(x!=y) ans+=getSum(tree[y])-getSum(tree[x]);
    return ans ;
}