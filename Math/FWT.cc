/*******************************************
解决一类卷积问题
c[x]=∑_{x=i◎j}a[i]×b[j] ,◎表示位运算
注意FWT的长度必须为2^k
*******************************************/
void FWT(int a[],int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%MOD,a[i+j+d]=(x-y+MOD)%MOD;
                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+MOD)%MOD;
                //and:a[i+j]=x+y;
                //or :a[i+j+d]=x+y;
            }
}
void UFWT(int a[],int n){
    const int rev = (MOD+1)>>1;
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*rev%MOD,a[i+j+d]=(1LL*(x-y)*rev%MOD+MOD)%MOD;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;  inv
                //and:a[i+j]=x-y;
                //or :a[i+j+d]=y-x;
            }
}
void solve(int a[],int b[],int n){
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%MOD;
    UFWT(a,n);
}