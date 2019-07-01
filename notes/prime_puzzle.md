# 奇数码问题
## 题目大意
[原题目][src]  
在一个![n*n][n*n]的网格中（![n][n]为奇数），分布有![1...n^2-1][1...n^2-1]的数和一个空格，该空格每次可以和上下左右相邻的数交换位置。  
判断是否存在一种移动空格的方式，使得其中一个局面可以变化到另一个局面。

## 题解[\[ref0\]][ref0]
我一开始以为这是一道搜索题，但是此题的状态转移很复杂，搜索做不了。
你可以试着随便移动那个空格，但是最后将它移回原来的位置。
此时虽然空格在同一位置，状态却改变了。

所以，此题需要找出对于每个能相互转换的局面的集合所独有的特征。
于是就有了本题的题解：求逆序对个数的奇偶性。
所有逆序对个数为奇数的都能相互转化，为偶数的也是。

[src]: https://www.acwing.com/problem/content/description/110/
[n*n]: https://latex.codecogs.com/gif.download?n%5Ctimes%20n
[n]: https://latex.codecogs.com/gif.download?n
[1...n^2-1]: https://latex.codecogs.com/gif.download?1...n%5E2-1
[ref0]: https://www.acwing.com/solution/acwing/content/847/