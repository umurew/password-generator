#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <stdio.h>
#include <sstream>

using namespace std;

string toUpperCase(string inputString) {
	char* char_array = new char[inputString.length() + 1];
	char_array[inputString.length()] = '\0';

	for (int i = 0; i < inputString.length(); i++) {
		char_array[i] = inputString[i] - 32;
	}

	return char_array;
}

string getOSInformation(string inputString)
{
	string public_osName;
	string public_osVersionWithBuild;
	string public_osArthitecture;
	string combined;

	#ifdef _WIN32 || _WIN64
		public_osName = "Windows ";
	#elif __APPLE__ || __MACH__
		public_osName = "MacOS ";
	#elif __linux__
		public_osName = "Linux ";
	#elif __FreeBSD__
		public_osName = "FreeBSD ";
	#elif __unix || __unix__
		public_osName = "Unix ";
	#else
		public_osName = "Unkwnown OS ";
	#endif

		DWORD dwVersion = 0;
		DWORD dwMajorVersion = 0;
		DWORD dwMinorVersion = 0;
		DWORD dwBuild = 0;

		dwVersion = ::GetVersion();

		dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
		dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

		if (dwVersion < 0x80000000)
			dwBuild = (DWORD)(HIWORD(dwVersion));

		ostringstream stream;

		stream << dwMajorVersion;
		public_osVersionWithBuild += stream.str();

		public_osVersionWithBuild.append(".");

		stream << dwMinorVersion;
		public_osVersionWithBuild += stream.str();

		public_osVersionWithBuild.append(" (Build ");

		stream << dwBuild;
		public_osVersionWithBuild += stream.str();

		public_osVersionWithBuild.append(") ");

		combined = inputString;
		combined.append(public_osName);
		combined.append(public_osVersionWithBuild);
		combined.append("x32");

		return combined;
}

string generatePassword(int length, bool includeSymbols, bool includeUppercase, bool includeNumerals) {
	const string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
	const string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const string symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";
	const string numerals = "0123456789";

	string password;
	string allChars = lowercaseChars;

	if (includeUppercase)
		allChars += uppercaseChars;

	if (includeSymbols)
		allChars += symbols;

	if (includeNumerals)
		allChars += numerals;

	random_shuffle(allChars.begin(), allChars.end());

	char lastChar = '\0';

	for (int i = 0; i < length; ++i) {
		char randomChar;
		do {
			randomChar = allChars[rand() % allChars.length()];
		} while (randomChar == lastChar);

		password += randomChar;
		lastChar = randomChar;
	}

	return password;
}

int main() {
	int passwordLength;
	bool includeSymbols;
	bool includeUppercase;
	bool includeNumerals;

	string temporaryString;
	string end_title = getOSInformation("Password Generator ");

	SetConsoleTitleA(end_title.c_str());
	cout << "Welcome to password generator wizard!\nPlease use [Y/N] when answering questions, otherwise answer will be ignored." << endl << endl;
	cout << "ChatGPT is used to assist programming.\nNo copyrights reserved. All free to use." << endl << endl;

	cout << "Enter password lenght: ";
	while (!(cin >> passwordLength))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try numerical instead: " << endl;
	}

	cin.clear();

	cout << "Include symbols in password? [Y/N]: ";
	cin >> temporaryString;

	if (toUpperCase(temporaryString) == "Y" || toUpperCase(temporaryString) == "y") {
		includeSymbols = true;
	}
	else
	{
		includeSymbols = false;
	}

	cin.clear();

	cout << "Include uppercase letters in password? [Y/N]: ";
	cin >> temporaryString;

	if (toUpperCase(temporaryString) == "Y" || toUpperCase(temporaryString) == "y") {
		includeUppercase = true;
	}
	else
	{
		includeUppercase = false;
	}

	cin.clear();

	cout << "Include numerals in password? [Y/N]: ";
	cin >> temporaryString;

	if (toUpperCase(temporaryString) == "Y" || toUpperCase(temporaryString) == "y") {
		includeNumerals = true;
	}
	else
	{
		includeNumerals = false;
	}

	srand(static_cast<unsigned>(time(0)));

	string generatedPassword = generatePassword(passwordLength, includeSymbols, includeUppercase, includeNumerals);

	cout << endl << endl << "Generated password: " << generatedPassword;
	cout << endl << endl << "15 seconds remaining to close this window automatically.";
	Sleep(15000);

	return 0;
}