#include "CMyVector.h"
#include <iostream>
#include <vector>
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


void DetectLeak(long goToLine = -1)
{
	//Also need this for memory leak code stuff
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(goToLine); //Important!
}

#endif // _DEBUG

using namespace std;

class TestType
{
public:
	TestType()
	{
		_a = 0;
		_b = 0;
		_c = 'a';
	}
	TestType(int a, int b, char c = 'a')
	{
		_a = a;
		_b = b;
		_c = c;
	}
	void print()
	{
		cout << "A:" << _a << " B :" << _b << " C :" << _c << endl;
	}

public:
	int _a;
	int _b;
	char _c;

};
/*
	T* newData = new T[new_size];
	size_t replace_size = new_size > _size ? _size : new_size;
	for (size_t i = 0; i < replace_size; ++i)
	{
		newData[i] = std::move(_tData[i]);
		_tData[i].~T();
	}
	delete[] _tData;
	_tData = newData;

	_size = replace_size;
	_capacity = new_size;

*/



int main()
{
	#ifdef _DEBUG
	DetectLeak();
	#endif // _DEBUG
	//_CrtSetBreakAlloc(188);


	CMyVector<std::string> mVstring;
	CMyVector<std::string> mVstringB;

	mVstring.push_back("abcd");
	mVstring.push_back("abcde");
	mVstring.push_back("abcdf");
	mVstring.push_back("abcdg");
	mVstring.push_back("abcdh");
	mVstringB.push_back("aaaa");
	//mVstring.insert(mVstring.begin(), "abcdefg");

	//mVstringB = std::move(mVstring);
	
	mVstring.clear();
	//cout << "size : " << mVstringB.size() << " cap : " << mVstringB.capacity() << endl;
	//for (size_t i = 0; i < mVstringB.size(); ++i)
	//{
	//	cout << mVstringB[i] << endl;
	//}

	//CMyVector<CMyVector<int>> mVMaster;
	//CMyVector<int> mVectorA;
	//CMyVector<int> mVectorB;
	//CMyVector<int> mVectorC;

	////mVMaster.reserve(8);

	//mVectorA.push_back(10);
	//mVectorA.push_back(20);
	//mVectorA.push_back(30);
	//mVectorA.push_back(40);

	//mVectorB.push_back(1);
	//mVectorB.push_back(2);
	//mVectorB.push_back(3);
	//mVectorB.push_back(4);
	//mVectorB.push_back(5);
	//mVectorB.push_back(6);
	//mVectorB.push_back(7);
	//mVectorB.push_back(8);

	//mVectorC.push_back(100);
	//mVectorC.push_back(200);
	//mVectorC.push_back(300);
	//mVectorC.push_back(400);
	//mVectorC.push_back(500);
	//mVectorC.push_back(600);
	//mVectorC.push_back(700);
	//mVectorC.push_back(800);
	//mVectorC.push_back(900);
	//mVectorC.push_back(1000);
	//mVectorC.push_back(1100);
	//mVectorC.push_back(1200);

	//mVectorC.clear();

	//mVMaster.push_back(mVectorA);
	//mVMaster.push_back(mVectorB);
	//mVMaster.push_back(mVectorC);
	//mVMaster.resize(5,mVectorC);

	//cout << mVMaster[0][0] << endl;
	//cout << mVMaster[1][1] << endl;
	//cout << mVMaster[2][10] << endl;
	//cout << mVMaster[4][10] << endl;
	//mVMaster[4][1] = 1;
	//cout << mVMaster[2][1] << endl;
	//cout << mVMaster[4][1] << endl;
	//mVMaster.resize(2);

	//CMyVector<TestType> mVector;
	//CMyVector<TestType> mVectorB;

	//cout << "size : " << mVector.size() << " cap : " << mVector.capacity() << endl;

	////mVector.reserve(12);

	//mVector.emplace_back(1, 1, 'a');
	//mVector.emplace_back(1, 2, 'b');
	//mVector.emplace_back(1, 3, 'c');
	//mVector.emplace_back(1, 4, 'd');

	//cout << "size : " << mVector.size() << " cap : " << mVector.capacity() << endl;
	//for (size_t i = 0; i < mVector.size(); ++i)
	//{
	//	mVector[i].print();
	//}
	//mVector.push_back(TestType(1,5,'e'));
	//cout << "size : " << mVector.size() << " cap : " << mVector.capacity() << endl;
	//for (size_t i = 0; i < mVector.size(); ++i)
	//{
	//	mVector[i].print();
	//}
	//mVectorB = mVector;

	//mVector.clear();

	//cout << "size : " << mVector.size() << " cap : " << mVector.capacity() << endl;
	//mVector.emplace_back(1, 2, 'b');
	//mVector.emplace_back(1, 3, 'c');
	//mVector.emplace_back(1, 4, 'd');
	//cout << "size : " << mVector.size() << " cap : " << mVector.capacity() << endl;
	//for (size_t i = 0; i < mVector.size(); ++i)
	//{
	//	mVector[i].print();
	//}
	//cout << "size : " << mVectorB.size() << " cap : " << mVectorB.capacity() << endl;
	//for (size_t i = 0; i < mVectorB.size(); ++i)
	//{
	//	mVectorB[i].print();
	//}

	return 0;
}

