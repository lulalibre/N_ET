#include "speciator.h"

void species::procreate() {
	the_selected.clear();
	
	
	
}

species::species(genome g_in) {
	rng.seed((unsigned int)time(NULL));
}
void species::multiply_mutate(std::uint32_t num) {
	num_g_types = geno_types.size();
	if ((num_g_types + num) > max_g_types) {
		kill_the_weak((num + num_g_types) - max_g_types);
	}
	std::uniform_int_distribution<std::uint32_t> dis(0, num_g_types - 1);
	for (std::uint32_t i = 0; i < num; i++) {
		genome g(geno_types[dis(rng)]);
		if (!g.add_random_connection()) {
			g.add_random_node();
			g.add_random_connection();
		}
		g.mutate_random_connection();
		
		geno_types.push_back(g);
	}

}

bool species::speciate(genome* in) {
	float biggest_so_far = 0;
	std::uint32_t the_one=0;
	for (std::uint32_t i = 0; i < geno_types.size(); i++) {
		float otherness = 0;
		genome g_test = geno_types[i];
		for (std::uint32_t j = 0;j < geno_types.size(); j++) {
			if (j == i) continue;
			else {
				otherness += compute_d(g_test, geno_types[j]);
			}
		}
		float val = float(otherness / (float)geno_types.size());
		if (val > biggest_so_far) {

			biggest_so_far = val;
			the_one = i;
		}
	}
	genome ret = geno_types[the_one];
	if (biggest_so_far > speciation_threshold) {
		
		geno_types.erase(geno_types.begin() + the_one);
		*in = ret;
		return true;
	}
	else {
		in = NULL;
		return false;
	}
}

void speciator::create_new_species() {
	num_species = species_s.size();
	for (std::uint32_t i = 0; i < num_species; i++) {
		genome g(i_nov);
		if (species_s[i].speciate(&g)) {
			species_s.push_back(species(g));
			species_s[species_s.size() - 1].multiply_mutate(10);
		}
	}
	num_species = species_s.size();
}