// 筛法求素数

// 埃拉托斯特尼筛法
void Prime(){
    memset(Or,0,sizeof(Or));
    for(int i=2;i<N;i++){
        if(Or[i]==0){
            p[++p[0]]=i;
            for(int j=i+i;j<N;j+=i)
                Or[j]=1;
        }
    }
}

// 线性筛
int prime[20000],kp=0;
int Is_or[65536];
void Prime(){
    int n =65536; //2~n之间的素数
    kp=0;
    memset(Is_or,1,sizeof(Is_or));
    Is_or[0]=Is_or[1]=0;
    for(int i=2;i<n;i++){
        if(Is_or[i])    prime[kp++]=i;
        for(int j=0;j<kp&&i*prime[j]<n;j++){
            Is_or[i*prime[j]]=0;
            if(i%prime[j]==0) break;
        }
    }
    return ;
}

// 区间筛 hdu 6069
// 给你1<=l<=r<=1e12,r-l<=1e6 ,问[l,r]区间有多少个素数
void Prime(){
    kp = 0;
    memset(Is,true,sizeof(Is));
    for(int i=2;i<N;i++){
        if(Is[i]){
            prime[kp++]=i;
            for(int j=i+i;j<N;j+=i) Is[j]=0;
        }
    }
//    printf("kp = %d\n",kp);
}
void Prime2(LL l,LL r){
    memset(Is,true,sizeof(Is));
    for(LL i=0,b;i<kp;i++){
        b=l/prime[i];
        while(b*prime[i]<l||b<=1) b++;
        for(LL j=b*prime[i];j<=r;j+=prime[i])if(j>=1){
            Is[j-l]=false
        }
    }
    if(l==1) Is[0]=false;
    return ;
}