#pragma once

#if !defined _CONVERSIONS
	#define _CONVERSIONS
	
	#include "../../stdafx.h"

	class Conversions {
		public:
			/*
			Converte de uma std::string para um TCHAR
			*/
			static TCHAR * stringToTCHAR(std::string input);

			/*
			Converte de uma char* para um TCHAR
			*/
			static TCHAR * charToTCHAR(char *input);

			/*
			Converte de uma TCHAR* para um std::string
			*/
			static std::string TCHARToString(TCHAR *input);
	};

#endif