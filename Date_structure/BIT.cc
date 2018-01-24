//一维树状数组
const int N = 50000 + 5;            //数列的大小
#define lowbit(x)  (x&(-x))         //lowbit操作
int sum[N],cnt;                     
void update(int index,int val){     //单点更新  （+val）
    for(int i=index;i<N;i+=lowbit(i)){//i<=N   不能<=cnt<--错了
        sum[i]+=val;
    }
}
int getSum(int index) {             //求解1~index的和
  int ans = 0;
  for (int i = index; i; i -= lowbit(i))
    ans += sum[i];
  return ans;
}
void update(int l,int r,int val){
    update(l,val),update(r+1,-val);
}
int query(int l,int r){
    return getSum(r)-getSum(l-1);
}
/*
一维区间更新（a,b）
update(a,1);
update(b+1,-1);
% 注意这种情况下 不能区间查询
*/

//二维区间更新
const int N = 1000+5;
#define lowbit(x) (x&-x)
LL sum[N][N];
void update(int xi,int yi,int val){
    for(int i=xi;i<=N;i+=lowbit(i))
        for(int j=yi;j<=N;j+=lowbit(j))
            sum[i][j]+=val;
    return;
}
int getSum(int xi,int yi){//就是(x,y)这个位置的值
    int ans = 0;
    for(int i=xi;i>0;i-=lowbit(i))
        for(int j=yi;j>0;j-=lowbit(j))
            ans+=sum[i][j];
    return ans ;
}
void update(int x,int y,int X,int Y,int val){
    update(x,y,val);
    update(x,Y+1,-val);
    update(X+1,y,-val);
    update(X+1,Y+1,val);
}
/*
二维区间更新{(a,b)|a∈[x,X],b∈[y,Y]} 
1.update(x,y,val); 
2.update(x,Y+1,-val); 
3.update(X+1,y,-val); 
4.update(X+1,Y+1,val); 
% 注意这种情况下 不能区间查询

*/