#pragma once

#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <queue>

template <typename T>
class Array
{
public:
	virtual void Insert(T item, size_t ind) = 0;
	virtual T Remove(size_t ind) = 0;
	virtual std::string ClassName() const = 0;
	virtual size_t Size() const = 0;
};

template <typename T>
class SingleArray : public Array<T>
{
public:
	using Iterator = T*;
	using ConstIterator = const T*;

	SingleArray() = default;
	SingleArray(size_t size)
		: size_(size)
	{
		ptr_ = new T[size];
	}
	SingleArray(std::initializer_list<T> list)
	{
		ptr_ = new T[list.size()];
		for (T el : list)
		{
			ptr_[size_] = el;
			++size_;
		}
	}

	void Insert(T item, size_t ind) override
	{
		T* old_ptr = ptr_;
		ptr_ = new T[size_ + 1];
		std::move(old_ptr, old_ptr + ind, ptr_);
		ptr_[ind] = item;
		std::move(old_ptr + ind, old_ptr + size_, ptr_ + ind + 1);
		delete[] old_ptr;
		++size_;
	}

	T Remove(size_t ind) override
	{
		T res = ptr_[ind];
		std::move(ptr_ + ind + 1, ptr_ + size_, ptr_ + ind);
		--size_;
		return res;
	}

	Iterator begin() noexcept
	{
		return ptr_;
	}

	Iterator end() noexcept
	{
		return ptr_ + size_;
	}

	ConstIterator cbegin() const noexcept
	{
		return ptr_;
	}

	ConstIterator cend() const noexcept
	{
		return ptr_ + size_;
	}

	size_t Size() const noexcept
	{
		return size_;
	}

	T& operator[](size_t index)
	{
		return ptr_[index];
	}

	std::string ClassName() const noexcept override
	{
		return "Single Array";
	}

	bool operator==(const SingleArray<T>& other) const
	{
		return std::equal(cbegin(), cend(), other.cbegin(), other.cend());
	}

	~SingleArray()
	{
		std::destroy(ptr_, ptr_ + size_);
		delete[] ptr_;
	}

public:
	T* ptr_ = nullptr;

private:
	size_t size_ = 0;
	//T* ptr_ = nullptr;
};


template <typename T>
class VectorArray : public Array<T>
{
public:
	using Iterator = T*;
	using ConstIterator = const T*;
	VectorArray() = default;
	VectorArray(size_t size, size_t delta = 20)
		: size_(size), delta_(delta)
	{
		ptr_ = new T[size];
	}

	VectorArray(std::initializer_list<T> list, size_t delta = 20)
		: delta_(delta)
	{
		ptr_ = new T[list.size()];
		
		for (T el : list)
		{
			ptr_[size_] = el;
			++size_;
		}
		capacity_ = size_;
	}

	void Insert(T item, size_t ind) override
	{
		if (capacity_ == size_)
		{
			T* old_ptr = ptr_;
			ptr_ = new T[size_ + delta_];
			std::move(old_ptr, old_ptr + ind, ptr_);
			ptr_[ind] = item;
			std::move(old_ptr + ind, old_ptr + size_, ptr_ + ind + 1);
			std::destroy_n(old_ptr, size_);
			++size_;
			capacity_ += delta_;
		}
		else
		{
			int cnt = (ptr_ + size_) - (ptr_ + ind);
			std::move_backward(ptr_ + ind, ptr_ + size_, ptr_ + size_ + 1);
			ptr_[ind] = item;
			++size_;
		}
	}

	T Remove(size_t ind) override
	{
		T res = ptr_[ind];
		std::move(ptr_ + ind + 1, ptr_ + size_, ptr_ + ind);
		std::destroy_at(ptr_ + size_ - 1);
		--size_;
		return res;
	}

	Iterator begin() noexcept
	{
		return ptr_;
	}

	Iterator end() noexcept
	{
		return ptr_ + size_;
	}

	ConstIterator cbegin() const noexcept
	{
		return ptr_;
	}

	ConstIterator cend() const noexcept
	{
		return ptr_ + size_;
	}

	T& operator[](size_t index)
	{
		return ptr_[index];
	}

	std::string ClassName() const noexcept override
	{
		return "Vector Array";
	}

	bool operator==(const VectorArray<T>& other) const
	{
		return std::equal(cbegin(), cend(), other.cbegin(), other.cend());
	}

	size_t Size() const noexcept
	{
		return size_;
	}

