#include <iostream>
#include <cmath>
#define COMMONDENOM(op) (((this->numerator_) * (f2.denominator_)) op ((f2.numerator_) * (this->denominator_))), ((this->denominator_) * (f2.denominator_))

class ZeroDenom : std::exception {
public:
	const char* what() const override {
		return "Знаменатель не должен быть равен 0!";
	}
};

class Fraction
{
private:
	int numerator_{};
	int denominator_{};

public:

	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}

	int GetNum() {
		return numerator_;
	}

	int GetDenom() {
		return denominator_;
	}

	Fraction Euclid() {
		Fraction gcd(abs(this->numerator_),abs(this->denominator_));
		if (gcd.numerator_ == gcd.denominator_) {
			return Fraction(1, 1);
		}
		else if (gcd.numerator_ == 0) {
			return Fraction(0, 0);
		}
		else {
			while (gcd.numerator_ != gcd.denominator_) {
				if (gcd.numerator_ > gcd.denominator_) {
					gcd.numerator_ -= gcd.denominator_;
				}
				else {
					gcd.denominator_ -= gcd.numerator_;
				}
			}
			return Fraction((this->numerator_ / gcd.numerator_), (this->denominator_ / gcd.denominator_));
		}
	}

	Fraction operator+(Fraction f2) {
		Fraction temp(COMMONDENOM(+));
		return temp.Euclid();
	}

	Fraction operator-(Fraction f2) {
		Fraction temp(COMMONDENOM(-));
		return temp.Euclid();
	}

	Fraction operator*(Fraction f2) {
		Fraction temp((this->numerator_ * f2.numerator_), this->denominator_ * f2.denominator_);
		return temp.Euclid();
	}

	Fraction operator/(Fraction f2) {
		if (f2.numerator_ == 0) {
			throw ZeroDenom();
		}
		int temp{};
		temp = f2.numerator_;
		f2.numerator_ = f2.denominator_;
		f2.denominator_ = temp;
		return (*this * f2).Euclid();
	}

	Fraction operator-(int sub) {
		return Fraction(this->numerator_ - this->denominator_ * sub, this->denominator_);
	}

	Fraction operator--() {
		*this = *this - 1;
		return *this;
	}

	Fraction& operator--(int) {
		Fraction oldF(*this);
		*this = --(*this);
		return oldF;
	}

	Fraction operator-() {
		return Fraction(-(this->numerator_), -(this->denominator_));
	}

	Fraction operator+(int add) {
		return Fraction(this->numerator_ + this->denominator_ * add, this->denominator_);
	}

	Fraction operator++() {
		*this = *this + 1;
		return *this;
	}

	Fraction& operator++(int) {
		Fraction oldF(*this);
		*this = ++(*this);
		return oldF;
	}

	friend std::ostream& operator<<(std::ostream& out, Fraction);
	friend Fraction operator-(int, Fraction);
	friend Fraction operator+(int, Fraction);
};

std::ostream& operator<<(std::ostream& out, Fraction f) {
	if (f.numerator_ == 0) {
		out << 0;
		return out;
	}
	else if (f.numerator_ == f.denominator_) {
		out << 1;
		return out;
	}
	else {
		out << f.numerator_ << "/" << f.denominator_;
		return out;
	}
}

Fraction operator-(int sub, Fraction f) {
	return Fraction(f.denominator_ * sub - f.numerator_, f.denominator_);
}

Fraction operator+(int add, Fraction f) {
	return Fraction(f.denominator_ * add + f.numerator_, f.denominator_);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Введите числитель дроби 1: ";
	int numerator{};
	std::cin >> numerator;
	int denominator{};
	do {
		try {
			std::cout << "Введите знаменатель дроби 1: ";
			std::cin >> denominator;
			if (denominator == 0) {
				throw ZeroDenom();
			}
		}
		catch (ZeroDenom er) { std::cout << er.what() << std::endl; }
	} while (denominator == 0);
	Fraction f1(numerator, denominator);
	std::cout << "Введите числитель дроби 2: ";
	std::cin >> numerator;
	do {
		try {
			std::cout << "Введите знаменатель дроби 2: ";
			std::cin >> denominator;
			if (denominator == 0) {
				throw ZeroDenom();
			}
		}
		catch (ZeroDenom er) { std::cout << er.what() << std::endl; }
	} while (denominator == 0);
	Fraction f2(numerator, denominator);
	std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;
	std::cout << f1 << " - " << f2 << " = " << f1 - f2 << std::endl;
	std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl;
	try {
		std::cout << f1 << " / " << f2 << " = " << f1 / f2 << std::endl;
	}
	catch (ZeroDenom er) { std::cout << er.what() << std::endl; }
	std::cout << "Вычитание целого числа из дроби и дроби из целого числа" << std::endl << "Введите целое число: ";
	int sub{};
	std::cin >> sub;
	std::cout << f1 << " - " << sub << " = " << f1 - sub << std::endl;
	std::cout << f2 << " - " << sub << " = " << f2 - sub << std::endl;
	std::cout << sub << " - " << f1 << " = " << sub - f1 << std::endl;
	std::cout << sub << " - " << f2 << " = " << sub - f2 << std::endl;
	std::cout << "Сложение целого числа и дроби" << std::endl;
	std::cout << f1 << " + " << sub << " = " << f1 + sub << std::endl;
	std::cout << f2 << " + " << sub << " = " << f2 + sub << std::endl;
	std::cout << sub << " + " << f1 << " = " << sub + f1 << std::endl;
	std::cout << sub << " + " << f2 << " = " << sub + f2 << std::endl;
	std::cout << "Инкремент постфиксный и префиксный" << std::endl;
	std::cout << "++" << f1 << " = " << ++f1 << std::endl;
	std::cout << "++" << f2 << " = " << ++f2 << std::endl;
	std::cout << f1 << "++ = " << f1++ << ". f1 = " << f1 << std::endl;
	std::cout << f2 << "++ = " << f2++ << ". f2 = " << f2 << std::endl;
	std::cout << "Декремент  постфиксный и префиксный" << std::endl;
	std::cout << "--" << f1 << " = " << --f1 << std::endl;
	std::cout << "--" << f2 << " = " << --f2 << std::endl;
	std::cout << f1 << "-- = " << f1-- << ". f1 = " << f1 << std::endl;
	std::cout << f2 << "-- = " << f2-- << ". f2 = " << f2 << std::endl;
	std::cout << std::endl;
	std::cout << "++" << f1 << " * " << f2 << " = " << ++f1 * f2 << std::endl;
	std::cout << "Значение дроби 1 = " << f1 << "\n";
	std::cout << f1 << "-- * " << f2 << " = " << f1-- * f2 << std::endl;
	std::cout << "Значение дроби 1 = " << f1 << "\n";
}
