#include <iostream>
#include <cassert>

using namespace std;

#include"Vector.h"

int main() {
	Vector<int> vec;
	vec.push_back(23);
	vec.push_back(12);
	vec.push_back(5);
	vec.push_front(78);
	vec.push_front(4);

	cout << vec << endl;
	cout << vec.front() << endl;
	cout << vec.back() << endl;
	cout << vec.at(3) << endl;
	//vec.clear();
	//cout << vec.empty() << endl;
	
	//vec.resize(3);
	//cout << vec << endl;

	//vec.erase(2, 4);
	//cout << vec << endl;

	Vector<int> vec2;
	vec2.push_back(12);
	vec2.push_back(32);
	vec2.push_back(21);
	vec2.push_back(8);
	cout << vec2 << endl;

	//vec.replace(1, 3, vec2);
	//cout << vec << endl;

	cout << (vec == vec2) << endl;
	cout << (vec != vec2) << endl;
	
	return 0;
}