#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

class Vertical_sticks {
public:
    bool permute(std::vector<int>& data) {
        int k = data.size() - 2;
        while (data[k] >= data[k + 1]) {
            k--;
            if (k < 0) {
                return false;
            }
        }
        int l = data.size() - 1;
        while (data[k] >= data[l]) {
            l--;
        }
        swap(data, k, l);
        int length = data.size() - (k + 1);
        for (int i = 0; i < length / 2; i++) {
            swap(data, k + 1 + i, data.size() - i - 1);
        }
        return true;
    }

     void swap(std::vector<int>& data, int k, int l) {
        data[k] = data[k] + data[l];
        data[l] = data[k] - data[l];
        data[k] = data[k] - data[l];
    }

     double process(std::vector<int>& set) {
        std::sort( set.begin(), set.end());
        long v = 0, count = 0;
        do {
            v += perform(set);
            count++;
        } while (permute(set));
        double ret = (double) v / count;
        return ret;
    }

     size_t perform(std::vector<int>& intArray) {
        size_t len = intArray.size();
        size_t total_len = 0;
        for (int i = len - 1; i > 0; i--) {
            size_t ray_len = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (intArray[j] >= intArray[i]) {
                    break;
                }
                ray_len++;
            }
            total_len += ray_len;
        }
        return total_len + 1;
    }
};

int main ( int argc, char **argv) {
    size_t T;
    std::cin >> T;
    Vertical_sticks v_sticks;
    for (size_t i = 0; i < T; i++) {
        size_t N;
        std::cin >> N;
        std::vector<int> sticks;
        sticks.resize(N);
        for (size_t j = 0; j < N; j++) {
            std::cin >> sticks[j];
        }
        std::cout << std::fixed << std::setprecision(2) << v_sticks.process(sticks) << std::endl;
    }
}
