#pragma once

template<class T>
class Vector {
private:
	T* _arr = nullptr;
	size_t _size = 0;
	size_t _capacity = 4;

public:
	Vector();
	Vector(size_t length);

	T* getData() const { return _arr; }
	size_t size() const { return _size; }
	size_t capacity() const { return _capacity; }

	void print() const;
	T& operator[](size_t index);
	T& operator()(size_t index);

	Vector<T>& push_back(const T value);
	Vector<T>& push_front(const T value);
	Vector<T>& pop_back();
	Vector<T>& pop_front();

	void delete_by_index(const size_t index);
	void insert_by_index(const size_t index, const T element);
	size_t find(const T element);
	size_t rfind(const T element);
	void sort(bool reverse);

	Vector<T> operator+(const Vector<T>& other);
	bool operator==(const Vector<T>& other);
	bool operator!=(const Vector<T>& other);

	T& front();
	T& back();
	T& at(size_t index);

	void clear();
	void resize(size_t newSize);
	bool empty() const;
	void replace(size_t pos, size_t count, const Vector<T>& other);
	void erase(size_t first, size_t last);

	template <class T>
	friend istream& operator>>(istream& in, Vector<T>& vec);

	template <class T>
	friend ostream& operator<<(ostream& print, const Vector<T>& vec);
	
	~Vector();
};

template <class T>
istream& operator>>(istream& in, Vector<T>& vec) {
	size_t length;
	in >> length;
	vec = Vector<T>(length);
	for (size_t i = 0; i < length; i++)
		in >> vec._arr[i];
	vec._size = length;
	return in;
}

template <class T>
ostream& operator<<(ostream& print, const Vector<T>& vec) {
	for (size_t i = 0; i < vec._size; i++)
		print << vec._arr[i] << " ";
	return print;
}

template<class T>
Vector<T>::Vector() {
	this->_arr = new T[_capacity];
}

template<class T>
Vector<T>::Vector(size_t length) {
	while (_capacity <= length) {
		this->_capacity *= 2;
	}
	this->_arr = new T[_capacity];
}

template<class T>
void Vector<T>::print() const {
	for (size_t i = 0; i < _size; i++) {
		cout << this->_arr[i] << " ";
	}
	cout << endl;
}

template<class T>
T& Vector<T>::operator[](size_t index) {
	if (index >= 0 && index < _size) {
		return this->_arr[index];
	}
	assert(!"Index out of range!!");
}

template<class T>
T& Vector<T>::operator()(size_t index) {
	return (*this)[index];
}

template<class T>
Vector<T>& Vector<T>::push_back(const T value) {
	if (_size >= _capacity) {
		this->_capacity *= 2;

		T* temp = new T[_capacity];
		for (size_t i = 0; i < _size; i++) {
			temp[i] = this->_arr[i];
		}
		temp[_size] = value;
		this->_size++;

		delete[]_arr;
		this->_arr = temp;
	}
	else {
		this->_arr[_size] = value;
		this->_size++;
	}
	return *this;
}

template<class T>
Vector<T>& Vector<T>::push_front(const T value) {
	if (_size >= _capacity) {
		this->_capacity *= 2;

		T* temp = new T[_capacity];
		temp[0] = value;
		for (size_t i = 0; i < _size; i++) {
			temp[i + 1] = this->_arr[i];
		}
		this->_size++;
		delete[]_arr;
		this->_arr = temp;
	}
	else {
		T* temp = new T[_capacity];
		temp[0] = value;
		for (size_t i = 0; i < _size; i++) {
			temp[i + 1] = this->_arr[i];
		}
		this->_size++;
		delete[]_arr;
		this->_arr = temp;
	}
	return *this;
}

template<class T>
Vector<T>& Vector<T>::pop_back() {
	if (_size > 0)
		this->_size--;
	return*this;
}

template<class T>
Vector<T>& Vector<T>::pop_front() {
	if (_size > 0) {
		this->_size--;
		for (size_t i = 0; i < _size; i++)
			this->_arr[i] = this->_arr[i + 1];
	}
	return*this;
}

template<class T>
void Vector<T>::delete_by_index(const size_t index) {
	if (index >= 0 && index < _size) {
		this->_size--;
		for (size_t i = index; i < _size; i++)
			this->_arr[i] = this->_arr[i + 1];

		T* temp = new T[_capacity];
		for (size_t i = 0; i < _size; i++)
			temp[i] = this->_arr[i];
		delete[] _arr;
		this->_arr = temp;
	}
}

