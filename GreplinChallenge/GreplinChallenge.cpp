#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

typedef std::vector<int> IntVector;
typedef IntVector::iterator IntVectorItr;


class GreplineChallenge1{
private:
	std::string getPalindromeAt(int position, std::string str) {
		int max_lower = 0, max_upper = 0, len = str.length();
		int lower, upper = position + 1;
		for(int j = 0; j < 2; j++) {
			lower = position - j;
			for(;lower >= 0 && upper < len && str[lower] == str[upper]; upper++, lower--){};
			if((max_upper - max_lower) < (upper - lower - 2)) {
				max_lower = lower + 1, max_upper = upper - 1;
			}
		}
		return str.substr(max_lower, max_upper - max_lower + 1);
	}
	std::string findLongestPalindrome(std::string str) {
		std::string max = "";
		for(int i = 0; i < str.length(); i++) {
			std::string palindrome = getPalindromeAt(i, str);
			if(palindrome.length() > max.length()) {
				max = palindrome;
			}
		}
		return max;
	}
public:
	void solve() {
		std::string password1 = findLongestPalindrome("roughtforthonthiscontainentanewnationconceivedinzLibertyanddedicatedtothepropositionthatallmenarecreatedequalNowweareengagedinagreahtcivilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth") ;
		std::cout << password1 << std::endl;
	}
};
class GreplineChallenge2{
public:
	GreplineChallenge2(){
		m_solution = 0;
	}
	int m_solution ;
private:
	bool isPrime(int number) {
      if (number == 1)     return false;
      if (number == 2)     return true;
      if (number % 2 == 0) return false;
      for (int d = 3; d <= (int)sqrt((double)number); d++)
            if (number % d == 0)
                  return false;
      return true;
	}
	void find_primeFactors(int x){
		int i = 3, r = x;
		while (!(r & 1)) {
			m_solution += 2;
			r >>= 1;
		}
		while (i <= (sqrt((double)r)+1)) {
			if ((r % i) == 0) {
				m_solution += i;
				r/=i;
			}
			else {
				i+=2;
			}
		}
		if (r > 1){
			m_solution += r;
		}
	}
public:
	void solve() {
		std::vector <int> fib;
		fib.push_back(0);
		fib.push_back(1); 
		int result = 0;
		int i = 2;
		while ( result <= 227000 ) {
			result = fib[i-1] + fib[i-2];
			i++;
			fib.push_back(result);
		}
		while (1) {
			result = fib[i-1] + fib[i-2];
			fib.push_back(result);
			bool flag = isPrime ( result );
			if ( flag == true ) {
				break;
			}
			i++;
		}
		find_primeFactors(result + 1 );
		std::cout << m_solution << std::endl;
	}
};
class GreplineChallenge3 {
public:
	GreplineChallenge3() {
		m_solution = 0;
	}
private:
	int m_solution;
	void subset_sum_r(IntVector& num_vector, int target, IntVector& partial) {
		int sum = 0;
		sum = sum + std::accumulate( partial.begin(), partial.end(), 0 );
		if ( sum == target ) {
			m_solution++;
		}
		if ( sum >= target ) {
			return;
		}
		for ( int i = 0 ; i < (int)num_vector.size(); i++) {
			IntVector remaining_vector;
			int n = num_vector[i];
			std::copy(num_vector.begin() + i + 1, num_vector.end(), std::back_inserter(remaining_vector));
			IntVector partial_rec(partial);
			partial_rec.push_back(n);

			subset_sum_r(remaining_vector,target,partial_rec);
		}
	}
	void subset_sum(IntVector& num_vector, int target) {
		IntVector partial;
		subset_sum_r(num_vector, target, partial);
	}
public:
	void solve() {
		int number[] = {3,4,9,14,15,19,28,37,47,50,54,56,59,61,70,73,78,81,92,95,97,99};
		int size = sizeof(number)/sizeof(number[0]);
		int	j = 1;
		for ( int i = size; i > 0; i--) {
			IntVector num_vector (number, number + size - j);
			subset_sum(num_vector, number[i-1]);	
			j++;
		}
		std::cout << m_solution << std::endl;
	}
};

int main ( int argc, char **argv ) {	
	GreplineChallenge1 gc1;
	GreplineChallenge2 gc2;
	GreplineChallenge3 gc3;

	gc1.solve();
	gc2.solve();
	gc3.solve();

	return 0;
}

