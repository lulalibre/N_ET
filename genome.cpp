#include "genome.h"

std::uint32_t genome::random_i_node() {
	std::uniform_int_distribution<std::uint32_t> dis_i(0, num_input+num_hidden -1);
	std::uint32_t i_n = dis_i(rng);
	if (i_n > (num_input - 1)) i_n += num_output;
	return i_n;
}

bool genome::add_random_connection() {
	std::uniform_int_distribution<std::uint32_t> dis_o(num_input,num_input+num_hidden+num_output-1);
	std::uniform_real_distribution <float> dis_w(-1, 1);
	for (std::uint32_t i = 0; i < 4; i++) {
		bt::tuple hyp;
		do {
			hyp.a =random_i_node(); hyp.b = dis_o(rng);
		} while (hyp.a == hyp.b);
		if (tree.insert(hyp)) {
			c_gene newc(hyp.a, hyp.b, i_nov.get_i_num(), dis_w(rng));
			conns.push_back(newc);
			return true;
		}
	}
	return false;
}

void genome::add_random_node() {
	std::uniform_int_distribution<std::uint32_t> dis(0, conns.size()-1);
	std::uint32_t x = dis(rng);
	conns[x].is_expressed = false;
	
	std::uint32_t new_n_id = tree.biggest_node()+1;
	std::uint32_t old_in=conns[x].i_node;
	std::uint32_t old_out = conns[x].o_node;
	c_gene newc1(old_in,new_n_id,i_nov.get_i_num(),1), newc2(new_n_id,old_out,i_nov.get_i_num(),conns[x].weight);
	tree.insert(bt::tuple(newc1.i_node, newc1.o_node));
	tree.insert(bt::tuple(newc2.i_node, newc2.i_node));
	conns.push_back(newc1);
	conns.push_back(newc2);
	num_hidden++;
	
}
void genome::mutate_random_connection() {
	std::uniform_int_distribution<std::uint32_t> dis(0, conns.size());
	std::uint32_t x = dis(rng);
	std::uniform_real_distribution<float> dis_w(-0.2f, 0.2f);
	conns[x].weight += dis(rng);
}
genome::genome(innovation_n& i_n):num_input(3),num_output(2),num_hidden(0),i_nov(i_n) {
	rng.seed((unsigned int)time(NULL));
	performance = 0;
	
}
genome::genome(const genome& t):i_nov(t.i_nov){
	tree = t.tree;
	conns = t.conns;
	
	num_hidden = t.num_hidden;
	num_output = t.num_output;
	num_input = t.num_input;
	rng.seed((unsigned int)time(NULL));
	performance = t.performance;
	biggest_node = t.biggest_node;

}
void genome::operator=(const genome& t) {
	conns = t.conns;
	tree = t.tree;
	num_hidden = t.num_hidden;
	num_input = t.num_input;
	num_output = t.num_output;
	performance = t.performance;
	
	i_nov = t.i_nov;
	rng.seed((unsigned int)time(NULL));
}
bool genome::insert(c_gene in)
{
	return false;
}
genome::genome(std::uint32_t num_in, std::uint32_t num_out,innovation_n& i_n):
	i_nov(i_n),
	num_input(num_in),
	num_output(num_out),
	num_hidden(0),
	performance(0)
	{
	auto tp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	
		rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		

	}
genome::genome(std::vector<c_gene>& cs, std::uint32_t n_in, std::uint32_t n_out,innovation_n &i_n):
	i_nov(i_n),
	num_input(n_in),
	num_output(n_out),
	performance(0.f)
{
	rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	for (auto gene : cs) {
		tree.insert(bt::tuple(gene.i_node, gene.o_node));

	}

}

genome mate(const genome& uno, const genome& duo) {
	std::default_random_engine rng(time(NULL));
	std::bernoulli_distribution dis(0.5);
	auto it_uno = uno.conns.begin();
	auto it_duo = duo.conns.begin();
	std::vector<c_gene> child;
	std::vector<c_gene> uno_leftout;
	std::vector<c_gene> duo_leftout;

	for (;(it_uno!=uno.conns.end())&&(it_duo!=duo.conns.end());) {
		if ((*it_uno).innovation_n == (*it_duo).innovation_n) {

			if (it_uno == uno.conns.end() ) {
				while (it_duo != duo.conns.end()) {
					child.push_back(*it_duo);
					it_duo++;
				}
				break;
				
			}
			if (it_duo == duo.conns.end() ) {
				while (it_uno != uno.conns.end()) {
					child.push_back(*it_uno);
					it_uno++;
				}
				break;
			}
			if (dis(rng)) {
				child.push_back(*it_uno);
			}
			else child.push_back(*it_duo);
			it_uno++; it_duo++;
			continue;

		}
		if ((*it_uno).innovation_n > (*it_duo).innovation_n) {
			if (it_duo == duo.conns.end()) {
				while (it_uno != uno.conns.end()) {
					child.push_back(*it_uno);
					it_uno++;

				}
				break;
			}
			child.push_back(*it_duo);
			it_duo++;
			continue;

		}
		if ((*it_uno).innovation_n < (*it_duo).innovation_n) {
			if (it_uno == uno.conns.end()) {
				while (it_duo != duo.conns.end()) {
					child.push_back(*it_duo);
					it_duo++;
				}
				break;

			}
			child.push_back(*it_uno);
			it_uno++;
			continue;
		}



	}
	genome g_out(uno.i_nov);
	g_out.conns = child;
	g_out.num_input = uno.num_input;
	g_out.num_output = uno.num_output;
	
	g_out.performance = 0;
	g_out.rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	
	for (std::uint32_t i = 0; i < child.size(); i++) {
		g_out.tree.insert(bt::tuple(child[i].i_node, child[i].o_node));
	}

	g_out.biggest_node = g_out.tree.biggest_node();
	g_out.num_hidden = uno.num_hidden;

	return g_out;
}

float compute_d(const genome& uno, const genome& duo) {
	auto it_uno = uno.conns.begin();
	auto it_duo = duo.conns.begin();

	std::uint32_t excess = 0;
	std::uint32_t common = 0;

	for (;(it_uno!=uno.conns.end())&&(it_duo!=duo.conns.end());) {
		if ((*it_uno).innovation_n == (*it_duo).innovation_n) {
			common++;
			if (it_uno == uno.conns.end() - 1) {
				while (it_duo != duo.conns.end()) {
				it_duo++;
				}
				break;
							}
			if (it_duo == duo.conns.end() ) {
				while (it_uno != uno.conns.end()) {
				it_uno++;
				}
				break;
			}
			it_uno++; it_duo++;
			continue;
		}
		if ((*it_uno).innovation_n > (*it_duo).innovation_n) {
			if (it_duo == duo.conns.end()) {
				while (it_uno != uno.conns.end()) {
				it_uno++;
				}
				break;
			}
			it_duo++;
			continue;
		}
		if ((*it_uno).innovation_n < (*it_duo).innovation_n) {
			if (it_uno == uno.conns.end()) {
				while (it_duo != duo.conns.end()) {
				it_duo++;
				}
				break;
			}
			it_uno++;
			continue;
		}
	}
	return (float)common;
}

