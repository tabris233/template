// 预处理
int SG[MAX+10],s[N+10],has[N+10];
void getSG(int n){ //n 代表最大的状态既石子个数
    SG[0]=0;
    for(int i=1; i<=n; i++) {
        memset(has,0,sizeof(has));  //has数组的大小可以优化 否则可能会TLE
        for(int j=0; j<t; j++)      //t代表所有可以取的石子的数量的种类数
            if(i-s[j]>=0/*这里可以加入has数组的上界以防数组越界*/)  
                has[SG[i-s[j]]]=1;
        for(int j=0;; j++)if(!has[j]){
            SG[i]=j;break;
        }
    }
}
// 记忆化搜索
//注意要先对SG memset(SG,-1,sizeof(SG));
int SG[MAX+10],s[N+10];
bool has[min(MAX,N)+10];
int dfsSG(int n){
    if(SG[n]!=-1)return SG[n];
    memset(has,0,sizeof(has));
    for(int i=0; i<t; i++)
        if(x-s[i]>=0) vis[dfs(x-s[i])]=1;
    for(int i=0;; i++)if(0==has[i]){
        SG[x]=i;break;
    }
    return SG[n];
}
