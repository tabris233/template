inline LL qmod(LL a, LL b,LL P) {
    LL ans=1;
    for(; b; b>>=1, a=a*a%P)
        if(b&1) ans=ans*a%P;
    return ans;
}