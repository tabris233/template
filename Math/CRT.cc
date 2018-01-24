LL CRT(LL a[],LL m[],LL len){ //x%m[i]=a[i],m[]必须满足两两互质
    LL i,x,y,M,n=1,ret=0;
    for(i=0; i<len; ++i) n*=m[i];
    for(i=0; i<len; ++i){
        M=n/m[i];
        exgcd(M,m[i],x,y);
        ret=(ret+qmod(qmod(x,M,n),a[i],n))%n;
    }
    return (ret+n)%n;
}