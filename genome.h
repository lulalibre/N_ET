#pragma once
#include<vector>
#include"c_gene.h"
#include<random>
#include"tree.h"
#include<ctime>
#include<chrono>

struct n_gene {
	enum class type
	{
		input, output,hidden
	};
	type t;
	n_gene(n_gene::type t):t(t){}
	n_gene():t(n_gene::type::hidden){}

};

class innovation_n {
	 std::uint32_t num;
public:
	innovation_n() { num = 0; }
	std::uint32_t get_i_num() {
		num++;
		return num;
	}
};

struct genome
{
	bt::tree tree;
	innovation_n& i_nov;
	float performance;
	std::default_random_engine rng;
	std::uint32_t num_input;
	std::int32_t num_output;
	std::int32_t num_hidden;
	std::uint32_t biggest_node;

	std::vector<c_gene> conns;
	

	bool add_random_connection();
	void add_random_node();
	void mutate_random_connection();
	std::uint32_t random_i_node();
	genome(innovation_n& i_n);
	genome(std::uint32_t num_in, std::uint32_t num_out,innovation_n& i_n);
	genome(std::vector<c_gene>& cs, std::uint32_t n_in, std::uint32_t n_out,innovation_n& i_n);
	
	genome(const genome& t);
	void operator= (const genome& t);
	bool insert(c_gene in);
	
};
genome mate(const genome& uno, const genome& duo);
float compute_d(const genome& uno, const genome& duo);
