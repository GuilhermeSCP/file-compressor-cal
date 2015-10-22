/*
 * Ambiente de desenvolvimento: Eclipse
 *      Grupo: T07G02
 *    	 	 David Clemente
 *   	  	 Cristiano Carvalheiro
 */

#ifndef CORES_H_
#define CORES_H_

#pragma once
#include <iostream>
#include <windows.h>

/*
 * @brief Funcao que coloca o a letras da consola a azul e o fundo da consola a verde
 */
inline std::ostream& blue(std::ostream &s) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(
			hStdout,
			FOREGROUND_BLUE
					| FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	return s;
}

/*
 * @brief Funcao que coloca o a letras da consola a vermelho e o fundo da consola a verde
 */
inline std::ostream& red(std::ostream &s) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(
			hStdout,
			FOREGROUND_RED
					| FOREGROUND_INTENSITY);
	return s;
}

/*
 * @brief Funcao que coloca o a letras da consola a branco e o fundo da consola a verde
 */
inline std::ostream& white(std::ostream &s) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(
			hStdout,
			FOREGROUND_RED
					| FOREGROUND_GREEN | FOREGROUND_BLUE);
	return s;
}

/*
 * @brief Funcao que coloca o a letras da consola a preto e o fundo da consola a verde
 */
inline std::ostream& black(std::ostream &s) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	return s;
}

struct color {
	color(WORD attribute) :
			m_color(attribute) {
	}
	;
	WORD m_color;
};

template<class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>&
operator<<(std::basic_ostream<_Elem, _Traits>& i, color& c) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, c.m_color);
	return i;
}


#endif
