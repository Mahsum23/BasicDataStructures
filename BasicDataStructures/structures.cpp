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
	for (size_t i = 0; i < total; ++i)
	{
		ar.Remove(0);
	}
}

template <typename T>
void TestArrayRemoveMid(Array<T>& ar, size_t total)
{
	for (size_t i = 0; i < total; ++i)
	{
		ar.Remove(ar.Size() / 2);
	}
}

template <typename T>
void TestArrayRemoveEnd(Array<T>& ar, size_t total)
{
	
	for (size_t i = 0; i < total; ++i)
	{
		ar.Remove(ar.Size());
	}
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

static int allocated = 0;

void* operator new(size_t size) 
{ 
	allocated += size;
	return malloc(size); 
}

void operator delete(void* memory, size_t size)
{
	allocated -= size;
	free(memory);
}
//
void operator delete[](void* memory, size_t size)
{
	allocated -= size;
	free(memory);
}

#include <thread>

struct Pup
{
	int x, y, z;
};

struct Obj
{
	Obj()
	{
		ptr_ = new Pup[100000];
		cout << allocated << endl;
		delete ptr_;
		cout << allocated << endl;
	}

	void del()
	{
		delete[] ptr_;
	}
	Pup* ptr_;
};

int main()
{
	//TestSingleArray();
	//TestVectorArray();
	//TestFactorArray();
	//TestMatrixArray();
	//TestStandardArray();
	//AllArrayInsertionTest(10000);
	//AllArrayRemovalTest(10000);
	// 
	// 
	// 
	//{
	//	int* par[100000];
	//	for (int i = 0; i < 100000; ++i)
	//	{
	//		par[i] = new int(99);
	//		std::this_thread::sleep_for(500ns);
	//	}
	//	cout << allocated << endl;
	//	for (int i = 0; i < 100000; ++i)
	//	{
	//		delete par[i];
	//		std::this_thread::sleep_for(500ns);
	//	}
	//}
	//{
	//	unique_ptr<Obj> p = make_unique<Obj>();
	//	cout << allocated << endl;
	//}
	//cout << allocated << endl;


	//{
	//	Pup* p = new Pup[10];
	//	std::this_thread::sleep_for(1s);
	//	cout << allocated << endl;
	//	delete[] p;
	//	cout << allocated << endl;
	//}

	{
		int* p = new int[1000000];
		std::this_thread::sleep_for(1s);
		cout << allocated << endl;
		delete[] p;
		cout << allocated << endl;
	}
	

	//Obj obj = Obj();
	//cout << allocated << endl;
	//std::this_thread::sleep_for(1s);
	//obj.del();
	//cout << allocated << endl;

	//{
	//	SingleArray<int> sa;
	//	for (int i = 0; i < 100000; ++i)
	//	{
	//		sa.Insert(0, 0);
	//		std::this_thread::sleep_for(100ns);
	//	}
	//	delete[] sa.ptr_;
	//}
	std::this_thread::sleep_for(10s);
	//cout << "OK" << endl;
	
	cin.get();
}