#include "BigInt.h"

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
	bool is_number = false;
	for(int i = num._amount_digits - 1; i >= 0; --i) {
		if(num._digits[i] == 0 && !is_number)
			continue;

		is_number = true;
		os << num._digits[i];

	}
	return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
	char* new_num = new char[num._amount_digits];
	is >> new_num;
	
	size_t num_size = 0;
	while(new_num[num_size] != 0)
		++num_size;
	
	for(size_t i = 0; i < num._amount_digits; ++i)
		num._digits[i] = 0;

	for(size_t i = 0; i < num_size; ++i) 
		num._digits[num_size - i - 1] += new_num[i] - '0';
	
	delete[] new_num;
	return is;
}

BigInt operator+(BigInt res, const BigInt& num) {
	res += num;
	return res;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt res;
	
	for(size_t i = 0; i < a._amount_digits; ++i)
		for(size_t j = 0; j < a._amount_digits - i; ++j)
			res._digits[i + j] += a._digits[i] * b._digits[j];
	
	for(size_t i = 0; i < res._amount_digits - 1; ++i) {
		res._digits[i + 1] += res._digits[i] / res._BASE;
		res._digits[i] %= res._BASE;
	}

	return res;
}

BigInt::BigInt(): _amount_digits(100), _digits(new int[_amount_digits]) {
	for(size_t i = 0; i < _amount_digits; ++i)
		_digits[i] = 0;
}

BigInt::BigInt(size_t num): BigInt() {
	size_t next = 0;
	while(num) {
		_digits[next++] = num % _BASE;
		num /= _BASE;
	}

	_amount_digits = next;
}

BigInt::BigInt(const BigInt& other): _amount_digits(other._amount_digits), _digits(new int[_amount_digits]) {
	for(size_t i = 0; i < _amount_digits; ++i)
		_digits[i] = other._digits[i];
}

BigInt& BigInt::operator=(BigInt other) {
	swap(other);
	return *this;
}

BigInt::BigInt(BigInt&& other) noexcept : _amount_digits(other._amount_digits), _digits(other._digits) {
	other._digits = nullptr;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
	BigInt res(std::move(other));
	swap(res);

	return *this;
}

void BigInt::swap(BigInt& other) noexcept {
	std::swap(_amount_digits, other._amount_digits);
	std::swap(_digits, other._digits);
}

BigInt::~BigInt() {
	delete[] _digits;
}

void BigInt::operator+=(const BigInt& other) {
	for(size_t i = 0; i < _amount_digits; ++i)
		_digits[i] += other._digits[i];

	for(size_t i = 0; i < _amount_digits - 1; ++i) {
		_digits[i + 1] += _digits[i] / _BASE;
		_digits[i] %= _BASE;
	}
		
}

void BigInt::operator*=(const BigInt& other) {
	BigInt res = std::move(*this * other);
	*this = res;
}

int BigInt::operator[](const size_t& ind) {
	if(ind < 0 || ind >= _amount_digits)
		abort();

	return _digits[ind];
}

void BigInt::set_amount_digits(size_t amount) {
	_amount_digits = amount;
	delete[] _digits;
	_digits = new int[_amount_digits];
}
