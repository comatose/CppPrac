#ifndef SORT_H
#define SORT_H

class printer : public unary_function<int, void>{
public:
	void operator()(int i){
		cout << i << ' ';
	}
};

template<class T>
T qpart(T begin, T end){
	T i = begin;
	T pivot = --end;
	while(i < end){
		if(*i < *pivot){
			swap(*i, *begin++);
		}
		++i;
	}
	swap(*begin, *pivot);
	return begin;
}

template<class T>
void nth(T begin, T n, T end){
	T pos = qpart(begin, end);
	if(pos == n)
		return;
	if(pos > n){
		nth(begin, n, pos);
	}
	else{
		nth(pos + 1, n, end);
	}
}

template<class T>
void quickSort(T begin, T end){
	if(begin >= end)
		return;

	T pivot = qpart(begin, end);
	quickSort(begin, pivot);
	quickSort(pivot + 1, end);
}

template<class T, class V>
T binarySearch(T begin, T end, V v){
	if(begin >= end)
		return end;
	T mid = begin + (end - begin) / 2;
	if(*mid == v){
		return mid;
	}
	else if(*mid < v){
		return binarySearch(mid + 1, end, v);
	}
	else if(*mid > v){
		T result = binarySearch(begin, mid , v);
		return (result == mid)?end:result;
	}
}

template <class T, class V>
T binarySearch2(T begin, T end, V v){
	T none = end;
	while(begin < end){
		T mid = begin + (end - begin) / 2;
		if(*mid == v)
			return mid;
		else if(*mid < v)
			begin = mid + 1;
		else if(v < *mid)
			end = mid;
	}
	return none;
}

template<class T>
void doPermute(vector<T>& prefix, vector<T>& postfix){
	if(postfix.size() == 1){
		ostream_iterator<T> out(cout, ", ");
		copy(prefix.begin(), prefix.end(), out);
		copy(postfix.begin(), postfix.end(), out);
		cout << endl;
	}
	for(int i = 0; i < postfix.size(); ++i){
		vector<T> temp = prefix;
		temp.push_back(postfix[i]);
		vector<T> temp2 = postfix;
		temp2.erase(temp2.begin() + i);
		doPermute(temp, temp2);
	}
}

template<class T>
void permute(T begin, T end){
	vector<typename T::value_type> prefix;
	vector<typename T::value_type> postfix(begin, end);
	doPermute(prefix, postfix);
}

template<class T>
static void doCombine(T begin, T end, vector<string>& s){
	if(begin >= end)
		return;
	--end;
	cout << *end << endl;
	int size = s.size();
	s.push_back(string(1, *end));
	for(int i = 0; i < size; ++i){
		cout << *end << s[i] << endl;
		string str(1, *end);
		str.append(s[i]);
		s.push_back(str);
	}
	doCombine(begin, end, s);
}

template<class T>
void combine(T begin, T end){
	vector<string> s;
	doCombine(begin, end, s);
}

inline void testSort(){
	vector<T> ary(11);
	generate(ary.begin(), ary.end(), rand);
	for(int i = 0; i < ary.size(); ++i)
		cout << ary[i] << ' ';
	cout << endl;
	quickSort(ary.begin(), ary.end());
	for(int i = 0; i < ary.size(); ++i)
		cout << ary[i] << ' ';
	cout << endl;
	typename vector<T>::iterator it = binarySearch2(ary.begin(), ary.end(), 29359);
	if(it == ary.end())
		cout << "No" << endl;
	else
		cout << *it << endl;

	string str = "wxyz";
	combine(str.begin(), str.end());
}

#endif