	~VectorArray()
	{
		std::destroy(ptr_, ptr_ + capacity_);
		delete[] ptr_;
	}



private:
	size_t size_ = 0;
	size_t delta_ = 20;
	size_t capacity_ = 0;
	T* ptr_ = nullptr;
};

template <typename T>
class MatrixArray;

template <typename T>
class FactorArray : public Array<T>
{
public:
	friend class MatrixArray<T>;
	using Iterator = T*;
	using ConstIterator = const T*;

	FactorArray() = default;

	FactorArray(size_t size, size_t factor = 2)
		: factor_(factor), size_(size)
	{
		ptr_ = new T[size];
	}

	FactorArray(std::initializer_list<T> list, size_t factor = 2)
		: factor_(factor)
	{
		ptr_ = new T[list.size()];

		for (T el : list)
		{
			ptr_[size_] = el;
			++size_;
		}
		capacity_ = size_;
	}

	void Insert(T item, size_t ind) override
	{
		if (capacity_ <= size_)
		{
			T* old_ptr = ptr_;
			ptr_ = new T[size_ * factor_ + 1];
			std::move(old_ptr, old_ptr + ind, ptr_);
			ptr_[ind] = item;
			std::move(old_ptr + ind, old_ptr + size_, ptr_ + ind + 1);
			delete[] old_ptr;
			++size_;
			capacity_ *= factor_;
		}
		else
		{
			ptr_[ind] = item;
			std::move_backward(ptr_ + ind, ptr_ + size_, ptr_ + size_ + 1);
			++size_;
		}
	}

	T Remove(size_t ind) override
	{
		T res = ptr_[ind];
		std::move(ptr_ + ind + 1, ptr_ + size_, ptr_ + ind);
		std::destroy_at(ptr_ + size_ - 1);
		--size_;
		return res;
	}

	Iterator begin() noexcept
	{
		return ptr_;
	}

	Iterator end() noexcept
	{
		return ptr_ + size_;
	}

	ConstIterator cbegin() const noexcept
	{
		return ptr_;
	}

	ConstIterator cend() const noexcept
	{
		return ptr_ + size_;
	}

	T& operator[](size_t index)
	{
		return ptr_[index];
	}

	const T& operator[](size_t index) const
	{
		return ptr_[index];
	}

	std::string ClassName() const noexcept override
	{
		return "Factor Array";
	}

	bool operator==(const FactorArray<T>& other) const
	{
		return std::equal(cbegin(), cend(), other.cbegin(), other.cend());
	}

	size_t Size() const noexcept
	{
		return size_;
	}

	~FactorArray()
	{
		std::destroy(ptr_, ptr_ + capacity_);
	}



private:
	size_t size_ = 0;
	size_t factor_ = 2;
	size_t capacity_ = 0;
	T* ptr_ = nullptr;
};


template <typename T>
class MatrixArray : public Array<T>
{
public:

	using Iterator = T*;
	using ConstIterator = const T*;

	MatrixArray() = default;

	MatrixArray(size_t size, size_t inner_size = 10)
	{
		size_t outer_size = size / inner_size_ + 1;
		for (int i = 0; i < outer_size; ++i)
			data_.Insert(FactorArray<T>(inner_size_), i / inner_size_);
		size_ = size;
	}

	MatrixArray(std::initializer_list<T> list, size_t inner_size = 10)
		: inner_size_(inner_size)
	{
		size_t outer_size = list.size() / inner_size_ + 1;
		for (int i = 0; i < outer_size; ++i)
		{
			data_.Insert(FactorArray<T>(inner_size_), i / inner_size_);
			capacity_ += inner_size_;
		}
		for (int i = 0; i < list.size(); ++i)
		{
			(*this)[i] = *(list.begin() + i);
		}
		size_ = list.size();
	}

	void Insert(T item, size_t ind) override
	{
		assert(ind <= size_);
		if (capacity_ == size_)
		{
			data_.Insert(FactorArray<T>(inner_size_), size_ / inner_size_);
			capacity_ += inner_size_;
			size_t outer_ind = ind / inner_size_;
			size_t inner_ind = ind % inner_size_;
		}
		for (size_t i = size_; i > ind; --i)
		{
			(*this)[i] = (*this)[i - 1];
		}
		(*this)[ind] = item;
		++size_;
	}

	T Remove(size_t ind) override
	{
		assert(ind < size_);
		T res = (*this)[ind];
		for (size_t i = ind; i < size_-1; ++i)
		{
			(*this)[i] = (*this)[i + 1];
		}
		std::destroy_at(data_[size_ / inner_size_].ptr_ + size_ % inner_size_);
		--size_;
		return res;
	}

