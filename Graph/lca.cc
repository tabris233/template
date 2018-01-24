// 一. 树链剖分
// 复杂度O(n)-O(\log{n})

// 代码略

// 二. 倍增求lca
// 复杂度O(n\log{n})-O(\log{n})

int fa[N][20],dep[N],mi[N][20];//(顺带求路上边长最小值)
void dfs(int u,int f,int d){
    fa[u][0]=f;dep[u]=d;
    for(int i=1;i<20;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1],mi[u][i]=min(mi[u][i-1],mi[fa[u][i-1]][i-1]);
    int gz=G[u].size();
    for(int i=0,to;i<gz;i++){
        to=G[u][i].first;
        if(to==f)continue;
        mi[to][0]=G[u][i].second;
        dfs(to,u,d+1);
    }
}
void solve(int u,int v){
    if(dep[u]<dep[v]) swap(u,v);
    int lca=-1,tu=u,tv=v;

    for(int i=19;i>=0;i--)
        if(dep[fa[u][i]]>=dep[v])
            u=fa[u][i];

    if(u==v) lca=v;// return v;
    else{
        for(int i=19;i>=0;i--){
            if(fa[u][i]==fa[v][i]) continue;
            u=fa[u][i];
            v=fa[v][i];
        }
        lca = fa[v][0];
    }
    int miu=INF,miv=INF;
    for(int i=19;i>=0;i--){
        if(dep[fa[tu][i]]>=dep[lca])
            miu=min(miu,mi[tu][i]),tu=fa[tu][i];
        if(dep[fa[tv][i]]>=dep[lca])
            miv=min(miv,mi[tv][i]),tv=fa[tv][i];
    }
    printf("%d\n",min(miu,miv));
}

// 三. lca转rmq
// 复杂度O(n\log{n})-O(\log{n})

vector<int> g[N], sp;
int dep[N], dfn[N], lg[2 * N];
pair<int, int> dp[21][2 * N];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            sp.push_back(u);
        }
    }
}

void lca_init() {
    int n=sp.size();
    for (int i=1,j=0;i<=n;i++) {
        if (i==(1<<(j+1)))j++;
        lg[i]=j;
    }
    for(int i=0;i<n;i++){
        dp[0][i]={dfn[sp[i]],sp[i]};
    }
    for(int j=1; (1<<j)<=n;j++) {
        for (int i=0;i+(1<<j)-1<n;i++) {
        dp[j][i]=min(dp[j-1][i],dp[j-1][i+(1<<(j-1))]);
        }
    }   
}

int lca(int u, int v) {
    int l=dfn[u],r=dfn[v];
    if (l>r) swap(l,r);
    int j=lg[r-l+1];
    return min(dp[j][l],dp[j][r-(1<<j)+1]).second;
}

