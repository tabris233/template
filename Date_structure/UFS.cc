//一般并查集
int pre[N];
int findi(int x){
    return pre[x]=(x==pre[x])?x:findi(pre[x]);
}
void join(int x,int y){
    int fx = findi(x),fy = findi(y);
    pre[fx]=fy;
    return ;
}

//带权并查集

int pre[N];
int findi(int x){
    if(pre[x]==x) return x;
    int r = findi(pre[x]);
    /**
    省略了权值间关系转化,具体视情况而定
    */
    pre[x]=r;
    return r;
}


//并查集(可拆点)

int pre[N],h[N],hh;
int findi(int x){
    if(pre[x]==x) return x;
    int r = findi(pre[x]);
    pre[x]=r;
    return r;
}
void join(int x,int y,int X,int Y){
    int fx = findi(x),fy = findi(y);
    pre[fx]=fy;
    return ;
}
void creat(int now){
    h[now]=++hh;
    pre[hh]=hh;
}

//可持久化
int n , m ;
struct node {
    int ls , rs ;
    int l , r ;
    int fa ;
    int dep ;
}a[200000 * 50];
  
int cnt ;
int root[200050];
  
int build(int l,int r) {
    ++cnt ;
    a[cnt].l = l ;a[cnt].r = r ;
    a[cnt].fa = l ;a[cnt].dep = 0 ;
    if(l == r)   return cnt;
    int mid = (l + r) >>1 ;
    int z = cnt ;
    a[z].ls = build(l , mid) ;
    a[z].rs = build(mid + 1 , r) ;
    return z ;
}
  
void upda(int x , int &y , int pos , int val) {
    y = ++cnt ;
    if(a[x].l == a[x].r) {
        a[y] = a[x] ;
        a[y].fa = val ;
        return ;
    }
    a[y] = a[x] ;
    int mid = (a[y].l + a[y].r) >>1 ;
    if(pos <= mid) upda(a[x].ls , a[y].ls , pos , val) ;
    else           upda(a[x].rs , a[y].rs , pos , val) ;
    return ;
}
  
int query(int x , int pos) {
    if(a[x].l == a[x].r) return x ;
    int mid = (a[x].l + a[x].r) >>1 ;
    if(pos <= mid) return query(a[x].ls , pos) ;
    else return query(a[x].rs , pos) ;
}
  
int find_(int x , int pos) {
    int p = query(x , pos) ;
    if(a[p].fa != pos)  return find_(x , a[p].fa) ;
    else return p ;
}
  
void add(int x , int pos) {
    if(a[x].l == a[x].r) {
        a[x].dep ++ ;
        return ;
    }
    int mid = (a[x].l + a[x].r) >>1 ;
    if(pos <= mid) add(a[x].ls , pos) ;
    else add(a[x].rs , pos) ;
}
  
int main() {
    while(scanf("%d%d",&n,&m) != EOF) {
        cnt=0;
        root[0]=build(1,n);
        int last=0;
        for(int i=1,op,q,w,k;i<=m;i++){
            scanf("%d",&op) ;
            if(op == 1) {
                scanf("%d%d",&q,&w) ;
                q ^= last ;
                w ^= last ;
                root[i] = root[i-1] ;
                int pp = find_(root[i] , q) ;
                int qq = find_(root[i] , w) ;
                if(a[pp].dep > a[qq].dep) swap(pp , qq) ;
  
                if(a[pp].fa == a[qq].fa) continue ;
  
                upda(root[i-1] , root[i] , a[pp].fa , a[qq].fa) ;
  
                if(a[pp].dep == a[qq].dep) 
                    add(root[i],a[qq].fa);
            }
            else if(op == 2) {
                scanf("%d",&k) ;
                root[i] = root[k^last] ;
            }
            else {
                scanf("%d%d",&q,&w);
                q^=last;w^=last;
                root[i]=root[i-1];
                int fq=find_(root[i-1],q);
                int fw=find_(root[i-1],w);
                if(fq!=fw) last=0;
                else last=1;
                printf("%d\n",last) ;
            }
        }
    }
}
