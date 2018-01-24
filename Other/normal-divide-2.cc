struct P{
    int x, y;
    bool operator <(const P& B)const { return x < B.x; }
}p[100050];
int dis(P &A, P &B) { return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y); }
P Q[100050];
int Divide(int l, int r){
    if(l == r) return 1e7;
    int mid = (l+r)>>1, d, tx = p[mid].x, tot = 0;
    d = min(Divide(l, mid), Divide(mid+1, r));
    for(int i = l, j = mid+1; (i <= mid || j <= r); i++){
        while(j <= r && (p[i].y > p[j].y || i > mid)) Q[tot++] = p[j], j++; //归并按y排序
        if(abs(p[i].x - tx) < d && i <= mid) { //选择中间符合要求的点
            for(int k = j-1; k > mid && j-k < 3; k--) d = min(d, dis(p[i], p[k]));
            for(int k = j; k <= r && k-j < 2; k++) d = min(d, dis(p[i], p[k]));
        }
        if(i <= mid) Q[tot++] = p[i];
    }
    for(int i = l, j = 0; i <= r; i++, j++) p[i] = Q[j];
    return d;
}
int main(){
    int n;cin>>n;
    for(int i = 1; i <= n; i++) cin>>p[i].x>>p[i].y;
    sort(p+1, p+1+n); cout<<Divide(1, n)<<endl;
}