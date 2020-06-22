#include "n_t.h"
#include <cmath>

inline float transfer(float in) {
	return ((1.f / (1.f + expf(-in))) - 0.5f) * 2.f;
}

void node::connect_f() {
	
	for (std::uint32_t i = 0; i < outputs.size(); i++) {
		
		nodes[outputs[i]].num_activators++;
		if (nodes[outputs[i]].num_activators == nodes[outputs[i]].inputs.size()) {
			activation_order.push_back(outputs[i]);
			nodes[outputs[i]].connect_f();

		}
	}
}

n_t::n_t(genome in):num_input(in.num_input),num_output(in.num_output),num_hidden(in.num_hidden) {
	
	nodes.resize(in.num_hidden+in.num_input+in.num_output, node(nodes,activation_order));
	
	for (std::uint32_t i = 0; i < in.conns.size(); i++) {
		if (in.conns[i].is_expressed) {
			nodes[in.conns[i].o_node].inputs.push_back(in.conns[i].i_node);
			nodes[in.conns[i].o_node].i_ws.push_back(in.conns[i].weight);

			nodes[in.conns[i].i_node].outputs.push_back(in.conns[i].o_node);
			nodes[in.conns[i].i_node].o_ws.push_back(in.conns[i].weight);
		}

	}
	set_activationOrder_f();
	
}
void n_t::set_activationOrder_f() {
	activation_order.reserve( num_hidden);
	
	for (std::uint32_t i = 0; i < num_input; i++) {
		nodes[i].connect_f();
	}
}
	
	
std::vector<float> n_t::process_f(std::vector<float>& in) {
	for (std::uint32_t i = 0; i < num_input; i++) {
		nodes[i].output = transfer(in[i]);
	}
	for (std::uint32_t i = 0; i<activation_order.size(); i++) {
		float activation = 0;
		for (std::uint32_t j = 0; j < nodes[i].inputs.size(); j++) {
			nodes[i].activation += nodes[nodes[i].inputs[j]].output;
			
		}
		nodes[i].output = transfer(nodes[i].activation);
	}
	std::vector<float> ret;
	ret.reserve(num_output);
	for (std::uint32_t i = num_input; i < num_input+num_output; i++) {
		ret.push_back(nodes[i].output);
	}
	return ret;
}



