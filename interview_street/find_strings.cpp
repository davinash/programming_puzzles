#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>

char txt[2000], *p[2000];
int m, n;

std::vector<std::string> V;

int cmp(const void *p, const void *q) {
    int rc = memcmp(*(char **)p, *(char **)q, m);
    return rc;
}
void solve() {
    size_t Qi = 0;
    std::cin >> Qi;

    if ( V.size() < Qi - 1 ) {
        std::cout << "INVALID" << std::endl;
    } else {
        std::cout << V[Qi - 1] << std::endl;
    }
}

int main() {
    int N;
    std::cin >> N;
    int i;
    for ( int idx = 0; idx < N ; idx++) {
        m = 0; n = 0;
        std::cin >> txt;
        n = strlen(txt);
        int k;
        for (m = 1; m <= n; m++) {
            for (k = 0; k+m <= n; k++)
                p[k] = txt+k;
            qsort(p, k, sizeof(p[0]), &cmp);
            for (i = 0; i < k; i++) {
                if (i != 0 && cmp(&p[i-1], &p[i]) == 0){
                    continue;
                }
                char cur_txt[2000];
                memcpy(cur_txt, p[i],m);
                cur_txt[m] = '\0';
                V.push_back(cur_txt);
            }
        }
    }
    std::sort(V.begin(), V.end());
    V.erase(std::unique(V.begin(), V.end()), V.end());
    int q;
    std::cin >> q;
    for ( int i = 0; i < q; i++) {
        solve();
    }

    return 0;
}
