#include <cassert>

#include "structures.hpp"
#include <vector>
#include <chrono>

using namespace std;


void TestSingleArray()
{
	SingleArray<int> ar{ 1,2,3 };
	
	ar.Insert(5, 1);
	assert(ar.Size() == 4);
	assert(ar == SingleArray<int>({ 1,5,2,3 }));
	ar.Remove(2);
	assert(ar.Size() == 3);
	assert(ar == SingleArray<int>({ 1,5,3 }));
	ar.Insert(7, 3);
	assert(ar.Size() == 4);
	assert(ar == SingleArray<int>({ 1,5,3,7 }));
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	assert(ar == SingleArray<int>());
	assert(ar.Size() == 0);
}

void TestVectorArray()
{
	VectorArray<int> ar{ 1,2,3 };

	ar.Insert(5, 1);
	assert(ar.Size() == 4);
	assert(ar == VectorArray<int>({ 1,5,2,3 }));
	ar.Remove(2);
	assert(ar.Size() == 3);
	assert(ar == VectorArray<int>({ 1,5,3 }));
	ar.Insert(7, 3);
	assert(ar.Size() == 4);
	assert(ar == VectorArray<int>({ 1,5,3,7 }));
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	assert(ar == VectorArray<int>());
	assert(ar.Size() == 0);
}

void TestFactorArray()
{
	FactorArray<int> ar{ 1,2,3 };
	
	ar.Insert(5, 1);
	assert(ar.Size() == 4);
	assert(ar == FactorArray<int>({ 1,5,2,3 }));
	ar.Remove(2);
	assert(ar.Size() == 3);
	assert(ar == FactorArray<int>({ 1,5,3 }));
	ar.Insert(7, 3);
	assert(ar.Size() == 4);
	assert(ar == FactorArray<int>({ 1,5,3,7 }));
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	assert(ar == FactorArray<int>());
	assert(ar.Size() == 0);
}

void TestMatrixArray()
{
	MatrixArray<int> ar{ 1,2,3 };

	ar.Insert(5, 1);
	assert(ar.Size() == 4);
	assert(ar == MatrixArray<int>({ 1,5,2,3 }));
	ar.Remove(2);
	assert(ar.Size() == 3);
	assert(ar == MatrixArray<int>({ 1,5,3 }));
	ar.Insert(7, 3);
	assert(ar.Size() == 4);
	assert(ar == MatrixArray<int>({ 1,5,3,7 }));
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	assert(ar.Size() == 0);
}

void TestStandardArray()
{
	StandardArray<int> ar{ 1,2,3 };

	ar.Insert(5, 1);
	assert(ar.Size() == 4);
	assert(ar == StandardArray<int>({ 1,5,2,3 }));
	ar.Remove(2);
	assert(ar.Size() == 3);
	assert(ar == StandardArray<int>({ 1,5,3 }));
	ar.Insert(7, 3);
	assert(ar.Size() == 4);
	assert(ar == StandardArray<int>({ 1,5,3,7 }));
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	ar.Remove(0);
	assert(ar.Size() == 0);
}

using clk = std::chrono::system_clock;

template <typename T>
void TestArrayInsertStart(Array<T>& ar, size_t total)
{
	auto t1 = clk::now();
	for (size_t i = 0; i < total; ++i)
	{
		ar.Insert(T(), 0);
	}
	auto t2 = clk::now();
	std::cout << ar.ClassName() << " ";
	std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
}

template <typename T>
void TestArrayInsertMid(Array<T>& ar, size_t total)
{
	auto t1 = clk::now();
	for (size_t i = 0; i < total; ++i)
	{
		ar.Insert(T(), ar.Size() / 2);
	}
	auto t2 = clk::now();
	std::cout << ar.ClassName() << " ";
	std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
}

template <typename T>
void TestArrayInsertEnd(Array<T>& ar, size_t total)
{
	auto t1 = clk::now();
	for (size_t i = 0; i < total; ++i)
	{
		ar.Insert(T(), ar.Size());
	}
	auto t2 = clk::now();
	std::cout << ar.ClassName() << " ";
	std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
}

template <typename T>
void TestArrayRemoveStart(Array<T>& ar, size_t total)
{
	auto t1 = clk::now();
	for (size_t i = 0; i < total; ++i)
	{
		ar.Remove(0);
	}
	auto t2 = clk::now();
	std::cout << ar.ClassName() << " ";
	std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
}

template <typename T>
void TestArrayRemoveMid(Array<T>& ar, size_t total)
{
	auto t1 = clk::now();
	for (size_t i = 0; i < total; ++i)
	{
		ar.Remove(ar.Size() / 2);
	}
	auto t2 = clk::now();
	std::cout << ar.ClassName() << " ";
	std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
}

template <typename T>
void TestArrayRemoveEnd(Array<T>& ar, size_t total)
{
	auto t1 = clk::now();
	for (size_t i = 0; i < total; ++i)
	{
		ar.Remove(ar.Size()-1);
	}
	auto t2 = clk::now();
	std::cout << ar.ClassName() << " ";
	std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
}

