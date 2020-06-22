#pragma once
#include<vector>



struct c_gene
{
	std::uint32_t i_node, o_node;
	float weight;
	std::uint32_t innovation_n;
	bool is_expressed;
	c_gene(std::uint32_t in, std::uint32_t on, std::uint32_t inno, float w)
		:i_node(in), o_node(on), innovation_n(inno), weight(w)
	{

		is_expressed = true;

	}
	c_gene() :i_node(0), o_node(0), innovation_n(0), weight(0), is_expressed(false) {}
};



inline bool operator< (const c_gene& lhs, const c_gene& rhs) {
	if (lhs.i_node < rhs.o_node) return true;
	else if (lhs.i_node == rhs.o_node) {
		if (lhs.o_node < rhs.o_node) return true;
		else return false;
	}
	return false;
}
inline bool operator> (const c_gene& lhs, const c_gene& rhs) {
	if (lhs.i_node > rhs.o_node) return true;
	else if (lhs.i_node == rhs.o_node) {
		if (lhs.o_node > rhs.o_node) return true;
		else return false;
	}
	return false;
}
inline bool operator==(const c_gene& lhs, const c_gene& rhs) {
	if ((lhs.o_node == rhs.o_node) && (lhs.i_node == rhs.i_node)) return true;
	else return false;
}


