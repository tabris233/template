struct LT{
    const static int maxn=N;
    int tot=0,v[maxn],l[maxn],r[maxn],d[maxn],fa[maxn];
    int merge(int x,int y){ //合并两个堆 然后返回写的堆顶
        if(!x) return fa[x]=y;
        if(!y) return fa[y]=x;
        if(v[x]<v[y])swap(x,y);
        
        r[x]=merge(r[x],y);
        fa[r[x]]=x;

        if(d[l[x]]<d[r[x]]) swap(l[x],r[x]);

        d[x]=d[r[x]]+1;
        return x;
    }
    int init(int x){//初始化一个权值为x的点
        tot++;
        v[tot]=x;
        l[tot]=r[tot]=d[tot]=0;
        fa[tot]=-1;
        return tot;
    }
    int insert(int x,int y){//往第x个左偏树插入一个权值为y的点
        return merge(x,init(y));
    }
    int pop(int x){ //将堆顶pop出去 返回写的根
        int root=merge(l[x],r[x]);
        fa[root]=-1;
        l[x]=r[x]=0;
        return root;
    }
    int root(int x){
        while(fa[x]!=-1) x=fa[x];
        return x;
    }
    int top(int x){return v[root(x)];} 
}lt;