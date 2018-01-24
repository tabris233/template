/******************************************************
二分图匹配

算法介绍 
最大匹配数    ：最大匹配的匹配边的数目 
最小点覆盖数  ：选取最少的点，使任意一条边至少有一个端点被选择 
最大独立数    ：选取最多的点，使任意所选两点均不相连 
最小路径覆盖数：对于一个 DAG（有向无环图），选取最少条路径，使得每个顶点属于且仅属于一条路径。路径长可以为 0（即单个点）。

定理1：最小点覆盖数   = 最大匹配数（这是 Konig 定理） 
定理2：最大独立数     = 顶点数 - 最大匹配数 
定理3：最小路径覆盖数 = 顶点数 - 最大匹配数

独立集：任意两点都不相连的顶点的集合
独立数：独立集中顶点的个数
完全子图：任意两点都相连的顶点的集合
最大完全数：最大完全子图中顶点的个数
最大完全数=原图的补图的最大独立数
最大独立数=顶点数-最大匹配数

匈牙利算法求解二分图匹配问题
******************************************************/
int k,n,m;
int match[N];
int vis[N];
vector<int >G[N];

int tot,a;
int col[N];
//二分图染色  用来判断是不是二分图
bool color(int s){
    queue<int>q;
    q.push(s);col[s]=1;
    while(!q.empty()){
        int u = q.front();q.pop();
        tot++;
        if(col[u]==1) a++;
        int gz=G[u].size();
        for(int i=0,to;i<gz;i++){
            to=G[u][i];
            if(col[to]==0){
                col[to]=3-col[u];
                q.push(to);
            }
            else if(col[to]==col[u])
                return false;
        }
    }
    return true;
}

bool findi(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]==0){
            vis[v]=1;
            if(match[v]==-1||findi(match[v])){
                match[v]=u;
                return true;
            }
        }
    }
    return false;
}

void init(){
    memset(match,-1,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear(),col[i]=vis[i]=0;
}

void add(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u); //无向图才需要
}

int maxMATCH(){
    int ans = 0;  //ans 是最大匹配数,
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        if(findi(i)) ans++;
    }
    ans/=2;   //对于无向图的话 需要ans/=2;
    return ans ;
}

bool perfectMATCH(){
    if(maxMATCH()==n) return true;
    else              return false;
}
