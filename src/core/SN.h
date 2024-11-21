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


//typedef enum mantissa{float, double, (long double)};
//typedef enum exponent{char, int, long int};

/*
 * ######
 *  SN :)
 * ######
 * Scientific Number
 * It allows to store big numbers
 * under scientific notation.
 * Recommended uses : 	(float, char)
 * 						(double, char)
 * 						##(double, int)
 */
template<typename M, typename E> struct SN : public Printable {
	M m;						// Mantissa
	E e;						// Exponent

	SN();
	SN(M m, E e);

	void recal();												//:)

	//long double to_long_double() const;							//:)
	void operator=(const SN& nb);								//:)
	//void operator=(const long double& nb);						//:)
	void operator+=(const SN& nb);								//:)
	//void operator+=(const long double& nb);						//:)
	void operator-=(const SN& nb);								//:)
	//void operator-=(const long double& nb);						//:)
	void operator*=(const SN& nb);								//:)
	//void operator*=(const long double& nb);						//:)
	void operator/=(const SN& nb);								//:)
	//void operator/=(const long double& nb);						//:)

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//bool operator!=(const SN& nb1, const long double& nb2);		//:)
//bool operator!=(const long double& nb1, const LSN& nb2);		//:)
template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//bool operator<=(const SN& nb1, const long double& nb2);		//:)
//bool operator<=(const long double& nb1, const LSN& nb2);		//:)
template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const SN<M, E>& nb2);				//:)
//bool operator>=(const SN& nb1, const long double& nb2);		//:)
//bool operator>=(const long double& nb1, const LSN& nb2);		//:)
template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const SN<M, E>& nb2);					//:)
//bool operator<(const SN& nb1, const long double& nb2);			//:)
//bool operator<(const long double& nb1, const LSN& nb2);			//:)
template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const SN<M, E>& nb2);					//:)
//bool operator>(const SN& nb1, const long double& nb2);			//:)
//bool operator>(const long double& nb1, const LSN& nb2);			//:)

template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const SN<M, E>& nb2);					//:)
//SN operator+(const SN& nb1, const long double& nb2);			//:)
//LSN operator+(const long double& nb1, const LSN& nb2);			//:)
template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const SN<M, E>& nb2);					//:)
//LSN operator-(const LSN& nb1, const long double& nb2);			//:)
//LSN operator-(const long double& nb1, const LSN& nb2);			//:)
template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb1, const SN<M, E>& nb2);					//:)
//LSN operator*(const LSN& nb, const long double& k);				//:)
//LSN operator*(const long double& k, const LSN& nb);				//:)
template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb1, const SN<M, E>& nb2);					//:)
//LSN operator/(const LSN& nb, const long double& k);				//:)
//LSN operator/(const long double& k, const LSN& nb);				//:)

template<typename M, typename E> SN<M, E> abs(const SN<M, E>& nb);											//:)
template<typename M, typename E> SN<M, E> pow(const SN<M, E>& nb, const long int& exp);					//:)
template<typename M, typename E> SN<M, E> nrt(const SN<M, E>& nb, const long int& rt);
template<typename M, typename E> SN<M, E> sqrt(const SN<M, E>& nb);





/*
 * Methods of SN
 */

template<typename M, typename E> SN<M, E>::SN() {
	this->m=0;
	this->e=0;
}

template<typename M, typename E> SN<M, E>::SN(M m, E e) {
	this->m=m;
	this->e=e;
	this->recal();
}

/*
 * Recalculate the LSN under scientific notation.
 * Ex: 1.27x10⁹
 */
template<typename M, typename E> void SN<M, E>::recal() {
	//printf(("Number : "+this->to_string()+"\n").c_str());
	if (m==0){
		e=0;
	}else{
		//std::cout<<"m!=0\n";
		int l_m=std::log(abs(m)) / std::log(10);//Number of chiffres avant/après la virgule

		e+=(l_m);
		m/=std::pow(10, (l_m));
	}
}

