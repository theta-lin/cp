# 奇数码问题
## 题目大意
[原题目][src]  
在一个![n*n][n*n]的网格中（![n][n]为奇数），分布有![1...n^2-1][1...n^2-1]的数和一个空格，该空格每次可以和上下左右相邻的数交换位置。  
给定两个局面，判断是否存在一种移动空格的方式，使得其中一个局面可以变化到另一个局面。

## 题解[\[ref0\]][ref0]
我一开始以为这是一道搜索题，但是此题的状态转移很复杂，搜索做不了。
你可以试着随便移动那个空格，但是最后将它移回原来的位置。
此时虽然空格在同一位置，状态却改变了。

所以，此题需要找出对于每个能相互转换的局面的集合所独有的特征。
于是就有了本题的题解：求逆序对个数的奇偶性。
所有逆序对个数为奇数的都能相互转化，为偶数的也是。

具体过程：  
假设我们的局面如下  
1   2 **0**  
8   6   3  
7   9   4  
==> 1 2 **0** 8 6 3 7 9 4          将其排成一维  
==> 1 2 8 6 3 7 9 4                     将0忽略  
==> 计算这个一维数组中的逆序对个数， 判断奇偶性  
    若所给的两个局面的逆序对个数的奇偶性相同，则可以相互转化，反之不行

**重要提醒：在实现中答案可能会超过32位整数类型的存储上限！！！**

## 证明
那么为什么无论上下左右移动，奇偶性都不会变化呢？

### 我们先考虑左右移动：  
1     2     8 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  1     2     8  
6   **0**   3 ==>                                 **0**   6     3  
7     9     4 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  7     9     4

1 2 8 6 **0** 3 7 9 4 ==> 1 2 8 **0** 6 3 7 9 4  
此时如果将0忽略，对逆序对个数根本没有影响。

### 那么上下移动呢？  
1     2     8 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  1   **0**   8  
6   **0**   3 ==>                                   6     2     3  
7     9     4 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  7     9     4

1 2 8 6 **0** 3 7 9 4 ==> 1 **0** 8 6 2 3 7 9 4  
&nbsp;&nbsp;&nbsp;^--**I**-**I**--^
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
^--**I**-**I**--^  
此时我们可以看出，题目中![n][n]是奇数其实别有深意，因为此时如果将0上下移动，在一维数组中就相当于将与其交换的那个数向前（向后）跳过了偶数个数。

为了证明上下移动不会改变逆序对个数的奇偶性，我们先假设将元素![x][x]向上（下）移动至![x'][x']。
设![x][x]与![x'][x']之间的元素为  
![A_{1}, A_{2},...,A{a},B_{1},B_{2},...,B_{b}][A_{1}, A_{2},...,A{a},B_{1},B_{2},...,B_{b}]  
其中![A_{i}&lt;x,B_{j}&gt;x][A_{i}&lt;x,B_{j}&gt;x]  
此时因为跳过了偶数个数，则![a+b][a+b]为偶数  
即![a,b][a,b]同奇偶  
所以![a-b][a-b]为偶数  
因为移动后与![x][x]成逆序对的元素增加（向上）或减少（向下）了![a-b][a-b]  
所以总的逆序对数增加（减少）了偶数个  
即其奇偶性不变

## 参考资料
\[ref0\]: https://www.acwing.com/solution/AcWing/content/847/

[src]: https://www.acwing.com/problem/content/description/110/
[n*n]: https://latex.codecogs.com/svg.latex?n%5Ctimes%20n
[n]: https://latex.codecogs.com/svg.latex?n
[1...n^2-1]: https://latex.codecogs.com/svg.latex?1...n%5E2-1
[x]: https://latex.codecogs.com/svg.latex?x
[x']: https://latex.codecogs.com/svg.latex?x%27
[A_{1}, A_{2},...,A{a},B_{1},B_{2},...,B_{b}]: https://latex.codecogs.com/svg.latex?A_%7B1%7D%2C%20A_%7B2%7D%2C...%2CA%7Ba%7D%2CB_%7B1%7D%2CB_%7B2%7D%2C...%2CB_%7Bb%7D
[A_{i}&lt;x,B_{j}&gt;x]: https://latex.codecogs.com/svg.latex?A_%7Bi%7D%3Cx%2CB_%7Bj%7D%3Ex
[a+b]: https://latex.codecogs.com/svg.latex?a+b
[a,b]: https://latex.codecogs.com/svg.latex?a%2Cb
[a-b]: https://latex.codecogs.com/svg.latex?a-b
[ref0]: https://www.acwing.com/solution/AcWing/content/847/
