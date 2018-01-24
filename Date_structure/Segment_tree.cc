/*********************************
线段树是重中之重,最考验思维的东西了
但线段树的编码很容易,这里给出维护[区间加+区间乘+区间和MOD]的代码+[二维线段树]
*********************************/

// 维护[区间加+区间乘+区间和MOD] -----------------------------------------
int n,p;
int a[N];

LL sum[N<<2],mul[N<<2],add[N<<2];

void pushup(int rt){
    sum[rt]=(sum[rt<<1]+sum[rt<<1|1])%p;
}

void pushdown(int rt,int l,int r){
    add[rt<<1]  =(add[rt<<1]  *mul[rt]+add[rt])%p;
    add[rt<<1|1]=(add[rt<<1|1]*mul[rt]+add[rt])%p;
    mul[rt<<1]  =(mul[rt<<1]  *mul[rt])%p;
    mul[rt<<1|1]=(mul[rt<<1|1]*mul[rt])%p;
    int m = r+l >> 1;
    sum[rt<<1]  =(sum[rt<<1]  *mul[rt]+add[rt]*(m-l+1))%p;
    sum[rt<<1|1]=(sum[rt<<1|1]*mul[rt]+add[rt]*(r-m))%p;
    add[rt]=0,mul[rt]=1;
}

void build(int rt,int l,int r){
    mul[rt]=1,add[rt]=0;
    if(l==r){sum[rt]=a[l]%p; return;}
    int m = r+l >> 1;
    build(rt<<1  ,l  ,m);
    build(rt<<1|1,m+1,r);
    pushup(rt);
}

void update(int rt,int l,int r,int L,int R,int tadd,int tmul){
    if(L<=l&&r<=R){
        if(tadd!=-1){
            add[rt]=(add[rt]+tadd)%p;
            sum[rt]=(sum[rt]+(LL)tadd*(r-l+1))%p;
        }
        if(tmul!=-1){
            add[rt]=(add[rt]*tmul)%p;
            mul[rt]=(mul[rt]*tmul)%p;
            sum[rt]=(sum[rt]*tmul)%p;
        }
        return ;
    }
    pushdown(rt,l,r);
    int m = r+l >> 1;
    if(L<=m) update(rt<<1  ,l  ,m,L,R,tadd,tmul);
    if(R> m) update(rt<<1|1,m+1,r,L,R,tadd,tmul);
    pushup(rt);
    return ;
}

LL query(int rt,int l,int r,int L,int R){
    if(L<=l&&r<=R)    return sum[rt]%p;
    pushdown(rt,l,r);
    int m = r+l >> 1;LL ans = 0;
    if(L<=m) ans=(ans+query(rt<<1  ,l  ,m,L,R))%p;
    if(R> m) ans=(ans+query(rt<<1|1,m+1,r,L,R))%p;
    pushup(rt);
    return ans%p;
}

int main(){
    while(~scanf("%d%d",&n,&p)){
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        build(1,1,n);
        int m ;scanf("%d",&m);
        int op,l,r,c;
        while(m--){
            scanf("%d",&op);
            if(op==1){//区间加
                scanf("%d%d%d",&l,&r,&c);
                update(1,1,n,l,r,-1,c);
            }
            else if(op==2){//区间乘
                scanf("%d%d%d",&l,&r,&c);
                update(1,1,n,l,r,c,-1);
            }
            else {
                scanf("%d%d",&l,&r);
                printf("%lld\n",query(1,1,n,l,r));
            }
        }
    }
    return 0;
}

// 维护[二维最大值,最小值]-----------------------------------------
//实现二 : 树套树实现

#define y0 fucky0
#define y1 fucky1
int mmin,mmax,x0,y0,x1,y1; //待查询的矩形+查询出来的最大最小值

int mx[N<<2][N<<2];
int mn[N<<2][N<<2];

