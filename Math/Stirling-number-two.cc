/**********************************************************
第二类Stirling数
定理：第二类Stirling数S(p,k)计数的是把p元素集合划分到k个不可区分的盒子里且没有空盒子的划分个数。
递推公式有：
S(p,p)=1 (p>=0)
S(p,0)=0 (p>=1)
S(p,k)=k*S(p-1,k)+S(p-1,k-1)  (1<=k<=p-1)
**********************************************************/
long long s[maxn][maxn];//存放要求的Stirling数
const long long mod = 1e9 + 7; //取模

void init() { //预处理
    memset(s,0,sizeof(s));
    s[1][1]=1;
    for(int i=2;i<=maxn-1;i++)
        for(int j=1;j<=i;j++) {
            s[i][j]=s[i-1][j-1]+j*s[i-1][j];
            if (s[i][j]>=mod)
                s[i][j]%=mod;
        }
}