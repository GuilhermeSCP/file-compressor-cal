/*
 * Ambiente de desenvolvimento: Eclipse
 *      Grupo: T07G02
 *    	 	 David Clemente
 *   	  	 Cristiano Carvalheiro
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Cores.h"
#include "Programa.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

class Interface {
	string nomeFicheiro;

	Programa * compressor;

	/*
	 * @brief Funcao que le uma string instroduzida na consola
	 * @return Devolve a string introduzida
	 */
	string leString(string msg);

	/*
	 * @brief Funcao que mostra a interface do menu incial
	 * @param options Vector de strings com as opcoes de escolha a mostrar
	 * @param titulo Titulo a mostrar na interface
	 */
	int interfaceHandler(const vector<string> & options, const string titulo);

	void carregaFicheiro();

	void inciarCompressao();

	void fazCompressao();

	void showResults();

public:

	/*
	 * @brief Contrutor basico da classe Interface
	 */
	Interface();


	/*
	 * @brief Funcao que mostra o menu inicial
	 */
	void mostraMenuPrincipal();

	Programa *retornaCompressor() const;

	void modificaCompressor(Programa *compressor);
};

#endif
