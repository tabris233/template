/*************SPLAY-tree*********
Splay 为伸展树,也是一颗平衡树

第一种是 利用二叉排序树性质维护一堆数的
另一种是 利用伸展树性质维护一个序列的
***/

int n,m;

int ch[N][2];  //ch[][0] lson ch[][1] rson
int f[N];      //father
int sz[N];     //size
int val[N];    //value of node_i
int cnt[N];    //counts of the node_i
int root;      //root of splay-tree
int tot;       //tot,total,is the number of node of tree

void pushup(int x){
    if(x)sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
}

void rotate(int x,int k){   // k = 0 左旋， k = 1 右旋
    int y=f[x];int z=f[y];
    ch[y][!k]=ch[x][k];if(ch[x][k])f[ch[x][k]]=y;
    f[x]=z;if(z)ch[z][ch[z][1]==y]=x;
    f[y]=x;ch[x][k]=y;
    pushup(y),pushup(x);
}
// 单旋
// void splay(int x,int goal){
//     for(int y=f[x];f[x]!=goal;y=f[x])
//         rotate(x,(ch[y][0]==x));
//     if(goal==0) root=x;
// }
// 双旋
void splay(int x,int goal){//将x旋转到goal的下面  
    while(f[x] != goal){  
        if(f[f[x]] == goal) rotate(x , ch[f[x]][0] == x);  
        else   {  
            int y=f[x],z=f[y];  
            int K = (ch[z][0]==y);  
            if(ch[y][K] == x) rotate(x,!K),rotate(x,K);  
            else rotate(y,K),rotate(x,K);  
        }  
    }  
    pushup(x);  
    if(goal==0) root=x;  
}  
void newnode(int rt,int v,int fa){
//    printf("newnode : rt =  %d\n",rt);
    f[rt]=fa;val[rt]=v,sz[rt]=cnt[rt]=1;
    ch[rt][0]=ch[rt][1]=0;
}

void delnode(int &rt){ //其实是为内存回收做准备的  回头再完善
    f[rt]=val[rt]=sz[rt]=cnt[rt]=0;
    ch[rt][0]=ch[rt][1]=rt=0;
}

/***************************以下是DEBUG***************************/

void Traversal(int rt){
    if(!rt) return;
    Traversal(ch[rt][0]);
    printf("%d f[]=%d sz[]=%d lson=%d rson=%d val[]=%d\n",rt,f[rt],sz[rt],ch[rt][0],ch[rt][1],val[rt]);
    Traversal(ch[rt][1]);
}
void debug(){
    printf("ROOT = %d <---\n",root);
    Traversal(root);
}

/**************************以下是前置操作**************************/

//以x为根的子树 的极值点  0 极小 1 极大
int extreme(int x,int k){
    while(ch[x][k])x=ch[x][k];splay(x,0);
    return x;
}
//以x为根的子树 第k个数的位置
int kth(int x,int k){
    if(sz[ch[x][0]]+1<=k&&k<=sz[ch[x][0]]+cnt[x]) return x;
    else if(sz[ch[x][0]]>=k) return kth(ch[x][0],k);
    else return kth(ch[x][1],k-sz[ch[x][0]]-cnt[x]);
}
int search(int rt,int x){
        if(ch[rt][0]&&val[rt]>x) return search(ch[rt][0],x);
    else if(ch[rt][1]&&val[rt]<x)return search(ch[rt][1],x);
    else return rt;
}
/***************************以下是正经操作*************************/
//前驱
int prec(int x){
    int k=search(root,x);
    splay(k,0);//debug();
    if(val[k]<x) return k;
    return extreme(ch[k][0],1);
}
//后继
int sufc(int x){
    int k=search(root,x);
    splay(k,0);//debug();
    if(val[k]>x) return k;
    return extreme(ch[k][1],0);
}
//返回数值x的排名 
int rk(int x){
    int k=search(root,x);
    splay(k,0);
    return sz[ch[root][0]]+1;
}
//按照二叉排序树性质插入x
void _insert(int x){
    int y=search(root,x),k=-1;
    if(val[y]==x){
        cnt[y]++;
        sz[y]++;
        for(int yy=y;yy;yy=f[yy]) pushup(yy);
    }
    else {
        int p=prec(x),s=sufc(x);
        splay(p,0);splay(s,p);
        newnode(++tot,x,ch[root][1]);
        ch[ch[root][1]][0]=tot;
        for(int z=ch[root][1];z;z=f[z])pushup(z);
    }
    if(k==-1) splay(y,0);else splay(tot,0);
}

