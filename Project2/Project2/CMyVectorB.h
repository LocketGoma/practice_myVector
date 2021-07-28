//#pragma once
//
//#include <string>
//#include <xmemory>
//
//using namespace std;
//
//template <typename T>
//class CMyVectorB
//{
//	//using pointer = typename T::const_pointer;
//
////열거자
//public:
//	template <typename T>
//	class iterator
//	{
//	private:
//		T* cur;
//	public:
//
//		iterator(T* p = nullptr) : cur(p) {}
//
//		iterator& operator = (T* p)
//		{
//			cur = p;
//		}
//
//		iterator& operator ++ ()
//		{
//			++cur;
//
//			return *this;
//		}
//
//		iterator& operator -- ()
//		{
//			--cur;
//
//			return *this;
//		}
//
//		T& operator*()
//		{
//			return *cur;
//		}
//
//		bool operator == (const iterator& ref)
//		{
//			return cur == ref.cur;
//		}
//		bool operator != (const iterator& ref)
//		{
//			return cur != ref.cur;
//		}
//	};
//
//	//생성자 & 소멸자
//public:
//	CMyVectorB();												 //1
//	//CMyVectorB(size_t count, const T& value, 
//	//const Allocator& alloc = Allocator())						 //2 : Allocator기반이라 무시
//	CMyVectorB(size_t count, const T& value);					 //3
//	CMyVectorB(size_t count);									 //4
//	CMyVectorB(T first, T last) = delete;						 //5 : integral type 타입일시 [fisrt, last). 미구현
//	CMyVectorB(const CMyVectorB& other);							 //6
//	//CMyVectorB(const CMyVectorB& other, const Allocator& alloc); //7 : Allocator기반이라 무시
//	CMyVectorB(CMyVectorB&& other);								 //8
//	//CMyVectorB(CMyVectorB&& other, const Allocator& alloc);		 //9 : Allocator기반이라 무시
//	//10번은 이해못했음 + Allocator 기반이라 패스
//
//	~CMyVectorB() noexcept;
//
//	CMyVectorB& operator = (const CMyVectorB& other)
//	{
//		clear();
//
//		delete[] _tData;
//		_tData = new T[other._capacity];
//
//		for (size_t i = 0; i < other._capacity; ++i)
//		{
//			_tData[i] = T(other._tData[i]);
//		}
//
//		_size = other._size;
//		_capacity = other._capacity;
//
//		return *this;
//
//	};		//복사
//
//	CMyVectorB& operator = (CMyVectorB&& other) noexcept
//	{
//		clear();
//
//		delete[] _tData;
//
//		_tData = other._tData;
//		other._tData = nullptr;
//
//		_size = other._size;
//		_capacity = other._capacity;
//
//		other.~CMyVectorB();						//이래도 됨?
//
//		return *this;
//	};		//이동
//
//	//탐색
//public:
//	T& at(size_t i) { return operator[](i); }
//	const T& at(size_t i) const { return operator[](i); }
//	T& operator [] (size_t i) { return _tData[i]; }
//	const T& operator [] (size_t i) const { return _tData[i]; }
//
//	T& front() { return _tData[0]; }
//	const T& front() const { return _tData[0]; }
//	T& back() { return _tData[_size - 1]; }
//	const T& back() const { return _tData[_size - 1]; }
//
//	T* data() { return _tData; }
//	const T* data() const { return _tData; }
//
//	//열거자 (iterators)
//public:
//	iterator<T> begin() { return iterator<T>(&_tData[0]); };
//	const iterator<T> begin() const { return iterator<T>(&_tData[0]); };
//	iterator<T> end() { return iterator<T>(&_tData[_size]); };
//	const iterator<T> end() const { return iterator<T>(&_tData[_size]); };
//
//	//메모리 사이즈 관련
//public:
//	bool empty() const { return _size == 0; }
//	size_t size() const { return _size; }
//	//size_t max_size() const {}					//구현할 필요가 없어보여서 미구현
//	void reserve(size_t new_cap);
//	size_t capacity() const { return _capacity; };
//	void shrink_to_fit();
//	void resize(size_t new_size);
//	void resize(size_t new_size, const T& value);
//	void swap(CMyVectorB& other);
//
//	//데이터 추가,삭제
//public:
//	void clear() noexcept;
//
//	//열거자 방식 함수들
//	///삽입 연산자
//	iterator<T> insert(iterator<T> pos, const T& value)  //1	copy
//	{
//		if (isFull())
//		{
//			resize(_capacity << 1);
//		}
//		iterator<T> iter = end();
//		iterator<T> m_iter = end();
//
//		--m_iter;
//
//		while (iter != pos)
//		{
//			*iter = *m_iter;
//
//			--m_iter;
//			--iter;
//		}
//		*pos = T(value);
//
//		++_size;
//
//		return pos;
//
//	}
//	iterator<T> insert(iterator<T> pos, T&& value)		  //2 move
//	{
//		if (isFull())
//		{
//			resize(_capacity << 1);
//		}
//		iterator<T> iter = end();
//		iterator<T> m_iter = end();
//
//		--m_iter;
//
//		while (iter != pos)
//		{
//			*iter = *m_iter;
//
//			--m_iter;
//			--iter;
//		}
//		*pos = T(value);
//
//		++_size;
//
//		return pos;
//	}
//
//	template<typename... Args>
//	iterator<T> emplace(iterator<T> pos, Args&&... args)
//	{
//		return insert(pos, T(args...));
//	}
//
//	///삭제 연산자
//	iterator<T> erase(iterator<T> pos)
//	{
//		iterator<T> iter = begin();
//		iterator<T> m_iter;
//
//		while (iter != pos)
//		{
//			++iter;
//		}
//		(*iter).~T();
//
//		m_iter = iter;
//		++m_iter;
//
//		while (iter != end())
//		{
//			//memcpy_s(&(*iter), sizeof(T), (&(*(iter)) + 1), sizeof(T));
//			*iter = *m_iter;
//
//			++iter;
//			++m_iter;
//		}
//
//		--_size;
//
//		return pos;
//	}
//
//
//	//일반 방식 함수들
//	///삽입 연산자
//	void push_back(const T& value);			//copy
//	void push_back(T&& value);				//move
//	void pop_back();
//
//	//https://stackoverflow.com/questions/58881357/how-to-create-an-emplace-back-method
//	template<typename... Args>
//	void emplace_back(Args&&... args)
//	{
//		//push_back(T(std::forward<Args>(args)...)); //더 확실한것
//		push_back(T(args...));
//	}
//
//	//내부 판단용 함수
//private:
//	bool isFull() { return _capacity == _size; }
//
//	//메모리 관련
//private:
//	size_t _capacity;			// 할당된 용량
//	size_t _size;				// 사용중인 사이즈
//	T* _tData;					// 데이터 배열
//
//	static const size_t Default_size = 1;
//};
////1번 생성자
//template<typename T>
//inline CMyVectorB<T>::CMyVectorB()
//{
//	_capacity = Default_size;
//	_size = 0;
//	_tData = new T[Default_size];
//}
//
////3번 생성자
//template<typename T>
//inline CMyVectorB<T>::CMyVectorB(size_t count, const T& value)
//{
//	_capacity = count;
//	_size = count;
//
//	_tData = new T[_capacity];
//
//	//수정 필요
//	for (size_t i = 0; i < _size; ++i)
//	{
//		_tData[i] = value;
//	}
//
//
//}
////4번 생성자
//template<typename T>
//inline CMyVectorB<T>::CMyVectorB(size_t count)
//{
//	_capacity = count;
//	_size = 0;
//	_tData = new T[_capacity];
//
//}
//
////5번 생성자
////template<typename T>
////inline CMyVectorB<T>::CMyVectorB(T first, T last)
////{
////	//보류
////}
//
////6번 생성자 - 복사 생성
//template<typename T>
//inline CMyVectorB<T>::CMyVectorB(const CMyVectorB& other)
//{
//	_capacity = other._capacity;
//	_size = other._size;
//
//	_tData = new T[_capacity];
//
//	for (size_t i = 0; i < _size; ++i)
//	{
//		_tData[i] = T(other._tData[i]);
//	}
//
//}
//
////8번 생성자 - 이동 생성
//template<typename T>
//inline CMyVectorB<T>::CMyVectorB(CMyVectorB&& other)
//{
//	_tData = new T[_capacity];
//
//	for (size_t i = 0; i < _size; ++i)
//	{
//		_tData[i] = T(other._tData[i]);
//	}
//
//	other.clear();
//	other._size = 0;
//
//}
////얘도 고쳐야 하구요
//template<typename T>
//inline CMyVectorB<T>::~CMyVectorB() noexcept
//{
//
//	if (_tData != nullptr)
//	{
//		for (size_t i = 0; i < _capacity; ++i)
//		{
//			_tData[i].~T();
//		}
//	}
//	delete[] _tData;
//	_tData = nullptr;
//}
//
//template<typename T>
//inline void CMyVectorB<T>::reserve(size_t new_cap)
//{
//	if (_capacity >= new_cap)
//	{
//		return;
//	}
//
//	T* newData = new T[new_cap];
//
//	for (size_t i = 0; i < _size; ++i)
//	{
//		newData[i] = T(_tData[i]);
//	}
//
//	delete[] _tData;
//
//	_tData = newData;
//
//	_capacity = new_cap;
//
//}
//
//template<typename T>
//inline void CMyVectorB<T>::shrink_to_fit()
//{
//	if (_capacity == _size)
//	{
//		return;
//	}
//
//	T* newData = new T[_size];
//
//	//newData = malloc(sizeof(T) * new_cap);
//	for (size_t i = 0; i < _size; ++i)
//	{
//		newData[i] = T(_tData[i]);
//	}
//
//	delete[] _tData;
//
//	_tData = newData;
//
//	_capacity = _size;
//
//}
////리사이즈 꼭 고쳐야하구요
//template<typename T>
//inline void CMyVectorB<T>::resize(size_t new_size)
//{
//	T* newData = new T[new_size];
//	size_t replace_size = new_size > _size ? _size : new_size;
//	for (size_t i = 0; i < replace_size; ++i)
//	{
//		newData[i] = std::move(_tData[i]);
//		_tData[i].~T();
//	}
//	delete[] _tData;
//	_tData = newData;
//	newData = nullptr;
//
//	_size = replace_size;
//	_capacity = new_size;
//
//}
//
//template<typename T>
//inline void CMyVectorB<T>::resize(size_t new_size, const T& value)
//{
//	T* newData = new T[new_size];
//
//	if (new_size > _size)
//	{
//		for (size_t i = 0; i < new_size; ++i)
//		{
//			if (i < _size)
//			{
//				//memmove(&newData[i], &_tData[i], sizeof(T));
//				newData[i] = std::move(_tData[i]);
//				_tData[i].~T();
//			}
//			else
//			{
//				//memmove(&newData[i], &value, sizeof(T));
//				newData[i] = value;
//			}
//		}
//	}
//	else
//	{
//		for (size_t i = 0; i < new_size; ++i)
//		{
//			newData[i] = std::move(_tData[i]);
//		}
//	}
//	delete[] _tData;
//	_tData = newData;
//
//	_size = new_size;
//	_capacity = new_size;
//}
//
//template<typename T>
//inline void CMyVectorB<T>::swap(CMyVectorB& other)
//{
//	T* temp = _tData;
//	_tData = other._tData;
//	other._tData = temp;
//
//	size_t tempSize = _size;
//	_size = other._size;
//	other._size = tempSize;
//
//	size_t tempCapacity = _capacity;
//	_capacity = other._capacity;
//	other._capacity = tempCapacity;
//
//	temp = nullptr;
//}
//
//template<typename T>
//inline void CMyVectorB<T>::clear() noexcept
//{
//	if (_tData != nullptr)
//	{
//		for (size_t i = 0; i < _size; ++i)
//		{
//			//_Destroy_range(&_tData[0], &_tData[_size]);  //써도되나 싶으면 물어보고 쓸것
//			_tData[i].~T();
//		}
//	}
//
//	_size = 0;
//}
//
//template<typename T>
//inline void CMyVectorB<T>::push_back(const T& value)
//{
//	if (_capacity == _size)
//	{
//		resize(_capacity * 2);
//		_capacity << 1;
//	}
//	_tData[_size] = value;
//	//memmove(&_tData[_size], &value, sizeof(T));
//	++_size;
//
//}
//
//template<typename T>
//inline void CMyVectorB<T>::push_back(T&& value)
//{
//	if (_capacity == _size)
//	{
//		resize(_capacity * 2);
//		_capacity << 1;
//	}
//
//	_tData[_size] = value;
//	++_size;
//}
//
//template<typename T>
//inline void CMyVectorB<T>::pop_back()
//{
//	if (empty())
//	{
//		return;
//	}
//	_tData[_size - 1] = T();
//
//	--_size;
//
//}
