# ���������������̰���㷨

## �򵥵�������[\[ref0\]][ref0][\[ref1\]][ref1]

### ��Ŀ����
��һ��ֱ���ϸ��������߶�![(S, E)][(S, E)]����������Ŀ�ʼ������ʱ�䣩��������ͷS�ͽ�βE�������߶β��ص�������£���ѡȡ������߶�����

### ����
*���������������뵽�����֣��������ִ�������ڲο�������*

1. ���߶ΰ���![S][S]��С�������򣬲������ܴ�С����ѡȡ  
   �˷�����Ȼ����ȷ���������£�  

   >A: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\-\-\-\-\-\-\-\-\-\-\-\-\-\-  
   >B: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\-\-\-\-\-  
   >C: \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-  
   >��ʱѡ��A��B�����ŵģ����Ǹò��Ի�ѡ��C  
   >��������£���һ����ʼ���磬������������߶�  

2. ���߶ΰ���![E][E]��С�������򣬲������ܴ�С����ѡȡ  

   >������ȷ�Ĳ��ԣ�ʹ����ʱ�価���磬�Բ�Ӱ����������  
   >���ǣ�����Ϊ�Ͻ���֤��Ҳ�Ǳ���ģ��������Ľ���

### ֤��������2����ȷ��
����һ�����Ž�Ļ��![E][E]��С��������õ���![a_{1},a_{2},...,a_{n}][a_{1},a_{2},...,a_{n}]  
���谴�ղ���2ѡ���Ļ���Ѿ���![E][E]��С��������Ϊ��![b_{1},b_{2},...,b{m}][b_{1},b_{2},...,b{m}]

����ѧ���ɷ�����֤����
 
1. ���![a_{1}\neq b_{1}][a_{1}\neq b_{1}]  
   �ɲ���2�ã�![E(b_{1})\le E(a_{1})][E(b_{1})\le E(a_{1})]  
   ��ˣ������ڲ���![a_{2},a_{3},...,a_{n}][a_{2},a_{3},...,a_{n}]�غϵ�����£���![a_{1}][a_{1}]�滻Ϊ![b_{1}][b_{1}]��
   ʹ��Ϊ��һ�����Ž�  
2. ����![a_{1}=b_{1},a_{2}=b_{2},...,a_{i}=b_{i}][a_{1}=b_{1},a_{2}=b_{2},...,a_{i}=b_{i}]����  
3. ���![a_{i+1}\neq b_{i+1}][a_{i+1}\neq b_{i+1}]  
   ��Ϊ![E(b_{i+1})\le E(a_{i+1})][E(b_{i+1})\le E(a_{i+1})]  
   ���ԣ������ڲ���![a_{i+2},a_{i+3},...,a_{n}][a_{i+2},a_{i+3},...,a_{n}]�غϵ�����£���![a_{i+1}][a_{i+1}]�滻Ϊ![b_{i+1}][b_{i+1}]��
   ʹ��Ϊ��һ�����Ž�

���Բ���2ѡ������һ�����Ž�

## Sunscreen

### ��Ŀ����
[ԭ��Ŀ][src]  
��Cֻţ����iֻţ��minSPF\_i��maxSPF\_i��  
��Lƿ��ɹ˪����iƿ��SPF\_i���ܸ���cover\_iֻţ��  
ֻ�е�SPF��С��minSPF���Ҳ�����maxʱ�����ܸ��Ǹ�ֻţ��  
������ܱ����ǵ�ţ��������

### һ����� [\[ref2\]][ref2]
��ţ����maxSPF\_i��С��������ÿ�ξ���ѡȡ��С��ȡ�ķ�ɹ˪��

���룺  
```cpp  
read(C, L, cow, lotion);
sort(cow, by_maxSPF);
sort(lotion, by_SPF);
int ans = 0;
for(int i = 1 to C)
{
	iterator it = lotion.lower_bound(cow[i].minSPF, by_SPF);  // ��һ��SPF��С��minSPF�ķ�ɹ˪
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

### ������˼��
��һ��ʼ���뷨�ǽ�ţ����minSPF��С��������ÿ�ξ���ѡȡ��С��ȡ�ķ�ɹ˪��
���Ǵ�ʱ�������������⣺

>A: &nbsp;&nbsp;&nbsp;--------------\*----------------\*--------  
>B: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;------\*------&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*  
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2  
>�����ߴ���ţ��SPF��Χ�����ߴ����ɹ˪��SPF��  
>��ʱA��minSPFС��B��minSPF������A��ѡ���ɹ˪1��B���޷�ɹ˪����ѡ��  
>���������maxSPF��С��������B��maxSPF��С����B��ѡ��1��A�Կ���ѡ��2  

**��Ŀǰ�벻�����������Ͻ���֤��**  
**�����ϻ���һ�������ȶ��еĽⷨ**  
**TODO������֤������һ�ֽⷨ**  

## �ο�����
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
