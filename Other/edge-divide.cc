#include <bits/stdc++.h>
using namespace std;

#define MAXN 210000
#define MAXM 4000000
#define WHITE 1
#define BLACK 0

int V[MAXM],E[MAXM],NEXT[MAXM],FIR[MAXN]; int N;
int v[MAXN*2],e[MAXN*2],next[MAXN*2],pre[MAXN*2],fir[MAXN],ed[MAXN]; int n;
int col[MAXN],size[MAXN];
int p,mi,midedge,tot;

char buf[8000000],*pt = buf,*o = buf;
int getint(){
    int f = 1,x = 0;
    while((*pt != '-') && (*pt < '0' || *pt > '9'))    pt ++;
    if(*pt == '-')    f = -1,pt ++;    else    x = *pt++ - 48;
    while(*pt >= '0' && *pt <= '9')    x = x * 10 + *pt ++ - 48;
    return x * f;
}
char getch(){
    char ch;
    while(*pt < 'A' || *pt > 'Z')    pt ++;
    ch=*pt;pt++;    
    return ch;
}

void ADD1(int x,int y,int z){
    V[tot]=y;E[tot]=z;NEXT[tot]=FIR[x];FIR[x]=tot;tot++;
}

void ADD(int x,int y,int z){
    V[tot]=y;E[tot]=z;NEXT[tot]=FIR[x];FIR[x]=tot;tot++;
    V[tot]=x;E[tot]=z;NEXT[tot]=FIR[y];FIR[y]=tot;tot++;
}

void add(int x,int y,int z){
    v[tot]=y;e[tot]=z;next[tot]=fir[x];fir[x]=tot;tot++;
    v[tot]=x;e[tot]=z;next[tot]=fir[y];fir[y]=tot;tot++;
}

void getpre(){
    memset(ed,255,sizeof(ed));
    for(int i=1;i<=n;i++)
        for(int j=fir[i];~j;j=next[j]){
            pre[j]=ed[i];
            ed[i]=j;
        }
}

void _delete(int x,int i){
    if(fir[x]==i) fir[x]=next[i]; else next[pre[i]]=next[i];
    if(ed[x]==i) ed[x]=pre[i]; else pre[next[i]]=pre[i];
}

void init(){
    memset(FIR,255,sizeof(FIR));tot=0;
    N=getint();
    for(int i=1;i<N;i++){
        int x=getint(),y=getint(),z=getint();
        ADD(x,y,z);
    }
}

void check(int u,int fa){
    int father=0;
    for(int i=FIR[u];~i;i=NEXT[i])
    if(V[i]!=fa)
        if(father==0){
            add(u,V[i],E[i]);
            father=u;
            check(V[i],u);
        }else{
            ++n;col[n]=BLACK;
            add(father,n,0);add(n,V[i],E[i]);
            father=n;
            check(V[i],u);
        }
}

void rebuild(){
    memset(fir,255,sizeof(fir));tot=0;
    n=N;
    for(int i=1;i<=n;i++) col[i]=WHITE;
    check(1,0);
    getpre();
    memset(FIR,255,sizeof(FIR));tot=0;
}

struct point{
    int dist,id;
    bool operator<(const point&b)const{
        return dist<b.dist;
    }
};
    
struct node{
    int rt,midlen,ans;
    int lc,rc;
    priority_queue<point>Q;
}T[MAXN*4];

int cnt=0;

void dfs_size(int u,int fa,int dist){
    ADD1(u,p,dist);if(col[u])T[p].Q.push((point){dist,u});
    size[u]=1;
    for(int i=fir[u];~i;i=next[i])
        if(v[i]!=fa){
            dfs_size(v[i],u,dist+e[i]);
            size[u]+=size[v[i]];
        }
}

void dfs_midedge(int u,int code){
    if(max(size[u],size[T[p].rt]-size[u])<mi){
        mi=max(size[u],size[T[p].rt]-size[u]);
        midedge=code;
    }
    for(int i=fir[u];~i;i=next[i])
        if(i!=(code^1))
            dfs_midedge(v[i],i);
}

void push_up(int p){
    T[p].ans=-1;
    while(!T[p].Q.empty()&&(col[T[p].Q.top().id]==0)) T[p].Q.pop();
    int lc=T[p].lc,rc=T[p].rc;
    if(lc==0&&rc==0){
         if(col[T[p].rt]) T[p].ans=0;
    }else{
        if(T[lc].ans>T[p].ans) T[p].ans=T[lc].ans;
        if(T[rc].ans>T[p].ans) T[p].ans=T[rc].ans;
        if(!T[lc].Q.empty()&&!T[rc].Q.empty())
            T[p].ans=max(T[lc].Q.top().dist+T[rc].Q.top().dist+T[p].midlen,T[p].ans);
    }
}

void dfs(int pt,int u){
    T[pt].rt=u;
    p=pt;dfs_size(u,0,0);
    midedge=-1;mi=n;dfs_midedge(u,-1);
    if(~midedge){
        int p1=v[midedge],p2=v[midedge^1];
        T[pt].midlen=e[midedge];
        _delete(p1,midedge^1);
        _delete(p2,midedge);
        dfs(T[pt].lc=++cnt,p1);
        dfs(T[pt].rc=++cnt,p2);        
    }
    push_up(pt);
}

void change(int x){
    col[x]^=1;
    if(col[x]==BLACK)
        for(int i=FIR[x];~i;i=NEXT[i])
            push_up(V[i]);
    else
        for(int i=FIR[x];~i;i=NEXT[i]){
            T[V[i]].Q.push((point){E[i],x});
            push_up(V[i]);
        }
}
     

void solve(){
    int x;char op;
    int q=getint();
    while(q--){
        op=getch();
        if(op=='A')
            if(~T[1].ans)
                printf("%d\n",T[1].ans);
            else
                puts("They have disappeared.");
        else{
            x=getint();
            change(x);
        }
    }
}

int main(){
    init();
    rebuild();
    dfs(cnt=1,1);
    solve();
    return 0;
}

QTREE4