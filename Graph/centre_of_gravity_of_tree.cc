/*****************************************************
树的重心

树的重心：找到一个点，其所有的子树中最大的子树节点数最少,那么这个点就是这棵树的重心,删去重心后，生成的多棵树尽可能平衡。 
树的重心可以通过简单的两次搜索求出，第一遍搜索求出每个结点的子结点数量son[u]，第二遍搜索找出使max{son[u],n-son[u]-1}最小的结点。 
实际上这两步操作可以在一次遍历中解决。对结点u的每一个儿子v，递归的处理v，求出son[v]，然后判断是否是结点数最多的子树，处理完所有子结点后，判断u是否为重心。
例题poj 1655
*****************************************************/
int n;

vector<int >G[N];
void add(int u,int v){G[u].push_back(v);}

int sz[N],siz,zx;

void dfs(int u,int f=0){
    sz[u]=1;int mx=0;
    int gz=G[u].size();
    for(int i=0,to;i<gz;i++){
        to = G[u][i];
        if(to == f) continue;
        dfs(to,u);
        sz[u]+=sz[to];
        mx=max(mx,sz[to]);
    }
    mx=max(mx,n-sz[u]);
    if(mx==siz&&u<zx) zx=u;
    if(mx<siz) zx=u,siz=mx;
}

int main(){
    int _;
    for(scanf("%d",&_);_--;){
        scanf("%d",&n);
        for(int i=1,u,v;i<n;i++){
            scanf("%d%d",&u,&v);
            add(u,v);add(v,u);
        }
        siz = n*10; dfs(1);
        printf("%d %d\n",zx,siz);
        for(int i=1;i<=n;i++) G[i].clear();
    }
    return 0;
}