void pushup(int rt,int xrt){
    mx[xrt][rt]=max(mx[xrt][rt<<1],mx[xrt][rt<<1|1]);
    mn[xrt][rt]=min(mn[xrt][rt<<1],mn[xrt][rt<<1|1]);
}
void buildY(int rt,int l,int r,int xrt,int x){
    if(l==r){
        if(x<0){
            mx[xrt][rt]=max(mx[xrt<<1][rt],mx[xrt<<1|1][rt]);
            mn[xrt][rt]=min(mn[xrt<<1][rt],mn[xrt<<1|1][rt]);
        }
        else {
            mx[xrt][rt]=mn[xrt][rt]=a[x][l];
        }
        return ;
    }
    int m = r+l >> 1;
    buildY(rt<<1  ,l  ,m,xrt,x);
    buildY(rt<<1|1,m+1,r,xrt,x);
    pushup(rt,xrt);
}
void buildX(int rt,int l,int r){
    if(l==r){
        buildY(1,1,n,rt,l);
        return ;
    }
    int m = r+l >> 1;
    buildX(rt<<1  ,l  ,m);
    buildX(rt<<1|1,m+1,r);
    buildY(1,1,n,rt,-1);
}
void updateY(int rt,int l,int r,int xrt,int x,int y,int v){
    if(l==r){
        if(x<0){
            mx[xrt][rt]=max(mx[xrt<<1][rt],mx[xrt<<1|1][rt]);
            mn[xrt][rt]=min(mn[xrt<<1][rt],mn[xrt<<1|1][rt]);
        }
        else {
            mx[xrt][rt]=mn[xrt][rt]=v;
        }
        return ;
    }
    int m = r+l >> 1;
    if(y<=m) updateY(rt<<1  ,l  ,m,xrt,x,y,v);
    else     updateY(rt<<1|1,m+1,r,xrt,x,y,v);
    pushup(rt,xrt);
}
void updateX(int rt,int l,int r,int x,int y,int v){
    if(l==r){
        updateY(1,1,n,rt,l,y,v);
        return ;
    }
    int m = r+l >> 1;
    if(x<=m) updateX(rt<<1  ,l  ,m,x,y,v);
    else     updateX(rt<<1|1,m+1,r,x,y,v);
    updateY(1,1,n,rt,-1,y,v);
}
void queryY(int rt,int l,int r,int xrt){
    if(y0<=l&&r<=y1){
        mmin=min(mmin,mn[xrt][rt]);
        mmax=max(mmax,mx[xrt][rt]);
        return ;
    }
    int m = r+l >> 1;
    if(y0<=m) queryY(rt<<1  ,l  ,m,xrt);
    if(y1> m) queryY(rt<<1|1,m+1,r,xrt);
}
void queryX(int rt,int l,int r){
    if(x0<=l&&r<=x1){queryY(1,1,n,rt);return;}
    int m = r+l >> 1;
    if(x0<=m) queryX(rt<<1  ,l  ,m);
    if(x1> m) queryX(rt<<1|1,m+1,r);
}


int main(){
    int _ = 1,kcase = 0;
    for(scanf("%d",&_);_--;){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
        buildX(1,1,n);
        int x,y,l;
        printf("Case #%d:\n",++kcase);
        for(scanf("%d",&m);m--;){
            scanf("%d%d%d",&x,&y,&l);

            x0=max(1,x-l/2);  
            y0=max(1,y-l/2);  
            x1=min(n,x+l/2);  
            y1=min(n,y+l/2); 
            mmin=INF,mmax=-INF;

            queryX(1,1,n);
            printf("%d\n",(mmin+mmax)/2);
            updateX(1,1,n,x,y,(mmin+mmax)/2);
        }
    }
    return 0;
}

// [矩形面积并] -----------------------------------------
int n;
struct Seg {
    double l, r, h; int d;
    Seg() {}
    Seg(double l, double r, double h, int d): l(l), r(r), h(h), d(d) {}
    bool operator< (const Seg& rhs) const {return h < rhs.h;}
} a[N];

int cnt[N << 2]; //根节点维护的是[l, r+1]的区间
double sum[N << 2], all[N];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void push_up(int l, int r, int rt) {
    if(cnt[rt]) sum[rt] = all[r + 1] - all[l];
    else if(l == r) sum[rt] = 0; //leaves have no sons
    else sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int L, int R, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        cnt[rt] += v;
        push_up(l, r, rt);
        return;
    }
    int m = l + r >> 1;
    if(L <= m) update(L, R, v, lson);
    if(R > m) update(L, R, v, rson);
    push_up(l, r, rt);
}

