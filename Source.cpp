#include <iostream>
#include <algorithm>    // std::transform
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

// Functions Declarations
void print_header();
void setup_filenames(int& number_of_files, string*& filenames); // Using Call-By-Reference Method
void menu(int& choice, string& keyword, string& replace_of_keyword, int& number_of_files, string*& filenames); // Using Call-By-Reference Method
string get_file_contents(string filename);
bool contents_has_keyword(string file_contents, string keyword);
void find_and_print_colored(string filename, string keyword, int choice);
int find_and_replace(string filename, string keyword, string replace_of_keyword);

int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);	// Run As Fullscreen Console

	int choice, number_of_changes, number_of_files;
	string keyword, replace_of_keyword, file_contents;
	string* filenames;
/**/
	print_header();
	setup_filenames(number_of_files, filenames);

	while (true) {
		menu(choice, keyword, replace_of_keyword, number_of_files, filenames);
		for (int i = 0; i < number_of_files; i++) 
		{
			string filename = filenames[i];
			file_contents = get_file_contents(filename);
			if (contents_has_keyword(file_contents, keyword)) 
			{
				cout << "--" << "-------------------------------------------------------------------------------------------------------------------------------------" << "--" << endl;
				cout << "--" << " # Found Keyword: '" << keyword << "' in the file: " << filename << endl;
				cout << "--" << "-------------------------------------------------------------------------------------------------------------------------------------" << "--" << endl;
				if (choice == 1) 
				{
					find_and_print_colored(filename, keyword, choice);
				}
				else if (choice == 2) 
				{
					number_of_changes = find_and_replace(filename, keyword, replace_of_keyword); // for modifiy keyword with replace_of_keyword
					find_and_print_colored(filename, replace_of_keyword, choice);
				}
				else if (choice == 3) 
				{
					find_and_print_colored(filename, keyword, choice);
					number_of_changes = find_and_replace(filename, keyword, replace_of_keyword); // for delete keyword the replace_of_keyword = ""
/**/
				}
				if (choice == 2 || choice == 3) 
				{
					cout << "--" << "-------------------------------------------------------------------------------------------------------------------------------------" << "--" << endl;
					cout << "--" << " " << number_of_changes << " changes were made" << endl;
				}
				cout << "--" << "-------------------------------------------------------------------------------------------------------------------------------------" << "--" << endl;
			}
		}
		system("PAUSE");
/**/
	}

	return 0;
}

// Functions Definitions
void print_header() {
	cout << "==" << "=====================================================================================================================================" << "==" << endl;
	cout << "==" << "====================================================== Mini Search Application ======================================================" << "==" << endl;
	cout << "==" << "=====================================================================================================================================" << "==" << endl;
	cout << "==" << " # This project aims to search on some keywords in a group of documents and return the name of the document that contains this word. " << "==" << endl;
	cout << "==" << " # The project also has options to delete and modify the selected word.                                                              " << "==" << endl;
	cout << "==" << " # (Bouns) The project also has options to Search for a given keyword and return the set of documents containing the keyword.        " << "==" << endl;
	cout << "==" << "=====================================================================================================================================" << "==" << endl;
}

void setup_filenames(int& number_of_files, string*& filenames) 
{
	cout << "==" << "========================================" << "==" << endl;
	cout << "==" << "====== Setup FileNames To Be Used ======" << "==" << endl;
	cout << "==" << "========================================" << "==" << endl;
	cout << "==" << " Enter Number Of Files: ";	
	cin >> number_of_files;
	while (!cin.good()) 
	{
		//something went wrong, we reset the buffer's state to good
		cin.clear();
		cin.ignore();
		cout << "==" << " Please Choose A Correct Choice         " << "==" << endl;
		cout << "==" << " Enter Number Of Files: ";	
		cin >> number_of_files;
	}
	cout << "==" << " Enter FileNames One By One:            " << "==" << endl;
	cout << "==" << " (Note) FileNames Can't Have Spaces     " << "==" << endl;
	filenames = new string[number_of_files];
/**/
	for (int i = 0; i < number_of_files; i++) 
	{ 
		cout << "==" << i + 1 << "- ";	
		cin >> filenames[i]; 
	}
	cout << "==" << "========================================" << "==" << endl;
}

void menu(int& choice, string& keyword, string& replace_of_keyword, int& number_of_files, string*& filenames) 
{
	system("CLS");
/**/
	print_header();
/**/
	choice = 0;
	keyword = "";
	replace_of_keyword = "";
	cout << "==" << "========================================" << "==" << endl;
	cout << "==" << " Press                                  " << "==" << endl;
	cout << "==" << " 1- Search for Keyword                  " << "==" << endl;
	cout << "==" << " 2- Modify for Keyword                  " << "==" << endl;
	cout << "==" << " 3- Delete for Keyword                  " << "==" << endl;
	cout << "==" << " 4- Re-Setup FileNames To Be Used       " << "==" << endl;
	cout << "==" << " 5- Close The Application               " << "==" << endl;
	cout << "==" << "========================================" << "==" << endl;

	while (true) 
	{
		cout << "==" << " ";   
		cin >> choice;
		if (cin.good()) 
/**/
		{
			if (choice == 1 || choice == 2 || choice == 3) 
			{ 
			cout << "==" << " Enter The Keyword: ";     
			cin >> keyword; 
			}
			else if (choice == 4) 
			{
				setup_filenames(number_of_files, filenames);
				return menu(choice, keyword, replace_of_keyword, number_of_files, filenames);
/**/
			}
			else if (choice == 5) 
			{ 
			exit(0);
			}
			else 
			{ 
			  cout << "==" << " Please Choose A Correct Choice         " << "==" << endl;    
			continue;
/**/
			}
			if (choice == 2) 
			{
				cout << "==" << " Replace It With:   ";
				cin >> replace_of_keyword;
			}
		}
		else
		{
			//something went wrong, we reset the buffer's state to good
			cin.clear();
			cin.ignore();
			cout << "==" << " Please Choose A Correct Choice         " << "==" << endl;
			continue;
		}
		break;
	}
	cout << "==" << "========================================" << "==" << endl;
}

