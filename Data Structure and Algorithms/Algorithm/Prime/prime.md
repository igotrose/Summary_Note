# 素数总结 

## 素数的基本定义
在大于 ***1*** 的自然数中，除了 ***1*** 和它本身布置在有 ***其他因数***的自然数。   
即素数是大于 ***1*** 的整数，并且只有两个因子，最小的素数。***2***。
## 素数的三种基本算法

###  普通筛法 -- 枚举试除法
**原理**  
正如字面义，判断素数可以直接将这个数与$(2, x-1)$ 的数进行试除,如果被整除，根据定义就不是素数，反之。
#### 在上法的基础上，为了提升程序的效率，以下是几种优化方式：  
**1**.我们知道一个数可以写成 $x = a * b$ 的形式，那我们不妨让 $a = 2$ 这样试除的范围就缩小了一半。  
**时间复杂度**:$O(n/2)$  
**2**.基于前两种方式，不难发现，素数都是奇数，那么在遍历的时候便可以直接跳过偶数，从奇数开始进行试除。  
**时间复杂度**：$O(n/2)$  
**3**.一个自然数可以表示为$x = a * b$的形式，$a$ 和 $b$ 这两个因子总是一前一后、一大一小,如此就会有一个分界点。即 $sqrt(x)$ ，对这个数进行开方操作,如果 $(2, sqrt(x))$ 这个范围内没有因子，那么 $(sqrt(x),x-1)$ 的范围内也不会有因子。    
具体代码见**Ordinary _sieve_method.c**

### 埃式筛法 -- 埃拉托斯特尼筛法
**原理**  
素数的倍数一定不是素数，任意一个合数可以表示为一个素数和另一个数的乘积。  
**做法**  
1.设置两个数组，一个数组放置所有的数字并用来标记此数字是否被访问过，即*访问数组*；另一个数组用来存储已经筛出的素数方便输出，为*素数数组*。  
2.将*访问数组*中的标记全部设为未访问，清空*素数数组*，即对两个数组进行初始化。  
3.从2开始循环，判断每一个数字是否被访问过，设定访问过的数为合数，未访问过的数为素数。  
4.对这个素数进行倍增操作，其中得到的数字结果的访问标记都设置为已访问，重复3、4，知道循环结束。    
**时间复杂度**：$O(nloglogn)$  
具体代码见**Eratosthene_sieve_method.c**

### 欧拉筛法 -- 线性筛法  
**原理**  
基于埃式筛法，欧拉筛法实在用现在遍历到的数字，去乘以素数表中已有的素数，这样一来就可以避免重复删除，并求出合数的最小质因子。  
**做法**  
前几步跟埃式筛法的做法是一样的，关键是在确保素数倍增后，如何不重复删除。在遍历一个数之后，把它乘以*素数数组*里的所有数，并在*访问数组*中将这些数全部标记。
