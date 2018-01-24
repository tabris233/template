LL exgcd_euclid(LL a,LL b,LL &x,LL &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    LL r=exgcd_euclid(b,a%b,x,y);
    LL t=x;x=y;y=t-a/b*y;
    return r;
}

LL exgcd(LL m,LL &x,LL n,LL &y){
    LL x1,x0,y1,y0;
    x0=1,y0=0;
    x1=0,y1=1;
    LL r=(m%n+n)%n;
    LL q=(m-r)/n;
    x=0,y=1;
    while(r){
        x=x0-q*x1,y=y0-q*y1,x0=x1,y0=y1;
        x1=x,y1=y;
        m=n,n=r,r=m%n;
        q=(m-r)/n;
    }
    return n;
}