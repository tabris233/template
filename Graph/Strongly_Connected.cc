vector<int>G[N];
vector<pair<int,int> >G2[N];

int low[N],dfn[N],w[N],d[N];
int vis[N],val[N];
int color[N],cnt,tot;
int mystack[N],len;

void dfs(int u){vis[u]=1;
    dfn[u]=low[u]=++cnt;
    mystack[++len]=u;
    int gz=G[u].size();
    for(int to,i=0;i<gz;i++){
        to=G[u][i];
        if(vis[to]==0) dfs(to);
        if(vis[to]==1) low[u]=min(low[u],low[to]);
    }

    if(dfn[u]==low[u]){
        ++tot;
        do{
            val[tot]+=w[mystack[len]];
            color[mystack[len]]=tot;
            vis[mystack[len]]=2;
        }while(mystack[len--]!=u);
    }
}

int n,m;
int main(){
    scanf("%d%d",&n,&m);
    cnt=tot=len=0;
    for(int i=1;i<=n;i++)    scanf("%d",&w[i]);

    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        G[u].push_back(v); //看是有向图还是无向图
    }

    //缩点
    for(int i=1;i<=n;i++)if(vis[i]==0) dfs(i);

    //建新图G2

    for(int i=1,gz;i<=n;i++){vis[i]=0,d[i]=0;
        gz=G[i].size();
        for(int j=0,to;j<gz;j++){
            to=G[i][j];
            if(color[i]!=color[to])
                G2[color[i]].push_back(make_pair(val[color[to]],color[to]));
        }
    }

    return 0;
}