#include <iostream>
#include <string>
#include <numeric>
/* trying with brute force approach */
void sum_of_digits_and_square(long long input, long long& sum, long long& sum_square) {
	sum = sum_square = 0L;
	while (input != 0L) {
		long long digit = input % 10L;
		sum        += digit;
		sum_square += digit * digit;
		input /= 10L;
	}	
}
bool isPrime(long long x) {
	long long max = static_cast <long long> (x);
	if (x <= 0 || x == 1 || (x % 2 == 0 && x != 2)) return false;
	for (long long i = 3; i < max; i += 2)
		if (x % i == 0)
			return false;
	return true;
}
int main ( int argc, char** argv) {
	int T;
	std::cin >> T;

	while ( T-- ) {
		int result = 0;
		long long A;
		long long B;
		std::cin >> A >> B;
		for ( long long i = A; i <= B; i++) {
			long long sum        = 0;
			long long sum_square = 0;
			sum_of_digits_and_square(i,sum,sum_square);
			if ( isPrime(sum)) {
				if ( isPrime(sum_square)){
					result++;
				}
			}
		}
		std::cout << result << std::endl;
	}
	return 0;
}