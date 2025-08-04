#pragma warning(disable : 4996)

#include <iostream>
#include <array>
#include <cmath>
#include <ctime>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
using namespace std;
struct stClients {
	string AccountNumber;
	string PIN;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};
short TransactionScreen() {
	short Num = 0;
	system("cls");
	cout << "======================================\n";
	cout << "\t    Main Menu Screen\n";
	cout << "======================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "======================================\n";
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Num;
	return Num;
}
const string ClientFilename = "Clients.txt";
bool FindClientByAccountNumber(string AccountNumber,vector<stClients> vClients,stClients& sClient) {
	for (stClients& C : vClients) {
		if (C.AccountNumber == AccountNumber)
		{
			sClient = C;
			return true;
		}
	}
	return false;
}
bool IsClientExist(string ClientID) {
	stClients sCLient;
	vector<stClients> vClients;
	if (FindClientByAccountNumber(ClientID,vClients,sCLient))
	{
		return true;
	}
	else {
		return false;
	}
}
void ShowClientCard(stClients sClient) {
	cout << "\n--------------------------------------------\n";
	cout << "Account Number " << setw(5) << right << ": " << sClient.AccountNumber;
	cout << "\nPIN Code" << setw(12) << right << " : " << sClient.PIN;
	cout << "\nName" << setw(16) << right << " : " << sClient.Name;
	cout << "\nPhone Number" << setw(8) << right << " : " << sClient.PhoneNumber;
	cout << "\nAccount Balance" << setw(5) << right << " : " << sClient.AccountBalance;
	cout << "\n--------------------------------------------\n";
}
string FindClientForm() {
	string Target;
	cout << "Please Enter Account Number: ";
	cin >> Target;

	return Target;
}
stClients FillClientInfo(stClients &C, bool ChangeID = true) {
	
	if (ChangeID)
	{
	cout << "Account Number: ";
	getline(cin >> ws, C.AccountNumber);
	}
	while (IsClientExist(C.AccountNumber));
	{
		cout << "Client Account Number Exist, Please Enter Another ID: \n";
		cout << "\n\nAccount Number: ";
		getline(cin >> ws, C.AccountNumber);
	}
	cout << "Client PIN: ";
	getline(cin >> ws, C.PIN);
	cout << "Client Name: ";
	getline(cin, C.Name);
	cout << "Phone Number: ";
	getline(cin, C.PhoneNumber);
	cout << "Account Balance: ";
	cin >> C.AccountBalance;

	return C;
}
bool FindClientScrren(vector<stClients> vClients) {
	stClients sClient;
	string Target = FindClientForm();

	if (FindClientByAccountNumber(Target, vClients, sClient))
	{
		ShowClientCard(sClient);
		return true;
	}
	else cout << "We Couldn't Find (" << Target << ") In Client Data" << endl;
	return false;
}
vector<string> splitString(string S1, string Delim = "#//#") {
	vector<string> vString;
	string sWord;
	short pos = 0;

	while ((pos = S1.find(Delim)) != string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
vector<stClients> ConvertRawStringToClientData() {
	fstream MyFile;
	vector<string> RawClientData;
	vector<stClients> vClients;
	MyFile.open(ClientFilename, ios::in);
	stClients C;
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line)) {
	        RawClientData = splitString(Line);
	        C.AccountNumber = RawClientData[0];
	        C.PIN = RawClientData[1];
	        C.Name = RawClientData[2];
	        C.PhoneNumber = RawClientData[3];
	        C.AccountBalance = stod(RawClientData[4]);
			vClients.push_back(C);
		}
	MyFile.close();
	}

	return vClients;
}
string ConvertRecordToLine(stClients sClient,string Delim = "#//#") {
	string Line = "";
	Line += sClient.AccountNumber + Delim;
	Line += sClient.PIN + Delim;
	Line += sClient.Name + Delim;
	Line += sClient.PhoneNumber + Delim;
	Line += to_string(sClient.AccountBalance);

	return Line;
}
void ConvertRecordToFile(stClients sClient, string Filename = ClientFilename) {
	fstream MyFile;
	string DataLine;
	MyFile.open(Filename,ios::out | ios::app);
	if (MyFile.is_open())
	{
		DataLine = ConvertRecordToLine(sClient);
		MyFile << DataLine << endl;
		MyFile.close();
	}
}
void AddNewClient() {
	stClients sClient;
	FillClientInfo(sClient);
	ConvertRecordToFile(sClient);
};
void AddClients() {
	char AddMore = 'Y';
	do
	{
		AddNewClient();
		cout << "do you want to add more clients? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void ShowAllClientsData(vector<stClients> vClient) {
	cout << "\t\t Client List (" << vClient.size() << ") Client(s).\n";
	cout << "----------------------------------------------------------------------------------------------\n";
	cout << "| " << setw(15) << left << "Account Number" << " | " << setw(10) << left << "PIN Code" << " | " << setw(30) << left << " Client Name" << " | " << setw(12) << left << "Phone" << " | " << setw(12) << left << "Balance ";
	cout << "\n--------------------------------------------------------------------------------------------\n";
	for (stClients& C : vClient) {
		cout << "| " << setw(15) << left << C.AccountNumber << " | " << setw(10) << left << C.PIN << " | " << setw(30) << left << C.Name << " | " << setw(12) << left << C.PhoneNumber << " | " << setw(10) << left << C.AccountBalance << endl;
	}
}
void StartMainMenu() {
	system("cls");
	cout << "======================================\n";
	cout << "\t    Main Menu Screen\n";
	cout << "======================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit Program.\n";
	cout << "======================================\n";
}
void ScreenScaller(string ScrrenObjective) {
	cout << "\n-----------------------------------\n";
	cout << "\t" << ScrrenObjective;
	cout << "\n-----------------------------------\n\n";


}
bool MarkDeleteClient(string AccountNumber,vector<stClients>& vClient) {
	for (stClients& C : vClient) {
		if (AccountNumber == C.AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool SaveClientDataToFileAfterDeletion(vector<stClients>& vClient) {
	fstream MyFile;
	MyFile.open(ClientFilename, ios::out);

	if (MyFile.is_open())
	{
		string Line;
		for (stClients& C : vClient) {
			if (C.MarkForDelete == false)
			{
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
		return true;
	}
	return false;
}
bool DeleteClientByAccountNumber(vector<stClients>& vClient) {
	stClients sClient;
	string ClientID = FindClientForm();
	char IsSure = 'n';
	if (FindClientByAccountNumber(ClientID,vClient, sClient))
	{
		ShowClientCard(sClient);
		cout << "\nAre you sure you want to delete this Client? y/n: ";
		cin >> IsSure;
		if (toupper(IsSure) == 'Y')
		{
		MarkDeleteClient(ClientID, vClient);
		SaveClientDataToFileAfterDeletion(vClient);

		vClient = ConvertRawStringToClientData();

		return true;
		}
	}
	return false;
}
bool UpdateClientByAccountNumber(vector<stClients>& vClient) {
	char IsSure = 'n';
	stClients sClient;
	string ClientID = FindClientForm();
	if (FindClientByAccountNumber(ClientID,vClient,sClient))
	{
		ShowClientCard(sClient);
		cout << "\nAre you sure You want to update this client? y/n: ";
		cin >> IsSure;
		if (toupper(IsSure) == 'Y')
		{
	for (stClients& C : vClient) {
		if (C.AccountNumber == ClientID) {
			FillClientInfo(C,false);
			break;
		}
	}
	SaveClientDataToFileAfterDeletion(vClient);
	vClient = ConvertRawStringToClientData();
	return true;
	    }
	}
	return false;
}
bool DespositMenu(vector<stClients>& vClients) {
	int Num = 0;
	char accept = 'N';
	stClients sClient;
	while (FindClientByAccountNumber(FindClientForm(), vClients, sClient))
	{
		ShowClientCard(sClient);
		cout << "\nPlease Enter Deposit amount?";
		cin >> Num;
		cout << "Are you sure you want perform this transaction? y/n ?";
		cin >> accept;
		if (toupper(accept) == 'Y') {
			for (stClients& C : vClients) {
				if (C.AccountNumber == sClient.AccountNumber)
				{
					C.AccountBalance += Num;
				}
			}
			SaveClientDataToFileAfterDeletion(vClients);
			cout << "Client Balance changed" << endl;
			return true;
		}
		else
			return false;
	}

}
bool WithdrawMenu(vector<stClients>& vClients) {
	int Num = 0;
	char accept = 'N';
	stClients sClient;
	while (FindClientByAccountNumber(FindClientForm(), vClients, sClient))
	{
		ShowClientCard(sClient);
		cout << "\nPlease Enter Withdraw amount?";
		cin >> Num;
		cout << "Are you sure you want perform this transaction? y/n ?";
		cin >> accept;
		if (toupper(accept) == 'Y') {
			for (stClients& C : vClients) {
				if (C.AccountNumber == sClient.AccountNumber)
				{
					while (Num > C.AccountBalance)
					{
						cout << "\n Amount Exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
						cout << "Please Enter Another amount: ";
						cin >> Num;
					}
					C.AccountBalance -= Num;
				}
			}
			SaveClientDataToFileAfterDeletion(vClients);
			cout << "Client Balance changed" << endl;
			return true;
		}
		else
			return false;
	}

}
void TotalBalance(vector<stClients> vClients) {
	double TotalAmount = 0;
	for (stClients C : vClients) {
		TotalAmount += C.AccountBalance;
	}
	ShowAllClientsData(vClients);
	cout << "\n\t\t\t Total Balances = " << TotalAmount << endl;
}
short TransactionScreenNavigator(short Num, vector<stClients> vClients) {
	system("cls");
	switch (Num)
	{
	case 1:
		ScreenScaller("Deposit Screen");
		DespositMenu(vClients);
		break;
	case 2:
		ScreenScaller("Withdraw Screen");
		WithdrawMenu(vClients);
		break;
	case 3:
		TotalBalance(vClients);
		break;
	case 4:
		return 0;
	}
	
}
short ScreenNavigator() {
	vector<stClients> vClient = ConvertRawStringToClientData();
	short Navi = 0;
	cout << "\nWelcome To Our Banking System!!\nPlease Choose In [1 To 6] To navigate the System: ";
	cin >> Navi;
	system("cls");
	switch (Navi)
	{
	case 1:
		ShowAllClientsData(vClient);
		break;
	case 2 :
		AddClients();
		break;
	case 3:
		ScreenScaller("Delete Client Screen");
		DeleteClientByAccountNumber(vClient);
		break;
	case 4:
		ScreenScaller("Update Client Screen");
		UpdateClientByAccountNumber(vClient);
		break;
	case 5:
		ScreenScaller("Find Client Screen");
		FindClientScrren(vClient);
		break;
	case 6:
		TransactionScreenNavigator(TransactionScreen(),vClient);
		break;
	case 7:
		return 7;
	}
}
void BankingSystem() {
	
	short InMenu = 6;

	do
	{
		
		StartMainMenu();
		
		
		InMenu = ScreenNavigator();
		if (InMenu != 6)
		{
		cout << "\n\nPress any key to go back to Main Menu...";
		system("pause>0");
		}
	} while (toupper(InMenu) != 6);
}

int main() {
	BankingSystem();
	
	return 0;
}








