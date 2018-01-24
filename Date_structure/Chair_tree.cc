/*******************************************
主席树(函数式线段树,可持久化线段树)

主席树(函数式线段树,可持久化线段树)其实就是维护多颗线段树, 
每更新一个元素,那么就根据它的上一状态新建一颗线段树,然后就是线段树的操作了, 
一般来维护(区间第K大,区间不同元素个数(在线做法)) 
每次新建一颗线段树,都只是开O(log(n))的节点, 
然后指向前一状态的其他不需要更新的节点,这样的话大大降低了总空间复杂度

主席树的具体维护要看不同情况而定,需要怎么维护就怎么维护即可 
主席树一般可以看做维护树与树的前缀和,
******************************************/

int rt[N*20];   //表示更新当前元素所形成的不同线段树的树根,
int ls[N*20];   //当前节点的左儿子
int rs[N*20];   //当前节点的右儿子
int sum[N*20];  //主席树节点维护的值
int tot;        //节点的标号

void build(int &rt,int l,int r){ //建树 一般是先建一颗空树(即没有元素更新在其上) 让之后的更新依他开始,
    rt=++tot;
    sum[rt]=0;
    if(l==r) return ;
    int m = (r+l)>>1;
    build(ls[rt],l,m);
    build(rs[rt],m+1,r);
}

void update(int &rt,int l,int r,int last,int pos){
    rt = ++tot;
    ls[rt]=ls[last];
    rs[rt]=rs[last];
    sum[rt]=sum[last]+1;
    if(l==r) return ;
    int m = (r+l)>>1;
    if(pos<=m) update(ls[rt],l,m,ls[last],pos);
    else       update(rs[rt],m+1,r,rs[last],pos);
}

int query(int ss,int tt,int l,int r,int k){
    if(l==r)return l;
    int m = (l+r)>>1;
    int cnt=sum[ls[tt]]-sum[ls[ss]];   
    if(k<=cnt) return query(ls[ss],ls[tt],l,m,k);
    else       return query(rs[ss],rs[tt],m+1,r,k-cnt);
}

/*******************************************
可修改的主席树

利用树状数组来维护修改信息

*******************************************/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define lson l, m
#define rson m+1, r
const int N=60005;
int a[N], Hash[N];
int T[N], L[N<<5], R[N<<5], sum[N<<5];
int S[N];
int n, m, tot;
struct node{
    int l, r, k;
    bool Q;
}op[10005];

int build(int l, int r){
    int rt=(++tot);
    sum[rt]=0;
    if(l>=r) return rt;
    int m=(l+r)>>1;
    L[rt]=build(lson);
    R[rt]=build(rson);
    return rt;
}

int update(int pre, int l, int r, int x, int val){
    int rt=(++tot);
    L[rt]=L[pre], R[rt]=R[pre], sum[rt]=sum[pre]+val;
    if(l>=r) return rt;
    int m=(l+r)>>1;
    if(x<=m)  L[rt]=update(L[pre], lson, x, val);
    else      R[rt]=update(R[pre], rson, x, val);
    return rt;
}

#define lowbit(x) (x&-x)
int use[N];
void add(int x, int pos, int val){
    for(;x<=n;x+=lowbit(x))
        S[x]=update(S[x], 1, m, pos, val);
}
int Sum(int x){
    int ret=0;
    for(;x>0;x-=lowbit(x)) ret+=sum[L[use[x]]];
    return ret;
}

int query(int u, int v, int lr, int rr, int l, int r, int k){
    if(l>=r)     return l;
    int m=(l+r)>>1;
    int tmp=Sum(v)-Sum(u)+sum[L[rr]]-sum[L[lr]];
    if(tmp>=k){
        for(int i=u;i;i-=lowbit(i)) use[i]=L[use[i]];
        for(int i=v;i;i-=lowbit(i)) use[i]=L[use[i]];
        return query(u, v, L[lr], L[rr], lson, k);
    }
    else{
        for(int i=u;i;i-=lowbit(i)) use[i]=R[use[i]];
        for(int i=v;i;i-=lowbit(i)) use[i]=R[use[i]];
        return query(u, v, R[lr], R[rr], rson, k-tmp);
    }
}

void modify(int x, int p, int d){
    for(;x<=n;x+=lowbit(x))
        S[x]=update(S[x], 1, m, p, d);
}

int main(){
    int _;
    for(scanf("%d", &_);_--;){
        int q;
        scanf("%d%d", &n, &q);
        tot=0; m=0;
        for(int i=1;i<=n;i++) {
            scanf("%d", &a[i]);
            Hash[++m]=a[i];
        }
        for(int i=0;i<q;i++) {
            char s[10];
            scanf("%s", s);
            if(s[0]=='Q') {
                scanf("%d%d%d", &op[i].l, &op[i].r, &op[i].k);
                op[i].Q=1;
            }
            else {
                scanf("%d%d", &op[i].l, &op[i].r);
                op[i].Q=0;
                Hash[++m]=op[i].r;
            }
        }
        sort(Hash+1, Hash+1+m);
        int mm=unique(Hash+1, Hash+1+m)-(Hash+1);
        m=mm;
        T[0]=build(1, m);
        for(int i=1;i<=n;i++) T[i]=update(T[i-1], 1, m, lower_bound(Hash+1, Hash+1+m, a[i])-Hash, 1);
        for(int i=1;i<=n;i++) S[i]=T[0];
        for(int i=0;i<q;i++)  {
            if(op[i].Q) {
                for(int j=op[i].l-1;j;j-=lowbit(j)) use[j]=S[j];
                for(int j=op[i].r  ;j;j-=lowbit(j)) use[j]=S[j];
                printf("%d\n", Hash[query(op[i].l-1, op[i].r, T[op[i].l-1], T[op[i].r], 1, m, op[i].k)]);
            }
            else {
                modify(op[i].l, lower_bound(Hash+1, Hash+1+m, a[op[i].l])-Hash, -1);
                modify(op[i].l, lower_bound(Hash+1, Hash+1+m,   op[i].r )-Hash,  1);
                a[op[i].l]=op[i].r;
            }
        }
    }
    return 0;
}
