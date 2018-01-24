/**************************************************************
拓扑排序（Topological Sorting）是一个有向无环图（DAG, Directed Acyclic Graph）的所有顶点的线性序列。
该序列必须满足下面两个条件：
1.每个顶点出现且只出现一次。
2.若存在一条从顶点 A 到顶点 B 的路径，那么在序列中顶点 A 出现在顶点 B 的前面。

是'特殊'的图中的一种,可以在排序过程中进行计算一些值.
***************************************************************/    

void topo(){
    queue<int>q;
    for(int i=1;i<=n;i++)if(0==deg[i]) q.push(i);

    for(int u;!q.empty();){
        u=q.front();
        for(int i=head[u],to;i!=-1;i=G[i].next){
            to = G[i].to;
            deg[to]--;
            if(0==deg[to]) q.push(to);
        }
    }
}