/*
 * SN.hpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SN_HPP_

#define SN_HPP_

//#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <math.h>
#include <string>

#include "../utilities/functions.hpp"


/**
 * ############
 *  SN<M, E> :)
 * ############
 * @brief
 * Scientific Number
 * It allows to store extremely big or 
 * small numbers under scientific notation.
 * Recommended usage : 	<float, char>
 * 						<double, char>
 * 						<double, int>
 * Overwritten for M, doubles and ints :
 * 		3.14 is by default double
 * 		2 is by default int
 */
template<typename M, typename E> struct SN {
	M m=0;						// Mantissa
	E e=0;						// Exponent

	SN();
	SN(M m, E e);
	SN(M nb);
	SN(const SN<M, E>& nb);

	void recal();												//:)

	M to_m_type() const;										//:)
	void operator=(const SN<M, E>& nb);							//:)
	void operator=(const M& nb);								//:)
	//void operator=(const int& nb);								//
	//void operator=(const double& nb);							//
	SN<M, E> operator++();										//X
	SN<M, E> operator++(int);									//X
	void operator+=(const SN<M, E>& nb);						//:)
	void operator+=(const M& nb);								//:)
	//void operator+=(const int& nb);								//
	//void operator+=(const double& nb);							//
	SN<M, E> operator--();										//X
	SN<M, E> operator--(int);									//X
	void operator-=(const SN<M, E>& nb);						//:)
	void operator-=(const M& nb);								//:)
	//void operator-=(const int& nb);								//
	//void operator-=(const double& nb);							//
	void operator*=(const SN<M, E>& nb);						//:)
	void operator*=(const M& nb);								//:)
	//void operator*=(const int& nb);								//
	//void operator*=(const double& nb);							//
	void operator/=(const SN<M, E>& nb);						//:)
	void operator/=(const M& nb);								//:)
	//void operator/=(const int& nb);								//:)
	//void operator/=(const double& nb);							//:)
};

