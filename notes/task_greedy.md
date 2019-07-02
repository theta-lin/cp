# 关于任务安排问题的贪心算法

## 简单的任务安排[\[ref0\]][ref0][\[ref1\]][ref1]

### 题目大意
在一条直线上给定多条线段![(S, E)][(S, E)]（代表任务的开始、结束时间），给定开头S和结尾E，求在线段不重叠的情况下，能选取的最多线段数。

### 策略
*以下是我最容易想到的两种，还有两种错误策略在参考资料中*

1. 将线段按照![S][S]从小到大排序，并尽可能从小到大选取  
   此方法显然不正确，例子如下：  

   >A: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\-\-\-\-\-\-\-\-\-\-\-\-\-\-  
   >B: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\-\-\-\-\-  
   >C: \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-  
   >此时选择A和B是最优的，但是该策略会选择C  
   >这种情况下，有一条开始很早，但结束很晚的线段  

2. 将线段按照![E][E]从小到大排序，并尽可能从小到大选取  

   >这是正确的策略，使结束时间尽量早，以不影响后面的任务  
   >但是，我以为严谨的证明也是必须的，将在下文讲述

### 证明：策略2是正确的
假设一种最优解的活动按![E][E]从小到大排序得到：![a_{1},a_{2},...,a_{n}][a_{1},a_{2},...,a_{n}]  
假设按照策略2选出的活动（已经按![E][E]从小到大排序）为：![b_{1},b_{2},...,b{m}][b_{1},b_{2},...,b{m}]

用数学归纳法进行证明：
 
1. 如果![a_{1}\neq b_{1}][a_{1}\neq b_{1}]  
   由策略2得，![E(b_{1})\le E(a_{1})][E(b_{1})\le E(a_{1})]  
   因此，可以在不与![a_{2},a_{3},...,a_{n}][a_{2},a_{3},...,a_{n}]重合的情况下，将![a_{1}][a_{1}]替换为![b_{1}][b_{1}]，
   使其为另一种最优解  
2. 假设![a_{1}=b_{1},a_{2}=b_{2},...,a_{i}=b_{i}][a_{1}=b_{1},a_{2}=b_{2},...,a_{i}=b_{i}]成立  
3. 如果![a_{i+1}\neq b_{i+1}][a_{i+1}\neq b_{i+1}]  
   因为![E(b_{i+1})\le E(a_{i+1})][E(b_{i+1})\le E(a_{i+1})]  
   所以，可以在不与![a_{i+2},a_{i+3},...,a_{n}][a_{i+2},a_{i+3},...,a_{n}]重合的情况下，将![a_{i+1}][a_{i+1}]替换为![b_{i+1}][b_{i+1}]，
   使其为另一种最优解

所以策略2选出的是一种最优解

## Sunscreen

### 题目大意
[原题目][src]  
有C只牛，第i只牛有minSPF\_i，maxSPF\_i。  
有L瓶防晒霜，第i瓶有SPF\_i，能覆盖cover\_i只牛。  
只有当SPF不小于minSPF，且不大于max时，才能覆盖该只牛。  
求最多能被覆盖的牛的数量。

### 一种题解 [\[ref2\]][ref2]
将牛按照maxSPF\_i从小到大排序，每次尽量选取最小可取的防晒霜。

代码：  
```cpp  
read(C, L, cow, lotion);
sort(cow, by_maxSPF);
sort(lotion, by_SPF);
int ans = 0;
for(int i = 1 to C)
{
	iterator it = lotion.lower_bound(cow[i].minSPF, by_SPF);  // 第一个SPF不小于minSPF的防晒霜
	if (found && *it.SPF <= cow[i].maxSPF)
	{  
		++ans;
		--*it.cover;
		if (*it.cover == 0)
		{
			lotion.erase(it);
		}
	}
}
print(ans);
```  

### 对题解的思考
我一开始的想法是将牛按照minSPF从小到大排序，每次尽量选取最小可取的防晒霜。
但是此时会有这样的问题：

>A: &nbsp;&nbsp;&nbsp;--------------\*----------------\*--------  
>B: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;------\*------&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*  
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2  
>（横线代表牛的SPF范围，竖线代表防晒霜的SPF）  
>此时A的minSPF小于B的minSPF，所以A先选择防晒霜1，B就无防晒霜可以选用  
>而如果按照maxSPF从小到大排序，B的maxSPF较小，则B先选择1，A仍可以选择2  

**我目前想不出对这个题解严谨的证明**  
**网络上还有一种用优先队列的解法**  
**TODO：补充证明和另一种解法**  

## 参考资料
\[ref0\]: https://www.cnblogs.com/ruruozhenhao/p/7446216.html  
\[ref1\]: https://blog.csdn.net/baidu_38304645/article/details/83818009  
\[ref2\]: https://blog.csdn.net/C_13579/article/details/81940242

[(S, E)]: https://latex.codecogs.com/svg.latex?%28S%2C%20E%29
[S]: https://latex.codecogs.com/svg.latex?S
[E]: https://latex.codecogs.com/svg.latex?E
[a_{1},a_{2},...,a_{n}]: https://latex.codecogs.com/svg.latex?a_%7B1%7D%2Ca_%7B2%7D%2C...%2Ca_%7Bn%7D
[b_{1},b_{2},...,b{m}]: https://latex.codecogs.com/svg.latex?b_%7B1%7D%2Cb_%7B2%7D%2C...%2Cb%7Bm%7D
[a_{1}\neq b_{1}]: https://latex.codecogs.com/svg.latex?a_%7B1%7D%5Cneq%20b_%7B1%7D
[E(b_{1})\le E(a_{1})]: https://latex.codecogs.com/svg.latex?E%28b_%7B1%7D%29%5Cle%20E%28a_%7B1%7D%29
[a_{2},a_{3},...,a_{n}]: https://latex.codecogs.com/svg.latex?a_%7B2%7D%2Ca_%7B3%7D%2C...%2Ca_%7Bn%7D
[a_{1}]: https://latex.codecogs.com/svg.latex?a_%7B1%7D
[b_{1}]: https://latex.codecogs.com/svg.latex?b_%7B1%7D
[a_{1}=b_{1},a_{2}=b_{2},...,a_{i}=b_{i}]: https://latex.codecogs.com/svg.latex?a_%7B1%7D%3Db_%7B1%7D%2Ca_%7B2%7D%3Db_%7B2%7D%2C...%2Ca_%7Bi%7D%3Db_%7Bi%7D
[a_{i+1}\neq b_{i+1}]: https://latex.codecogs.com/svg.latex?a_%7Bi+1%7D%5Cneq%20b_%7Bi+1%7D
[E(b_{i+1})\le E(a_{i+1})]: https://latex.codecogs.com/svg.latex?E%28b_%7Bi+1%7D%29%5Cle%20E%28a_%7Bi+1%7D%29
[a_{i+2},a_{i+3},...,a_{n}]: https://latex.codecogs.com/svg.latex?a_%7Bi+2%7D%2Ca_%7Bi+3%7D%2C...%2Ca_%7Bn%7D
[a_{i+1}]: https://latex.codecogs.com/svg.latex?a_%7Bi+1%7D
[b_{i+1}]: https://latex.codecogs.com/svg.latex?b_%7Bi+1%7D
[src]: http://bailian.openjudge.cn/practice/3374/
[ref0]: https://www.cnblogs.com/ruruozhenhao/p/7446216.html
[ref1]: https://blog.csdn.net/baidu_38304645/article/details/83818009
[ref2]: https://blog.csdn.net/C_13579/article/details/81940242
