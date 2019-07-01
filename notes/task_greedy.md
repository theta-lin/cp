# 关于任务安排问题的贪心算法

## 简单的任务安排[\[ref0\]][ref0][\[ref1\]][ref1]

### 题目大意
在一条直线上给定多条线段![(S, E)][(S, E)]（代表任务的开始、结束时间），给定开头S和结尾E，求在线段不重叠的情况下，能选取的最多线段数。

### 策略
*以下是我最容易想到的两种，还有两种错误策略在参考资料中*

1. 将线段按照![S][S]从小到大排序，并尽可能从小到大选取  
   >此方法显然不正确，例子如下：  
   >A: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\-\-\-\-\-\-\-\-\-\-\-\-\-\-  
   >B: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\-\-\-\-\-  
   >C: \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-  
   >此时选择A和B是最优的，但是该策略会选择C  
   >这种情况下，有一条开始很早，但结束很晚的线段  
2. 将线段按照![E][E]从小到大排序，并尽可能从小到大选取  
   >这是正确的策略，使结束时间尽量早，以不影响后面的任务  
   >但是，我以为严谨的证明也是必须的，将在下文讲述

### 证明：策略2是正确的
假设最优解的活动按![E][E]从小到大排序得到：![a_{1}, a_{2},...,a_{n}][a_{1}, a_{2},...,a_{n}]  
假设按照策略2选出的活动（已经按![E][E]从小到大排序）为：

## 参考资料
\[ref0\]: https://www.cnblogs.com/ruruozhenhao/p/7446216.html  
\[ref1\]: https://blog.csdn.net/baidu_38304645/article/details/83818009

[(S, E)]: https://latex.codecogs.com/svg.latex?%28S%2C%20E%29
[S]: https://latex.codecogs.com/svg.latex?S
[E]: https://latex.codecogs.com/svg.latex?E
[a_{1}, a_{2},...,a_{n}]: https://latex.codecogs.com/svg.latex?a_%7B1%7D%2C%20a_%7B2%7D%2C...%2Ca_%7Bn%7D
[ref0]: https://www.cnblogs.com/ruruozhenhao/p/7446216.html
[ref1]: https://blog.csdn.net/baidu_38304645/article/details/83818009