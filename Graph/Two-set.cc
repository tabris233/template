vector<int> G[N];
vector<int> G2[N];

vector<int> S;
int vis[N] ;  //标记数组
int sccno[N]; //记录数组 sccno[i] 记录  i属于哪个联通分支
int scc_cnt;  
int n;
void dfs1(int u){
    if(vis[u]) return ;
    vis[u] = true;
    for(int i = 0; i < G[u].size(); i++){
        dfs1(G[u][i]);
    }
    S.push_back(u);
}
void dfs2(int u){
    if(sccno[u]) return;
    sccno[u] = scc_cnt;
    for(int i = 0; i < G2[u].size(); i++){
        dfs2(G2[u][i]);
    }
}
void find_scc(int n){
    scc_cnt = 0;
    S.clear();
    memset(vis , 0 , sizeof(vis));
    memset(sccno , 0 , sizeof(sccno));
    for(int i = 0; i < n; i++) dfs1(i);
    for(int i = n - 1; i >= 0; i--) if(!sccno[S[i]]){
        scc_cnt++;
        dfs2(S[i]);
    }
}
void AddEdge(int u , int v) {
    G[u].push_back(v);
    G2[v].push_back(u);
}
int solve(){
    /***
    输入数据
    */
    /***
    加边  边为两者不能匹配的  
    example ： {u,v}  当选择u的时候一定不能选择v ,需要选择v';
    */
    find_scc(2 * n);  //注意x2

    for(int i = 0; i < n; i++){
        if(sccno[i] == sccno[i + n]){
            //如果有x与x'同时被取或者未取，则匹配失败
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    for(int i = 0; i < n; i++){
        if(sccno[i] > sccno[i + n]){
            //相关 i;
        }
        else {
            //相关 i';
        }
    }
    return 0;
}