// 威佐夫博弈(Wythoff Game)：有两堆各若干个物品，
// 两个人轮流从某一堆或同时从两堆中取同样多的物品，
// 规定每次至少取一个，多者不限，最后取光者得胜。

void (int n,int m){
    if(n<m)n=n^m,m=m^n,n=n^m;
    int k=n-m;
    n=(int)(k*(1+sqrt(5))/2.0);
    if(n==m) first lose;
    else first win;
}