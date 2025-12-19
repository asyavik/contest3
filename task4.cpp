#include <algorithm>
#include <iostream>
#include <numeric> 
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

#include <stdint.h>

class Ip {
public:
	int a;
	int b;
	int c;
	int d;
	Ip() : a(0), b(0), c(0), d(0) {}
	Ip(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}

	std::vector<Ip> Diap(const Ip& other) {
		Ip ip_1 = *this;
		Ip ip_2 = other;
		std::vector<Ip> result;
		uint32_t start = 256 * 256 * 256 * ip_1.a + 256 * 256 * ip_1.b + 256 * ip_1.c + ip_1.d;
		uint32_t end = 256 * 256 * 256 * ip_2.a + 256 * 256 * ip_2.b + 256 * ip_2.c + ip_2.d;
		if (start > end) {
			throw std::invalid_argument("Первое число должно быть меньше");
		}
		for (uint32_t i = start; i <= end; i++) {
			uint32_t n = i;
			int n_d = n % 256;
			n = n / 256;
			int n_c = n % 256;
			n = n / 256;
			int n_b = n % 256;
			n = n / 256;
			int n_a = n % 256;
			Ip new_ip = Ip(n_a, n_b, n_c, n_d);
			result.push_back(new_ip);
		}
		return result;
	}
};
std::istream& operator>>(std::istream& in, Ip& ip) {
	std::string new_ip;
	in >> new_ip;
	std::stringstream ss(new_ip);
	std::string part;

	int a, b, c, d;
	std::getline(ss, part, '.');
	a = std::stoi(part);
	std::getline(ss, part, '.');
	b = std::stoi(part);
	std::getline(ss, part, '.');
	c = std::stoi(part);
	std::getline(ss, part, '.');
	d = std::stoi(part);
	if (a >= 0 && a <= 255 &&
		b >= 0 && b <= 255 &&
		c >= 0 && c <= 255 &&
		d >= 0 && d <= 255) {
		ip.a = a;
		ip.b = b;
		ip.c = c;
		ip.d = d;
	}
	else {
		throw std::invalid_argument("Все числа должны быть в диапозоне от 0 до 255");
	}
	return in;
}
std::ostream& operator<<(std::ostream& os, const Ip& ip) {
	os << ip.a << "." << ip.b << "." << ip.c << "." << ip.d;
	return os;
}


int main() {
	Ip first, last;
	std::cin >> first >> last;

	std::vector<Ip> range = first.Diap(last);

	for (const auto& ip : range) {
		std::cout << ip << std::endl;
	}
	return 0;
}