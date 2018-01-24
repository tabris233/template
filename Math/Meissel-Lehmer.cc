// 代码一: 
// 复杂度大概O(n^(3/4))

#include <bits/stdc++.h>  
#define ll long long  
using namespace std;  
ll f[340000],g[340000],n;  
void init(){  
    ll i,j,m;  
    for(m=1;m*m<=n;++m)f[m]=n/m-1;  
    for(i=1;i<=m;++i)g[i]=i-1;  
    for(i=2;i<=m;++i){  
        if(g[i]==g[i-1])continue;  
        for(j=1;j<=min(m-1,n/i/i);++j){  
            if(i*j<m)f[j]-=f[i*j]-g[i-1];  
            else f[j]-=g[n/i/j]-g[i-1];  
        }  
        for(j=m;j>=i*i;--j)g[j]-=g[j/i]-g[i-1];  
    }  
}  
int main(){  
    while(scanf("%I64d",&n)!=EOF){  
        init();  
        cout<<f[1]<<endl;  
    }  
    return 0;  
}  

// 代码二: 
// 复杂度大概O(n^(2/3))

#include<cstdio>  
#include<cmath>  
using namespace std;  
#define LL long long  
const int N = 5e6 + 2;  
bool np[N];  
int prime[N], pi[N];  
int getprime()  {  
    int cnt = 0;  
    np[0] = np[1] = true;  
    pi[0] = pi[1] = 0;  
    for(int i = 2; i < N; ++i)  {  
        if(!np[i]) prime[++cnt] = i;  
        pi[i] = cnt;  
        for(int j = 1; j <= cnt && i * prime[j] < N; ++j)  {  
            np[i * prime[j]] = true;  
            if(i % prime[j] == 0)   break;  
        }  
    }  
    return cnt;  
}  
const int M = 7;  
const int PM = 2 * 3 * 5 * 7 * 11 * 13 * 17;  
int phi[PM + 1][M + 1], sz[M + 1];  
void init()  {  
    getprime();  
    sz[0] = 1;  
    for(int i = 0; i <= PM; ++i)  phi[i][0] = i;  
    for(int i = 1; i <= M; ++i)  {  
        sz[i] = prime[i] * sz[i - 1];  
        for(int j = 1; j <= PM; ++j) phi[j][i] = phi[j][i - 1] - phi[j / prime[i]][i - 1];  
    }  
}  
int sqrt2(LL x)  {  
    LL r = (LL)sqrt(x - 0.1);  
    while(r * r <= x)   ++r;  
    return int(r - 1);  
}  
int sqrt3(LL x)  {  
    LL r = (LL)cbrt(x - 0.1);  
    while(r * r * r <= x)   ++r;  
    return int(r - 1);  
}  
LL getphi(LL x, int s)  {  
    if(s == 0)  return x;  
    if(s <= M)  return phi[x % sz[s]][s] + (x / sz[s]) * phi[sz[s]][s];  
    if(x <= prime[s]*prime[s])   return pi[x] - s + 1;  
    if(x <= prime[s]*prime[s]*prime[s] && x < N)  {  
        int s2x = pi[sqrt2(x)];  
        LL ans = pi[x] - (s2x + s - 2) * (s2x - s + 1) / 2;  
        for(int i = s + 1; i <= s2x; ++i) ans += pi[x / prime[i]];  
        return ans;  
    }  
    return getphi(x, s - 1) - getphi(x / prime[s], s - 1);  
}  
LL getpi(LL x)  {  
    if(x < N)   return pi[x];  
    LL ans = getphi(x, pi[sqrt3(x)]) + pi[sqrt3(x)] - 1;  
    for(int i = pi[sqrt3(x)] + 1, ed = pi[sqrt2(x)]; i <= ed; ++i) ans -= getpi(x / prime[i]) - i + 1;  
    return ans;  
}  
LL lehmer_pi(LL x)  {  
    if(x < N)   return pi[x];  
    int a = (int)lehmer_pi(sqrt2(sqrt2(x)));  
    int b = (int)lehmer_pi(sqrt2(x));  
    int c = (int)lehmer_pi(sqrt3(x));  
    LL sum = getphi(x, a) +(LL)(b + a - 2) * (b - a + 1) / 2;  
    for (int i = a + 1; i <= b; i++)  {  
        LL w = x / prime[i];  
        sum -= lehmer_pi(w);  
        if (i > c) continue;  
        LL lim = lehmer_pi(sqrt2(w));  
        for (int j = i; j <= lim; j++) sum -= lehmer_pi(w / prime[j]) - (j - 1);  
    }  
    return sum;  
}  

//照素数统计只多了这么个部分.. 
// 4因子个数统计
LL getans(LL x){ // x < 1e11
    LL ans = pi[sqrt3(x)];
    for(int i=1,ed=pi[sqrt2(x-1)];i<=ed;++i){
        ans += lehmer_pi(x/p[i])-i;
    }
    return ans;
}

int main(){  
    init(); 
    for(LL n;~scanf("%lld",&n);)  {  
        printf("%lld\n",lehmer_pi(n));  
    }  
    return 0;  
}  