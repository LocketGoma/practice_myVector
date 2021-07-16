#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename T>
class CMyVector
{
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
			//if (operator == (CMyVector<T>.end()))
			//{
			//	return *this;
			//}
			++cur;
			//cur = cur + 1;

			return *this;
		}
		iterator& operator -- ()
		{
			//if (operator == (CMyVector<T>.begin()))
			//{
			//	return *this;
			//}
			--cur;
			//cur = cur - 1;

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
	CMyVector();												//1
	//CMyVector(size_t count, const T& value, 
	//const Allocator& alloc = Allocator())						//2 : Allocator기반이라 무시
	CMyVector(size_t count, const T& value);					//3
	CMyVector(size_t count);									//4
	CMyVector(T first, T last) = delete;						//5 : integral type 타입일시 [fisrt, last). 미구현
	CMyVector(const CMyVector& other);							//6
	//CMyVector(const CMyVector& other, const Allocator& alloc);//7 : Allocator기반이라 무시
	CMyVector(CMyVector&& other);								//8
	//CMyVector(CMyVector&& other, const Allocator& alloc);		//9 : Allocator기반이라 무시
	//10번은 이해못했음 + Allocator 기반이라 패스
	
	~CMyVector();

	CMyVector& operator = (const CMyVector& other)
	{
		clear();

		_tData = new T[other._capacity];
		memcpy_s(_tData, sizeof(T) * other._size, other._tData, sizeof(T) * other._size);
		_size = other._size;
		_capacity = other._capacity;

		return *this;

	};		//복사
	CMyVector& operator = (CMyVector&& other) noexcept
	{
		clear();

		_tData = other._tData;		
		_size = other._size;
		_capacity = other._capacity;

		other._tData = nullptr;
		//other.~CMyVector();						//이래도 됨?
		other.clear();

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

	//열거자 (iterators) - 나중에
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
	void clear();

	//열거자 방식 함수들
	///삽입 연산자
	iterator<T> insert(iterator<T> pos, const T& value)  //1	copy
	{
		if (isFull())
		{
			resize(_capacity << 1);
		}
		iterator<T> iter = end();

		while (iter != pos)		//으아악 연산자 순서
		{
			memcpy_s(&(*iter), sizeof(T), (&(*(iter))-1), sizeof(T));
			--iter;
		}
		memcpy_s(&(*pos), sizeof(T), &(value), sizeof(T));

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

		while (iter != pos)		//으아악 연산자 순서
		{
			memcpy_s(&(*iter), sizeof(T), (&(*(iter)) - 1), sizeof(T));
			--iter;
		}
		memcpy_s(&(*pos), sizeof(T), &(value), sizeof(T));

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

		while (iter != pos)
		{
			++iter;
		}
		*iter = T();

		while (iter != end())
		{
			memcpy_s(&(*iter), sizeof(T), (&(*(iter)) + 1), sizeof(T));
			++iter;
		}

		--_size;

		return pos;
	}


	//일반 방식 함수들
	///삽입 연산자
	void push_back(const T& value);			//copy
	void push_back(T&& value);				//move
	void pop_back();

	//https://stackoverflow.com/questions/58881357/how-to-create-an-emplace-back-method
	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		//push_back(T(std::forward<Args>(args)...)); //더 확실한것
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
//1번 생성자
template<typename T>
inline CMyVector<T>::CMyVector()
{
	_capacity = Default_size;
	_size = 0;
	_tData = new T[Default_size];
}

//3번 생성자
template<typename T>
inline CMyVector<T>::CMyVector(size_t count, const T& value)
{
	_capacity = count;
	_size = count;

	_tData = new T[_capacity];

	//수정 필요
	for (size_t i = 0; i < _size; ++i)
	{
		_tData[i] = value;
	}


}
//4번 생성자
template<typename T>
inline CMyVector<T>::CMyVector(size_t count)
{
	_capacity = count;
	_size = 0;
	_tData = new T[_capacity];

}

//5번 생성자
//template<typename T>
//inline CMyVector<T>::CMyVector(T first, T last)
//{
//	//보류. 다이나믹 캐스트 쓸까 했는데 그건 너무 노답인거 같음.
//}

//6번 생성자 - 복사 생성
template<typename T>
inline CMyVector<T>::CMyVector(const CMyVector& other)
{
	_capacity = other._capacity;
	_size = other._size;

	_tData = new T[_capacity];

	for (size_t i = 0; i < _size; ++i)
	{
		memcpy(_tData[i],other._tData[i], sizeof(T));
	}

}

//8번 생성자 - 이동 생성
template<typename T>
inline CMyVector<T>::CMyVector(CMyVector&& other)
{
	_tData = new T[_capacity];

	for (size_t i = 0; i < _size; ++i)
	{
		memmove(_tData[i], other._tData[i], sizeof(T));
	}

	delete[] other._tData;
	other._size = 0;

}
//얘도 고쳐야 하구요
template<typename T>
inline CMyVector<T>::~CMyVector()
{
	_capacity = 0;
	_size = 0;
	if (_tData != nullptr)
		delete[] _tData;

	_tData = nullptr;
}

template<typename T>
inline void CMyVector<T>::reserve(size_t new_cap)
{
	if (_capacity >= new_cap)
	{
		return;
	}

	T* newData = new T[new_cap];

	memcpy_s(newData, sizeof(T) * _capacity, _tData, sizeof(T) * _capacity);

	delete[] _tData;			//?

	_tData = newData;

	_capacity = new_cap;

}

template<typename T>
inline void CMyVector<T>::shrink_to_fit()
{
	if (_capacity == _size)
	{
		return;
	}

	T* newData = new T[_size];

	//newData = malloc(sizeof(T) * new_cap);

	memcpy_s(newData, sizeof(T) * _size, _tData, sizeof(T) * _size);

	delete[] _tData;			//?

	_tData = newData;

	_capacity = _size;

}
//리사이즈 꼭 고쳐야하구요
template<typename T>
inline void CMyVector<T>::resize(size_t new_size)
{
	T* newData = new T[new_size];
	size_t replace_size = new_size > _size ? _size : new_size;
	for (size_t i = 0; i < replace_size; ++i)
	{
		newData[i] = std::move(_tData[i]);
		//memmove(&newData[i], &_tData[i], sizeof(T));		
	}
	//안 지워졌거든?
	//delete[] _tData;
	_tData = newData;

	_size = replace_size;
	_capacity = new_size;

}

template<typename T>
inline void CMyVector<T>::resize(size_t new_size, const T& value)
{
	T* newData = new T[new_size];
	
	if (new_size > _size)
	{
		for (size_t i = 0; i < new_size; ++i)
		{
			if (i < _size)
			{
				//memmove(&newData[i], &_tData[i], sizeof(T));
				newData[i] = std::move(_tData[i]);
			}
			else
			{
				//memmove(&newData[i], &value, sizeof(T));
				newData[i] = value;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < new_size; ++i)
		{
			newData[i] = std::move(_tData[i]);
		}
	}
	_tData = newData;

	_size = new_size;
	_capacity = new_size;
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
inline void CMyVector<T>::clear()
{
	if (_tData == nullptr)
	{
		_tData = new T[_capacity];
	}
	else
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_tData[i] = T();
		}
	}
	_size = 0;

}

template<typename T>
inline void CMyVector<T>::push_back(const T& value)
{
	if (_capacity == _size)
	{
		resize(_capacity * 2);
		_capacity << 1;	
	}
	_tData[_size] = value;
	//memmove(&_tData[_size], &value, sizeof(T));
	++_size;

}

template<typename T>
inline void CMyVector<T>::push_back(T&& value)
{
	if (_capacity == _size)
	{
		resize(_capacity * 2);
		_capacity << 1;
	}

	_tData[_size] = value;
	++_size;
}

template<typename T>
inline void CMyVector<T>::pop_back()
{
	if (empty())
	{
		return;
	}
	_tData[_size - 1] = T();

	--_size;

}
