// 如果mod 为素数
int get(int mod) {
    for(int i = 2; ; i++) {
        set<int> s;
        for(int j = 1, x = 1; j < mod; j++) {
            x = (x*i)%mod;
            s.insert(x);
        }
        if(s.size() == mod-1) return i;
    }
    return -1; //没有原根 ,但是不可能 素数一定有原根
}

----------------------------------------------------------------
//注意爆int，所以用LL
LL qmod(LL a,LL b,LL c){
    LL res = 1;a%=c;
    for(;b;b>>=1,a=a*a%c)
        if(b&1) res=res*a%c;
    return res;
}

int prime[N];
int Is_or[N][2];

void Prime(){
    int n = 100000;
    prime[0]=0;
    memset(Is_or,1,sizeof(Is_or));
    for(int i=2;i<=n;i++){
        if(Is_or[i][0]) prime[++prime[0]]=i,Is_or[i][1]=prime[0];
        for(int j=1;j<=prime[0]&&i*prime[j]<=n;j++){
            Is_or[i*prime[j]][0]=0;
            if(0==i%prime[j]) break;
        }
    }
    return ;
}

int Phi(int x){
    //因为本题中数据都是质数，所以欧拉函数值就都是x-1了。
    return x-1;
}

int a[10000],cnt;
void divide(int n){
    cnt = 0;
    for(int i=1;prime[i]*prime[i]<=n;i++){
        if(n<=prime[prime[0]]&&Is_or[n][0]){a[++cnt]=n;n=1;break;}
        if(n%prime[i]==0){a[++cnt]=prime[i];n/=prime[i];}
        while(n%prime[i]==0){n/=prime[i];}
    }
    if(n>1)a[++cnt]=n;
    return;
}

void work(int n){
    int phi = Phi(n);
    bool flag ;
    for(int i=2;i<n;i++){ //一个数的原根是很小的 所以暴力枚举就行,但其实是有优化方法的,
        flag = true;
        for(int j=1;j<=cnt;j++){
            int tmp = phi/a[j];
            if(qmod(i,tmp,n)==1){ flag = false; break; }
        }
        if(flag){ printf("%d\n",i);return ; }
    }
	puts("没有原根");
}

int main(){
    Prime();
    for(int n;~scanf("%d",&n);){
        divide(Phi(n));work(n);
    }
    return 0;
}