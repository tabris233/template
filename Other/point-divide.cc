#include <bits/stdc++.h>
typedef long long int LL;
using namespace std;
const int N   = 20000+7;

int n,k,ans;

bool vis[N];
int d[N],f[N];

struct edge{
    int to,next;
    int w;
}G[N<<1];
int head[N],tot;
void add(int u,int v,int w=0){
    G[tot].w=w,G[tot].to=v,G[tot].next=head[u],head[u]=tot++;
}

/********重心 begin********/
int sz[N],dn[N],siz,zx;

void getzx(int u,int fa=0){
    sz[u]=1;dn[u]=0;
    for(int i=head[u],to;i!=-1;i=G[i].next){
        to = G[i].to;
        if(to == fa||vis[to]) continue;
        getzx(to,u);
        sz[u]+=sz[to];
        dn[u]=max(dn[u],sz[to]);
    }
    dn[u]=max(dn[u],siz-sz[u]);
    if(dn[u]<dn[zx]) zx=u;
}

/*********重心 end********/
/**
d[] 为当前节点到当前树根的距离
f[] 就是记录当前处理的子树的每个节点的d[]
*/
void getd(int u,int fa=0){
    f[++f[0]] = d[u];
    for(int i=head[u],to;i!=-1;i=G[i].next){
        to=G[i].to;
        if(to==fa||vis[to]) continue;
        d[to]=d[u]+G[i].w;
        getd(to,u);
    }
}

int cal(int u,int w){
    d[u]=w; f[0]=0;int sum = 0;
    getd(u); sort(f+1,f+f[0]+1);
    for(int l=1,r=f[0];l<r;){
        if(f[l]+f[r]<=k){sum+=r-l;l++;}
        else r--;
    }
    return sum;
}
void solve(int u){
    ans+=cal(u,0);
    vis[u]=1;
    for(int i=head[u],to;i!=-1;i=G[i].next){
        to=G[i].to;
        if(vis[to]) continue;
        ans-=cal(to,G[i].w);
        siz=sz[to],zx=0;getzx(to);
        solve(zx);
    }
}
int main(){
    while(~scanf("%d%d",&n,&k)&&(n||k)){
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        dn[0]=n*10;zx=0;tot=0;

        for(int i=1,u,v,w;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);add(v,u,w);
        }

        siz = n; getzx(1);
        ans = 0;solve(zx);

        printf("%d\n",ans);
    }
    return 0;
}