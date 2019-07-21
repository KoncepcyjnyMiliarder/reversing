#pragma once
#include <Windows.h>
#include <deque>
#include <string>
#include <fstream>

class BlockingGUI
{
public:
	void Spawn(HINSTANCE hInst);
private:

	struct GUIState
	{
		GUIState(HWND hWndDlg)
			:hWndDlg(hWndDlg) {}
		void HandleDrop(const wchar_t* filename);
		void AddLogLine(const std::string& text);
		void ParseItems(std::fstream& file);
		void ParseSkills(std::fstream& file);
	private:
		std::string log;
		HWND hWndDlg;
	};

	static int __stdcall DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
	
};