	Iterator begin() noexcept
	{
		return data_[0].begin();
	}

	Iterator end() noexcept
	{
		return data_[size_ / inner_size_].end();
	}

	ConstIterator cbegin() const noexcept
	{
		return data_[0].cbegin();
	}

	ConstIterator cend() const noexcept
	{
		return data_[size_ / inner_size_].cend();
	}

	T& operator[](size_t index) 
	{
		return data_[index / inner_size_][index % inner_size_];
	}

	const T& operator[](size_t index) const
	{
		return data_[index / inner_size_][index % inner_size_];
	}

	std::string ClassName() const noexcept override
	{
		return "Matrix Array";
	}

	bool operator==(const MatrixArray<T>& other) const
	{
		if (other.Size() != Size())
			return false;
		for (int i = 0; i < Size(); ++i)
		{
			if (other[i] != (*this)[i])
				return false;
		}
		return true;
	}

	size_t Size() const noexcept
	{
		return size_;
	}

	~MatrixArray()
	{
		
	}



private:
	size_t size_ = 0;
	size_t capacity_ = 0;
	size_t inner_size_ = 10;
	
	FactorArray<FactorArray<T>> data_;
	
};

template <typename T>
class StandardArray : public Array<T>
{
public:

	StandardArray() = default;
	StandardArray(size_t size)
	{
		data_ = std::vector<T>(size);
	}
	StandardArray(std::initializer_list<T> list)
		: data_(list)
	{
	}

	void Insert(T item, size_t ind) override
	{
		data_.insert(data_.begin() + ind, item);
	}

	T Remove(size_t ind) override
	{
		T res = data_[ind];
		data_.erase(data_.begin() + ind);
		return res;
	}

	auto begin() noexcept
	{
		return data_.begin();
	}

	auto end() noexcept
	{
		return data_.end();
	}

	auto cbegin() const noexcept
	{
		return data_.cbegin();
	}

	auto cend() const noexcept
	{
		return data_.cend();
	}

	size_t Size() const noexcept
	{
		return data_.size();
	}

	T& operator[](size_t index)
	{
		return data_[index];
	}

	std::string ClassName() const noexcept override
	{
		return "Standard Array";
	}

	bool operator==(const StandardArray<T>& other) const
	{
		return std::equal(cbegin(), cend(), other.cbegin(), other.cend());
	}

private:
	std::vector<T> data_;
};


template <typename T>
class PriorityQueue
{
public:
	virtual void Enqueue(T value) = 0;
	virtual T Peek() const = 0;
	virtual T Pop() = 0;
	virtual bool Empty() const = 0;
};

template <typename T, typename Cont = std::vector<T>, typename Comp = std::greater<>>
class CustomPQ : public PriorityQueue<T>
{
public:

	void Enqueue(T value) override
	{
		data_.push_back(value);
		std::swap(data_[0], data_.back());
		HeapifyAll();
	}

	T Peek() const override
	{
		return data_[0];
	}

	T Pop() override
	{
		std::swap(data_[0], data_.back());
		T res = data_.back();
		data_.pop_back();
		HeapifyAll();
		
		return res;
	}
	
	bool Empty() const override
	{
		return data_.size() == 0;
	}

private:
	void HeapifyAll()
	{
		for (int i = (data_.size() - 2) / 2; i >= 0; --i)
		{
			Heapify(i);
		}
	}
	void Heapify(int index)
	{
		int l = 2 * index + 1;
		int r = 2 * index + 2;
		int x = index;
		if (l < data_.size() && Comp()(data_[index], data_[l])) x = l;
		if (r < data_.size() && Comp()(data_[index], data_[r])) x = r;
		if (x == index) return;
		std::swap(data_[x], data_[index]);
		Heapify(x);
	}

	Cont data_;
};

template <typename T>
class StandardPQ : public PriorityQueue<T>
{
public:
	void Enqueue(T value) override
	{
		pq_.push(value);
	}

	T Peek() const override
	{
		return pq_.top();
	}

	T Pop() override
	{
		T res = pq_.top();
		pq_.pop();
		return res;
	}

	bool Empty() const override
	{
		return pq_.empty();
	}

private:
	std::priority_queue<T> pq_;
};



template <typename T>
std::ostream& operator<<(std::ostream& out, SingleArray<T>& ar)
{
	for (T el : ar)
	{
		out << el << " ";
	}
	out << std::endl;
	return out;
}