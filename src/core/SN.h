/*
 * LSN.h
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SN_H_

#define SN_H_

//#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include "../utilities/functions.h"
#include "../utilities/Printable.h"


/**
 * ######
 *  SN :)
 * ######
 * Scientific Number
 * It allows to store big numbers
 * under scientific notation.
 * Recommended usage : 	<float, char>
 * 						<double, char>
 * 						<double, int>
 */
template<typename M, typename E> struct SN : public Printable {
	M m;						// Mantissa
	E e;						// Exponent

	SN();
	SN(M m, E e);
	SN(const SN<M, E>& nb);
	SN(const SN<M, E>* pnb);

	void recal();												//:)

	M to_m_type() const;										//:)
	void operator=(const SN<M, E>& nb);							//:)
	void operator=(const M& nb);								//:)
	void operator+=(const SN<M, E>& nb);						//:)
	void operator+=(const M& nb);								//:)
	void operator-=(const SN<M, E>& nb);						//:)
	void operator-=(const M& nb);								//:)
	void operator*=(const SN<M, E>& nb);						//:)
	void operator*=(const M& nb);								//:)
	void operator/=(const SN<M, E>& nb);						//:)
	void operator/=(const M& nb);								//:)

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const M& nb2);					//:)
template<typename M, typename E> bool operator!=(const M& nb1, const SN<M, E>& nb2);					//:)
template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const M& nb2);					//:)
template<typename M, typename E> bool operator<=(const M& nb1, const SN<M, E>& nb2);					//:)
template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const M& nb2);					//:)
template<typename M, typename E> bool operator>=(const M& nb1, const SN<M, E>& nb2);					//:)
template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const M& nb2);
template<typename M, typename E> bool operator<(const M& nb1, const SN<M, E>& nb2);
template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator>(const SN<M, E>& nb1, M& nb2);							//:)
template<typename M, typename E> bool operator>(const M& nb1, const SN<M, E>& nb2);						//:)

template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const M& nb2);					//:)
template<typename M, typename E> SN<M, E> operator+(const M& nb1, const SN<M, E>& nb2);					//:)
template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const M& nb2);					//:)
template<typename M, typename E> SN<M, E> operator-(const M& nb1, const SN<M, E>& nb2);					//:)
template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb, const M& k);					//:)
template<typename M, typename E> SN<M, E> operator*(const M& k, const SN<M, E>& nb);					//:)
template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb1, const SN<M, E>& nb2);			//:)
template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb1, const M& nb2);					//:)
template<typename M, typename E> SN<M, E> operator/(const M& nb1, const SN<M, E>& nb2);					//:)

template<typename M, typename E> SN<M, E> abs(const SN<M, E>& nb);											//:)
template<typename M, typename E> SN<M, E> pow(const SN<M, E>& nb, const E& exp);					//:)
//template<typename M, typename E> SN<M, E> nrt(const SN<M, E>& nb, const long int& rt);
template<typename M, typename E> SN<M, E> sqrt(const SN<M, E>& nb);





/*
 * Methods of SN
 */

template<typename M, typename E> SN<M, E>::SN() {
	this->m=(M)0;
	this->e=(E)0;
}

/*template<> SN<float, char>::SN() {
	this->m=0.;
	this->e=0;
}*/

template<typename M, typename E> SN<M, E>::SN(M m, E e) {
	this->m=m;
	this->e=e;
	this->recal();
}

/*template<> SN<float, char>::SN(float m, char e) {
	this->m=m;
	this->e=e;
}*/

template<typename M, typename E> SN<M, E>::SN(const SN<M, E>& nb) {
	this->m=nb.m;
	this->e=nb.e;
	this->recal();
}

template<typename M, typename E> SN<M, E>::SN(const SN<M, E>* pnb) {
	this->m=pnb->m;
	this->e=pnb->e;
	this->recal();
}

/*
 * Recalculate the SN under scientific notation.
 * Ex: 1.27x10⁹
 */
template<typename M, typename E> void SN<M, E>::recal() {
	if (m==(M)0){
		this->e=(E)0;
	}else{
		//std::cout<<"m!=0\n";
		int l_m=std::log((M)abs(m)) / std::log(10);//Number of digits before/after the comma

		e+=(E)(l_m);
		m/=(M)std::pow(10, l_m);
	}
}

/*template<> void SN<float, char>::recal() {//printf(("Number : "+this->to_string()+"\n").c_str());
	if (m==0){
		e=0;
	}else{
		int l_m=std::log(abs(m)) / std::log(10.);//Number of chiffres avant/après la virgule

		e+=l_m;
		m/=std::pow(10, l_m);
	}
}*/

