/****************
CDQ分治解决[三维偏序]问题
一维排序 二维CDQ 三维BIT
对一个区间[l,r] 它的答案是 [l,m]+[m+1,r]+[l,m]对[m+1,r]影响的贡献
****************/
int n,m;
int f[N],ans[N];

typedef pair<pair<int,int>,pair<int,int> > node ;

node a[N],tl[N],tr[N];
bool cmp(node a,node b){return a.y<b.y;}

int sum[N];
#define lowbit(x) (x&-x)
int update(int i,int v){for(;i&&i<N;i+=lowbit(i))sum[i]+=v;}
int getSum(int i){int ans=0;for(;i;i-=lowbit(i))ans+=sum[i];return ans;}

void cal(int l,int r){
    int m = r+l >> 1;
    int ll=0,lr=0,pl=1,pr=1;
    for(int i=l  ;i<=m;i++) tl[++ll]=a[i];sort(tl+1,tl+ll+1,cmp);
    for(int i=m+1;i<=r;i++) tr[++lr]=a[i];sort(tr+1,tr+lr+1,cmp);

    vector<int> v;
    for(;pr<=lr;++pr){
        for(;pl<=ll&&tl[pl].y<=tr[pr].y;++pl){
            update(tl[pl].z,1);
            v.push_back(tl[pl].z);
        }
        ans[tr[pr].id]+=getSum(tr[pr].z);
    }
    for(int i=0;i<v.size();++i) update(v[i],-1);
}

void solve(int l,int r){
    if(l == r) return ;
    int m = r+l >> 1;
    solve(l  ,m);
    cal(l,r);
    solve(m+1,r);
}

int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
    sort(a+1,a+n+1);
    rep(i,1,n) a[i].id = i;
    solve(1,n);

    for(int i=n-1;i;i--)if(a[i].first==a[i+1].first && a[i].z == a[i+1].z){
        ans[i] = max(ans[i],ans[i+1]);
    }
    for(int i=1;i<=n;i++) ++f[ans[i]];
    for(int i=0;i<n;i++) printf("%d\n",f[i]);
    return 0;
}