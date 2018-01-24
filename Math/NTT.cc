/******************************************
类似FFT,也是求一类卷积问题,
在模意义下的卷积问题,对模数有要求.多数情况下为998244353
注意NTT的长度必须为2^k
******************************************/
const int Maxn=50000;
LL A[Maxn<<2],B[Maxn<<2];
int ans[Maxn<<2];
inline LL qmod(LL a, LL b,LL P) {
    LL ans=1;
    for(; b; b>>=1, a=a*a%P)
        if(b&1) ans=ans*a%P;
    return ans;
}
struct NTT {
    int pos[Maxn<<2],k,G,Mod;
    inline void init(int len) {
        Mod = 998244353,G = 3;
        for(k=1; k<=len; k<<=1);
        for(int i=1; i<k; i++)
            pos[i]=(i&1)?((pos[i>>1]>>1)^(k>>1)):(pos[i>>1]>>1);
    }
    inline void dft(LL *a) {
        for(int i=1; i<k; i++)if(pos[i]>i)swap(a[pos[i]],a[i]);
        for(int m1=1; m1<k; m1<<=1) {
            int m2=m1<<1;
            LL wn=qmod(G,(Mod-1)/m2,Mod)%Mod;
            for(int i=0; i<k; i+=m2) {
                LL w=1;
                for(int j=0; j<m1; j++) {
                    LL &A=a[i+j],&B=a[i+j+m1],t=B*w%Mod;
                    B=(A-t+Mod)%Mod;
                    A=(A+t)%Mod;
                    w=w*wn%Mod;
                }
            }
        }
    }
    inline void mui(LL *A,LL *B,int m) {
        init(m);
        dft(A);dft(B);
        for(int i=0; i<k; i++)A[i]=A[i]*B[i]%Mod;
        dft(A);
        reverse(A+1,A+k);
        int inv=qmod(k,Mod-2,Mod)%Mod;
        for(int i=0; i<k; i++)A[i]=inv*A[i]%Mod;
    }
} ntt;