void AllArrayInsertionTest(size_t ar_size)
{
	{
		cout << "Insertion at the beginning: " << endl;
		SingleArray<int> sa;
		VectorArray<int> va;
		StandardArray<int> sta;
		FactorArray<int> fa;
		MatrixArray<int> ma;
		TestArrayInsertStart(sa, ar_size);
		TestArrayInsertStart(va, ar_size);
		TestArrayInsertStart(fa, ar_size);
		TestArrayInsertStart(ma, ar_size);
		TestArrayInsertStart(sta, ar_size);
	}
	{
		cout << "Insertion in the middle: " << endl;
		SingleArray<int> sa;
		VectorArray<int> va;
		StandardArray<int> sta;
		FactorArray<int> fa;
		MatrixArray<int> ma;
		TestArrayInsertMid(sa, ar_size);
		TestArrayInsertMid(va, ar_size);
		TestArrayInsertMid(fa, ar_size);
		TestArrayInsertMid(ma, ar_size);
		TestArrayInsertMid(sta, ar_size);
	}
	{
		cout << "Insertion at the end: " << endl;
		SingleArray<int> sa;
		VectorArray<int> va;
		StandardArray<int> sta;
		FactorArray<int> fa;
		MatrixArray<int> ma;
		TestArrayInsertEnd(sa, ar_size);
		TestArrayInsertEnd(va, ar_size);
		TestArrayInsertEnd(fa, ar_size);
		TestArrayInsertEnd(ma, ar_size);
		TestArrayInsertEnd(sta, ar_size);
	}
}

void AllArrayRemovalTest(size_t ar_size)
{
	{
		cout << "Removal at the beginning: " << endl;
		SingleArray<int> sa(ar_size);
		FactorArray<int> fa(ar_size);
		MatrixArray<int> ma(ar_size);
		StandardArray<int> sta(ar_size);
		
		TestArrayRemoveStart(sa, ar_size);
		TestArrayRemoveStart(fa, ar_size);
		TestArrayRemoveStart(ma, ar_size);
		TestArrayRemoveStart(sta, ar_size);
	}
	{
		cout << "Removal in the middle: " << endl;
		SingleArray<int> sa(ar_size);
		FactorArray<int> fa(ar_size);
		MatrixArray<int> ma(ar_size);
		StandardArray<int> sta(ar_size);

		TestArrayRemoveMid(sa, ar_size);
		TestArrayRemoveMid(fa, ar_size);
		TestArrayRemoveMid(ma, ar_size);
		TestArrayRemoveMid(sta, ar_size);
	}
	{
		cout << "Removal at the end: " << endl;
		SingleArray<int> sa(ar_size);
		FactorArray<int> fa(ar_size);
		MatrixArray<int> ma(ar_size);
		StandardArray<int> sta(ar_size);

		TestArrayRemoveEnd(sa, ar_size);
		TestArrayRemoveEnd(fa, ar_size);
		TestArrayRemoveEnd(ma, ar_size);
		TestArrayRemoveEnd(sta, ar_size);
	}
}

void TestCustomPriorityQueue()
{
	CustomPQ<int> cpq;
	cpq.Enqueue(99);
	cpq.Enqueue(97);
	cpq.Enqueue(100);
	cpq.Enqueue(101);
	cpq.Enqueue(23);
	assert(cpq.Pop() == 23);
	assert(cpq.Peek() == 97);
	assert(cpq.Pop() == 97);
	assert(cpq.Pop() == 99);
	assert(cpq.Pop() == 100);
	assert(cpq.Pop() == 101);
}

void PriorityQueueEnqueueTest(int total)
{
	{
		auto t1 = clk::now();
		CustomPQ<int> cpq;
		for (size_t i = 0; i < total; ++i)
		{
			cpq.Enqueue(i);
		}
		auto t2 = clk::now();
		std::cout << "CustomPQ Enqueue Test" << " ";
		std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
	}

	{
		auto t1 = clk::now();
		StandardPQ<int> spq;
		for (size_t i = 0; i < total; ++i)
		{
			spq.Enqueue(i);
		}
		auto t2 = clk::now();
		std::cout << "StandardPQ Enqueue Test" << " ";
		std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
	}
}

void PriorityQueuePopTest(int total)
{
	{
		CustomPQ<int> cpq;
		for (int i = 0; i < total; ++i)
			cpq.Enqueue(i);
		
		auto t1 = clk::now();
		while (!cpq.Empty())
		{
			cpq.Pop();
		}
		auto t2 = clk::now();
		std::cout << "CustomPQ Pop Test" << " ";
		std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
	}

	{
		StandardPQ<int> spq;
		for (int i = 0; i < total; ++i)
			spq.Enqueue(i);

		auto t1 = clk::now();
		while (!spq.Empty())
		{
			spq.Pop();
		}
		auto t2 = clk::now();
		std::cout << "StandardPQ Pop Test" << " ";
		std::cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " ms"s << endl;
	}
}

int main()
{
	TestSingleArray();
	TestVectorArray();
	TestFactorArray();
	TestMatrixArray();
	TestStandardArray();
	AllArrayInsertionTest(10000);
	AllArrayRemovalTest(10000);

	PriorityQueueEnqueueTest(10000);
	PriorityQueuePopTest(10000);
	cout << "OK" << endl;
	
	cin.get();
}