template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E, typename K> bool operator==(const SN<M, E>& nb1, const K& nb2);		//:)
template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const M& nb2);					//:)
//template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const int& nb2);					//:)
//template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const double& nb2);				//:)
//template<typename M, typename E, typename K> bool operator==(const K& nb1, const SN<M, E>& nb2);		//:)
template<typename M, typename E> bool operator==(const M& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator==(const int& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator==(const double& nb1, const SN<M, E>& nb2);				//:)

template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E, typename K> bool operator!=(const SN<M, E>& nb1, const K& nb2);		//:)
template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const M& nb2);					//:)
//template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const int& nb2);					//:)
//template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const double& nb2);				//:)
//template<typename M, typename E, typename K> bool operator!=(const K& nb1, const SN<M, E>& nb2);		//:)
template<typename M, typename E> bool operator!=(const M& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator!=(const int& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator!=(const double& nb1, const SN<M, E>& nb2);				//:)

template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E, typename K> bool operator<=(const SN<M, E>& nb1, const K& nb2);		//:)
template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const M& nb2);					//:)
//template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const int& nb2);					//:)
//template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const double& nb2);				//:)
//template<typename M, typename E, typename K> bool operator<=(const K& nb1, const SN<M, E>& nb2);		//:)
template<typename M, typename E> bool operator<=(const M& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator<=(const int& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator<=(const double& nb1, const SN<M, E>& nb2);				//:)

template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E, typename K> bool operator>=(const SN<M, E>& nb1, const K& nb2);		//:)
template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const M& nb2);					//:)
//template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const int& nb2);					//:)
//template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const double& nb2);				//:)
//template<typename M, typename E, typename K> bool operator>=(const K& nb1, const SN<M, E>& nb2);		//:)
template<typename M, typename E> bool operator>=(const M& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator>=(const int& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator>=(const double& nb1, const SN<M, E>& nb2);				//:)

template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E, typename K> bool operator<(const SN<M, E>& nb1, const K& nb2);		//:)
template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const M& nb2);						//:)
//template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const int& nb2);					//:)
//template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const double& nb2);				//:)
//template<typename M, typename E, typename K> bool operator<(const K& nb1, const SN<M, E>& nb2);		//:)
template<typename M, typename E> bool operator<(const M& nb1, const SN<M, E>& nb2);						//:)
//template<typename M, typename E> bool operator<(const int& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator<(const double& nb1, const SN<M, E>& nb2);				//:)

template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E, typename K> bool operator>(const SN<M, E>& nb1, const K& nb2);		//:)
template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const M& nb2);						//:)
//template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const int& nb2);					//:)
//template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const double& nb2);				//:)
//template<typename M, typename E, typename K> bool operator>(const K& nb1, const SN<M, E>& nb2);		//:)
template<typename M, typename E> bool operator>(const M& nb1, const SN<M, E>& nb2);						//:)
//template<typename M, typename E> bool operator>(const int& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> bool operator>(const double& nb1, const SN<M, E>& nb2);				//:)

template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
//template<typename M, typename E, typename K> SN<M, E> operator+(const SN<M, E>& nb1, const K& nb2);	//:)
template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const M& nb2);					//:)
//template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const int& nb2);				//:)
//template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const double& nb2);			//:)
//template<typename M, typename E, typename K> SN<M, E> operator+(const K& nb1, const SN<M, E>& nb2);	//:)
template<typename M, typename E> SN<M, E> operator+(const M& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> SN<M, E> operator+(const int& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E> SN<M, E> operator+(const double& nb1, const SN<M, E>& nb2);			//:)

template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
//template<typename M, typename E, typename K> SN<M, E> operator-(const SN<M, E>& nb1, const K& nb2);	//:)
template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const M& nb2);					//:)
//template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const int& nb2);				//:)
//template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const double& nb2);			//:)
//template<typename M, typename E, typename K> SN<M, E> operator-(const K& nb1, const SN<M, E>& nb2);	//:)
template<typename M, typename E> SN<M, E> operator-(const M& nb1, const SN<M, E>& nb2);					//:)
//template<typename M, typename E> SN<M, E> operator-(const int& nb1, const SN<M, E>& nb2);				//:)
//template<typename M, typename E> SN<M, E> operator-(const double& nb1, const SN<M, E>& nb2);			//:)

template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
//template<typename M, typename E, typename K> SN<M, E> operator*(const SN<M, E>& nb1, const K& nb2);	//:)
template<typename M, typename E, typename K> SN<M, E> operator*(const SN<M, E>& nb1, const M& nb2);		//:)
//template<typename M, typename E, typename K> SN<M, E> operator*(const SN<M, E>& nb1, const int& nb2);	//:)
//template<typename M, typename E, typename K> SN<M, E> operator*(const SN<M, E>& nb1, const double& nb2);//:)
//template<typename M, typename E, typename K> SN<M, E> operator*(const K& k, const SN<M, E>& nb);		//:)
template<typename M, typename E, typename K> SN<M, E> operator*(const M& k, const SN<M, E>& nb);		//:)
//template<typename M, typename E, typename K> SN<M, E> operator*(const int& k, const SN<M, E>& nb);		//:)
//template<typename M, typename E, typename K> SN<M, E> operator*(const double& k, const SN<M, E>& nb);	//:)

template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
//template<typename M, typename E, typename K> SN<M, E> operator/(const SN<M, E>& nb1, const K& nb2);	//:)
template<typename M, typename E, typename K> SN<M, E> operator/(const SN<M, E>& nb1, const M& nb2);		//:)
//template<typename M, typename E, typename K> SN<M, E> operator/(const SN<M, E>& nb1, const int& nb2);	//:)
//template<typename M, typename E, typename K> SN<M, E> operator/(const SN<M, E>& nb1, const double& nb2);//:)
//template<typename M, typename E, typename K> SN<M, E> operator/(const K& nb1, const SN<M, E>& nb2);	//:)
template<typename M, typename E, typename K> SN<M, E> operator/(const M& nb1, const SN<M, E>& nb2);		//:)
//template<typename M, typename E, typename K> SN<M, E> operator/(const int& nb1, const SN<M, E>& nb2);	//:)
//template<typename M, typename E, typename K> SN<M, E> operator/(const double& nb1, const SN<M, E>& nb2);//:)

template<typename M, typename E> SN<M, E> abs(const SN<M, E>& nb);										//:)
template<typename M, typename E> SN<M, E> pow(const SN<M, E>& nb, const E& exp);						//:)
//template<typename M, typename E> SN<M, E> nrt(const SN<M, E>& nb, const long int& rt);
template<typename M, typename E> SN<M, E> sqrt(const SN<M, E>& nb);										//:(





/*
 * Methods of SN
 */

/**
 * @brief
 * Constructor
 */
template<typename M, typename E> inline SN<M, E>::SN() {
	this->m=(M)0;
	this->e=(E)0;
}

/**
 * @brief
 * Constructor
 */
template<typename M, typename E> inline SN<M, E>::SN(M m, E e) {
	this->m=m;
	this->e=e;
	this->recal();
}

/**
 * @brief
 * Constructor
 */
template<typename M, typename E> inline SN<M, E>::SN(M nb) {
	this->m=nb;
	this->e=(E)0;
	this->recal();
}

/**
 * @brief
 * Constructor
 */
template<typename M, typename E> inline SN<M, E>::SN(const SN<M, E>& nb) {
	this->m=nb.m;
	this->e=nb.e;
	//this->recal();
}





/**
 * @brief
 * Recalculate the SN under scientific notation.
 * Ex: 1.27x10⁹
 */
template<typename M, typename E> inline void SN<M, E>::recal() {
	if (m==(M)0){
		this->e=(E)0;
	}else{
		E l_m=floor(std::log(abs((double)m)) / std::log(10.0));//Number of digits before/after the comma (abs works well only with double)

		e+=l_m;
		m/=(M)std::pow(10, l_m);
	}
}

// Optimisation attempt
/*template<> void SN<float, char>::recal() {
	if (m==0.){
		this->e=0;
	}else{
		//std::cout<<"m!=0\n";
		char l_m=floorf(std::log(abs(m)) / std::log(10.));//Number of digits before/after the comma

		e+=l_m;
		m/=std::pow(10, l_m);
	}
}*/





template<typename M, typename E> inline M SN<M, E>::to_m_type() const {
	return (this->m)*(M)(pow(10, this->e));
}

template<typename M, typename E> inline void SN<M, E>::operator=(const SN<M, E>& nb) {
	this->m=nb.m;
	this->e=nb.e;
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator=(const M& nb) {
	this->m=nb;
	this->e=(E)0;
	this->recal();
}

/*template<typename M, typename E> inline void SN<M, E>::operator=(const int& nb) {
	this->m=(M)nb;
	this->e=(E)0;
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator=(const double& nb) {
	this->m=(M)nb;
	this->e=(E)0;
	this->recal();
}*/

template<typename M, typename E> inline SN<M, E> SN<M, E>::operator++() {
	this->m+=(M)1;
	this->recal();
	return *this;
}

template<typename M, typename E> inline SN<M, E> SN<M, E>::operator++(int) {
	SN<M, E> old = *this; // copy old value
	operator++();  // prefix increment
	return old;    // return old value
}

template<typename M, typename E> inline void SN<M, E>::operator+=(const SN<M, E>& nb) {
	this->m+=nb.m*(M)pow(10., (M)(nb.e-this->e));
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator+=(const M& nb) {//X
	this->m+=nb/pow(10., (M)(this->e));
	this->recal();
}

/*template<typename M, typename E> inline void SN<M, E>::operator+=(const int& nb) {//X
	this->m+=(M)nb/pow(10., (M)(this->e));
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator+=(const double& nb) {//X
	this->m+=(M)nb/pow(10., (M)(this->e));
	this->recal();
}*/

template<typename M, typename E> inline SN<M, E> SN<M, E>::operator--() {
	this->m-=(M)1;
	this->recal();
	return *this;
}

template<typename M, typename E> inline SN<M, E> SN<M, E>::operator--(int) {
	SN<M, E> old = *this; // copy old value
	operator--();  // prefix increment
	return old;    // return old value
}

template<typename M, typename E> inline void SN<M, E>::operator-=(const SN<M, E>& nb) {
	this->m-=nb.m*pow(10., (M)(nb.e-this->e));
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator-=(const M& nb) {
	this->m-=nb/pow(10., (M)(this->e));
	this->recal();
}

/*template<typename M, typename E> inline void SN<M, E>::operator-=(const int& nb) {
	this->m-=(M)nb/pow(10., (M)(this->e));
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator-=(const double& nb) {
	this->m-=(M)nb/pow(10., (M)(this->e));
	this->recal();
}*/

template<typename M, typename E> inline void SN<M, E>::operator*=(const SN<M, E>& nb) {
	this->m*=nb.m;
	this->e+=nb.e;
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator*=(const M& nb) {
	this->m*=nb;
	this->recal();
}

/*template<typename M, typename E> inline void SN<M, E>::operator*=(const int& nb) {
	this->m*=(M)nb;
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator*=(const double& nb) {
	this->m*=(M)nb;
	this->recal();
}*/

template<typename M, typename E> inline void SN<M, E>::operator/=(const SN<M, E>& nb) {
	this->m/=nb.m;
	this->e-=nb.e;
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator/=(const M& nb) {
	this->m/=nb;
	this->recal();
}

/*template<typename M, typename E> inline void SN<M, E>::operator/=(const int& nb) {
	this->m/=(M)nb;
	this->recal();
}

template<typename M, typename E> inline void SN<M, E>::operator/=(const double& nb) {
	this->m/=(M)nb;
	this->recal();
}*/







/*:)
 *
 */
template<typename M, typename E> inline bool operator==(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m==nb2.m && nb1.e==nb2.e){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}

/*:)
 *
 */
/*template<typename M, typename E, typename K> inline bool operator==(const SN<M, E>& nb1, const K& nb2) {
	if (nb1.m==(M)nb2/(M)(pow(10, nb1.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}*/

/*:)
 *
 */
template<typename M, typename E> inline bool operator==(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m==nb2/(M)(pow(10, nb1.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}

/*:)
 *
 */
/*template<typename M, typename E> inline bool operator==(const SN<M, E>& nb1, const int& nb2) {
	if (nb1.m==(M)nb2/(M)(pow(10, nb1.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}*/

/*:)
 *
 */
/*template<typename M, typename E> inline bool operator==(const SN<M, E>& nb1, const double& nb2) {
	if (nb1.m==(M)nb2/(M)(pow(10, nb1.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}*/

/*:)
 *
 */
/*template<typename M, typename E, typename K> inline bool operator==(const K& nb1, const SN<M, E>& nb2) {
	if (nb2.m==(M)nb1/(M)(pow(10, nb2.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}*/

/*:)
 *
 */
template<typename M, typename E> inline bool operator==(const M& nb1, const SN<M, E>& nb2) {
	if (nb2.m==nb1/(M)(pow(10, nb2.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}

/*:)
 *
 */
/*template<typename M, typename E> inline bool operator==(const int& nb1, const SN<M, E>& nb2) {
	if (nb2.m==(M)nb1/(M)(pow(10, nb2.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}*/

/*:)
 *
 */
/*template<typename M, typename E> inline bool operator==(const double& nb1, const SN<M, E>& nb2) {
	if (nb2.m==(M)nb1/(M)(pow(10, nb2.e))){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}*/

/*
 * :)
 */
template<typename M, typename E> inline bool operator!=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m!=nb2.m || nb1.e!=nb2.e){							// If e and m are not the same. n(A and B)=nA or nB.
		return true;
	}
	return false;
}

/*template<typename M, typename E, typename K> inline bool operator!=(const SN<M, E>& nb1, const K& nb2) {
	if (nb1.m!=(M)nb2/(M)(pow(10, nb1.e))){							//
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator!=(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m!=nb2/(M)(pow(10, nb1.e))){							//
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator!=(const SN<M, E>& nb1, const int& nb2) {
	if (nb1.m!=(M)nb2/(M)(pow(10, nb1.e))){							//
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator!=(const SN<M, E>& nb1, const double& nb2) {
	if (nb1.m!=(M)nb2/(M)(pow(10, nb1.e))){							//
		return true;
	}
	return false;
}*/

/*template<typename M, typename E, typename K> inline bool operator!=(const K& nb1, const SN<M, E>& nb2) {
	if (nb2.m!=(M)nb1/(M)(pow(10, nb2.e))){							//
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator!=(const M& nb1, const SN<M, E>& nb2) {
	if (nb2.m!=nb1/(M)(pow(10, nb2.e))){							//
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator!=(const int& nb1, const SN<M, E>& nb2) {
	if (nb2.m!=(M)nb1/(M)(pow(10, nb2.e))){							//
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator!=(const double& nb1, const SN<M, E>& nb2) {
	if (nb2.m!=(M)nb1/(M)(pow(10, nb2.e))){							//
		return true;
	}
	return false;
}*/

/*
 * :)
 */
template<typename M, typename E> inline bool operator<=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))<=nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E, typename K> inline bool operator<=(const SN<M, E>& nb1, const K& nb2) {
	if (nb1.m<=(M)nb2/(M)(pow(10, nb1.e))){
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator<=(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m<=nb2/(M)(pow(10, nb1.e))){
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator<=(const SN<M, E>& nb1, const int& nb2) {
	if (nb1.m<=(M)nb2/(M)(pow(10, nb1.e))){
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator<=(const SN<M, E>& nb1, const double& nb2) {
	if (nb1.m<=(M)nb2/(M)(pow(10, nb1.e))){
		return true;
	}
	return false;
}*/

/*template<typename M, typename E, typename K> inline bool operator<=(const K& nb1, const SN<M, E>& nb2) {
	if (nb2.m>=(M)nb1/(M)(pow(10, nb2.e))){	//
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator<=(const M& nb1, const SN<M, E>& nb2) {
	if (nb2.m>=nb1/(M)(pow(10, nb2.e))){	//
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator<=(const int& nb1, const SN<M, E>& nb2) {
	if (nb2.m>=(M)nb1/(M)(pow(10, nb2.e))){	//
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator<=(const double& nb1, const SN<M, E>& nb2) {
	if (nb2.m>=(M)nb1/(M)(pow(10, nb2.e))){	//
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator>=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E, typename K> inline bool operator>=(const SN<M, E>& nb1, const K& nb2) {
	if (nb1.m>=(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator>=(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m>=nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator>=(const SN<M, E>& nb1, const int& nb2) {
	if (nb1.m>=(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator>=(const SN<M, E>& nb1, const double& nb2) {
	if (nb1.m>=(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}*/

/*template<typename M, typename E, typename K> inline bool operator>=(const K& nb1, const SN<M, E>& nb2) {
	if (nb2.m<=(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator>=(const M& nb1, const SN<M, E>& nb2) {
	if (nb2.m<=nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator>=(const int& nb1, const SN<M, E>& nb2) {
	if (nb2.m<=(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator>=(const double& nb1, const SN<M, E>& nb2) {
	if (nb2.m<=(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator<(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))<nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E, typename K> inline bool operator<(const SN<M, E>& nb1, const K& nb2) {
	if (nb1.m<(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator<(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m<nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator<(const SN<M, E>& nb1, const int& nb2) {
	if (nb1.m<(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator<(const SN<M, E>& nb1, const double& nb2) {
	if (nb1.m<(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}*/

/*template<typename M, typename E, typename K> inline bool operator<(const K& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator<(const M& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator<(const int& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator<(const double& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator>(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))>nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E, typename K> inline bool operator>(const SN<M, E>& nb1, const K& nb2) {
	if (nb1.m>(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator>(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m>nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator>(const SN<M, E>& nb1, const int& nb2) {
	if (nb1.m>(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator>(const SN<M, E>& nb1, const double& nb2) {
	if (nb1.m>(M)nb2/(M)(pow(10, nb1.e))){	// .
		return true;
	}
	return false;
}*/

/*template<typename M, typename E, typename K> inline bool operator>(const K& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> inline bool operator>(const M& nb1, const SN<M, E>& nb2) {
	if (nb2.m>nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> inline bool operator>(const int& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> inline bool operator>(const double& nb1, const SN<M, E>& nb2) {
	if (nb2.m>(M)nb1/(M)(pow(10, nb2.e))){	// .
		return true;
	}
	return false;
}*/

/*:)
 * @brief
 * It's better to enter the bigger number first I think.
 */
template<typename M, typename E> inline SN<M, E> operator+(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m+nb2.m/pow(10., (M)(nb1.e-nb2.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E, typename K> inline SN<M, E> operator+(const SN<M, E>& nb1, const K& nb2) {
	M nm=nb1.m+nb2/pow(10., (M)(nb1.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator+(const SN<M, E>& nb1, const M& nb2) {
	M nm=nb1.m+nb2/pow(10., (M)(nb1.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator+(const SN<M, E>& nb1, const int& nb2) {
	M nm=nb1.m+(M)nb2/pow(10., (M)(nb1.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator+(const SN<M, E>& nb1, const double& nb2) {
	M nm=nb1.m+(M)nb2/pow(10., (M)(nb1.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

/*template<typename M, typename E, typename K> inline SN<M, E> operator+(const K& nb1, const SN<M, E>& nb2) {
	M nm=nb1+nb2.m*pow(10., (M)nb2.e);
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator+(const M& nb1, const SN<M, E>& nb2) {
	M nm=nb1+nb2.m*pow(10., (M)nb2.e);
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator+(const int& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1+nb2.m*pow(10., (M)nb2.e);
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator+(const double& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1+nb2.m*pow(10., (M)nb2.e);
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

/*:)
 * @brief
 * It's better to enter the bigger number first.
 */
template<typename M, typename E> inline SN<M, E> operator-(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m-nb2.m/pow(10., (M)(nb1.e-nb2.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E, typename K> inline SN<M, E> operator-(const SN<M, E>& nb1, const K& nb2) {
	M nm=nb1.m-nb2/pow(10., (M)nb1.e);
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator-(const SN<M, E>& nb1, const M& nb2) {
	M nm=nb1.m-nb2/pow(10., (M)nb1.e);
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator-(const SN<M, E>& nb1, const int& nb2) {
	M nm=nb1.m-(M)nb2/pow(10., (M)nb1.e);
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator-(const SN<M, E>& nb1, const double& nb2) {
	M nm=nb1.m-(M)nb2/pow(10., (M)nb1.e);
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

/*template<typename M, typename E, typename K> inline SN<M, E> operator-(const K& nb1, const SN<M, E>& nb2) {
	M nm=nb1-nb2.m*pow(10., (M)(nb2.e));
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator-(const M& nb1, const SN<M, E>& nb2) {
	M nm=nb1-nb2.m*pow(10., (M)(nb2.e));
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator-(const int& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1-nb2.m*pow(10., (M)(nb2.e));
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator-(const double& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1-nb2.m*pow(10., (M)(nb2.e));
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator*(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m*nb2.m;
	E ne=nb1.e+nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E, typename K> inline SN<M, E> operator*(const SN<M, E>& nb1, const K& nb2) {
	M nm=nb1.m*nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator*(const SN<M, E>& nb1, const M& nb2) {
	M nm=nb1.m*nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator*(const SN<M, E>& nb1, const int& nb2) {
	M nm=nb1.m*(M)nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator*(const SN<M, E>& nb1, const double& nb2) {
	M nm=nb1.m*(M)nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

/*template<typename M, typename E, typename K> inline SN<M, E> operator*(const K& nb1, const SN<M, E>& nb2) {
	M nm=nb1*nb2.m;
	E ne=nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator*(const M& nb1, const SN<M, E>& nb2) {
	M nm=nb1*nb2.m;
	E ne=nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator*(const int& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1*nb2.m;
	E ne=nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator*(const double& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1*nb2.m;
	E ne=nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator/(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m/nb2.m;
	E ne=nb1.e-nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E, typename K> inline SN<M, E> operator/(const SN<M, E>& nb1, const K& nb2) {
	M nm=nb1.m/nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator/(const SN<M, E>& nb1, const M& nb2) {
	M nm=nb1.m/nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator/(const SN<M, E>& nb1, const int& nb2) {
	M nm=nb1.m/(M)nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator/(const SN<M, E>& nb1, const double& nb2) {
	M nm=nb1.m/(M)nb2;
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

/*template<typename M, typename E, typename K> inline SN<M, E> operator/(const K& nb1, const SN<M, E>& nb2) {
	M nm=nb1/nb2.m;
	E ne=(-1)*nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/

template<typename M, typename E> inline SN<M, E> operator/(const M& nb1, const SN<M, E>& nb2) {
	M nm=nb1/nb2.m;
	E ne=(-1)*nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> inline SN<M, E> operator/(const int& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1/nb2.m;
	E ne=(-1)*nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

template<typename M, typename E> inline SN<M, E> operator/(const double& nb1, const SN<M, E>& nb2) {
	M nm=(M)nb1/nb2.m;
	E ne=(-1)*nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}*/




/*
 * Functions
 */
 
/**
 * @brief
 * Computes the absolute value of a SN
 */
template<typename M, typename E> inline SN<M, E> abs(const SN<M, E>& nb) {
	return SN<M, E>{(M)std::abs(nb.m), nb.e};
}

/**
 * @brief
 * Puts to the power 2
 */
template<typename M, typename E> inline SN<M, E> pow(const SN<M, E>& nb, const E& e) {
	M nm=pow(nb.m, (M)e);
	E ne=nb.e*e;
	SN<M, E> resp(nm, ne);
	resp.recal();
	return resp;
}

/*// Calculate the n root of a number
template<typename M, typename E> LSN nrt(LSN& nb, long int e) {
	//LSN nb2={1, 0};
	for (long int i(0) ; i<nb.e%e ; i++)
	{
		nb.m*=nb;
	}
	recal(nb2);
	return *(new LSN{pow(nb.m, e), nb.e*e});
}*/

/**
 * @brief
 * Calculate the square root of a number.
 */
template<typename M, typename E> inline SN<M, E> sqrt(const SN<M, E>& nb) {
	M nm=pow(nb.m, 0.5);
	E ne=nb.e/2;
	SN<M, E> resp(nm, ne);//Doesn't work (exponent cast to int)
	resp.recal();
	return resp;
}




#endif /* SN_HPP_ */