int main() {
    int kase = 0;
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 1; i <= n; ++i) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a[i] = Seg(x1, x2, y1, 1);
            a[i + n] = Seg(x1, x2, y2, -1);
            all[i] = x1; all[i + n] = x2;
        }
        n <<= 1;
        sort(a + 1, a + 1 + n);
        sort(all + 1, all + 1 + n);
        int m = unique(all + 1, all + 1 + n) - all - 1;

        memset(cnt, 0, sizeof cnt);
        memset(sum, 0, sizeof sum);

        double ans = 0;
        for(int i = 1; i < n; ++i) {
            int l = lower_bound(all + 1, all + 1 + m, a[i].l) - all;
            int r = lower_bound(all + 1, all + 1 + m, a[i].r) - all;
            if(l < r) update(l, r - 1, a[i].d, 1, m, 1);
            ans += sum[1] * (a[i + 1].h - a[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++kase, ans);
    }
    return 0;
}

// [矩形面积交] -----------------------------------------
int n;
struct Seg {
    double l, r, h; int d;
    Seg() {}
    Seg(double l, double r, double h, double d): l(l), r(r), h(h), d(d) {}
    bool operator< (const Seg& rhs) const {
        return h < rhs.h;
    }
} a[N];

int cnt[N << 2];
double one[N << 2], two[N << 2], all[N];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void push_up(int l, int r, int rt) {
    if(cnt[rt] >= 2) two[rt] = one[rt] = all[r + 1] - all[l];
    else if(cnt[rt] == 1) {
        one[rt] = all[r + 1] - all[l];
        if(l == r) two[rt] = 0;
        else two[rt] = one[rt << 1] + one[rt << 1 | 1];
    } else {
        if(l == r) one[rt] = two[rt] = 0;
        else {
            one[rt] = one[rt << 1] + one[rt << 1 | 1];
            two[rt] = two[rt << 1] + two[rt << 1 | 1];
        }
    }
}

void update(int L, int R, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        cnt[rt] += v;
        push_up(l, r, rt);
        return;
    }
    int m = l + r >> 1;
    if(L <= m) update(L, R, v, lson);
    if(R > m) update(L, R, v, rson);
    push_up(l, r, rt);
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a[i] = Seg(x1, x2, y1, 1);
            a[i + n] = Seg(x1, x2, y2, -1);
            all[i] = x1; all[i + n] = x2;
        }
        n <<= 1;
        sort(a + 1, a + 1 + n);
        sort(all + 1, all + 1 + n);
        int m = unique(all + 1, all + 1 + n) - all - 1;

        memset(cnt, 0, sizeof cnt);
        memset(one, 0, sizeof one);
        memset(two, 0, sizeof two);

        double ans = 0;
        for(int i = 1; i < n; ++i) {
            int l = lower_bound(all + 1, all + 1 + m, a[i].l) - all;
            int r = lower_bound(all + 1, all + 1 + m, a[i].r) - all;
            if(l < r) update(l, r - 1, a[i].d, 1, m, 1);
            ans += two[1] * (a[i + 1].h - a[i].h);
        }
        printf("%.2f\n", ans);
    }
    return 0;
}

// [矩形周长并] -----------------------------------------
int n, m[2];
int sum[N << 2], cnt[N << 2], all[2][N];
struct Seg {
    int l, r, h, d;
    Seg() {}
    Seg(int l, int r, int h, int d): l(l), r(r), h(h), d(d) {}
    bool operator< (const Seg& rhs) const {return h < rhs.h;}
} a[2][N];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

void push_up(int p, int l, int r, int rt) {
    if(cnt[rt]) sum[rt] = all[p][r + 1] - all[p][l];
    else if(l == r) sum[rt] = 0;
    else sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void update(int p, int L, int R, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        cnt[rt] += v;
        push_up(p, l, r, rt);
        return;
    }
    int m = l + r >> 1;
    if(L <= m) update(p, L, R, v, lson);
    if(R > m) update(p, L, R, v, rson);
    push_up(p, l, r, rt);
}

