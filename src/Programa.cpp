/*
 * Programa.cpp
 *
 *  Created on: 28 de Mai de 2012
 *      Author:
 */

#include "Programa.h"

Programa::Programa(string f) {
	ficheiro = f;

	ifstream entrada;
	string leitura;

	entrada.open(ficheiro.c_str());

	while(!entrada.eof()) {
		getline(entrada, leitura);
		leituraFicheiro.push_back(leitura);
	}

	entrada.close();
}

int Programa::retornaTamanhoFicheiro(string ficheiro) {
	FILE * pFile;
	long size;

	pFile = fopen(ficheiro.c_str(), "rb");
	if (pFile == NULL) {
		perror("Erro a abrir ficheiro\n\n");
		system("PAUSE");
		return 0;
	} else {
		fseek(pFile, 0, SEEK_END);
		size = ftell(pFile);
		fclose(pFile);
	}

	return size;
}

void Programa::algoritmoHuffman() {

	Huffman h;
	string p1 = ficheiro;
	string p2 = "HuffmanComprimido.txt";
	bool p3 = false;
	string p4 = "HuffmanDescomprimido.txt";

	h.comprimir(p1, p2, p3);
	h.descomprimir(p2, p4, p3);
}

// Comprime uma string numa lista de simbolos, o resultado e escrito no iterador res que e devolvido no final
template <typename Iterator>
Iterator Programa::comprimirLZW(const std::string &original, Iterator res)
{
	//constroi o dicionario de caracteres
	int dicioTam = 256;
	std::map<std::string,int> dicionario;
	for (int i = 0; i < 256; i++)
	{
		dicionario[std::string(1, i)] = i;
	}
	std::string w;
	for (std::string::const_iterator it = original.begin(); it != original.end(); ++it)
	{
		char c = *it;
		std::string wc = w + c;
		//se já existir sequencia igual no dicionario
		if (dicionario.count(wc))
		{
			w = wc;
		}
		//se não existir adiciona
		else
		{
			*res++ = dicionario[w];
			// Adiciona a nova sequencia wc ao dicionario
			dicionario[wc] = dicioTam++;
			w = std::string(1, c);
		}
	}
	if (!w.empty())
	{
		*res++ = dicionario[w];
	}
	return res;
}

// Descomprime uma lista de simbolos para uma string
template <typename Iterator>
std::string Programa::descomprimirLZW(Iterator begin, Iterator end)
{
	//constroi o dicionario
	int dicioTam = 256;
	std::map<int,std::string> dicionario;
	for (int i = 0; i < 256; i++)
	{
		dicionario[i] = std::string(1, i);
	}
	std::string w(1, *begin++);
	std::string res = w;
	std::string entry;
	for ( ; begin != end; begin++)
	{
		int k = *begin;
		//verifica se o dicionário já contêm essa sequência
		if (dicionario.count(k))
		{
			entry = dicionario[k];
		}
		else if (k == dicioTam)
		{
			entry = w + w[0];
		}
		//Avisa se o ficheiro tiver sido mal comprimido
		else
		{
			throw "Mal comprimido!";
		}

		res += entry;

		//adiciona o w+entry[0] para o dicionario
		dicionario[dicioTam++] = w + entry[0];
		w = entry;
	}
	return res;
}

void Programa::algotitmoLZW(string ficheiro, int tipo)
{
	if(tipo == 0)
	{

		for(int i=0; i<leituraFicheiro.size();i++)
		{
			comprimirLZW(leituraFicheiro[i], std::back_inserter(vectordeCompressao));
		}
		ofstream out("ficheiro.bin", ios::out | ios::binary);
		ifstream::pos_type tam=vectordeCompressao.size();
		char * memblock;
		if (out.is_open())
		{
			memblock = new char[tam];
			for(int j=0; j<tam; j++)
			{
				memblock[j]=vectordeCompressao[j];
			}
			out.write(memblock, tam);
			out.close();
		}
	}
	else
	{
		string descomprimido = descomprimirLZW(vectordeCompressao.begin(), vectordeCompressao.end());
		ofstream out("ficheiro.txt", ios::out);
		if (out.is_open())
		{
			out << descomprimido;
			out.close();
		}
		vectordeCompressao.clear();
	}
}

