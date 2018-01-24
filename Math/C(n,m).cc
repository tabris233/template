LL Fac[N],Inv[N];
LL qmod(LL a,LL b){
    LL res = 1ll;
    for(;b;b>>=1,a=a*a%MOD)
        if(b&1) res=res*a%MOD;
    return res;
}
void init(){
    //方法一  费马小定理
    fac[0]=1;
    for(LL i=1;i<N;i++)fac[i]=fac[i-1]*i%MOD;
    for(LL i=1;i<N;i++)inv[i]=qmod(fac[i],MOD-2);
 
    //方法二  inv{(n-i)!} = inv(n!)*n    //阶乘逆元
    Fac[0] = 1;
    for (LL i = 1; i < N; i++) Fac[i] = (Fac[i-1] * i) % MOD;
    Inv[N-1] = pow_mod(Fac[N-1], MOD-2);//Fac[N]^{MOD-2}
    for (LL i = N - 2; i >= 0; i--) Inv[i] = Inv[i+1] * (i + 1) % MOD;
}
LL C(int n,int m,int MOD){
	if(m>n) return 0;
	return Fac[n]*Inv[m]%MOD*Inv[n-m]%MOD;
}
LL A(int n,int m){
    if(m>n) return 0;
    return Fac[n]*Inv[n-m]%MOD;
}