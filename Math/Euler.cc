void phi_table(){ //欧拉函数。。。
    int i,j;
    for(i=2; i<=5e6; i++)phi[i]=0;
    phi[1]=1;
    for(i=2; i<=5e6; i++)if(!phi[i])
        for(j=i; j<=5e6; j+=i){
            if(!phi[j])phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    phi[0]=0;
    return 0;
}

void phi_table(int maxn){
    for(int i=1;i<=maxn;i++)phi[i]=i;
    for(int i=2;i<=maxn;i+=2)phi[i]/=2;
    for(int i=3;i<=maxn;i+=2)
    if(phi[i]==i)for(int j=i;j<=maxn;j+=i)
        phi[j]=phi[j]/i*(i-1);
    return ;
}
//  以上是打表的形式  这是求单个的 
LL Phi(LL n)
{
    LL rea=n;
    for(int i=0; prime[i]*prime[i]<=n&&i<kp; i++)
    {
        if(n%prime[i]==0)
        {
            rea=rea-rea/prime[i];
            while(n%prime[i]==0)
                n/=prime[i];
        }
    }
    if(n>1)    rea=rea-rea/n;
    return rea;
}
/************************/
// O(n)求素数+欧拉函数
// 用最小的素因子筛掉每个数
int prime[N],phi[N],cnt;// prime:记录质数，phi记录欧拉函数
int Min_factor[N];// i的最小素因子
bool vis[N];
void Init(){
    cnt=0;
    phi[1]=1;
    int x;
    for(int i=2;i<N;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
            Min_factor[i]=i;
        }
        for(int k=1;k<=cnt&&prime[k]*i<N;k++){
            x=prime[k]*i;
            vis[x]=true;
            Min_factor[x]=prime[k];
            if(i%prime[k]==0){
                phi[x]=phi[i]*prime[k];
                break;
            }
            else phi[x]=phi[i]*(prime[k]-1);
        }
    }
}