/*
 * Programa.h
 *
 *  Created on: 28 de Mai de 2012
 *      Author:
 */

#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include "Huffman.h"

#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <map>

using namespace std;

class Programa {
	string ficheiro;
	vector<string> leituraFicheiro;
	vector<int> vectordeCompressao;
public:

	/*
	 * @brief Contrutor basico da classe Programa
	 */
	Programa(string f);

	int retornaTamanhoFicheiro(string ficheiro);

	void algoritmoHuffman();

	template <typename Iterator> Iterator comprimirLZW(const std::string &original, Iterator res);
	template <typename Iterator> std::string descomprimirLZW(Iterator begin, Iterator end);
	void algotitmoLZW(string ficheiro, int tipo);

};

#endif /* PROGRAMA_H_ */