void _delete(int x){
    int y=search(root,x);
    if(val[y]!=x) return;
    if(cnt[y]>1){
        cnt[y]--;
        sz[y]--;
        for(int yy=y;yy;yy=f[yy]) pushup(yy);
    }
    else if(ch[y][0]==0||ch[y][1]==0){
        int z=f[y];
        ch[z][ch[z][1]==y]=ch[y][ch[y][0]==0];
        f[ch[y][ch[y][0]==0]]=z;delnode(y);
        for(int yy=z;yy;yy=f[yy]) pushup(yy);
    }
    else {
        int p=prec(x),s=sufc(x);
        splay(p,0);splay(s,p);
        ch[ch[root][1]][0]=0;
        delnode(ch[ch[root][1]][0]);
        for(int yy=s;yy;yy=f[yy]) pushup(yy);
    }
}

int main(){
    scanf("%d",&n);
    tot=0,root=1;
    newnode(++tot,-INF,0),newnode(++tot,INF,root);
    ch[root][1]=tot;
    for(int op,x;n--;){
        op=read(),x=read();
             if(op==1) _insert(x);
        else if(op==2) _delete(x);
        else if(op==3) printf("%d\n",rk(x)-1);
        else if(op==4) printf("%d\n",val[kth(root,x+1)]);
        else if(op==5) printf("%d\n",val[prec(x)]);
        else           printf("%d\n",val[sufc(x)]);
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

int n,m;

int ch[N][2];  //ch[][0] lson ch[][1] rson
int f[N];      //father
int sz[N];     //size
int val[N];    //value of node_i
int lazy[N];   //lazy-tag
int mi[N];     //min of son-tree : root of i
int rev[N];    //tag of revear
int root;      //root of splay-tree
int tot;       //tot,total,is the number of node of tree

void myswap(int &x,int &y){
    x^=y,y^=x,x^=y;
}
int min(int x,int y){
    return (x<y)?x:y;
}
void update_rev(int x){
    if(!x) return ;
    myswap(ch[x][0],ch[x][1]);
    rev[x]^=1;
}

void update_add(int x,int v){
    if(x) lazy[x]+=v,val[x]+=v,mi[x]+=v;
}

void pushdown(int x){
    if(!x) return ;
    if(lazy[x]){
        update_add(ch[x][0],lazy[x]);
        update_add(ch[x][1],lazy[x]);
        lazy[x]=0;
    }
    if(rev[x]){
        update_rev(ch[x][0]);
        update_rev(ch[x][1]);
        rev[x]=0;
    }
}

void pushup(int x){
    if(!x)return ;
    sz[x]=1,mi[x]=val[x];
    if(ch[x][0])sz[x]+=sz[ch[x][0]],mi[x]=min(mi[x],mi[ch[x][0]]);
    if(ch[x][1])sz[x]+=sz[ch[x][1]],mi[x]=min(mi[x],mi[ch[x][1]]);
}

void rotate(int x,int k){   // k = 0 左旋， k = 1 右旋
    int y=f[x];int z=f[y];
    pushdown(y),pushdown(x);
    ch[y][!k]=ch[x][k];if(ch[x][k])f[ch[x][k]]=y;
    f[x]=z;if(z)ch[z][ch[z][1]==y]=x;
    f[y]=x;ch[x][k]=y;
    pushup(y),pushup(x);
}
// 单旋
// void splay(int x,int goal){
//     for(int y=f[x];f[x]!=goal;y=f[x])
//         rotate(x,(ch[y][0]==x));
//     if(goal==0) root=x;
// }
// 双旋
void splay(int x,int goal){//将x旋转到goal的下面  
    while(f[x] != goal){  
        if(f[f[x]] == goal) rotate(x , ch[f[x]][0] == x);  
        else   {  
            int y=f[x],z=f[y];  
            int K = (ch[z][0]==y);  
            if(ch[y][K] == x) rotate(x,!K),rotate(x,K);  
            else rotate(y,K),rotate(x,K);  
        }  
    }  
    pushup(x);  
    if(goal==0) root=x;  
}  
void newnode(int rt,int v,int fa){
    f[rt]=fa;
    mi[rt]=val[rt]=v;sz[rt]=1;
    ch[rt][0]=ch[rt][1]=rev[rt]=lazy[rt]=0;
}
void delnode(int rt){
    f[rt]=mi[rt]=val[rt]=sz[rt]=0;
    ch[rt][0]=ch[rt][1]=rev[rt]=lazy[rt]=0;
}
void build(int &rt,int l,int r,int fa){
    if(l>r) return ;
    int m = r+l >> 1;
    rt=m; newnode(rt,val[rt],fa);
    build(ch[rt][0],l,m-1,rt);
    build(ch[rt][1],m+1,r,rt);
    pushup(rt);
}

void init(int n){
    root=0;
    f[0]=sz[0]=ch[0][0]=ch[0][1]=rev[0]=0;
    build(root,1,n,0);
    pushup(root);
}

/***************************以下是DEBUG***************************/
void Traversal(int rt){
    if(!rt) return;
    pushdown(ch[rt][0]);Traversal(ch[rt][0]);
    printf("%d f[]=%d sz[]=%d lson=%d rson=%d val[]=%d mi[]=%d \n",rt,f[rt],sz[rt],ch[rt][0],ch[rt][1],val[rt],mi[rt]);
    pushdown(ch[rt][1]);Traversal(ch[rt][1]);
    pushup(rt);
}
void debug(){
    printf("ROOT = %d <---\n",root);
    pushdown(root);
    Traversal(root);
}

/**************************以下是前置操作**************************/

//以x为根的子树 的最左节点
int x_left(int x){
    for(pushdown(x);ch[x][0];pushdown(x)) x=ch[x][0];
    return x;
}
//以x为根的子树 的最右节点
int x_right(int x){
    for(pushdown(x);ch[x][1];pushdown(x)) x=ch[x][1];
    return x;
}
//以x为根的子树 第k个数的位置
int kth(int x,int k){
    pushdown(x);
    if(sz[ch[x][0]]+1 == k) return x;
    else if(sz[ch[x][0]]>=k) return kth(ch[x][0],k);
    else return kth(ch[x][1],k-sz[ch[x][0]]-1);
}

/***************************以下是正经操作**************************/
/***
    如果有区间为[1,n]情况不好处理，
    所以我们可以 多添加一个head，一个tail
    这样的话区间[1,n]就是tail的左儿子了,
*/
//区间交换
void exchange(int l1,int r1,int l2,int r2){
    int x=kth(root,l2-1),y=kth(root,r2+1);
    splay(x,0),splay(y,x);
    int tmp_right = ch[y][0]; ch[y][0]=0;
    x=kth(root,l1-1),y=kth(root,l1);
    splay(x,0),splay(y,x);
    ch[y][0] = tmp_right;
    f[tmp_right]=y;
}

//区间翻转
void reversal(int l,int r){
    int x=kth(root,l-1),y=kth(root,r+1);
    splay(x,0);splay(y,x);
    update_rev(ch[y][0]);
}

//区间加
void add(int l,int r,int v){
    int x=kth(root,l-1),y=kth(root,r+1);
    splay(x,0);splay(y,x);
    update_add(ch[y][0],v);
}

//在第k个数后插入值为x的节点
void _insert(int k,int x){
    int r=kth(root,k),rr=kth(root,k+1);
    splay(r,0),splay(rr,r);
    newnode(++tot,x,rr);ch[rr][0]=tot;
    for(r=rr;r;r=f[r])pushdown(r),pushup(r);
    splay(rr,0);
}

//删除第k个数
void _delete(int k){
    splay(kth(root,k-1),0);
    splay(kth(root,k+1),root);
    delnode(ch[ch[root][1]][0]);
    ch[ch[root][1]][0]=0;
    pushup(ch[root][1]);
    pushup(root);
}

//int get_max(int l,int r){
//    int x=kth(root,l-1),y=kth(root,r+1);
//    splay(x,0);splay(y,x);
//    return mx[ch[y][0]];
//}

int get_min(int l,int r){
    int x=kth(root,l-1),y=kth(root,r+1);
    splay(x,0);splay(y,x);
    return mi[ch[y][0]];
}

/*****************************************************/

char s[12];

int main(){
    scanf("%d",&n);
    val[1]=val[n+2]=1000000000;
    for(int i=1+1;i<=n+1;i++) val[i]=read();
    tot=n+2;init(n+2);
    scanf("%d",&m);
    for(int i=1,d,l,r,v;i<=m;i++){
        scanf("%s",s);
        if(s[0]=='A'){ //ADD
            scanf("%d%d%d",&l,&r,&d);
            add(l+1,r+1,d);
        }
        else if(s[0]=='I'){ //INSERT
            scanf("%d%d",&l,&d);
            _insert(l+1,d);
        }
        else if(s[0]=='M'){ //MIN
            scanf("%d%d",&l,&r);
            printf("%d\n",get_min(l+1,r+1));
        }
        else if(s[0]=='D'){ //DELETE
            scanf("%d",&l);
            _delete(l+1);
        }
        else if(s[3]=='E'){ //REVERSE
            scanf("%d%d",&l,&r);
            reversal(l+1,r+1);
        }
        else { //REVOLVE
            scanf("%d%d%d",&l,&r,&d);
            d=(d%(r-l+1)+r-l+1)%(r-l+1);
            if(d) exchange(l +1,r-d +1,r-d+1 +1,r +1);
        }
    }
    return 0;
}