int main() {
    while(scanf("%d", &n) == 1) {
        for(int i = 1; i <= n; ++i) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            all[0][i] = x1, all[0][i + n] = x2;
            all[1][i] = y1, all[1][i + n] = y2;
            a[0][i] = Seg(x1, x2, y1, 1);
            a[0][i + n] = Seg(x1, x2, y2, -1);
            a[1][i] = Seg(y1, y2, x1, 1);
            a[1][i + n] = Seg(y1, y2, x2, -1);
        }
        n <<= 1;
        sort(all[0] + 1, all[0] + 1 + n);
        m[0] = unique(all[0] + 1, all[0] + 1 + n) - all[0] - 1;
        sort(all[1] + 1, all[1] + 1 + n);
        m[1] = unique(all[1] + 1, all[1] + 1 + n) - all[1] - 1;
        sort(a[0] + 1, a[0] + 1 + n);
        sort(a[1] + 1, a[1] + 1 + n);

//      for(int i = 0; i < 2; ++i){
//          for(int j = 1; j <= m[i]; ++j) cout << all[i][j] <<' '; cout << endl;
//      } cout << endl;

        int ans = 0;
        for(int i = 0; i < 2; ++i) {
            int t = 0, last = 0;
            memset(cnt, 0, sizeof cnt);
            memset(sum, 0, sizeof sum);
            for(int j = 1; j <= n; ++j) {
                int l = lower_bound(all[i] + 1, all[i] + 1 + m[i], a[i][j].l) - all[i];
                int r = lower_bound(all[i] + 1, all[i] + 1 + m[i], a[i][j].r) - all[i];
                if(l < r) update(i, l, r - 1, a[i][j].d, 1, m[i], 1);
                t += abs(sum[1] - last);
                last = sum[1];
            }
            ans += t;
        }
        printf("%d\n", ans);
    }
    return 0;
}

// [线段树合并] -----------------------------------------

/*****************************
是对多颗同样的线段树进行合并的操作,
合并过程对左右子树的关系进行计算.
对每个节点建立一颗线段树,进而在回溯的过程中进行合并
*****************************/

LL sum[N*10],ans,cnt0,cnt1;
int l[N],r[N],v[N],cnt ;
int ls[N*10],rs[N*10],root[N],tot;
 
void rd(int x){
    v[x]=read();
    if(!v[x]){
        l[x]=++cnt;rd(l[x]);
        r[x]=++cnt;rd(r[x]);
    }
}
 
void pushup(int rt){
    sum[rt]=sum[ls[rt]]+sum[rs[rt]];
}
 
void build(int &rt,int l,int r,int pos){
    if(0==rt)rt=++tot,ls[rt]=rs[rt]=0;
    if(l==r){sum[rt]=1;return;}
    int m = r+l >>1;
    if(pos<=m) build(ls[rt],l  ,m,pos);
    else       build(rs[rt],m+1,r,pos);
    pushup(rt);
}
 
int marge(int x,int y){
    if(!x)return y;if(!y)return x;
    cnt0+=sum[rs[x]]*sum[ls[y]]; // no change
    cnt1+=sum[ls[x]]*sum[rs[y]]; // change
    ls[x]=marge(ls[x],ls[y]);
    rs[x]=marge(rs[x],rs[y]);
    pushup(x);
    return x;
}
 
void solve(int x){
    if(!x) return ;
    solve(l[x]),solve(r[x]);
    if(!v[x]){
        cnt0=cnt1=0;
        root[x]=marge(root[l[x]],root[r[x]]);
        ans+=min(cnt0,cnt1);
    }
}
 
int n;
int main(){
    tot = cnt = 0;
    n=read();
    rd(++cnt);
    for(int i=1;i<=cnt;i++)if(v[i])
        build(root[i],1,n,v[i]);
    solve(1);
    printf("%lld",ans);
    return 0;
}