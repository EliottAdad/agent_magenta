/*
 * utils_Oct.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_OCT_HPP_

#define UTILS_OCT_HPP_

#include <memory>
#include "Oct.hpp"


template<typename U, typename T> std::string to_string(const Oct<U, T>& oct, const unsigned char& indent) {
	std::string mes="";
	
	mes+=to_stringTabs(indent);
	mes+="OCT[";
	std::stringstream ss;
	ss << &oct;
	mes+=ss.str();
	mes+="]:";
	
	mes+="[";
	mes+=to_string(oct.getA());								//a
	mes+=" | ";
	mes+=to_string(oct.getPoint());			//Point
	mes+=" | ";
	mes+=to_string(oct.getBarycenter());		//Barycenter
	mes+=" | ";
	std::stringstream ss2;
	ss2 << oct.getPU();						// m_pU
	mes+=ss2.str();
	mes+=" | ";
	mes+="w:" + to_string(oct.getTotWeight());
	mes+="]";
	
	mes+="\n";

	mes+=to_stringTabs(indent+1);
	mes+=(oct.BLBTree==NULL)?"NULL" : to_string(*oct.BLBTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.BRBTree==NULL)?"NULL" : to_string(*oct.BRBTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.BRFTree==NULL)?"NULL" : to_string(*oct.BRFTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.BLFTree==NULL)?"NULL" : to_string(*oct.BLFTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.TLBTree==NULL)?"NULL" : to_string(*oct.TLBTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.TRBTree==NULL)?"NULL" : to_string(*oct.TRBTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.TRFTree==NULL)?"NULL" : to_string(*oct.TRFTree, indent+1);
	
	mes+=to_stringTabs(indent+1);
	mes+=(oct.TLFTree==NULL)?"NULL" : to_string(*oct.TLFTree, indent+1);

	return mes;
}

template<typename U, typename T> void print(const Oct<U, T>& oct, const unsigned char& indent) {
	std::cout << to_string(oct, indent);
}


#endif /* FUNCTIONS_OCT_HPP_ */
