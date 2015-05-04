#pragma once

using namespace std;

typedef unordered_map<int, int> iMap;

/* *
 * �鲢�����㷨������������
 */
template <typename Comparable>
void mergeSort(vector<Comparable> & a)
{
	vector<Comparable> tmpArray(a.size());

	mergeSort(a, tmpArray, 0, a.size() - 1);
}

/* *
 * ���еݹ���õ����÷���.
 * a ��������Ž��бȽϵĶ��������.
 * tmpArray ��������������������.
 * left �ǵ�һ��������������ߵ�λ��.
 * right �ǵ�һ�������������ұߵ�λ��.
 */
template <typename Comparable>
void mergeSort(vector<Comparable> & a,
			   vector<Comparable> & tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}

/* *
 * ������˳��ϲ���������������÷���.
 * a ��������Ž��бȽϵĶ��������.
 * tmpArray ��������������������.
 * leftPos �ڶ���������ߵ�λ��.
 * rightPos �ǵڶ����ֵ���ʼλ��.
 * rightend �ǵڶ��������ұߵ�λ��.
 */
template <typename Comparable>
void merge(vector < Comparable> & a, vector<Comparable> & tmpArray,
		   int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	// ��ѭ��
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos] <= a[rightPos])
		{
			tmpArray[tmpPos++] = a[leftPos++];
		}
		else
		{
			tmpArray[tmpPos++] = a[rightPos++];
		}
	}
	while (leftPos <= leftEnd)
	{
		tmpArray[tmpPos++] = a[leftPos++];
	}
	while (rightPos <= rightEnd)
	{
		tmpArray[tmpPos++] = a[rightPos++];
	}

	// ����ʱ���鸴�ƻ�a
	for (int i = 0; i < numElements; i++, rightEnd--)
	{
		a[rightEnd] = tmpArray[rightEnd];
	}
}