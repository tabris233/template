// X mod a[i] = b[i]
// 求(0,m]之间满足的X的个数

LL exgcd(LL a,LL b,LL &x,LL &y){
    if(!b){ x=1,y=0; return a; }
    else{
        int r = exgcd(b,a%b,x,y);
        int t = x;x = y;
        y = t - (a/b)*y;
        return r;
    }
}
LL a[11],b[11];

LL lcm(int a,int b){
    return a/__gcd(a,b)*b;
}

int main(){
    int _;
    for(scanf("%d",&_);_--;){
        int n,m;
        scanf("%d%d",&m,&n);
        for(int i=0;i<n;i++) scanf("%I64d",&a[i]);
        for(int i=0;i<n;i++) scanf("%I64d",&b[i]);

        bool flag = 1;
        LL x,y,r,t,m0=1;
        int a1,b1,c1;
        for(int i=0;i<n;i++) m0=lcm(m0,a[i]);

        for(int i=1;i<n&&flag;i++){ 
            a1 = a[0],b1 = a[i],c1=b[i]-b[0];
            r = exgcd(a1,b1,x,y);

            if(c1%r!=0) flag = 0; //当前方程 没有解

            t = b1/r;
            x=(x*(c1/r)%t+t)%t;
            b[0]=a[0]*x+b[0];
            a[0]=a[0]*(a[i]/r);
        }
        // 最后的b[0] 是最终的解

        int sum = 0;
        b[0]%=m0 ;

        if(b[0]<=m)         sum = 1+(m-b[0])/m0;//sum 求的是(0,m]之间解的个数
        if(sum&&b[0]==0)    sum--;  //要求正整数时 不能有0

        if(!flag)     puts("0");
        else printf("%d\n",sum);

    }
    return 0;
}
