const int M = 4; // 方阵的大小为 M*M
struct Matrix{
    LL m[M][M];
    void clear0(){
        for(int i=0;i<M;i++)for(int j=0;j<M;j++)
                m[i][j]=0;
    }
    void clearE(){
        for(int i=0;i<M;i++)for(int j=0;j<M;j++)
                m[i][j]=(i==j);
    }
};
Matrix operator * (Matrix &a,Matrix &b){
    Matrix c;c.clear0();
    for(int k=0;k<M;k++)for(int i=0;i<M;i++)for(int j=0;j<M;j++)
                c.m[i][j]=(c.m[i][j]+a.m[i][k]*b.m[k][j]+MOD)%MOD;
    return c;
}
Matrix operator ^ (Matrix &a,LL b){
    Matrix c;c.clearE();
    for(;b;b>>=1,a=a*a)
        if(b&1) c=c*a;
    return c;
}