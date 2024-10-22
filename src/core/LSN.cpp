/*
 * LSN.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#include "LSN.h"



/*
 * Methods of LSN
 */

LSN::LSN() {
	m=0;
	exp=0;
}

LSN::LSN(long double m, long int exp) {
	this->m=m;
	this->exp=exp;
	this->recal();
}

/* :( Doesn't work for negative numbers
 * Recalculate the LSN under scientific notation.
 * Ex: 1.27x10⁹
 */
void LSN::recal() {//Sometimes doesn't work properly (because of the cast to an int Ex: (int)10.0000=9 when 10 is a double)
	//printf(("Number : "+this->to_string()+"\n").c_str());
	if (m==0){
		//std::cout<<"m=0\n";
		exp=0;
	}else{
		//std::cout<<"m!=0\n";
		int l_m=std::log(abs(m)) / std::log(10);//Number of chiffres avant/après la virgule
		//std::cout<<"lenght mantissa "<<l_m<<"\n";

		exp+=(l_m);
		m/=std::pow(10, (l_m));
	}
}

long double LSN::to_long_double() const {
	//long double ans=(this->m)*(long double)(pow(10, this->exp));
	//std::cout<< this->m << "\n";
	//std::cout<< (long double)(pow(10, this->exp)) << "\n";
	//std::cout<< (this->m)*(long double)(pow(10, this->exp)) << "\n";
	return (this->m)*(long double)(pow(10, this->exp));
}

void LSN::operator=(const LSN& nb) {
	this->m=nb.m;
	this->exp=nb.exp;
	this->recal();
}

void LSN::operator=(const long double& nb) {
	this->m=nb;
	this->exp=0;
	this->recal();
}

void LSN::operator+=(const LSN& nb) {
	this->m+=nb.m/pow(10, (nb.exp-this->exp));
	this->recal();
}

void LSN::operator+=(const long double& nb) {
	this->m+=nb/pow(10, (0-this->exp));
	this->recal();
}

void LSN::operator-=(const LSN& nb) {
	this->m-=nb.m/pow(10, (nb.exp-this->exp));
	this->recal();
}

void LSN::operator-=(const long double& nb) {
	this->m-=nb/pow(10, (0-this->exp));
	this->recal();
}

void LSN::operator*=(const LSN& nb) {
	this->m*=nb.m;
	this->exp+=nb.exp;
	this->recal();
}

void LSN::operator/=(const LSN& nb) {
	this->m/=nb.m;
	this->exp-=nb.exp;
	this->recal();
}

void LSN::operator*=(const long double& k) {
	this->m*=k;
	this->recal();
}

void LSN::operator/=(const long double& k) {
	this->m/=k;
	this->recal();
}







/*:)
 *
 */
bool operator==(const LSN& nb1, const LSN& nb2) {
	if (nb1.m==nb2.m && nb1.exp==nb2.exp)							// If exp and m are the same. A and B.
		return true;

	return false;
}

/*
 * :)
 */
bool operator!=(const LSN& nb1, const LSN& nb2) {
	if (nb1.m!=nb2.m || nb1.exp!=nb2.exp)							// If exp and m are not the same. n(A and B)=nA or nB.
		return true;

	return false;
}

bool operator!=(const LSN& nb1, const long double& nb2) {
	if (nb1.m!=nb2/pow(10, nb1.exp))							//
		return true;

	return false;
}

bool operator!=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10, nb2.exp)!=nb2.m)							//
		return true;

	return false;
}

/*
 * :)
 */
bool operator<=(const LSN& nb1, const LSN& nb2) {
	if (nb1.exp<nb2.exp or (nb1.exp==nb2.exp and nb1.m<=nb2.m)){	// Else if the exp are the same but m1<=m2.
		return true;
	}
	return false;
}

bool operator<=(const LSN& nb1, const long double& nb2) {
	if (nb1.m<=nb2/pow(10, nb1.exp)){
		return true;
	}
	return false;
}

bool operator<=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10, nb2.exp)<=nb2.m){
		return true;
	}
	return false;
}

bool operator>=(const LSN& nb1, const LSN& nb2) {
	if (nb1.exp>nb2.exp or (nb1.exp==nb2.exp and nb1.m>=nb2.m)){	// Else if the exp are the same but m1>=m2.
		return true;
	}
	return false;
}

