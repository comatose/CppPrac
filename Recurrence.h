#ifndef RECURRENCE_H_
#define RECURRENCE_H_

char getCharKey(int num, int place){
	static char table[8][4] = {"abc", "def", "ghi", "jkl", "mno", "prs", "tuv", "wxy"};
	return table[num - 2][place];
}

template<class T>
void doNTW(string prefix, T begin, T end){
	if(begin >= end){
		cout << prefix << endl;
		return;
	}

	if(*begin == 1 || *begin == 0){
		prefix.append(1, '0' + *begin);
		doNTW(prefix, begin + 1, end);
	}
	else{
		for(int i = 0; i < 3; ++i){
			string npx = prefix;
			npx.append(1, getCharKey(*begin, i));
			doNTW(npx, begin + 1, end);
		}
	}
}

template<class T>
void numToWords(T begin, T end){
	string pf("");
	doNTW(pf, begin, end);
}

#endif
