/*
 * Algorithm.h
 *
 *  Created on: May 6, 2010
 *      Author: comatose
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

#include <cmath>
#include <cstdlib>

template<class T>
void swap(T& v1, T& v2){
	T temp = v1;
	v1 = v2;
	v2 = temp;
}

template<class T1, class T2>
void copy(T1 begin1, T1 end1, T2 begin2){
	for(; begin1 != end1; ++begin1, ++begin2){
		*begin2 = *begin1;
	}
}

template<class T>
void randomShuffle(T begin, T end){
	for(; begin != end; ++begin){
		swap(*begin, *(begin + rand() % (end - begin)));
	}
}

template<class T>
void reverse(T begin, T end){
	--end;
	while(begin < end){
		std::swap(*begin++, *end--);
	}
}

template<class T>
void rotate(T begin, T end, int n){
	if(n > 0){
		::reverse(begin, end - n);
		::reverse(end - n, end);
		::reverse(begin, end);
	}
	if(n < 0){
		::reverse(begin - n, end);
		::reverse(begin, begin - n);
		::reverse(begin, end);
	}
}

template<class T>
void insertionSort(T begin, T end){
	for(T it1 = begin + 1; it1 != end; ++it1){
		for(T it2 = it1; it2 != begin && *it2 < *(it2 - 1); --it2){
			swap(*it2, *(it2 - 1));
		}
	}
}

template<class T>
void insertionSort2(T begin, T end){
	for(T it1 = begin + 1; it1 != end; ++it1){
		typename T::value_type value = *it1;
		T it2 = it1;
		for(; it2 != begin && value < *(it2 - 1); --it2){
			*it2 = *(it2 - 1);
		}
		*it2 = value;
	}
}

template<class T>
void insertionSort3(T begin, T end){
	for(T it1 = begin + 1; it1 != end; ++it1){
		T pos;
		for(pos = it1; pos != begin; --pos){
			if(*it1 > *(pos - 1))
				break;
		}
		::rotate(pos, it1 + 1, 1);
	}
}

template<class T>
T max(T begin, T end){
	T pos = begin;
	for(; begin != end; ++begin){
		if(*pos < *begin)
			pos = begin;
	}
	return pos;
}

template<class T>
T min(T begin, T end){
	T pos = begin;
	for(; begin != end; ++begin){
		if(*pos > *begin)
			pos = begin;
	}
	return pos;
}

template<class T>
void bubbleSort(T begin, T end){
	for(; begin != end; ++begin){
		std::swap(*begin, *::min(begin, end));
	}
}

template<class T>
typename T::value_type maxSubSum(T begin, T end){
	typeof(*begin) sum = *begin, maxSum = *begin;
	for(T it = begin + 1; it != end; ++it){
		sum += *it;
		if(sum < 0)
			sum = 0;
		else{
			maxSum = (sum>maxSum)?sum:maxSum;
		}
	}
	return maxSum;
}

template<class T>
T partition(T begin, T end){
	--end;
	T it = begin;
	for(; it != end; ++it){
		if(*it < *end){
			swap(*it, *begin);
			begin++;
		}
	}
	swap(*begin, *end);
	return begin;
}

template<class T>
void quickSort(T begin, T end){
	if(begin >= end)
		return;
	T pivot = partition(begin, end);
	quickSort(begin, pivot);
	quickSort(pivot + 1, end);
}

template<class T>
void select(T begin, T end, T nth){
	T pivot = partition(begin, end);
	if(pivot < nth){
		select(pivot + 1, end, nth);
	}
	else if(pivot > nth){
		select(begin, pivot, nth);
	}
}

template<class T, class V>
T binarySearch(T begin, T end, const V& value){
	if(begin >= end)
		return end;
	T mid = begin + (end - begin) / 2;
	if(*mid == value)
		return mid;
	else if(*mid < value)
		return binarySearch(mid + 1, end, value);
	else{
		T pos = binarySearch(begin, mid, value);
		return pos == mid?end:pos;
	}
}


template<class T, class V>
T binarySearch2(T begin, T end, const V& value){
	T notfound = end;
	while(begin < end){
		T mid = begin + (end - begin) / 2;
		if(*mid == value)
			return mid;
		else if(*mid < value)
			begin = mid + 1;
		else
			end = mid;
	}
	return notfound;
}

template <class T>
int AtoI(T begin, T end){
	int result = 0;
	bool negative = false;
	if(*begin == '-'){
		begin++;
		negative = true;
	}
	for(; begin < end; ++begin){
		result *= 10;
		result += *begin - '0';
	}
	return negative?-result:result;
}

template <class T>
double AtoF(T begin, T end){
	bool negative = false;
	if(*begin == '-'){
		begin++;
		negative = true;
	}
	T dot = std::find(begin, end, '.');
	double result = AtoI(begin, dot) + AtoI(dot + 1, end) * pow(10, dot + 1 - end);
	return negative?-result:result;
}

std::string ItoA(int num){
	if(num == 0)
		return std::string();
	return ItoA(num / 10).append(1, '0' + num % 10);
}

typedef std::vector<std::string> vs;
vs permuteString(const std::string& str){
	vs result;
	if(str.empty()){
		result.push_back("");
		return result;
	}
	for(unsigned int i = 0; i < str.size(); ++i){
		std::string substr = str;
		vs subresult = permuteString(substr.erase(i, 1));
		for(vs::iterator it2 = subresult.begin(); it2 != subresult.end(); ++it2){
			result.push_back(it2->insert(0, 1, str[i]));
		}
	}
	return result;
}

inline void testString(){
	std::string str1 = "123.213";
	std::string str2 = "-123";
	std::cout << AtoF(str1.begin(), str1.end()) << ", " << AtoF(str2.begin(), str2.end()) << std::endl;
	std::cout << ItoA(135135) << std::endl;

	std::ostream_iterator<std::string> oit(std::cout, "\n");
	vs ps = permuteString("1234");
	std::cout << "size:" << ps.size() << std::endl;
	std::copy(ps.begin(), ps.end(), oit);
	std::cout << std::endl;
}

inline void testSort(){
	std::ostream_iterator<int> oit(std::cout, " ");

	std::vector<int> ary(20);
	for(int i = 0; i < 20; ++i){
		ary[i] = i - 10;
	}
	randomShuffle(ary.begin(), ary.end());
	std::copy(ary.begin(), ary.end(), oit);
	std::cout << std::endl;

	select(ary.begin(), ary.end(), ary.begin()+8);
	std::cout << *(ary.begin()+8) << std::endl;

	quickSort(ary.begin(), ary.end());
	std::copy(ary.begin(), ary.end(), oit);
	std::cout << std::endl;

	randomShuffle(ary.begin(), ary.end());
	std::copy(ary.begin(), ary.end(), oit);
	std::cout << std::endl;

	insertionSort3(ary.begin(), ary.end());
	std::cout << "Ins ";
	std::copy(ary.begin(), ary.end(), oit);
	std::cout << std::endl;

	for(std::vector<int>::iterator it = ary.begin(); it != ary.end(); ++it){
		std::cout << *binarySearch2(ary.begin(), ary.end(), *it) << ' ';
	}
	std::cout << std::endl;
	if(binarySearch2(ary.begin(), ary.end(), 100) == ary.end())
		std::cout << "PASS" << std::endl;
	if(binarySearch2(ary.begin(), ary.end(), -100) == ary.end())
		std::cout << "PASS" << std::endl;
	std::cout << maxSubSum(ary.begin(), ary.end()) << std::endl;

	::reverse(ary.begin(), ary.end());
	std::cout << "Reverse ";
	std::copy(ary.begin(), ary.end(), oit);
	std::cout << std::endl;

	::rotate(ary.begin(), ary.end(), -5);
	std::cout << "Rotate-5 ";
	std::copy(ary.begin(), ary.end(), oit);
	std::cout << std::endl;
}

#endif /* ALGORITHM_H_ */
