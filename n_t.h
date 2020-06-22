#pragma once
#include"genome.h"
#include<set>

inline float transfer(float in);




struct node {
	std::vector<node>& nodes;
	std::vector<std::uint32_t>& activation_order;
	std::vector<float> i_ws;
	std::vector<float> o_ws;
	std::vector < std::uint32_t> inputs;
	std::vector < std::uint32_t> outputs;
	
	float activation;
	float output;
	std::uint32_t num_activators;
	node(std::vector<node>& ns,std::vector<std::uint32_t>&ao):activation(0),output(0),
	num_activators(0),nodes(ns),activation_order(ao){}
	void connect_f();


};

class n_t
{
	std::uint32_t num_output;
	std::uint32_t num_input;
	std::uint32_t num_hidden;
	
	
	std::vector<node> nodes;
	std::vector<std::uint32_t> activation_order;
public:
	n_t(genome in);

	void set_activationOrder_f();
	void set_activationOrder_b();
	std::vector<float> process_f(std::vector<float>& in);
	
};