template<> void SN<float, char>::recal() {//printf(("Number : "+this->to_string()+"\n").c_str());
	if (m==0){
		e=0;
	}else{
		int l_m=std::log(abs(m)) / std::log(10.);//Number of chiffres avant/après la virgule

		e+=l_m;
		m/=std::pow(10, l_m);
}

/*template<typename M, typename E> long double SN<M, E>::to_long_double() const {
	//long double ans=(this->m)*(long double)(pow(10, this->e));
	//std::cout<< this->m << "\n";
	//std::cout<< (long double)(pow(10, this->e)) << "\n";
	//std::cout<< (this->m)*(long double)(pow(10, this->e)) << "\n";
	return (this->m)*(long double)(pow(10, this->e));
}*/

template<typename M, typename E> void SN<M, E>::operator=(const SN<M, E>& nb) {
	this->m=nb.m;
	this->e=nb.e;
	this->recal();
}

/*template<typename M, typename E> void SN<M, E>::operator=(const long double& nb) {
	this->m=nb;
	this->e=0;
	this->recal();
}*/

template<typename M, typename E> void SN<M, E>::operator+=(const SN<M, E>& nb) {
	this->m+=nb.m*pow(10., (long double)(nb.e-this->e));
	this->recal();
}

template<> void SN<float, char>::operator+=(const SN<float, char>& nb) {
	this->m+=nb.m*pow(10., (float)(nb.e-this->e));
	this->recal();
}

/*template<typename M, typename E> void SN<M, E>::operator+=(const long double& nb) {//X
	this->m+=nb/pow(10., (long double)(this->e));
	this->recal();
}*/

template<typename M, typename E> void SN<M, E>::operator-=(const SN<M, E>& nb) {
	this->m-=nb.m*pow(10., (long double)(nb.e-this->e));
	this->recal();
}

/*template<typename M, typename E> void SN<M, E>::operator-=(const long double& nb) {
	this->m-=nb/pow(10., (long double)(this->e));
	this->recal();
}*/

template<typename M, typename E> void SN<M, E>::operator*=(const SN<M, E>& nb) {
	this->m*=nb.m;
	this->e+=nb.e;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator/=(const SN<M, E>& nb) {
	this->m/=nb.m;
	this->e-=nb.e;
	this->recal();
}

/*template<typename M, typename E> void SN<M, E>::operator*=(const long double& k) {
	this->m*=k;
	this->recal();
}

template<typename M, typename E> void SN<M, E>::operator/=(const long double& k) {
	this->m/=k;
	this->recal();
}*/







/*:)
 *
 */
template<typename M, typename E> bool operator==(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m==nb2.m && nb1.e==nb2.e)							// If e and m are the same. A and B.
		return true;

	return false;
}

/*
 * :)
 */
template<typename M, typename E> bool operator!=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m!=nb2.m || nb1.e!=nb2.e)							// If e and m are not the same. n(A and B)=nA or nB.
		return true;

	return false;
}

/*template<typename M, typename E> bool operator!=(const SN& nb1, const long double& nb2) {
	if (nb1.m!=nb2/pow(10., (long double)nb1.e))							//
		return true;

	return false;
}

template<typename M, typename E> bool operator!=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)nb2.e)!=nb2.m)							//
		return true;

	return false;
}*/

/*
 * :)
 */
template<typename M, typename E> bool operator<=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	printf("1)\n%Lf\n", nb1.m*pow(10., (long double)(nb1.e-nb2.e)));
	printf("2)\n%Lf\n", nb2.m);
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))<=nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> bool operator<=(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))<=nb2){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))<=nb2.m){	//
		return true;
	}
	return false;
}*/

template<typename M, typename E> bool operator>=(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}

/*template<typename M, typename E> bool operator>=(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))>=nb2){	// .
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))>=nb2.m){	// .
		return true;
	}
	return false;
}*/

template<typename M, typename E> bool operator<(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))<nb2.m){	// .
	//if (nb1.e<nb2.e or (nb1.e==nb2.e and nb1.m<nb2.m)){		// Else if the e are the same but m1<m2.
		return true;
	}
	return false;
}

