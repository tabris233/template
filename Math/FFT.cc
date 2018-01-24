/***********************************************
用于快速求卷积c=a⊙b 
卷积可以类比两个多项式相乘 
正常暴力求卷积的复杂度是O(n^2) ,
通过FFT加速 求卷积的复杂度能降到O(nlog_{2}n) 
注意FFT的长度必须为2^k
***********************************************/
struct Complex{
    double real, image;
    Complex(double _real, double _image){
        real = _real;
        image = _image;
    }
    Complex(){}

    Complex operator + (const Complex &tmp){return Complex(real + tmp.real, image + tmp.image);}
    Complex operator - (const Complex &tmp){return Complex(real - tmp.real, image - tmp.image);}
    Complex operator * (const Complex &tmp){return Complex(real*tmp.real - image*tmp.image, real*tmp.image + image*tmp.real);}
};
int rev(int id, int len){
    int ret = 0;
    for(int i = 0; (1 << i) < len; i++){
        ret <<= 1;
        if(id & (1 << i)) ret |= 1;
    }
    return ret;
}
Complex A[N];
void FFT(Complex *a, int len, int DFT){
    for(int i = 0; i < len; i++)
        A[rev(i, len)] = a[i];
    for(int s = 1; (1 << s) <= len; s++){
        int m = (1 << s);
        Complex wm = Complex(cos(DFT*2*PI/m), sin(DFT*2*PI/m));
        for(int k = 0; k < len; k += m){
            Complex w = Complex(1, 0);
            for(int j = 0; j < (m >> 1); j++){
                Complex t = w*A[k + j + (m >> 1)];
                Complex u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w*wm;
            }
        }
    }
    if(DFT == -1) for(int i = 0; i < len; i++) A[i].real /= len, A[i].image /= len;
    for(int i = 0; i < len; i++) a[i] = A[i];
    return;
}
int main()
{
    /**
    求卷积c=a⊗b
    la为a的长度
    lb为b的长度
    len为最后结果的长度.
    **/
    int sa,sb;
    sa=sb=0;
    while((1<<sa)<la) sa++;
    while((1<<sb)<lb) sb++;
    int len = (1<<(max(sa,sb)+1));
    A = FFT(A,len,1);
    B = FFT(B,len,1);
    for(int i=0;i<len;i++)  A[i]=A[i]*B[i],ans[i]=0;
    A = FFT(A,len,-1);
    /**
    这是最后的卷积的结果.
    **/
}