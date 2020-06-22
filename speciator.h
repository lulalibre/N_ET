#pragma once
#include"genome.h"
#include<set>
struct species {
	
	std::default_random_engine rng;
	std::vector<genome> geno_types;
	std::uint32_t num_g_types;
	std::uint32_t max_g_types;
	std::set<std::uint32_t> the_selected;
	genome operator[](std::uint32_t in) { return geno_types[in]; }
	void procreate();
	bool speciate(genome* in);
	void multiply_mutate(std::uint32_t num);
	void kill_the_weak(std::uint32_t num);
	species(genome g_in);
	float speciation_threshold;

};

class speciator
{
	innovation_n& i_nov;
	std::vector<species> species_s;
	std::uint32_t num_species;
	void create_new_species();
};

