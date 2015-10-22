/*
 * Ambiente de desenvolvimento: Eclipse
 *      Grupo: T07G02
 *    	 	 David Clemente
 *   	  	 Cristiano Carvalheiro
 */

#include "Interface.h"

int Interface::interfaceHandler(const vector<string> & options, const string titulo)
{
	COORD coord;
	coord.X = 0;

	size_t size = options.size();
	size_t current = 0;
	int pressedkey = 0;
	int dummy = 0;

	system("CLS");

	size_t width = 80 - ((80 - titulo.size()) / 2);

	cout << setw(width) << white << endl << titulo << white << endl << endl << endl;

	for (size_t i = 0; i < size; ++i) {
		if (i == 0) {
			cout << "\t" << red << options[i] << white << endl;
		} else
			cout << "\t" << options[i] << endl;
	}

	while (dummy != '\r') {
		if (_kbhit()) {
			dummy = _getch();
			if (dummy == 224) {
				pressedkey = _getch();

				if (pressedkey == 72 && current > 0) {
					--current;
					coord.Y = 5 + current;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
							coord);
					cout << "\t" << white << options[current + 1] << white
							<< endl;
					coord.Y = 4 + current;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
							coord);
					cout << "\t" << red << options[current] << white << endl;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
							coord);
				}

				else if (pressedkey == 80 && current < (size - 1)) {
					++current;
					coord.Y = 4 + current;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
							coord);
					cout << "\t" << red << options[current] << white << endl;
					coord.Y = 3 + current;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
							coord);
					cout << "\t" << white << options[current - 1] << white
							<< endl;
				}
			}
		}
	}

	return (current + 1);
}

void Interface::carregaFicheiro() {
	ifstream in;

	system("CLS");

	nomeFicheiro =
			leString(
					"\nIntroduza o nome do ficeiro que pretende comprimir(extensao .txt): ");

	nomeFicheiro += ".txt";

	in.open(nomeFicheiro.c_str());

	if (!in.is_open()) {
		in.close();
		cout
				<< "O ficheiro nao existe.\nCorrija esta situacao e tente novamente."
				<< endl << endl;
		nomeFicheiro = "";
		system("PAUSE");
	} else {
		cout
						<< "Ficheiro carregado."
						<< endl << endl;

		compressor = new Programa(nomeFicheiro);

		system("PAUSE");
	}


}

Interface::Interface() {
	nomeFicheiro = "";
}

string Interface::leString(string msg) {
	string tempString = "";

	while (tempString.size() == 0) {
		cout << msg;
		getline(cin, tempString);
		system("CLS");
	}

	return tempString;
}

Programa *Interface::retornaCompressor() const
{
    return compressor;
}

void Interface::modificaCompressor(Programa *compressor)
{
    this->compressor = compressor;
}

void Interface::mostraMenuPrincipal() {

	vector<string> options;
	options.push_back("Carregar Ficheiro");
	options.push_back("Iniciar Compressao");
	options.push_back("Sair");
	string greet = "Main menu";
	int option = 0;


	while (option != 8) {
		option = interfaceHandler(options, greet);

		switch (option) {
		case 1:
			carregaFicheiro();
			break;
		case 2:
			fazCompressao();
			break;
		case 3:
			system("CLS");
			int option = 0;

			vector<string> opt;
			opt.push_back("Sim");
			opt.push_back("Nao");

			option = interfaceHandler(opt, "Tem a certeza que pretende sair da aplicacao?");
			if (option == 1)
				return;
			else
				option = 0;
			break;
		};
	}
}

void Interface::fazCompressao() {
	system("CLS");

	if (nomeFicheiro.size() == 0) {
		cout << "Nenhum ficheiro carregado!\n\n";
		system("PAUSE");
		return;
	}

	cout << "\n\t A comprimir....\n\n";

	cout << "\n\t Algoritmo de Huffman(1/2)\n";

	compressor->algoritmoHuffman();

	cout << "\n\t Algoritmo LZW(2/2)\n\n";

	compressor->algotitmoLZW(nomeFicheiro, 0);
	compressor->algotitmoLZW(nomeFicheiro, 1);

	cout << "\t Comprimido!\n\n";

	system("PAUSE");

	showResults();

	system("PAUSE");
}

void Interface::showResults() {

	system("CLS");

	int tamanho = 0, tamanhoHuffman = 0, tamanhoLZW = 0,
			tamanhoHuffmanDes = 0, tamanhoLZWDes = 0;

	tamanho = compressor->retornaTamanhoFicheiro(nomeFicheiro);
	tamanhoHuffman = compressor->retornaTamanhoFicheiro("HuffmanComprimido.txt");
	tamanhoHuffmanDes = compressor->retornaTamanhoFicheiro("HuffmanDescomprimido.txt");
	tamanhoLZW = compressor->retornaTamanhoFicheiro("ficheiro.bin");
	tamanhoLZWDes = compressor->retornaTamanhoFicheiro("ficheiro.txt");

	cout << "\n\t\tResultados\n\n";

	cout << "\tFicheiro \"" << this->nomeFicheiro << "\" nao comprimido: " << tamanho << " bytes.";

	cout << "\n\n\tAlgoritmo de Huffman\n";
	cout << "\tFicheiro comprimido: " << tamanhoHuffman << " bytes";
	cout << "\n\tRacio de compressao: " << ((tamanhoHuffman * 100) / tamanho) << "%";
	cout << "\n\tFicheiro descomprimido: " << tamanhoHuffmanDes << " bytes";

	cout << "\n\n\tAlgoritmo de Lempel-Ziv-Welch(LZW)\n";
	cout << "\tFicheiro comprimido: " << tamanhoLZW << " bytes";
	cout << "\n\tRacio de compressao: " << ((tamanhoLZW * 100) / tamanho) << "%";
	cout << "\n\tFicheiro descomprimido: " << tamanhoLZWDes << " bytes\n\n";
}
