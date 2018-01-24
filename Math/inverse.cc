1.exgcd
void exgcd(int a,int b,int &d,int &x,int &y){
    if(b==0) {
        x = 1,y = 0,d=a;
        return ;
    }
    exgcd(b,a%b,d,x,y);
    int t = x;
    x = y;
    y = t - ( a / b ) * y;
    return ;
}
int inv(int a){
    int x,y,d;
    exgcd(a,MOD,d,x,y);
    if(d==1)  return (x%MOD+MOD)%MOD;   //返回最小正整数解
    return -1;  //不存在逆元
}
2.Femat
int qmod(int a,int b){
    int res = 1;
    for(;b;b>>=1,a=a*a%MOD)
        if(b&1) res=res*a%MOD;
    return res;
}
int inv(int a){
    return qmod(a,MOD-2);
}