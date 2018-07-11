#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<memory.h>

//去掉极值求平均分
//问题：如果是int数据，求和可能造成数据溢出，有没有其他方式？
//时间复杂度：O(n)
float average(float* brr, int length) {
	if (length < 3) {
		printf("the length of the array must bigger than 2!!");
		return 0.0f;
	}
	int i;
	float max = brr[0];
	float min = brr[0];
	float sum = brr[0];
	for (i = 1; i < length; i++) {
		if (brr[i] > max) max = brr[i];
		if (brr[i] < min) max = brr[i];
		sum += brr[i];
	}
	return (sum - max - min)/(length - 2);
}
//计算π的值
//问题1：随着计算精确度的提高，需要的计算步数会增加，那么有没有更好的方法，控制需要进行的计算步数，以减小计算的时间复杂度？（能不能用香克斯变换？）
//问题2：怎么去判断这个精确度满足条件了，就是下面这个while的终止条件是什么？
//公式：π/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ....
double get_pi(int accuracy) {
	int i = 1;
	double pi = 0;
	double acc = pow(10, accuracy);
	int result =(int) (M_PI/4 * acc);
	int temp = 0;
	while (result != temp) {//这个终止条件目前来看是有问题的！！
		if (i%2 != 0) pi = pi + 1.0/(2*i - 1);
		else pi = pi - 1.0/(2*i - 1);
		i++;
		temp =(int) (pi*acc);
	}
	printf("with accuracy: %d need %d steps\n", accuracy, i);
}

//9*9乘法表
void multiplication_table() {
	int i, j;
	for (i = 1; i <= 9; i++){
		for (j = 1; j <= i; j++) {
			printf("%d*%d=%d\t", j, i, i*j);
		}
		printf("\n");
	}
	return;
}

//洗牌问题
void shuffle(int* brr, int length) {
	int i, temp;
	srand((int)time(0));
	for (i = 0; i < length - 1; i++) {
		int index = i + (int)(1.0f*(length - i)*rand()/RAND_MAX);
		//printf("i-index:%d-%d\t", i, index);
		if (i == index) continue;
		temp = brr[i];
		brr[i] = brr[index];
		brr[index] = temp;		
	}
} 

//计算素数
//问题：如何计算素数，如何查找小于某个数N的素数？有什么方法，每种方法的时间复杂度？
//方法1：一般方法：依次判断每个数字是否是素数

void normal_prime(int n) {
	if (n < 2) {
		printf("there is no prime number below number 2!!");
		return;
	}
	printf("normal - the prime number below %d:\n", n);
	int i, j;
	int origin[n];
	for (i = 2; i <= n; i++) {
		origin[i] = 1;
		for (j = 2; j <= sqrt(i); j++) {
			if (i%j == 0){
				origin[i] = 0;
				break;
			}
		}
	}
	for (i = 2; i <= n; i++) {
		if (origin[i]) printf("%d\t", i);
	}
	printf("\n");
}
//方法2：埃氏筛法：从2开始选择质数，依次筛选排除掉小于N的所有该质数的倍数，外层循环只需要到根号N的位置
void aishi_prime(int n){
	if (n < 2) {
		printf("there is no prime number below number 2!!");
		return;
	}
	printf("aishi - the prime number below %d:\n", n);
	int i, j;
	int origin[n];
	memset(origin, 1, sizeof(origin));
	origin[0] = origin[1] = 0;
	for (i = 2; i <= sqrt(n); i++) {
		if (origin[i]) {
			for (j = i*i; j <= n; j += i) {
				origin[j] = 0;
			}
		}
	}
	for (i = 2; i <= n; i++) {
		if (origin[i]) printf("%d\t", i);
	}
	printf("\n");
}
//方法3：欧拉筛法：相对于埃氏筛法的优化是，每次筛掉的数很少，比如现在的质数是2，我们仅仅需要筛掉比2大不多少的合数，因为比2大很多的合数一定可以通过比该合数小一些的质数筛掉，这样避免了每个质数都去遍历数组做筛选，做到时间复杂度是O(n)
void oula_prime(int n) {
	if (n < 2) {
		printf("there is no prime number below number 2!!");
		return;
	}
	printf("oula - the prime number below %d:\n", n);
	int i, j;
	int origin[n];
	int prime[n];
	int num = 0;
	memset(origin, 1, sizeof(origin));
	
	for (i = 2; i <= n; i++) {
		if (origin[i]) {
			prime[num] = i;
			num++;
		}
		for (j = 0; j < num && i*prime[j] <= n; j++) {
			origin[i*prime[j]] = 0;
			if (i % prime[j] == 0) break;
		}
	}

	for (i = 0; i < num; i++) {
		printf("%d\t", prime[i]);
	}
	printf("\n");
}

void show_array(int* crr, int length){
	int i;
	for (i = 0; i < length; i++) {
		printf("%d ", crr[i]);
	}
	printf("\n");
}
int main(void) {
	/*
	printf("the average value:\n");
	float arr[] = {10.2f, 49.0f, 26.56f, 32.33f};
	float avg = average(arr, 4);
	printf("%.4f\n", avg);
	*/

	/*
	get_pi(7);
	*/

	/*
	multiplication_table();
	*/
	
	/*
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	shuffle(arr, 12);
	show_array(arr, 12);
	*/

	normal_prime(25);
	aishi_prime(25);
	oula_prime(25);
	return 0;
}


