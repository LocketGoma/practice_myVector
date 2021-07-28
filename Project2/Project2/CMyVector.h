#pragma once
using namespace std;

#include <xmemory>
#include <iostream>

template <typename T>
class CMyVector
{
	//using pointer = typename T::const_pointer;

//열거자
public:
	template <typename T>
	class iterator
	{
	private:
		T* cur;
	public:

		iterator(T* p = nullptr) : cur(p) {}

		iterator& operator = (T* p)
		{
			cur = p;
		}

		iterator& operator ++ ()
		{
			++cur;

			return *this;
		}

		iterator& operator -- ()
		{
			--cur;

			return *this;
		}

		T& operator*()
		{
			return *cur;
		}

		bool operator == (const iterator& ref)
		{
			return cur == ref.cur;
		}
		bool operator != (const iterator& ref)
		{
			return cur != ref.cur;
		}
	};

	//생성자 & 소멸자
public:
	CMyVector();												 //1
	//CMyVector(size_t count, const T& value, 
	//const Allocator& alloc = Allocator())						 //2 : Allocator기반이라 무시
	CMyVector(size_t count, const T& value);					 //3
	CMyVector(size_t count);									 //4
	CMyVector(T first, T last) = delete;						 //5 : integral type 타입일시 [fisrt, last). 미구현
	CMyVector(const CMyVector& other);							 //6
	//CMyVector(const CMyVector& other, const Allocator& alloc); //7 : Allocator기반이라 무시
	CMyVector(CMyVector&& other);								 //8
	//CMyVector(CMyVector&& other, const Allocator& alloc);		 //9 : Allocator기반이라 무시
	//10번은 이해못했음 + Allocator 기반이라 패스
	
	~CMyVector() noexcept;

	CMyVector& operator = (const CMyVector& other)
	{


		_size = other._size;
		_capacity = other._capacity;

		return *this;

	};		//복사

	CMyVector& operator = (CMyVector&& other) noexcept
	{


		_size = other._size;
		_capacity = other._capacity;



		return *this;
	} ;		//이동

	//탐색
public:
	T& at(size_t i) { return operator[](i); }
	const T& at(size_t i) const { return operator[](i); }
	T& operator [] (size_t i) { return _tData[i]; }
	const T& operator [] (size_t i) const { return _tData[i]; }

	T& front() { return _tData[0]; }
	const T& front() const { return _tData[0]; }
	T& back() { return _tData[_size - 1]; }
	const T& back() const { return _tData[_size - 1]; }

	T* data() { return _tData; }
	const T* data() const { return _tData; }

	//열거자 (iterators)
public:
	iterator<T> begin() { return iterator<T>(&_tData[0]); };
	const iterator<T> begin() const { return iterator<T>(&_tData[0]); };
	iterator<T> end() { return iterator<T>(&_tData[_size]); };
	const iterator<T> end() const { return iterator<T>(&_tData[_size]); };

	//메모리 사이즈 관련
public:
	bool empty() const { return _size == 0; }
	size_t size() const { return _size; }
	//size_t max_size() const {}					//구현할 필요가 없어보여서 미구현
	void reserve(size_t new_cap);
	size_t capacity() const { return _capacity; };
	void shrink_to_fit();
	void resize(size_t new_size);
	void resize(size_t new_size, const T& value);
	void swap(CMyVector& other);

	//데이터 추가,삭제
public :
	void clear() noexcept;

	//열거자 방식 함수들
	///삽입 연산자
	iterator<T> insert(iterator<T> pos, const T& value)  //1	copy
	{
		if (isFull())
		{
			resize(_capacity << 1);
		}
		iterator<T> iter = end();
		iterator<T> m_iter = end();

		--m_iter;

		while (iter != pos)		
		{
			*iter = *m_iter;

			--m_iter;
			--iter;
		}
		*pos = T(value);

		++_size;

		return pos;

	}
	iterator<T> insert(iterator<T> pos, T&& value)		  //2 move
	{
		if (isFull())
		{
			resize(_capacity << 1);
		}
		iterator<T> iter = end();
		iterator<T> m_iter = end();

		--m_iter;

		while (iter != pos)	
		{
			*iter = *m_iter;

			--m_iter;
			--iter;
		}
		*pos = T(value);

		++_size;

		return pos;
	}

	template<typename... Args>
	iterator<T> emplace(iterator<T> pos, Args&&... args)
	{
		return insert(pos, T(args...));
	}

	///삭제 연산자
	iterator<T> erase(iterator<T> pos)
	{
		iterator<T> iter = begin();
		iterator<T> m_iter;

		while (iter != pos)
		{
			++iter;
		}
		(*iter).~T();

		m_iter = iter;
		++m_iter;

		while (iter != end())
		{
			*iter = *m_iter;

			++iter;
			++m_iter;
		}

		--_size;

		return pos;
	}