template<class T>
void Vector<T>::insert_by_index(const size_t index, const T element) {
	if (index >= 0 && index < _size) {
		size_t new_size = _size + 1;
		if (new_size >= _capacity) {
			this->_capacity *= 2;
			T* temp = new T[_capacity];

			for (size_t i = 0; i < index; ++i)
				temp[i] = this->_arr[i];
			temp[index] = element;
			for (size_t i = index + 1; i < new_size; i++)
				temp[i] = this->_arr[i - 1];

			delete[] this->_arr;
			this->_arr = temp;
			this->_size = new_size;
		}
		else {
			T* temp = new T[_capacity];

			for (size_t i = 0; i < index; ++i)
				temp[i] = this->_arr[i];
			temp[index] = element;
			for (size_t i = index + 1; i < new_size; i++)
				temp[i] = this->_arr[i - 1];

			delete[] this->_arr;
			this->_arr = temp;
			this->_size = new_size;
		}
		return;
	}
	assert(!"Index out of range!!");
}

template<class T>
size_t Vector<T>::find(const T element) {
	for (size_t i = 0; i < _size; i++) {
		if (_arr[i] == element)
			return i;
	}

	return -1;
}

template<class T>
size_t Vector<T>::rfind(const T element) {
	for (size_t i = _size - 1; i >= 0; i--) {
		if (_arr[i] == element)
			return i;
	}

	return -1;
}

template<class T>
void Vector<T>::sort(bool reverse) {
	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size - i - 1; j++) {
			if ((!reverse && _arr[j] > _arr[j + 1]) || (reverse && _arr[j] < _arr[j + 1])) {
				int temp = _arr[j];
				_arr[j] = _arr[j + 1];
				_arr[j + 1] = temp;
			}
		}
	}
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) {
	Vector<T> result;
	result._size = _size + other._size;
	while (result._size >= result._capacity) {
		result._capacity = _capacity * 2;
	}
	result._arr = new T[result._capacity];

	for (size_t i = 0; i < _size; i++)
		result._arr[i] = _arr[i];

	for (size_t i = 0; i < other._size; i++)
		result._arr[_size + i] = other._arr[i];

	return result;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& other) {
	if (_size != other._size)
		return false;

	for (size_t i = 0; i < _size; ++i) {
		if (_arr[i] != other._arr[i])
			return false;
	}

	return true;
}

template<class T>
bool Vector<T>::operator!=(const Vector<T>& other) {
	return !(*this == other);
}

template<class T>
T& Vector<T>::front() {
	if (_size > 0) {
		return this->_arr[0];
	}
	assert(!"Vector is empty!!");
}

template<class T>
T& Vector<T>::back() {
	if (_size > 0) {
		return this->_arr[_size - 1];
	}
	assert(!"Vector is empty!!");
}

template<class T>
T& Vector<T>::at(size_t index) {
	if (index >= 0 && index < _size) {
		return this->_arr[index];
	}
	assert(!"Index out of range!!");
}

template<class T>
void Vector<T>::clear() {
	delete[] _arr;
	_arr = nullptr;
	_size = 0;
	_capacity = 0;
}

template<class T>
void Vector<T>::resize(size_t newSize) {
	if (newSize <= _size) {
		_size = newSize;
	}
	else {
		if (newSize >= _capacity) {
			while (_capacity <= newSize) {
				_capacity *= 2;
			}
			T* temp = new T[_capacity];
			for (size_t i = 0; i < _size; i++) {
				temp[i] = _arr[i];
			}
			delete[] _arr;
			_arr = temp;
		}
		for (size_t i = _size; i < newSize; i++) {
			_arr[i] = T();
		}
		_size = newSize;
	}
}

template<class T>
bool Vector<T>::empty() const {
	return _size == 0;
}

template<class T>
void Vector<T>::replace(size_t pos, size_t count, const Vector<T>& other) {
	if (pos > _size) {
		assert(!"Invalid position for replace!");
	}
	if (pos + count > _size) {
		count = _size - pos;
	}
	for (size_t i = pos; i < pos + count; i++) {
		_arr[i] = other._arr[i - pos];
	}
}

template<class T>
void Vector<T>::erase(size_t first, size_t last) {
	if (first >= _size) {
		assert(!"Invalid position for erase!");
	}
	if (last >= _size) {
		last = _size - 1;
	}
	size_t count = last - first + 1;
	for (size_t i = first; i <= last; i++) {
		_arr[i] = _arr[i + count];
	}
	_size -= count;
}

template<class T>
Vector<T>::~Vector() {
	delete[] _arr;
}