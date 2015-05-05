#pragma once

using namespace std;

typedef unordered_map<int, int> iMap;

/* *
 * �鲢�����㷨������������
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
 * ���еݹ���õ����÷���.
 * a ��������Ž��бȽϵĶ��������.
 * tmpvector ��������������������.
 * left �ǵ�һ��������������ߵ�λ��.
 * right �ǵ�һ�������������ұߵ�λ��.
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
 * ������˳��ϲ���������������÷���.
 * a ��������Ž��бȽϵĶ��������.
 * tmpvector ��������������������.
 * leftPos �ڶ���������ߵ�λ��.
 * rightPos �ǵڶ����ֵ���ʼλ��.
 * rightend �ǵڶ��������ұߵ�λ��.
 */
template <typename Comparable>
void merge(vector < Comparable> & a, vector<Comparable> & tmpvector, int leftPos, int rightPos, int rightEnd)
//void merge(array < Comparable, draNum> & a, array<Comparable, draNum> & tmpvector, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	// ��ѭ��
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

	// ����ʱ���鸴�ƻ�a
	for (int i = 0; i < numElements; i++, rightEnd--)
	{
		a[rightEnd] = tmpvector[rightEnd];
	}
}