template<typename M, typename E> M SN<M, E>::to_m_type() const {
	return (this->m)*(M)(pow(10, this->e));
}

template<typename M, typename E> void SN<M, E>::operator=(const SN<M, E>& nb) {
	this->m=nb.m;
	this->e=nb.e;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator=(const M& nb) {
	this->m=nb;
	this->e=(E)0;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator+=(const SN<M, E>& nb) {
	this->m+=nb.m*(M)pow(10., (M)(nb.e-this->e));
	this->recal();
}

/*template<> void SN<float, char>::operator+=(const SN<float, char>& nb) {
	this->m+=nb.m*pow(10., (float)(nb.e-this->e));
	this->recal();
}*/

template<typename M, typename E> void SN<M, E>::operator+=(const M& nb) {//X
	this->m+=nb/pow(10., (M)(this->e));
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator-=(const SN<M, E>& nb) {
	this->m-=nb.m*pow(10., (M)(nb.e-this->e));
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator-=(const M& nb) {
	this->m-=nb/pow(10., (M)(this->e));
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator*=(const SN<M, E>& nb) {
	this->m*=nb.m;
	this->e+=nb.e;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator*=(const M& k) {
	this->m*=k;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator/=(const SN<M, E>& nb) {
	this->m/=nb.m;
	this->e-=nb.e;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator/=(const M& k) {
	this->m/=k;
	this->recal();
}







/*:)
 *
 */
template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m==nb2.m && nb1.e==nb2.e){							// If e and m are the same. A and B.
		return true;
	}
	return false;
}

/*
 * :)
 */
template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m!=nb2.m || nb1.e!=nb2.e){							// If e and m are not the same. n(A and B)=nA or nB.
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m!=nb2/pow(10., (M)nb1.e)){							//
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator!=(const M& nb1, const SN<M, E>& nb2) {
	if (nb1/pow(10., (M)nb2.e)!=nb2.m){							//
		return true;
	}
	return false;
}

/*
 * :)
 */
template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))<=nb2.m){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e))<=nb2){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const M& nb1, const SN<M, E>& nb2) {
	if (nb1/pow(10., (M)(nb2.e))<=nb2.m){	//
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}

/*template<> bool operator>=(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	if (nb1.m*pow(10., (float)(nb1.e-nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e))>=nb2){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const M& nb1, const SN<M, E>& nb2) {
	if (nb1/pow(10., (M)(nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))<nb2.m){	// .
		return true;
	}
	return false;
}

/*template<> bool operator<(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	if (nb1.m*pow(10., (float)(nb1.e-nb2.e))<nb2.m){
		return true;
	}
	return false;
}*/

template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e))<nb2){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<(const M& nb1, const SN<M, E>& nb2) {
	if (nb1/pow(10., (M)(nb2.e))<nb2.m){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e-nb2.e))>nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> bool operator>(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	if (nb1.m*pow(10., (float)(nb1.e-nb2.e))>nb2.m){
		return true;
	}
	return false;
}*/

template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const M& nb2) {
	if (nb1.m*pow(10., (M)(nb1.e))>nb2){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>(const M& nb1, const SN<M, E>& nb2) {
	if (nb1/pow(10., (M)(nb2.e))>nb2.m){	// .
		return true;
	}
	return false;
}

/*:)
 * It's better to enter the bigger number first I think.
 */
template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m+nb2.m/pow(10., (M)(nb1.e-nb2.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator+(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	float nm=nb1.m+nb2.m/pow(10., (float)(nb1.e-nb2.e));
	char ne=nb1.e;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const M& nb2) {
	M nm=nb1.m+nb2/pow(10., (M)(nb1.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator+(const SN<float, char>& nb1, const float& nb2) {
	float nm=nb1.m+nb2/pow(10., (float)(nb1.e));
	char ne=nb1.e;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator+(const M& nb1, const SN<M, E>& nb2) {
	M nm=nb1+nb2.m*pow(10., (M)nb2.e);
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator+(const float& nb1, const SN<float, char>& nb2) {
	float nm=nb1+nb2.m*pow(10., (float)(nb2.e));
	char ne=0;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

/*:)
 * It's better to enter the bigger number first.
 */
template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m-nb2.m/pow(10., (M)(nb1.e-nb2.e));
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator-(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	float nm=nb1.m-nb2.m/pow(10., (float)(nb1.e-nb2.e));
	char ne=nb1.e;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const M& nb2) {
	M nm=nb1.m-nb2/pow(10., (M)nb1.e);
	E ne=nb1.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator-(const SN<float, char>& nb1, const float& nb2) {
	float nm=nb1.m-nb2/pow(10., (float)(nb1.e));
	char ne=nb1.e;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator-(const M& nb1, const SN<M, E>& nb2) {
	M nm=nb1-nb2.m*pow(10., (M)(nb2.e));
	E ne=0;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator-(const float& nb1, const SN<float, char>& nb2) {
	float nm=nb1-nb2.m*pow(10., (float)(nb2.e));
	char ne=0;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m*nb2.m;
	E ne=nb1.e+nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator*(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	float nm=nb1.m*nb2.m;
	char ne=nb1.e+nb2.e;
	//SN nnb(nm, ne)//So that it recalculates
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb, const M& k) {
	M nm=nb.m*k;
	E ne=nb.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator*(const SN<float, char>& nb, const float& k) {
	SN<float, char> nnb{nb.m*k, nb.e};
	nnb.recal();
	return nnb;
}*/

template<typename M, typename E> SN<M, E> operator*(const M& k, const SN<M, E>& nb) {
	M nm=k*nb.m;
	E ne=nb.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator*(const float& k, const SN<float, char>& nb) {
	SN<float, char> nnb{nb.m*k, nb.e};
	nnb.recal();
	return nnb;
}*/

template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	M nm=nb1.m/nb2.m;
	E ne=nb1.e-nb2.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<typename M, typename E> SN<float, char> operator/(const SN<float, char>& nb1, const SN<float, char>& nb2) {
	return {nb1.m/nb2.m, nb1.e-nb2.e};
}*/

template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb, const M& k) {
	M nm=nb.m/k;
	E ne=nb.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator/(const SN<float, char>& nb, const float& k) {
	float nm=nb.m*k;
	char ne=nb.e;
	return SN(nm, ne);
}*/

template<typename M, typename E> SN<M, E> operator/(const M& k, const SN<M, E>& nb) {
	M nm=k/nb.m;
	E ne=(-1)*nb.e;
	SN<M, E> nnb(nm, ne);// To recal
	return nnb;
}

/*template<> SN<float, char> operator/(const float& k, const SN<float, char>& nb) {
	float nm=k/nb.m;
	char ne=nb.e;
	return SN(nm, ne);
}*/



template<typename M, typename E> std::string SN<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	if (full_info){
		mes+="SN[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
		//mes;
	}else{
		//mes+=std::to_string(m).erase(4, std::to_string(m).length()) + "e" + std::to_string(e);
	}
	mes+=to_stringTabs(indent);
	mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

/*template<> std::string SN<float, char>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="LSN[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
		mes+=std::to_string(m) + "x10^" + std::to_string(e);
	}else{
		mes+=std::to_string(m).erase(4, std::to_string(m).length()) + "e" + std::to_string(e);
	}

	return mes;
}*/

template<typename M, typename E> void SN<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

/*template<> void SN<float, char>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}*/

/*
 * Functions
 */

template<typename M, typename E> SN<M, E> abs(const SN<M, E>& nb) {
	//printf("In the abs in SN\n");
	M nm=std::abs(nb.m);
	E ne=nb.e;
	SN<M, E> resp(nm, ne);//To recal
	//resp.recal();
	return resp;
}

/*template<> SN<float, char> abs(const SN<float, char>& nb) {
	SN<float, char> resp{std::abs(nb.m), nb.e};
	//resp.recal();
	return resp;
}*/

template<typename M, typename E> SN<M, E> pow(const SN<M, E>& nb, const E& e) {
	M nm=pow(nb.m, (M)e);
	E ne=nb.e*e;
	SN<M, E> resp(nm, ne);
	resp.recal();
	return resp;
}

/*template<> SN<float, char> pow(const SN<float, char>& nb, const char& e) {
	float nm(pow(nb.m, (float)e));
	char ne=nb.e*e;
	SN<float, char> resp{  nm   ,  ne   };
	//SN<float, char> resp{pow(nb.m, (float)e), 0};
	resp.recal();
	return resp;
}*/

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

/*
 * Calculate the square root of a number.
 */
template<typename M, typename E> SN<M, E> sqrt(const SN<M, E>& nb) {
	M nm=pow(nb.m, 0.5);
	E ne=nb.e/2;
	SN<M, E> resp(nm, ne);//Doesn't work (exponent cast to int)
	resp.recal();
	return resp;
}

/*template<> SN<float, char> sqrt(const SN<float, char>& nb) {
	SN<float, char> resp={(float)pow(nb.m, 0.5), (char)(nb.e/2)};//Doesn't work (exponent cast to int)
	resp.recal();
	return resp;
}*/




#endif /* SN_H_ */
