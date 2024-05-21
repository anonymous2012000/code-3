
/*
This test checks if a polynomial of degree 1 divides a polynomial of degree 3d+1 (where often d=100)
It includes (1) various sizes of hash tables where each hash table contains a polynomial and
(2) two different field sizes: 64 and 128 bits.
*/
//*********************************************************************
#include <iostream>
#include "gmp.h"
#include <unordered_map>
#include <gmpxx.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <assert.h>
#include <time.h>
#include <bitset>
#include <vector>
#include <NTL/ZZ.h>
#include <NTL/ZZXFactoring.h>
#include <NTL/ZZ_pXFactoring.h>
#include <NTL/ZZ_pEX.h>
#include <NTL/RR.h>
#include <NTL/tools.h>
#include <NTL/vec_ZZVec.h>
#include <NTL/fileio.h>
#include <NTL/FacVec.h>
#include <NTL/new.h>
using namespace NTL;
using namespace std;
typedef unsigned char byte;
//#include "assert.h"
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <vector>
using namespace NTL;
// Function to convert a vector of ZZ_p coefficients to a ZZ_pX polynomial
ZZ_pX vectorToPolynomial(const vector<ZZ_p>& coeffs) {
    ZZ_pX poly;
    for (long i = 0; i < coeffs.size(); i++) {
        SetCoeff(poly, i, coeffs[i]);
    }
    return poly;
}

// Function to generate a vector of random ZZ_p coefficients with 128-bit values
vector<ZZ_p> generateRandomCoeffs(long degree) {
    vector<ZZ_p> coeffs(degree + 1);
    for (long i = 0; i <= degree; i++) {
        ZZ random_coeff = RandomBits_ZZ(128); // Generate 128-bit random ZZ
        coeffs[i] = to_ZZ_p(random_coeff);    // Convert ZZ to ZZ_p
    }
    return coeffs;
}

int main() {
    // Set the modulus for the finite field (example: modulus 7)
    ZZ p;
    //p = conv<ZZ>("247742461804815734743746154725192129101");// 128-bit-- uncomment this and comment out the next line if the field size should be 128 bits
    p = conv<ZZ>("18446744073709551557");// 64-bit
    ZZ_p::init(p);
    double start;
    double end;
    double diff = 0;
    float count = 0;
    float count_expr = 0;
    int number_of_experiments = 100;
    // Set the total number of bins (or number of polynomilas) in a hash table
    vector<int> h={40, 163,	655, 2621, 10485, 41943};
    // Set the degrees of the polynomials
    long degree_f = 301; // Degree of the polynomial f(x)// degree of each bin  deg = 3d+1, where d = 100-- total numebr of divisions: h
    // where h in the range [40, 41943], when the set crdinalitiy in the range [2^10, 2^20] --- recall  hd = 4c.
    long degree_g = 1; // Degree of the polynomial g(x)
    for(int k = 0; k< h.size(); k++){
      for(int j = 0; j< number_of_experiments; j++){
        for(int i = 0; i < h[k]; i++){
          // Generate random coefficients for the polynomials
          vector<ZZ_p> f_coeffs = generateRandomCoeffs(degree_f);
          vector<ZZ_p> g_coeffs = generateRandomCoeffs(degree_g);
          // Convert vectors to ZZ_pX polynomials
          ZZ_pX f = vectorToPolynomial(f_coeffs);
          ZZ_pX g = vectorToPolynomial(g_coeffs);
          ZZ_pX q, r;
          start = 0;
          start = clock();
          // Perform polynomial division
          DivRem(q, r, f, g);
          end = 0;
      		end = clock();
          diff = 0;
      		diff = end - start;
      		count += diff/(double) CLOCKS_PER_SEC;
          // Check if remainder is zero
          bool is_divisible = (r == 0);
          // Uncomment the following 5 lines to get the Output results
          //cout << "Polynomial f(x): " << f << endl;
          //cout << "Polynomial g(x): " << g << endl;
          //cout << "Quotient: " << q << endl;
          //cout << "Remainder: " << r << endl;
          //cout << "Is divisible: " << (is_divisible ? "Yes" : "No") << endl;
        }
        count_expr += count;
        count = 0;
      }
      cout<<"\n=========\n"<<endl;
      cout<<"\n\n Average time for h["<<k <<"]: "<<h[k]<<" is :"<<count_expr/number_of_experiments<<endl;
      cout<<"\n=========\n"<<endl;

    }
    return 0;
  }

//comment out the above main and uncomment the below main if you want to test if DivRem can detect when a polynoimal ** does devide ** antoher.
//int main() {
    /////
    // ZZ p;
    // p = conv<ZZ>("247742461804815734743746154725192129101");
    // ZZ_p::init(p);
    // // Define coefficients for g(x) = x - 2
    // vector<ZZ_p> g_coeffs = {ZZ_p(-2), ZZ_p(1)};
    //
    // // Define coefficients for h(x) = x^2 + 3x + 5
    // vector<ZZ_p> h_coeffs = {ZZ_p(5), ZZ_p(3), ZZ_p(1)};
    // // Convert vectors to ZZ_pX polynomials
    // ZZ_pX g = vectorToPolynomial(g_coeffs);
    // ZZ_pX h = vectorToPolynomial(h_coeffs);
    //
    // // Compute f(x) = g(x) * h(x)
    // ZZ_pX f = g * h;
    //
    // // Perform polynomial division
    // ZZ_pX q, r;
    // DivRem(q, r, f, g);
    //
    // // Check if remainder is zero
    // bool is_divisible = (r == 0);
    //
    // // Output results
    // cout << "Polynomial f(x): " << f << endl;
    // cout << "Polynomial g(x): " << g << endl;
    // cout << "Quotient: " << q << endl;
    // cout << "Remainder: " << r << endl;
    // cout << "Is divisible: " << (is_divisible ? "Yes" : "No") << endl;
    // return 0;
  //}


//**********************************************************************
//g++   test2.cpp  -o test2  -lntl -lgmpxx -lgmp -std=c++11