bool operator>=(const LSN& nb1, const long double& nb2) {
	if (nb1.m>=nb2/pow(10, nb1.exp)){
		return true;
	}
	return false;
}

bool operator>=(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10, nb2.exp)>=nb2.m){
		return true;
	}
	return false;
}

bool operator<(const LSN& nb1, const LSN& nb2) {
	if (nb1.exp<nb2.exp or (nb1.exp==nb2.exp and nb1.m<nb2.m)){		// Else if the exp are the same but m1<m2.
		return true;
	}
	return false;
}

bool operator<(const LSN& nb1, const long double& nb2) {
	if (nb1.m<nb2/pow(10, nb1.exp)){
		return true;
	}
	return false;
}

bool operator<(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10, nb2.exp)<nb2.m){
		return true;
	}
	return false;
}

bool operator>(const LSN& nb1, const LSN& nb2) {
	if (nb1.exp>nb2.exp or (nb1.exp==nb2.exp and nb1.m>nb2.m)){		// Else if the exp are the same but m1>m2.
		return true;
	}
	return false;
}

bool operator>(const LSN& nb1, const long double& nb2) {
	if (nb1.m>nb2/pow(10, nb1.exp)){
		return true;
	}
	return false;
}

bool operator>(const long double& nb1, const LSN& nb2) {
	if (nb1/pow(10, nb2.exp)>nb2.m){
		return true;
	}
	return false;
}

/*:)
 * It's better to enter the bigger number first I think.
 */
LSN operator+(const LSN& nb1, const LSN& nb2) {
	return {nb1.m+nb2.m/pow(10, nb1.exp-nb2.exp), nb1.exp};
}

LSN operator+(const LSN& nb1, const long double& nb2) {
	return {nb1.m+nb2/pow(10, nb1.exp), nb1.exp};
}

LSN operator+(const long double& nb1, const LSN& nb2) {
	return {nb1+nb2.m/pow(10, 0-nb2.exp), 0};
}
/*:)
 * It's better to enter the bigger number first.
 */
LSN operator-(const LSN& nb1, const LSN& nb2) {
	return {nb1.m-nb2.m/std::pow(10, nb1.exp-nb2.exp), nb1.exp};
}

LSN operator-(const LSN& nb1, const long double& nb2) {
	return {nb1.m-nb2/std::pow(10, nb1.exp-0), nb1.exp};
}

LSN operator-(const long double& nb1, const LSN& nb2) {
	return {nb1-nb2.m/std::pow(10, 0-nb2.exp), 0};
}

LSN operator*(const LSN& nb1, const LSN& nb2) {
	return {nb1.m*nb2.m, nb1.exp+nb2.exp};
}

LSN operator*(const LSN& nb, const long double& k) {
	return {nb.m*k, nb.exp};
}

LSN operator*(const long double& k, const LSN& nb) {
	return {nb.m*k, nb.exp};
}

LSN operator/(const LSN& nb1, const LSN& nb2) {
	return {nb1.m/nb2.m, nb1.exp-nb2.exp};
}

LSN operator/(const LSN& nb, const long double& k) {
	return {nb.m/k, nb.exp};
}

LSN operator/(const long double& k, const LSN& nb) {
	return {nb.m/k, nb.exp};
}



std::string LSN::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="LSN ():";
		mes+=((spread)?"\n" : "");
	}
	mes+=std::to_string(m) + "x10^" + std::to_string(exp);

	return mes;
}

void LSN::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	this->to_string(spread, indent, full_info);
	printf((this->to_string(spread, indent, full_info)).c_str());
}


/*
 * Functions
 */

LSN abs(const LSN& nb) {
	LSN resp{std::abs(nb.m), nb.exp};
	//resp.recal();
	return resp;
}

LSN pow(const LSN& nb, const long int& exp) {
	LSN resp{pow(nb.m, exp), nb.exp*exp};
	resp.recal();
	return resp;
}

/*// Calculate the n root of a number
LSN nrt(LSN& nb, long int exp) {
	//LSN nb2={1, 0};
	for (long int i(0) ; i<nb.exp%exp ; i++)
	{
		nb.m*=nb;
	}
	recal(nb2);
	return *(new LSN{pow(nb.m, exp), nb.exp*exp});
}*/

/*
 * Calculate the square root of a number.
 */

LSN sqrt(const LSN& nb) {
	LSN resp={pow(nb.m, 0.5), nb.exp/2};
	resp.recal();
	return resp;
}