/*template<typename M, typename E> bool operator<(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))<nb2){	// .
	//if (nb1.m<nb2/pow(10, nb1.e)){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))<nb2.m){	// .
	//if (nb1/pow(10, nb2.e)<nb2.m){
		return true;
	}
	return false;
}*/

template<typename M, typename E> bool operator>(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e-nb2.e))>nb2.m){	// .
	//if (nb1.e>nb2.e or (nb1.e==nb2.e and nb1.m>nb2.m)){		// Else if the e are the same but m1>m2.
		return true;
	}
	return false;
}

/*template<typename M, typename E> bool operator>(const LSN& nb1, const long double& nb2) {
	if (nb1.m*pow(10., (long double)(nb1.e))>nb2){	// .
	//if (nb1.m>nb2/pow(10, nb1.e)){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10., (long double)(nb2.e))>nb2.m){	// .
	//if (nb1/pow(10, nb2.e)>nb2.m){
		return true;
	}
	return false;
}*/

/*:)
 * It's better to enter the bigger number first I think.
 */
template<typename M, typename E> SN<M, E> operator+(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	return {nb1.m+nb2.m/pow(10., (long double)(nb1.e-nb2.e)), nb1.e};
}
/*
template<typename M, typename E> LSN operator+(const LSN& nb1, const long double& nb2) {
	return {nb1.m+nb2/pow(10., (long double)nb1.e), nb1.e};
}

template<typename M, typename E> LSN operator+(const long double& nb1, const LSN& nb2) {
	return {nb1+nb2.m*pow(10., (long double)nb2.e), 0};
}*/

/*:)
 * It's better to enter the bigger number first.
 */
template<typename M, typename E> SN<M, E> operator-(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	return {nb1.m-nb2.m/pow(10., (long double)(nb1.e-nb2.e)), nb1.e};
}

/*template<typename M, typename E> LSN operator-(const LSN& nb1, const long double& nb2) {
	return {nb1.m-nb2/pow(10., (long double)nb1.e), nb1.e};
}

template<typename M, typename E> LSN operator-(const long double& nb1, const LSN& nb2) {
	return {nb1-nb2.m*pow(10., (long double)nb2.e), 0};
}*/

template<typename M, typename E> SN<M, E> operator*(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	return {nb1.m*nb2.m, nb1.e+nb2.e};
}

/*template<typename M, typename E> LSN operator*(const LSN& nb, const long double& k) {
	return {nb.m*k, nb.e};
}

template<typename M, typename E> LSN operator*(const long double& k, const LSN& nb) {
	return {nb.m*k, nb.e};
}*/

template<typename M, typename E> SN<M, E> operator/(const SN<M, E>& nb1, const SN<M, E>& nb2) {
	return {nb1.m/nb2.m, nb1.e-nb2.e};
}

/*template<typename M, typename E> LSN operator/(const LSN& nb, const long double& k) {
	return {nb.m/k, nb.e};
}

template<typename M, typename E> LSN operator/(const long double& k, const LSN& nb) {
	return {nb.m/k, nb.e};
}*/



template<typename M, typename E> std::string SN<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
}

template<typename M, typename E> void SN<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


/*
 * Functions
 */

template<typename M, typename E> SN<M, E> abs(const SN<M, E>& nb) {
	SN resp{std::abs(nb.m), nb.e};
	//resp.recal();
	return resp;
}

template<typename M, typename E> SN<M, E> pow(const SN<M, E>& nb, const long int& e) {
	SN resp{pow(nb.m, (long double)e), nb.e*e};
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

/*
 * Calculate the square root of a number.
 */

template<typename M, typename E> SN<M, E> sqrt(const SN<M, E>& nb) {
	SN resp={pow(nb.m, 0.5), nb.e/2};//Doesn't work (exponent cast to int)
	resp.recal();
	return resp;
}





#endif /* SN_H_ */
