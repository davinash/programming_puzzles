/* * * * * * * * * * * * * * * * * * * * *
* Dedicated to the public domain *
* dongre.avinash@gmail.com *
* * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

typedef struct {
    long start, finish, weight;
} Interval;

Interval  *I;
long      *M;
long      *P;

#define MAX(x, y)  (((x) > (y)) ? (x) : (y))

int compare(const void * left, const void * right) {
	return (((Interval *)left)->finish - ((Interval *) right)->finish);
}

int IntervalSearch(int start, int high){
	if (high == -1) return -1;
	int low = 0;
	int best = -1;
	int mid;
	int finish;
	while (low <= high) {
		mid = (low + high) /2 ;
		finish = I[mid].finish;
		if (finish >= start) {
			high = mid-1;
		} else {
			best = mid;
			low = mid + 1;
		}
	}
	return best;
}

long Compute_Opt(long j) {
	if (j == 0)
		return 0;
	if (M[j] != -1l) {
		return M[j];
	}
	M[j] = MAX(I[j].weight + Compute_Opt(P[j]), Compute_Opt(j - 1));
	return M[j];
}

int main( int argc, char **argv) {
    if ( argc <= 1 ) {
        return 0;
    }
    std::ifstream dnaInput(argv[1]);
    if ( dnaInput.peek() == EOF ) {
        return 0;
    }
    int lenDnaStr;
    dnaInput >> lenDnaStr ;
    for(int index = 0; index <= std::ceil(((float)lenDnaStr)/80.0); index++) {
        dnaInput.ignore( lenDnaStr + 1, '\n');
    }
    int numOfIv = 0;
    dnaInput >> numOfIv;
    if ( numOfIv == 0 ) {
        return 0;
    }
	numOfIv = numOfIv + 1;

	I = (Interval *) malloc (sizeof(Interval) * numOfIv);
	M = (long *)malloc(sizeof(long) * numOfIv);
	P = (long *)malloc(sizeof(long) * numOfIv);

	Interval t;
	t.start     = 0;
	t.finish    = 0;
	t.weight    = 0;
	I[0] = t;
	
    for ( int index = 1; index < numOfIv; index++) {
        int start = 0, finish = 0, weight = 0;
        dnaInput >> start >> finish >> weight;
		Interval t;
		t.start     = start;
		t.finish    = finish;
		t.weight    = weight;
		I[index] = t;
	}
    dnaInput.close();
	qsort(I, numOfIv, sizeof(Interval), compare);
	int best;
	for (int index = 1; index < numOfIv; index++){
		M[index] = -1l; 
		best = IntervalSearch(I[index].start,index - 1);
		if (best != -1) {
			P[index] = best;
		} else {
			P[index] = 0;
		}
	}
	long res = Compute_Opt(numOfIv - 1);
	free ( P );
	free ( I );
	free ( M );
    std::cout << res << std::endl;
	return 0;
}
