// 复杂度有时候会很坏 分解一个数组的时候要慎重
int prime[N],kp;
int Is_or[N][2];
void Prime(){
    kp = 0;
    memset(Is_or,true,sizeof(Is_or));
    Is_or[0][0]=Is_or[1][0]=0;
    for(int i=2;i<=100000;i++){
        if(Is_or[i][0]) Is_or[i][1]=kp,prime[kp++]=i;//记录其为第几个素数
        for(int j=0;j<kp&&prime[j]*i<=100000;j++){
            Is_or[prime[j]*i][0]=0;
            if(0==i%prime[j]) break;
        }
    }
    return ;
}
int main(){
    int tem;
    cin>>tem;
    for(int j=0;j<kp&&tem>=prime[j];j++){
        if(Is_or[tem][0]) {a[Is_or[tem][1]]++;break;}
        //if(0==tem%prime[j]) ;  
        while(0==tem%prime[j]) a[j]++,tem/=prime[j];
    }
}