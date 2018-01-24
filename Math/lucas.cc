LL Lucas(LL n,LL m,LL p) {
    if (m==0) return 1;
    return (C(n%p,m%p,p)*Lucas(n/p,m/p,p))%p;
}