string get_file_contents(string filename) 
{
	ifstream filein(filename);
	string contents;

	if (!filein.fail()) 
	{
		// Here is one way to read the whole file
		for (char ch; filein.get(ch); contents.push_back(ch)) {}
/**/
		filein.close();
	}
	else 
	{
		cout << "--" << "-------------------------------------------------------------------------------------------------------------------------------------" << "--" << endl;
/**/		cerr << "--" << " File: " << filename << " can not be opened file maybe does not exist" << endl;
		cout << "--" << "-------------------------------------------------------------------------------------------------------------------------------------" << "--" << endl;
	}

	return contents;
}

bool contents_has_keyword(string file_contents, string keyword) 
{
	// Case-Sensitive Solution
	/*
	return (file_contents.find(keyword) != string::npos);
	*/

	// Case-InSensitive Solution
	string file_contents_tolower_copy = file_contents;
	transform(file_contents_tolower_copy.begin(), file_contents_tolower_copy.end(), file_contents_tolower_copy.begin(), tolower);
	transform(keyword.begin(), keyword.end(), keyword.begin(), tolower);
	return (file_contents_tolower_copy.find(keyword) != string::npos);
/**/
}

void find_and_print_colored(string filename, string keyword, int choice) 
{
	// Case-Sensitive Solution
	/*
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	int OldColor = (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) ? csbi.wAttributes : 15;

	string file_contents = get_file_contents(filename);

	// This searches the file for the first occurence of the morn string.
	int old_pos = 0;
	auto pos = file_contents.find(keyword);
	while (pos != string::npos) {
		cout << file_contents.substr(old_pos, pos - old_pos);
		if (choice == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 46);   // 46 for Search
		}
		else if (choice == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // 224 for edit
		}
		else if (choice == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 206); // 206 for delete
		}
		cout << file_contents.substr(pos, keyword.length());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), OldColor);
		old_pos = pos + keyword.length();
		// Continue searching from here.
		pos = file_contents.find(keyword, old_pos);
	}
	cout << file_contents.substr(old_pos);
	cout << endl;
	*/

	// Case-InSensitive Solution
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	int OldColor = (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) ? csbi.wAttributes : 15;
/**/

	string file_contents = get_file_contents(filename);
	string file_contents_tolower_copy = file_contents;
	transform(file_contents_tolower_copy.begin(), file_contents_tolower_copy.end(), file_contents_tolower_copy.begin(), tolower);
	transform(keyword.begin(), keyword.end(), keyword.begin(), tolower);

	// This searches the file for the first occurence of the morn string.
	int old_pos = 0;
	auto pos = file_contents_tolower_copy.find(keyword);
	while (pos != string::npos) 
	{
		cout << file_contents.substr(old_pos, pos - old_pos);
		if (choice == 1) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 46);   // 46 for Search 
		}
		else if (choice == 2) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // 224 for edit
		}
		else if (choice == 3) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 206); // 206 for delete
		}
		cout << file_contents.substr(pos, keyword.length());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), OldColor);
		old_pos = pos + keyword.length();
		// Continue searching from here.
		pos = file_contents_tolower_copy.find(keyword, old_pos);
	}
	cout << file_contents.substr(old_pos);
	cout << endl;
/*all*/
}

int find_and_replace(string filename, string keyword, string replace_of_keyword) 
{
	// Case-Sensitive Solution
	/*
	string file_contents = get_file_contents(filename);
	int number_of_changes = 0;

	// This searches the file for the first occurence of the keyword string.
	auto pos = file_contents.find(keyword);
	while (pos != string::npos) {
		number_of_changes++;
		file_contents.replace(pos, keyword.length(), replace_of_keyword);
		// Continue searching from here.
		pos = file_contents.find(keyword, pos);
	}

	ofstream fileout(filename); // By Default this uses truncate (trunc) mode which means Any contents that existed in the file before it is open are discarded.
	fileout << file_contents;
	fileout.close();

	return number_of_changes;
	*/

	// Case-InSensitive Solution
	string file_contents = get_file_contents(filename);
	string file_contents_tolower_copy = file_contents;
	transform(file_contents_tolower_copy.begin(), file_contents_tolower_copy.end(), file_contents_tolower_copy.begin(), tolower);
	transform(keyword.begin(), keyword.end(), keyword.begin(), tolower);
	int number_of_changes = 0;

	// This searches the file for the first occurence of the keyword string.
	auto pos = file_contents_tolower_copy.find(keyword);
	while (pos != string::npos) 
	{
		number_of_changes++;
		file_contents.replace(pos, keyword.length(), replace_of_keyword);
		file_contents_tolower_copy.replace(pos, keyword.length(), replace_of_keyword);
		// Continue searching from here.
		pos = file_contents_tolower_copy.find(keyword, pos);
	}

	ofstream fileout(filename); // By Default this uses truncate (trunc) mode which means Any contents that existed in the file before it is open are discarded.
	fileout << file_contents;
	fileout.close();
/**/
	return number_of_changes;
}