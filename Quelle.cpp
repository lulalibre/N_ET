#include"genome.h"
#include"n_t.h"


int main() {
	innovation_n i_n;
	genome g1(4, 2,i_n);
	genome g2(4, 2, i_n);

	g1.add_random_connection();
	g2.add_random_connection();
	
	
	genome g3(mate(g1, g2));

	

}