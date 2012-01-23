#include <iostream>
#include <cmath>

bool isPrime(long long number) {
	if (number == 1L)
		return false;
	if (number == 2L)
		return true;
	if((number & 1) == 0)
		return false;
	for (long long  d = 3L; d <= (long long)sqrt((double)number); d += 2)
		if (number % d == 0)
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
		for ( register long long i = A; i <= B; ++i) {
			long long sum        = 0;
			long long sum_square = 0;
			for (register long long  n = i; n > 0; sum += n % 10, n /= 10) ;
			if ( isPrime(sum)) {
				for (register long long  n = i; n > 0; sum_square += (n % 10) * (n % 10), n /= 10) ;
				if ( isPrime(sum_square)){
					result++;
				}
			}
		}
		std::cout << result << std::endl;
	}
	return 0;
}