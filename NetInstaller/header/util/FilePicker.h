#pragma once
#if !defined _FILEPICKER
#define _FILEPICKER

#include "../../stdafx.h"

class FilePicker {

	protected:

		const int BUFFER_SIZE = 1024;

		HWND owner;
		std::string title;
		LPCWSTR typeFilter;

		DWORD flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
		OPENFILENAME *newOPENFILENAME();
		void cleanBuffer();

	public:

		TCHAR *buffer;

		FilePicker(HWND owner);
		FilePicker(HWND owner, std::string title);

		std::string getFilePath();

		FilePicker *setTitle(std::string title);
		FilePicker *seTypeFilter(LPCWSTR typeFilter);
};

#endif