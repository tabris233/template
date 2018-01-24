/********************************************
尽量不要用除法，三角函数，强制类型转换（尤其是double转int）等操作，否则精度损失比较大 。 
const double PI = acos(-1.0); 
const double EPS = 1e-8; 
对小数点后1位 取整 的方法为 ±1 （+1位进位 -1为退位） 
eg：8(double)=7.9999999999….; 
8(int)=8; 
int(8(double))=7; !!!!!! 
这样精度损失就大了~~~~
********************************************/
#include <bits/stdc++.h>
typedef long long int LL;
using namespace std;

/*****************************************************/
const double eps = 1e-7;
const double Pi  = acos(-1.0);

double torad(double deg) { return deg / 180 * PI; }
inline int dcmp(double x){
    if(fabs(x)<eps) return 0;
    else     return x<0?-1:1;
}
struct Point{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y) { }
    inline void read(){scanf("%lf%lf", &x, &y);}
};
/***********************************
叉乘 
(P1->P0)*(P2->P0)的叉积
若结果为正,则<P0,P1>在<P0,P2>的顺时针方向; 
若为0则<P0,P1><P0,P2>共线;
若为负则<P0,P1>在<P0,P2>的在逆时针方向; 
***********************************/
double multi(Point p1,Point p2,Point p0){
    return ((p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x));
}
/***********************************
点乘 
(P0->P1)·(P0->P2)的点积
若结果为正,方向基本相同,夹角在0°到90°之间; 
若为0     ,正交,相互垂直;
若为负    ,方向基本相反,夹角在90°到180°之间; 
***********************************/
double dot(Point p1,Point p2,Point p0){
    return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y));
}