	//일반 방식 함수들
	///삽입 연산자
	void push_back(const T& value);			//copy
	void push_back(T&& value);				//move
	void pop_back();

	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		push_back(T(args...));
	}

	//내부 판단용 함수
private :
	bool isFull() { return _capacity == _size; }

	//메모리 관련
private:
	size_t _capacity;			// 할당된 용량
	size_t _size;				// 사용중인 사이즈
	T* _tData;					// 데이터 배열
		
	static const size_t Default_size = 1;
};


template<typename T>
inline CMyVector<T>::CMyVector()
{
	_capacity = Default_size;
	_size = 0;
	reserve(_capacity);
}

template<typename T>
inline CMyVector<T>::CMyVector(size_t count, const T& value)
{
	_capacity = count;
	reserve(_capacity);

	for (size_t i = 0; i < _capacity; ++i)
	{
		_tData[i] = new (&_tData[i]) T(value);
	}
}

template<typename T>
inline CMyVector<T>::CMyVector(size_t count)
{
	_capacity = count;
	_size = 0;
	reserve(_capacity);
}

template<typename T>
inline CMyVector<T>::CMyVector(const CMyVector& other)
{
}

template<typename T>
inline CMyVector<T>::CMyVector(CMyVector&& other)
{
}

template<typename T>
inline CMyVector<T>::~CMyVector() noexcept
{
	for (size_t i = 0; i < _size; ++i)
	{
		_tData[i].~T();
	}
	free(_tData);

}


template<typename T>
inline void CMyVector<T>::reserve(size_t new_cap)
{
	if (_tData == nullptr)
	{
		std::cout << new_cap * sizeof(T) << std::endl;

		
		_tData = static_cast<T*>(malloc(new_cap * sizeof(T)));
		
	}
}

template<typename T>
inline void CMyVector<T>::shrink_to_fit()
{
	T* newCap = malloc(_size * sizeof(T));

	for (size_t i = 0; i < _size; ++i)
	{
		newCap[i] = new (newCap[i]) T(_tData[i]);
		_tData[i].~T();
	}
	
	delete[] _tData;

	_tData = newCap;
}

template<typename T>
inline void CMyVector<T>::resize(size_t new_size)
{
	if (new_size == _capacity)
		return;

	T* newCap = static_cast<T*>(malloc(new_size * sizeof(T)));

	if (new_size > _capacity)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			new (&newCap[i]) T(_tData[i]);
			_tData[i].~T();
		}

	}
	else
	{
		for (size_t i = 0; i < new_size; ++i)
		{
			new (&newCap[i]) T(_tData[i]);
			_tData[i].~T();
		}
		for (size_t i = new_size; i < _size; ++i)
		{
			_tData[i].~T();
		}
	}
	free(_tData);

	_tData = newCap;

}

template<typename T>
inline void CMyVector<T>::resize(size_t new_size, const T& value)
{
	if (new_size == _capacity)
		return;

	_capacity = new_size;

	T* newCap = malloc(new_size * sizeof(T));

	if (new_size > _capacity)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			newCap[i] = new (newCap[i]) T(_tData[i]);
			_tData[i].~T();
		}
		for (size_t i = _size; i < new_size; ++i)
		{
			_tData[i] = new (newCap[i]) T(value);
		}
	}
	else
	{
		for (size_t i = 0; i < new_size; ++i)
		{
			newCap[i] = new (newCap[i]) T(_tData[i]);
			_tData[i].~T();
		}
		for (size_t i = new_size; i < _size; ++i)
		{
			_tData[i].~T();
		}

		_size = new_size;
	}
	delete[] _tData;

	_tData = newCap;
	
}

template<typename T>
inline void CMyVector<T>::swap(CMyVector& other)
{
	T* temp = _tData;
	_tData = other._tData;
	other._tData = temp;

	size_t tempSize = _size;
	_size = other._size;
	other._size = tempSize;

	size_t tempCapacity = _capacity;
	_capacity = other._capacity;
	other._capacity = tempCapacity;

	temp = nullptr;

}

template<typename T>
inline void CMyVector<T>::clear() noexcept
{
	for (size_t i = 0; i < _size; ++i)
	{
		_tData[i].~T();
	}
	_size = 0;

}

template<typename T>
inline void CMyVector<T>::push_back(const T& value)
{
	if (_capacity == _size)
	{
		resize(_capacity * 2);
		_capacity = _capacity << 1;
	}
	new (&_tData[_size])T(value);
	++_size;
}

template<typename T>
inline void CMyVector<T>::push_back(T&& value)
{
	if (_capacity == _size)
	{
		resize(_capacity * 2);
		_capacity = _capacity << 1;
	}
	//_tData[_size] = value;
	new (&_tData[_size])T(value);


	++_size;
}

template<typename T>
inline void CMyVector<T>::pop_back()
{
	if (empty())
	{
		return;
	}
	_tData[_size-1].~T();
	--_size;

}
