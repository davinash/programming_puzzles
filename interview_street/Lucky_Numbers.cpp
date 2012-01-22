#include <iostream>
#include <string>
#include <numeric>
/* trying with brute force approach */
long long sum_of_digits(long long input) {
	long long total = 0;
	while (input != 0) {
		total += input % 10;
		input /= 10;
	}
	return total;
}
long long sum_of_square_digits(long long input) {
	long long total = 0;
	while (input != 0) {
		total += (input % 10)* (input % 10);
		input /= 10;
	}
	return total;
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
			long long sum        = sum_of_digits( i );
			long long sum_square = sum_of_square_digits( i );
			if ( isPrime(sum) && isPrime(sum_square)){
				result++;
			}
		}
		std::cout << result << std::endl;
	}
	return 0;
}