//两点距离
double dis(Point p1,Point p2){
    return(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
}

//极角排序
bool cmp(Point a,Point b){ //极角排序
    return a.y*b.x < a.x*b.y;
}

/***************
线段
***************/
//线段相交 s1e1 和 s2e2
bool IsIntersected(Point s1,Point e1,Point s2,Point e2) { //两个线段相交
    return(max(s1.x,e1.x)>=min(s2.x,e2.x))&&
          (max(s2.x,e2.x)>=min(s1.x,e1.x))&&
          (max(s1.y,e1.y)>=min(s2.y,e2.y))&&
          (max(s2.y,e2.y)>=min(s1.y,e1.y))&&
          (multi(s1,s2,e1)*multi(s1,e2,e1)<=0)&&
          (multi(s2,s1,e2)*multi(s2,e1,e2)<=0);
}
//两线段交点 /*AB与CD交点*/
point intersection(point &A,point &B,point &C,point &D){
    point p;
    double a1=A.y-B.y;
    double b1=B.x-A.x;
    double c1=A.x*B.y-B.x*A.y;

    double a2=C.y-D.y;
    double b2=D.x-C.x;
    double c2=C.x*D.y-D.x*C.y;

    p.x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
    p.y=(a2*c1-a1*c2)/(a1*b2-a2*b1);
    return p;
}

//相交圆面积
struct Round {
    double x, y;
    double r;
}
double solve(Round a, Round b){
    double d = dis(a, b);
    if (d >= a.r + b.r) return 0;
    if (d <= fabs(a.r - b.r)) {
        double r = a.r < b.r ? a.r : b.r;
        return PI * r * r;
    }
    double ang1 = acos((a.r * a.r + d * d - b.r * b.r) / 2. / a.r / d);
    double ang2 = acos((b.r * b.r + d * d - a.r * a.r) / 2. / b.r / d);
    double ret = ang1 * a.r * a.r + ang2 * b.r * b.r - d * a.r * sin(ang1);
    return ret;
}

//点到直线距离

/******************
点[p3]在向量[p1->p2]上的投影
设p0为p3在[p1->p2]的投影点
k = |P0-P1|/|P2-P1|
******************/
double k(Point p1,Point p2,point p3){
    return (P3-P1)*(P2-P1)/(|P2-P1|*|P2-P1|);
}

//三角形面积
// *已知三条边和[外]接圆半径,公式S = a*b*c/4/R
double trangle_Area(double a,double b,double c,double R){
    return a*b*c/4/R;
}
// *已知三条边和[内]接圆半径,公式S = a*b*c/4/R
double trangle_Area(double a,double b,double c,double R){
    return r*(a+b+c)/2.0;
}
// *已知三边求面积
double trangle_Area(double a,double b,double c){
    double p = (a+b+c)/2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
// *已知三点求面积
double trangle_Area(Point p1,Point p2,Point p3){
    double t = p1.y*(p3.x-p2.x)+p2.y*(p1.x-p3.x)+p3.y*(p2.x-p1.x);
    if(t<0) t=-t;
    return t/2.0;
}

//卷包法求凸包 (值得注意的是凸包大小<3的时候)
bool check(Point sp, Point ep, Point op){
    return (sp.x - op.x) * (ep.y - op.y) >= (ep.x - op.x) * (sp.y - op.y);
}
bool cmp_graham(Point a,Point b){
  return (a.y<b.y||a.y==b.y&&a.x<b.x);
}
// p[0~(n-1)]为点集 n为点集大小 res[0~(n-1)]/[1~n]为凸包集合
int graham(Point *p, int n, Point *res){
    int i,len,top=1;
    sort(p,p+n,cmp_graham); //排序
    if(n==0) return 0; res[0]=p[0];
    if(n==1) return 1; res[1]=p[1];
    if(n==2) return 2; res[2]=p[2];
    for (i=2;i<n;i++){
        while(top&&check(p[i],res[top],res[top-1])) top--;
        res[++top]=p[i];
    }
    len = top;
    res[++top]=p[n-2];
    for (i=n-3;i>=0;i--){
        while(top!=len&&check(p[i],res[top],res[top-1]))top--;
        res[++top]=p[i];
    }
    return top; //  返回凸包中点的个数
}

//旋转卡壳
double rotating_calipers(point *poi,int n) {
    int q=1;//第一个的对踵点是第二个（初始化） 
    double ans=0;//答案清零 
    poi[n]=poi[0];//最后一个点是它本身 （防+1溢出） 
    for(int p=0;p<n;p++){//找所有点 
        while(abs(multi(poi[p+1],poi[q+1],poi[p]))>abs(multi(poi[p+1],poi[q],poi[p])))//找三角形面积最大的：枚举法 
            q=(q+1)%n;//不忘模n 
        ans=max(ans,max(dis(poi[p],poi[q]),dis(poi[p+1],poi[q+1])));//三角形两边找一个最大的（还要处理p+1和q+1是防止平行） 
        ans=max(ans,max(dis(poi[p],poi[q+1]),dis(poi[p+1],poi[q])));
    } 
    return ans;
} 

//最小矩形覆盖凸包 *p 凸包点集 n 凸包个数
double Cross(Point a,Point b,Point c){  
    return (c.x-a.x)*(b.y-a.y) - (b.x-a.x)*(c.y-a.y);  
}  
double dot(Point p0,Point p1,Point p2){
    return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y));
}
double rotating_calipers(Point *p,int n){  
    int R=1,U=1,L;  
    double ans = 10000000000000;  
    p[n]=p[0];  
    for(int i=0;i<n;i++){  
        while(dcmp(Cross(p[i],p[i+1],p[U+1])-Cross(p[i],p[i+1],p[U]))<=0) U=(U+1)%n;//最上面一点  
        while(dcmp(dot(p[i],p[i+1],p[R+1])-dot(p[i],p[i+1],p[R]))>0) R=(R+1)%n;//最右一点  
        if(i==0) L=R;  
        while(dcmp(dot(p[i],p[i+1],p[L+1])-dot(p[i],p[i+1],p[L]))<=0) L=(L+1)%n;//最左一点  
        double d=dis(p[i],p[i+1])*dis(p[i],p[i+1]);  
        double area=fabs(Cross(p[i],p[i+1],p[U]))* //求面积  
            fabs(dot(p[i],p[i+1],p[R])-dot(p[i],p[i+1],p[L]))/d;  
        if(area<ans) ans = area;  
    }  
    return ans;  
}  

//半平面交
Point P[maxn];  
struct Line {  
    Point a, b;  
    double angle;  
    void getAngle() {angle = atan2(b.y-a.y, b.x-a.x);}  
} L[maxn], deq[maxn];  
  
