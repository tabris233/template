BigInteger or BigDecimal

import java.io.*;
import java.util.*;
import java.math.BigInteger;  
public class Main{
    public static void main(String args[]) throws Exception {
        Scanner cin=new Scanner(System.in); //输入
        int t,n;
        n = cin.nextInt(); //整数输入
        System.out.println("Case #"+cas+": "+m); //Java 输出

        BigInteger a; //大数声明 一
        BigInteger b; //大数声明 一

        BigInteger.valueOf(mod) //大数声明 二  直接计算 ，类似C++强转 支持整型和string类型
        
        cin.BigInteger();//读入一个BigInteger;

        //大数运算
        a.add(b)    //a+b;
        a.subtract(); //相减
        a.multiply(); //相乘
        a.divide();   //相除取整
        a.remainder();//取余
        a.pow();      //a.pow(b)=a^b
        a.gcd();      //最大公约数
        a.abs();      //绝对值 |a|
        a.negate();   //取反数 -a
        a.mod();      //a.mod(b)=a%b=a.remainder(b);
        max();min();  //
        if( a.compareTo(b) == 0 ) System.out.println("a == b"); //大整数a==b
    else if( a.compareTo(b) > 0 ) System.out.println("a > b"); //大整数a>b
    else if( a.compareTo(b) < 0 ) System.out.println("a < b"); //大整数a<b
        boolean equals(); //是否相等
        //
        a.toString()  // 转换为字符串
    }
}

BigDecimal //并且保留小数点后2位小数
DecimalFormat df = new DecimalFormat("0.00"); // 保留几位小数

stripTrailingZeros() //去掉小数末尾多余的0
toPlainString()      //不会出现科学计数法的数
