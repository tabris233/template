// - dfs
void dfs(int id,bool flag,int cnt){
    /**
    按要求计算值 cnt
    **/
    if(flag ) ans += cnt;
    else      ans -= cnt;
    for(int i=id+1;i<m;i++)dfs(i,!flag,cnt);
}
int main(){
    ans = 0;
    for(int i=0;i<m;i++) dfs(i,true,1);
    printf("%d\n",ans);
}

// - 二进制枚举
int ans = 0,num,sum;
for(int i=1;i<(1<<m);i++){
    num = 0, sum = 1;
    for(int j=0;j<m;j++){
        if(i&(1<<j)){
            /**
            按要求计算值 sum
            **/
            num++;
        }
    }
    if(num&1) ans+=sum;
    else      ans-=sum;
}