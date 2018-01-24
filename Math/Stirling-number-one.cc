/***************************************************
第一类Stirling数
定理：第一类Stirling数s(p,k)计数的是把p个对象排成k个非空循环排列的方法数。
递推公式为：
s(p,p)=1 (p>=0)  有p个人和p个圆圈，每个圆圈就只有一个人
s(p,0)=0 (p>=1)  如果至少有1个人，那么任何的安排都至少包含一个圆圈
s(p,k)=(p-1)*s(p-1,k)+s(p-1,k-1)
***************************************************/
long long s[maxn][maxn];//存放要求的第一类Stirling数  
const long long mod=1e9+7;//取模  
  
void init()//预处理  
{  
    memset(s,0,sizeof(s));  
    s[1][1]=1;  
    for(int i=2;i<=maxn-1;i++)  
        for(int j=1;j<=i;j++)  
    {  
        s[i][j]=s[i-1][j-1]+(i-1)*s[i-1][j];  
        if(s[i][j]>=mod)  
            s[i][j]%=mod;  
    }  
}  