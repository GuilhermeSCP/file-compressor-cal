/*
 * Ambiente de desenvolvimento: Eclipse
 *      Grupo: T07G02
 *    	 	 David Clemente
 *   	  	 Cristiano Carvalheiro
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<string>
#include<iomanip> //for width()
#include<cctype> //for sprintf()

using namespace std;

class Huffman {

public:

	void esc_huf(unsigned char i, ofstream & outfile);
	unsigned char le_huf(ifstream & infile);
	void comprimir(string ifile, string ofile, bool verbose);
	void descomprimir(string ifile, string ofile, bool verbose);

};

#endif
