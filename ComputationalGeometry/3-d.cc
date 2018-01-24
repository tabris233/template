/********************************************
三维空间
********************************************/
//点,线,面
struct point{
    double x,y,z;
};
struct line{
    point a,b;
};
struct plane{
    point a,b,c;
};
//计算 cross product U x V
point xmult(point u,point v){
    point ret;
    ret.x=u.y*v.z-v.y*u.z;
    ret.y=u.z*v.x-u.x*v.z;
    ret.z=u.x*v.y-u.y*v.x;
    return ret;
}
//计算 dot product  U . V
double dmult(point u,point v){
    return u.x*v.x+u.y*v.y+u.z*v.z;
}
//矢量差 U - V
point subt(point u,point v){
    point ret;
    ret.x=u.x-v.x;
    ret.y=u.y-v.y;
    ret.z=u.z-v.z;
    return ret;
}
//取平面法向量
point pvec(plane s){
    return xmult(subt(s.a,s.b),subt(s.b,s.c));
}
point pvec(point s1,point s2,point s3){
    return xmult(subt(s1,s2),subt(s2,s3));
}
//两点距离,单参数取向量大小
double dis(point p1,point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}
// 向量大小
double vlen(point p){
    return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}
//判断四点是不是共面
bool judge(point a,point b,point c,point d){
    double tmp = dmult(prec(a,b,c),smult(d,a));
    return  ( abs(tmp) < eps );
}
//点到平面距离
double ptoplane(point p,point s1,point s2,point s3){
    return fabs(dmult(pvec(s1,s2,s3),subt(p,s1)))/vlen(pvec(s1,s2,s3));
}
//三角形面积
double Area_triangle(point a,point b,point c){
    double ab=dis(a,b),bc=dis(b,c),ac=dis(a,c);
    double p=(ab+bc+ac)/2;
    return sqrt(p* (p-ab) * (p-bc)*(p-ac));
}
double Area_triangle(point b,point p1,point p2){
    point a=xmult(smult(b,p1),smult(b,p2));
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z)/2.0;
}
