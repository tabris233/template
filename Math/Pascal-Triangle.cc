/**************************************
k*C(n,k)=n*C(n-1,k-1); 
C(n,0)+C(n,2)+…=C(n,1)+C(n,3)+…
1*C(n,1)+2*C(n,2)+…+n*C(n,n)=n*2^(n-1)
**************************************/
LL f[2222][2222];
void init(){
    int n = 2000;
    for(int i=0; i<=n-1; i++)for(int j=0; j<=n-1; j++)
        f[i][0]=f[i][i]=1;
    for(int i=2; i<=n-1; i++)for(int j=1; j<=i-1; j++)
            f[i][j]=f[i-1][j-1]+f[i-1][j];
}
LL C(int n,int m){
    return f[n][m];
}
