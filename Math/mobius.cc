// Sqrt()计算
int mobius(int n){
	int m = 1;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			m*=-1;
			int k = 0;
			n/=i;
			if(n%i==0) {m=0;break;}//某个素因子的幂大于1
		}
	}
	if(n>1) m *= -1;
	return m;
}
// 普通筛法 求莫比乌斯函数
void mubius(){
    mu[1]=1;
    for(int i=1;i<=n;i++){
        for(int j=i+i;j<=n;i++)
            mu[j]-=mu[i];
    }
}

// 线性筛法预处理mobius函数
int prime[N],kp;
int Is_or[N],mu[N];

void Prime(){
    int x;
    mu[1]=1;
    memset(Is_or,true,sizeof(Is_or));
    for(int i=2;i<=n;i++){
        if(Is_or[i]) prime[kp++]=i,mu[i]=-1;
        for(int j=0;j<kp&&i*prime[j]<=n;j++){
            x = i*prime[j];
            Is_or[x]=false;
            if(0==i%prime[j]) break;
            mu[x] = -mu[i];
        }
    }
    return ;
}
