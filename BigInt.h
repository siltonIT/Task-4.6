#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <utility>

#define size_t unsigned int 

class BigInt {
	friend std::ostream& operator<<(std::ostream&, const BigInt&);

	friend std::istream& operator>>(std::istream&, BigInt&);

	friend BigInt operator+(BigInt, const BigInt&);

	friend BigInt operator*(const BigInt&, const BigInt&);

public:
	BigInt();

	BigInt(size_t);

	BigInt(const BigInt&);

	BigInt& operator=(BigInt);

	BigInt(BigInt&&) noexcept;

	BigInt& operator=(BigInt&&) noexcept;

	void swap(BigInt&) noexcept;

	~BigInt();

	void operator+=(const BigInt&);

	void operator*=(const BigInt&); 

	int operator[](const size_t&);

	void set_amount_digits(size_t);

private:
	//для перехода в сторичную сиситему изменить на 100
	//стоит 10 так как ндао вычислисть 100 факториал в десятичной
	static const size_t _BASE = 10;
	size_t _amount_digits;
	
	int* _digits;
};