int dcmp(double x) {  
    return x < -eps ? -1 : x > eps;  
}  
double xmult(Point a, Point b, Point c) {  
    return (a.x-c.x)*(b.y-c.y)-(a.y-c.y)*(b.x-c.x);  
}  
bool cmp(Line u, Line v) {  
    int d = dcmp(u.angle-v.angle);  
    if(d) return d > 0;  
    return dcmp(xmult(u.a, v.a, v.b)) > 0;  
    ///Clockwise:大于0取向量左半部分为半平面，小于0，取右半部分  
}  
Point intersection(Line u, Line v)  {  
    Point ret = u.a;  
    double t = ((u.a.x-v.a.x)*(v.a.y-v.b.y)  
               -(u.a.y-v.a.y)*(v.a.x-v.b.x))  
               /((u.a.x-u.b.x)*(v.a.y-v.b.y)  
               -(u.a.y-u.b.y)*(v.a.x-v.b.x));  
    ret.x += (u.b.x-u.a.x)*t, ret.y += (u.b.y-u.a.y)*t;  
    return ret;  
}  
bool judge(Line l1, Line l2, Line l3) {  
    Point p = intersection(l2, l3);  
    return dcmp(xmult(p, l1.a, l1.b)) < 0;  
    ///Clockwise:大于小于符号与上面cmp()中注释处相反  
}  
void HPI(Line L[], int n){  
    sort(L, L+n, cmp);  
    int tmp = 1;  
    for(int i = 1; i < n; ++i) {  
        if(dcmp(L[i].angle-L[tmp-1].angle) != 0) {  
            L[tmp++] = L[i];  
        }  
    }  
    n = tmp;  
    deq[0] = L[0], deq[1] = L[1];  
    head = 0, tail = 1;  
    for(int i = 2; i < n; ++i) {  
        while(head < tail && judge(L[i], deq[tail-1], deq[tail]))  
            tail--;  
        while(head < tail && judge(L[i], deq[head+1], deq[head]))  
            head++;  
        deq[++tail] = L[i];  
    }  
    while(head < tail && judge(deq[head], deq[tail-1], deq[tail]))  
        tail--;  
    while(head < tail && judge(deq[tail], deq[head+1], deq[head]))  
        head++;  
    if(head == tail) return ;  
    it = 0;  
    for(int i = head; i < tail; ++i) {  
        P[it++] = intersection(deq[i], deq[i+1]);  
    }  
    if(tail > head+1) {  
        P[it++] = intersection(deq[head], deq[tail]);  
    }  
}  
double getArea(Point p[], int n) {  
    double area = 0;  
    for(int i = 1; i < n-1; ++i) {  
        area += xmult(P[0], P[i], P[i+1]);  
    }  
    return fabs(area)/2.0;  
}  
  
int main()  {  
    int n;  
    while(~scanf("%d", &n)) {  
        n += 4;  //加四个点 表示四周
        L[0]=(Line){(Point){0, 10000}, (Point){0, 0}};  
        L[1]=(Line){(Point){10000, 10000}, (Point){0, 10000}};  
        L[2]=(Line){(Point){10000, 0}, (Point){10000, 10000}};  
        L[3]=(Line){(Point){0, 0}, (Point){10000, 0}};  
        L[0].getAngle(), L[1].getAngle(), L[2].getAngle(), L[3].getAngle();  
        for(int i = 4; i < n; ++i) {  
            scanf("%lf%lf%lf%lf", &L[i].a.x, &L[i].a.y, &L[i].b.x, &L[i].b.y);  
            L[i].getAngle();  
        }  
        HPI(L, n);  
        printf("%.1f\n", getArea(P, it));  
    }  
    return 0;  
}  

