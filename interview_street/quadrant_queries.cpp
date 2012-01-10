#include <iostream>
#include <vector>
#include <string>

int main ( int argc, char **argv) {
    int N;
    std::cin >> N;
    std::vector<std::vector<int> > points(N,std::vector<int>(2));
    for(int i=0; i< N; i++) {
        std::cin >> points[i][0];
        std::cin >> points[i][1];
    }
    int Q; std::cin >> Q;
    for(int i = 0; i < Q; i++) {
        std::string q; std::cin >> q;
        int min; std::cin >> min;
        int max; std::cin >> max;
        if(q == "C") {
            int k1 = 0, k2 = 0, k3 = 0, k4 = 0;
            for(int j = min - 1; j < max; j++) {
                if(points[j][0] > 0) {
                    if(points[j][1] > 0) k1++;
                    else k4++;
                } else {
                    if(points[j][1] > 0) k2++;
                    else k3++;
                }
            }
            std::cout << k1  << " "  << k2  << " "  << k3  << " "  << k4 << std::endl;
        } else if(q == "X" ){
            for(int j= min - 1; j < max; j++) {
                points[j][1] = -points[j][1];
            }
        } else {
            for(int j = min - 1; j < max; j++) {
                points[j][0] = -points[j][0];
            }
        }
    }
}