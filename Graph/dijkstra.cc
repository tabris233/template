vector<pair<int ,int > >G[N];
LL d[N];
LL dijkstra(int s,int t){
    for(int i=1;i<=n;i++)d[i]=INF;
    d[s]=0;
    priority_queue<pair<int ,int> >q;
    q.push(make_pair(-d[s],s));
    while(!q.empty()){
        int u =q.top().second;q.pop();
        if(u==t) return d[t];
        for(int i=0,v;i<G[u].size();i++){
            v=G[u][i].first;
            if(d[v]>d[u]+G[u][i].second){
                d[v]=d[u]+G[u][i].second;
                q.push(make_pair(-d[v],v));
            }
        }
    }
    return d[t];
}