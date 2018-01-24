// O(1)解决快速乘取膜
LLu qmodx(LLu a,LLu b,LLu c){
    a%=c,b%=c;
    if(c<=1000000000) return a*b%c;
    return (a*b-(LLu)(a/(long double)c*b+1e-8)*c+c)%c;
}