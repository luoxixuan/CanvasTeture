#pragma once

using namespace std;

typedef unordered_map<int, int> iMap;

/* *
 * 归并排序算法，驱动方法；
 */
template <typename Comparable>
void mergeSort(vector<Comparable> & a)
//void mergeSort(array<Comparable, draNum> & a)
{
	vector<Comparable> tmpvector(a.size());
	//array<Comparable, draNum> tmpvector();

	mergeSort(a, tmpvector, 0, a.size() - 1);
}

/* *
 * 进行递归调用的内置方法.
 * a 是用来存放进行比较的对象的向量.
 * tmpvector 是用来存放子数组的向量.
 * left 是第一部分子数组最左边的位置.
 * right 是第一部分子数组最右边的位置.
 */
template <typename Comparable>
void mergeSort(vector<Comparable> & a, vector<Comparable> & tmpvector, int left, int right)
//void mergeSort(array<Comparable, draNum> & a, array<Comparable, draNum> & tmpvector, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpvector, left, center);
		mergeSort(a, tmpvector, center + 1, right);
		merge(a, tmpvector, left, center + 1, right);
	}
}

/* *
 * 用来按顺序合并两个子数组的内置方法.
 * a 是用来存放进行比较的对象的向量.
 * tmpvector 是用来存放子数组的向量.
 * leftPos 第二部分最左边的位置.
 * rightPos 是第二部分的起始位置.
 * rightend 是第二部分最右边的位置.
 */
template <typename Comparable>
void merge(vector < Comparable> & a, vector<Comparable> & tmpvector, int leftPos, int rightPos, int rightEnd)
//void merge(array < Comparable, draNum> & a, array<Comparable, draNum> & tmpvector, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	// 主循环
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos] <= a[rightPos])
		{
			tmpvector[tmpPos++] = a[leftPos++];
		}
		else
		{
			tmpvector[tmpPos++] = a[rightPos++];
		}
	}
	while (leftPos <= leftEnd)
	{
		tmpvector[tmpPos++] = a[leftPos++];
	}
	while (rightPos <= rightEnd)
	{
		tmpvector[tmpPos++] = a[rightPos++];
	}

	// 把临时数组复制回a
	for (int i = 0; i < numElements; i++, rightEnd--)
	{
		a[rightEnd] = tmpvector[rightEnd];
	}
}