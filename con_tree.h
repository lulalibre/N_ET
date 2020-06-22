#pragma once
#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<random>
#include"c_gene.h"



struct tuple
{
	std::uint32_t a, b;
	tuple(int a, int b) :a(a), b(b) {}
	tuple(c_gene in) :a(in.i_node), b(in.o_node) {}

};
inline bool operator< (const tuple& lhs, const tuple& rhs) {
	if (lhs.a < rhs.a) return true;
	else if (lhs.a == rhs.a) {
		if (lhs.b < rhs.b) return true;
		else return false;
	}
	return false;
}
inline bool operator> (const tuple& lhs, const tuple& rhs) {
	if (lhs.a > rhs.a) return true;
	else if (lhs.a == rhs.a) {
		if (lhs.b > rhs.b) return true;
		else return false;
	}
	return false;
}
inline bool operator==(const tuple& lhs, const tuple& rhs) {
	if ((lhs.a == rhs.a) && (lhs.b == rhs.b)) return true;
	else return false;
}




struct n_ode
{
	std::vector<n_ode>& repo;

	std::uint32_t smaller;
	std::uint32_t bigger;
	c_gene data;
	n_ode(c_gene d, std::vector<n_ode>& ns)
		:data(d), repo(ns), smaller(0), bigger(0) { }
	bool insert(c_gene in, std::uint32_t& pos) {
		if (data == in) return false;
		else {
			if (data > in) {
				if (smaller == 0) {
					n_ode newNode(in, repo);
					repo.push_back(newNode);
					smaller = repo.size() - 1;
					pos = smaller;
					return true;
				}
				else return repo.at(smaller).insert(in, pos);
			}
			else {
				if (bigger == 0) {
					n_ode newNode(in, repo);
					repo.push_back(newNode);
					bigger = repo.size() - 1;
					pos = bigger;
					return true;
				}
				else return repo[bigger].insert(in, pos);
			}
		}

	}
	c_gene& find(tuple query) {
		if (query == tuple(data)) {
			return data;
		}
		else if (query > tuple(data)) {
			if (bigger != 0) return repo[bigger].find(query);
			else {
				c_gene ret; return ret;
			}

		}
		else if (query < tuple(data)) {
			if (smaller != 0) return repo[smaller].find(query);
			else {
				c_gene ret; return ret;
			}
		}
	}
};


struct con_tree {
	std::vector<n_ode> nodes;
	std::uint32_t current_biggest_node;
	bool insert(c_gene in, std::uint32_t& pos) {
		if (nodes.size() == 0) {
			if (in.i_node > current_biggest_node) current_biggest_node = in.i_node;
			if (in.o_node > current_biggest_node) current_biggest_node = in.o_node;

			nodes.push_back(n_ode(in, nodes));
			pos = 0;
			return true;
		}
		else return nodes[0].insert(in, pos);
	}

	con_tree() {
		nodes.reserve(1000);
		current_biggest_node = 0;
	}

	c_gene& find(tuple query) {
		if (nodes.empty()) {
			c_gene ret; return ret;
		}
		else if (query == tuple(nodes[0].data)) {
			return nodes[0].data;
		}
		else if (query > tuple(nodes[0].data)) {
			if (nodes[0].bigger != 0)
				return nodes[nodes[0].bigger].find(query);
			else {
				c_gene ret; return ret;
			}
		}
		else if (query < tuple(nodes[0].data)) {
			if (nodes[0].smaller != 0)
				return nodes[nodes[0].smaller].find(query);
			else {
				c_gene ret; return ret;
			}
		}

	}
	std::uint32_t get_biggest_node() {
		return current_biggest_node;
	}

};
