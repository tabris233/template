LL d[N];
int inq[N],n,m,q;
LL spfa(int s,int t){
    for(int i=1;i<=n;i++) d[i]=INF,inq[i]=0;
    queue<int >q;
    q.push(s);d[s]=0,inq[s]=1;
    while(!q.empty()){
        int u =q.front();q.pop();
        inq[u]=0;
        for(int i=head[u],v;i!=-1;i=G[i].next){
            v=G[i].to;
            if(d[v]>d[u]+G[i].w){
                d[v]=d[u]+G[i].w;
                if(inq[v]==1) continue;
                inq[v]=1;
                q.push(v);
            }
        }
    }
    return d[t];
}