//**********************************************************
#include<math.h>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define PI acos(-1.0)//3.14159265358979323846
//判断一个数是否为0,是则返回true,否则返回false
#define zero(x)(((x)>0?(x):-(x))<eps)
//返回一个数的符号，正数返回1，负数返回2，否则返回0
#define _sign(x)((x)>eps?1:((x)<-eps?2:0))
struct point {
    double x,y;
};
struct line{
    point a,b;
};//直线通过的两个点，而不是一般式的三个系数
//求矢量[p0,p1],[p0,p2]的叉积
//p0是顶点
//若结果等于0，则这三点共线
//若结果大于0，则p0p2在p0p1的逆时针方向
//若结果小于0，则p0p2在p0p1的顺时针方向
double xmult(point p1,point p2,point p0){
    return(p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//计算dotproduct(P1-P0).(P2-P0)
double dmult(point p1,point p2,point p0){
    return(p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
//两点距离
double distance(point p1,point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
//判三点共线
int dots_inline(point p1,point p2,point p3){
    return zero(xmult(p1,p2,p3));
}
//判点是否在线段上,包括端点
int dot_online_in(point p,line l){
    return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
}
//判点是否在线段上,不包括端点
int dot_online_ex(point p,line l){
    return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y))&&
            (!zero(p.x-l.b.x)||!zero(p.y-l.b.y));
}
//判两点在线段同侧,点在线段上返回0
int same_side(point p1,point p2,line l){
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
//判两点在线段异侧,点在线段上返回0
int opposite_side(point p1,point p2,line l){
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
}
//判两直线平行
int parallel(line u,line v){
    return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
}
//判两直线垂直
int perpendicular(line u,line v){
    return zero((u.a.x-u.b.x)*(v.a.x-v.b.x)+(u.a.y-u.b.y)*(v.a.y-v.b.y));
}
//判两线段相交,包括端点和部分重合
int intersect_in(line u,line v){
    if(!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
        return!same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
    return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
}
//判两线段相交,不包括端点和部分重合
int intersect_ex(line u,line v){
    return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
//计算两直线交点,注意事先判断直线是否平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point intersection(line u,line v){
    point ret=u.a;
    double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))/
            ((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}
//点到直线上的最近点
point ptoline(point p,line l){
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    return intersection(p,t,l.a,l.b);
}
//点到直线距离
double disptoline(point p,line l){
    return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
//点到线段上的最近点
point ptoseg(point p,line l){
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    if(xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
        return distance(p,l.a)<distance(p,l.b)?l.a:l.b;
    return intersection(p,t,l.a,l.b);
}
//点到线段距离
double disptoseg(point p,line l){
    point t=p;
    t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
    if(xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
        return distance(p,l.a)<distance(p,l.b)?distance(p,l.a):distance(p,l.b);
    return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
}
struct TPoint{
    double x,y;
    TPoint operator-(TPoint&a){
        TPoint p1;
        p1.x=x-a.x;
        p1.y=y-a.y;
        return p1;
    }
};

struct TLine{
    double a,b,c;
};

//求p1关于p2的对称点
TPoint symmetricalPoint(TPoint p1,TPoint p2){
    TPoint p3;
    p3.x=2*p2.x-p1.x;
    p3.y=2*p2.y-p1.y;
    return p3;
}
//p点关于直线L的对称点
TPoint symmetricalPointofLine(TPoint p,TLine L){
    TPoint p2;
    double d;
    d=L.a*L.a+L.b*L.b;
    p2.x=(L.b*L.b*p.x-L.a*L.a*p.x-2*L.a*L.b*p.y-2*L.a*L.c)/d;
    p2.y=(L.a*L.a*p.y-L.b*L.b*p.y-2*L.a*L.b*p.x-2*L.b*L.c)/d;
    return p2;
}
//求线段所在直线,返回直线方程的三个系数
//两点式化为一般式
TLine lineFromSegment(TPoint p1,TPoint p2){
    TLine tmp;
    tmp.a=p2.y-p1.y;
    tmp.b=p1.x-p2.x;
    tmp.c=p2.x*p1.y-p1.x*p2.y;
    return tmp;
}
//求直线的交点
//求直线的交点，注意平行的情况无解，避免RE
TPoint LineInter(TLine l1,TLine l2){
    //求两直线得交点坐标
    TPoint tmp;
    double a1=l1.a;
    double b1=l1.b;
    double c1=l1.c;
    double a2=l2.a;
    double b2=l2.b;
    double c2=l2.c;
    //注意这里b1=0
    if(fabs(b1)<eps){
        tmp.x=-c1/a1;
        tmp.y=(-c2-a2*tmp.x)/b2;
    }
    else{
        tmp.x=(c1*b2-b1*c2)/(b1*a2-b2*a1);
        tmp.y=(-c1-a1*tmp.x)/b1;
    }
    //cout<<"交点坐标"<<endl;
    //cout<<a1*tmp.x+b1*tmp.y+c1<<endl;
    //cout<<a2*tmp.x+b2*tmp.y+c2<<endl;
    return tmp;
}
//矢量（点）V以P为顶点逆时针旋转angle(弧度)并放大scale倍
point rotate(point v,point p,double angle,double scale){
    point ret=p;
    v.x-=p.x,v.y-=p.y;
    p.x=scale*cos(angle);
    p.y=scale*sin(angle);
    ret.x+=v.x*p.x-v.y*p.y;
    ret.y+=v.x*p.y+v.y*p.x;
    return ret;
}
//矢量（点）V以P为顶点逆时针旋转angle(弧度)
point rotate(point v,point p,double angle){
    double cs=cos(angle),sn=sin(angle);
    v.x-=p.x,v.y-=p.y;
    p.x+=v.x*cs-v.y*sn;
    p.y+=v.x*sn+v.y*cs;
    return p;
}