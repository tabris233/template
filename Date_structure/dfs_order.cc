/***************************************************************
dfs序

其实就是从根节点进行搜索， 
然后向下dfs遍历树，依次进行编号， 
同时能保证子树的编号一定大于父节点的编号，

同时借用两个数组，L[_],R[_] 
分别表示这个节点u的子树的节点编号在(L[u],R[u]),开区间内。

这样在进行对子树进行的操作的时候可以借助数据结构对区间进行查找，
***************************************************************/
vector<int >G[N];
int cnt = 0;
void dfs(int u,int f){
    L[u]=cnt++;
    for(int i=0;i<G[u].size();i++)if(G[u][i]!=f)
        dfs(G[u][i]);
    R[u]=cnt;
}