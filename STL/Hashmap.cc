Hashmap 

// 线性处理冲突

struct hashmap{
    unsigned long long int a[maxn];
    int head[hashh];
    int next[maxn];
    int b[maxn];
    int size,cnt;
    void init(){ //注意初始化
        memset(head,-1,sizeof(head));
        size=cnt=0;
    }
    bool find(unsigned long long int val){
        int tmp=(val%hashh+hashh)%hashh;
        for(int i=head[tmp];i!=-1;i=next[i])if(val==a[i])   
            return true;//b[i]; //可以映射为一个值 
        return false;//0;
    }
    void add(unsigned long long int val){
        int tmp=(val%hashh+hashh)%hashh;
        if(find(val))return ;
        a[size]=val;
        b[size]=++cnt;
        next[size]=head[tmp];//令next指向-1、
        head[tmp]=size++;
    }
}H;
