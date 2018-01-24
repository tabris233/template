//邻接表 空间复杂度O(e+v)
vectorG[N];  //G[i][j] 表示有一条i->G[i][j]的有向边
void add(int u,int v){
    G[u].push_back(v);
}
void dfs(int u,int f){
    int gz=G[u].size();
    for(int i=0,to;i<gz;i++){
        to = G[u][i];
        if(to == f) continue;
        dfs(to,u);
    }
}

//前向星  空间复杂度O(e)
struct edge{
    int to,next,w;
}G[N<<1];
int head[N],tot;
void add(int u,int v,int w){
    G[tot].w=w,G[tot].to=v,G[tot].next=head[u],head[u]=tot++;
}
void dfs(int u,int f){
    for(int i=head[u],to;i!=-1;i=G[i].next){
        to = G[i].to;
        if(to == f) continue;
        dfs(to,u);
    }
}