void regacyB(){
	CMyVector<int> mvector;
	CMyVector<int> mvectorB(size_t(10));
	//mvector.begin();

	mvector.push_back(11);
	mvector.push_back(12);

	cout << "size : " << mvector.size() << " cap : " << mvector.capacity() << endl;


	for (size_t i = 0; i < mvector.size(); ++i)
	{
		cout << mvector[i] << endl;
	}

	mvectorB.push_back(1);
	mvectorB.push_back(2);
	mvectorB.push_back(3);
	mvectorB.push_back(4);

	mvector = std::move(mvectorB);

	cout << "size : " << mvector.size() << " cap : " << mvector.capacity() << endl;
	for (size_t i = 0; i < mvector.size(); ++i)
	{
		cout << mvector[i] << endl;
	}

	cout << "size : " << mvectorB.size() << " cap : " << mvectorB.capacity() << endl;
	for (size_t i = 0; i < mvectorB.size(); ++i)
	{
		cout << mvectorB[i] << endl;
	}

}

void regacy()
{
	//CMyVector<TestType> tvector;
	//tvector.push_back(TestType(1, 2, 'a'));
	//tvector.push_back(TestType(1, 3, 'b'));
	//tvector.push_back(TestType(1, 4, 'd'));
	//tvector.emplace_back(1, 5, 'e');
	//
	//for (size_t i = 0; i < tvector.size(); ++i)
	//{
	//	tvector.at(i).print();
	//}

	//vector<int> testVector;
	//testVector.emplace_back(5);
	////testVector.push_back(1);
	////testVector.push_back(2);
	////testVector.push_back(3);
	////vector<int>::iterator testiter = testVector.begin();
	////++testiter;
	////cout << "tA" << *(testiter) << endl;
	////testiter = testVector.insert(testiter, 5);
	////cout << "tB" << *(testiter) << endl;
	//
	//mvector.reserve(5);

	//CMyVector<int>::iterator<int> iter = mvector.begin();
	////기본 사용
	//mvector.push_back(1);
	//mvector.push_back(2);
	//mvector.push_back(3);

	////삽입, 삭제
	//cout << *(++iter) << endl;
	//mvector.insert(iter, 5);
	//cout << *(iter) << endl;
	//mvector.emplace(iter, 22);
	//cout << *(iter) << endl;

	//cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	//for (int i = 0; i < mvector.size(); ++i)
	//{
	//	cout << mvector[i] << endl;
	//}

	//mvector.erase(++iter);

	//cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	//for (int i = 0; i < mvector.size(); ++i)
	//{
	//	cout << mvector[i] << endl;
	//}


	//////팝
	////mvector.pop_back();
	////for (int i = 0; i < mvector.size(); ++i)
	////{
	////	cout << mvector[i] << endl;
	////}
	////cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	////cout << "size : " << mvectorB.size() << " cap :" << mvectorB.capacity() << endl;


	//////스왑
	////mvector.swap(mvectorB);
	////cout << "mVector ::" << endl;
	////if (mvector.empty())
	////	cout << "mvector is empty!" << endl;
	////for (int i = 0; i < mvector.size(); ++i)
	////{
	////	cout << mvector[i] << endl;
	////}
	////cout << "mVectorB ::" << endl;
	////for (int i = 0; i < mvectorB.size(); ++i)
	////{
	////	cout << mvectorB[i] << endl;
	////}

	//////할당 사이즈 초과
	////mvector.push_back(11);
	////mvector.push_back(22);
	////mvector.push_back(33);
	////mvector.push_back(11);
	////mvector.push_back(22);
	////mvector.push_back(33);
	////mvector.push_back(11);
	////mvector.push_back(22);
	////mvector.push_back(33);
	////mvector.push_back(11);
	////mvector.push_back(22);
	////mvector.push_back(33);

	////for (int i = 0; i < mvector.size(); ++i)
	////{
	////	cout << mvector[i] << endl;
	////}
	////cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;


	////리사이즈 : 사이즈가 커지고 값을 넣을 경우
	//mvector.resize(12, 8);
	//cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	//for (int i = 0; i < mvector.size(); ++i)
	//{
	//	cout << mvector[i] << endl;
	//}
	////리사이즈 : 값이 작아질 경우
	//mvector.resize(4);
	//cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	//for (int i = 0; i < mvector.size(); ++i)
	//{
	//	cout << mvector[i] << endl;
	//}
	////리사이즈 : 커지기만 할 경우
	//mvector.resize(14);
	//cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	//for (int i = 0; i < mvector.size(); ++i)
	//{
	//	cout << mvector[i] << endl;
	//}
	////사이즈 최적화
	//mvector.shrink_to_fit();
	//cout << "size : " << mvector.size() << " cap :" << mvector.capacity() << endl;
	//return 0;
};