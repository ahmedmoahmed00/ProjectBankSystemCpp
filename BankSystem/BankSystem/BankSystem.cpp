#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

void BackToTransactionMenue();
struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;

	bool MarketForDelete = false;
};

struct sUeser 
{
	string UserName;
	string Password;
	short permissions = -1;
};

enum eUsersGoToFunction
{
	ListUser = 1, AddNewUsers = 2,
	DeleteUser = 3, UpdateUser = 4,
	FindUser = 5, MainMenue2 = 6,
};

enum eUserPermissions
{
	AccessListUsers = 1, AccessAddNewUser = 2,
	AccessDeleteUser = 4, AccessUpdateUser = 8,
	AccessFindUsers = 16, nTransactionX = 32,
	ManageUsersX = 64
};

enum enMainMenueOption
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient =3,eUpdateClient = 4,
	eFindClient = 5,  Transaction = 6,
	ManageUsers = 7,  eExit = 8
};

enum enTransactions {
	Deposite = 1, WhithDraw = 2,
	TotalBalances = 3, MainMenue = 4
};

const string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";

string UserNameToPermissions = "";
void ShowMainMenue();
void LoginUeser();
vector<sUeser> LoadUserData(string FillNAme);
void ShowManageUsersClientScreen();
string ReadDataName(string HeadCin);

vector <string> SplitString(string Line, string Delim)
{
	vector <string> Splite;
	short pos = 0;
	string Sword;

	while ((pos = Line.find(Delim)) != std::string::npos)
	{
		Sword = Line.substr(0, pos);
		if (Sword != "")
		{
			Splite.push_back(Sword);
		}
		Line.erase(0, pos + Delim.length());
	}
	if (Line != "")
	{
		Splite.push_back(Line);
	}

	return Splite;
}

sClient ConvertLineToRecord(string Line, string Sepretor = "#//#")
{

	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Sepretor);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key To Go Back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

vector <sClient> LoadCleintsDataDFromFile(string FillName)
{
	vector <sClient>vClients;

	fstream Myfile;
	Myfile.open(FillName, ios::in);

	if (Myfile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(Myfile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		Myfile.close();
	}
	return vClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientScreen()
{
	vector <sClient>vClients = LoadCleintsDataDFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client (s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\tNo Clients Available in The System!";
	else

		for (sClient Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}

}

short ReadMainMenueOption(string Message)
{
	cout << Message;
	short choice = 0;
	cin >> choice;
	return choice;
}

string ConverRecordToLine(sClient Client, string Sepretor = "#//#")
{
	string ClientToLine;

	ClientToLine = Client.AccountNumber + Sepretor;
	ClientToLine += Client.PinCode + Sepretor;
	ClientToLine += Client.Name + Sepretor;
	ClientToLine += Client.Phone + Sepretor;
	ClientToLine += to_string(Client.AccountBalance);

	return ClientToLine;
}

void AddDataLineToFile(string FillName, string Line)
{
	fstream Myfile;

	Myfile.open(FillName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << Line << endl;
	}
	Myfile.close();

}
//^^^^^^^^^^^^^
bool ClientExistsByAccountNumber(string AccountNumber, string FillName)
{
	vector <sClient> vClients;
	fstream Myfile;
	Myfile.open(FillName, ios::in);

	if (Myfile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(Myfile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				Myfile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		Myfile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter AccountNumber: ";

	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClint With [" << Client.AccountNumber << "] already exists, Enter another Account Number";
		getline(cin >> ws, Client.AccountNumber);
	}



	cout << "PinCode: ";
	getline(cin, Client.PinCode);

	cout << "Name: ";
	getline(cin, Client.Name);

	cout << "Phone: ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();

	AddDataLineToFile(ClientsFileName, ConverRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'y';
	do
	{
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N ";
		cin >> AddMore;
		if (tolower(AddMore) == 'y')
		{
			system("cls");
		}
	} while (tolower(AddMore) == 'y');
}

void ShowAddNewClientsScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-------------------------------------\n";

	AddNewClients();
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe Following are the client details:\n";
	cout << "-------------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code       : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Number : " << Client.AccountBalance << endl;
	cout << "-------------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient s : vClients)
	{
		if (s.AccountNumber == AccountNumber)
		{
			Client = s;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarketForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClient)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out);

	string DataLine;

	if (Myfile.is_open())
	{
		for (sClient& s : vClient)
		{
			if (s.MarketForDelete == false)
			{
				DataLine = ConverRecordToLine(s);
				Myfile << DataLine << endl;
			}
		}
		Myfile.close();
	}
	return vClient;
}

bool DeleteClientAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre You sure you want Delete This Client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
			SaveClientsDataToFile(ClientsFileName, vClient);

			vClient = LoadCleintsDataDFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\n\nThe Account Number (" << AccountNumber << ") is Not Found\n";
	}
}

string ReadClientAccountNumber()
{
	string AccountNumber;
	cout << "\nPlease Enter AccountNumber? ";
	cin >> AccountNumber;

	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tDelete Clients Screen";
	cout << "\n-------------------------------------\n";

	vector <sClient>vClient = LoadCleintsDataDFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientAccountNumber(AccountNumber, vClient);
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;

}

bool UpdateClientByaAccountNumber(string AccountNumber, vector <sClient>vClient)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre You sure you want Update This Client? y/n ? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClient);
			cout << "\n\nClient Updated SuccessFully.";
			return true;
		}
	}

}

void ShowUpdateClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Clients Screen";
	cout << "\n-------------------------------------\n";

	vector <sClient>vClient = LoadCleintsDataDFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByaAccountNumber(AccountNumber, vClient);
}

void ShowFindClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tFind Clients Screen";
	cout << "\n-------------------------------------\n";

	sClient Client;
	vector <sClient>vClient = LoadCleintsDataDFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient With Account Number [" << AccountNumber << "] is Not Found!";

}

void ShowExitClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tExit Programm Screen";
	cout << "\n-------------------------------------\n";

}

void DepositeClientByaAccountNumber(string AccountNumber, vector <sClient>vClient)
{
	double Balance = 0;
	char YourSure;

	double Deposite = 0;
	cout << "Please Enter Deposite amount?";
	cin >> Deposite;

	cout << "\n\nAre Youe sure you want perform this Transaction? y/n ? ";
	cin >> YourSure;

	if (tolower(YourSure) == 'y')
	{
		for (sClient& S : vClient)
		{
			if (S.AccountNumber == AccountNumber)
			{
				Balance = (S.AccountBalance + Deposite);
				S.AccountBalance = Balance;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClient);
		cout << "\nDone susscfully new Balance is [" << Balance << "]\n";
	}

}

void ShowDepositeClientsScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Deposite Screen";
	cout << "\n-------------------------------------\n";

	sClient Client;
	vector <sClient>vClient = LoadCleintsDataDFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!(FindClientByAccountNumber(AccountNumber, vClient, Client)))
	{
		cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);

	DepositeClientByaAccountNumber(Client.AccountNumber, vClient);
}

bool cheackWithDrawAndBalance(double AccountBalance, double withDraw)
{
	return AccountBalance > withDraw;
}

void WhithDrawClientByaAccountNumber(sClient Client, vector <sClient>vClient)
{
	short Balance = 0;
	char YourSure;
	double withDraw = 0;
	cout << "Please Enter withDraw amount?";
	cin >> withDraw;

	while (!cheackWithDrawAndBalance(Client.AccountBalance, withDraw))
	{
		cout << "\n\nAmount Exceeds The Balance, You Can WithDraw Up To: " << Client.AccountBalance << endl;
		cout << "Please Enter withDraw amount?";
		cin >> withDraw;
	}

	cout << "\n\nAre Youe sure you want perform this Transaction? y/n ? ";
	cin >> YourSure;

	if (tolower(YourSure) == 'y')
	{
		for (sClient& S : vClient)
		{
			if (S.AccountNumber == Client.AccountNumber)
			{
				Balance = S.AccountBalance - withDraw;
				S.AccountBalance = Balance;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClient);
		cout << "\nDone susscfully new Balance is [" << Balance << "]\n";
	}
}

void ShowWhithDrawClientsScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t WhithDraw Screen";
	cout << "\n-------------------------------------\n";

	sClient Client;
	vector <sClient>vClient = LoadCleintsDataDFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!(FindClientByAccountNumber(AccountNumber, vClient, Client)))
	{
		cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);

	WhithDrawClientByaAccountNumber(Client, vClient);

}

void printTransactionMenue(sClient S)
{
	cout << "| " << left << setw(15) << S.AccountNumber;
	cout << "| " << left << setw(40) << S.Name;
	cout << "| " << left << setw(12) << S.AccountBalance;
	cout << endl;
}

void ShowTotalBalancesClientsScreen()
{
	vector <sClient>vClient = LoadCleintsDataDFromFile(ClientsFileName);
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = 0;

	for (sClient& S : vClient)
	{
		TotalBalances += S.AccountBalance;
		printTransactionMenue(S);
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances << endl;
}

void perfromMainTransactionOption(enTransactions TransactionsMenue)
{
	switch (TransactionsMenue)
	{
	case enTransactions::Deposite:
		system("cls");
		ShowDepositeClientsScreen();
		BackToTransactionMenue();
		break;
	case enTransactions::WhithDraw:
		system("cls");
		ShowWhithDrawClientsScreen();
		BackToTransactionMenue();
		break;
	case enTransactions::TotalBalances:
		system("cls");
		ShowTotalBalancesClientsScreen();
		BackToTransactionMenue();
		break;
	case enTransactions::MainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}

void ShowTransactionClientScreen()
{
	cout << "==========================================\n";
	cout << "\t Transaction menue Screen";
	cout << "\n==========================================\n";
	cout << "\t[1]Deposit.\n";
	cout << "\t[2]WithDraw.\n";
	cout << "\t[3]Total Balances.\n";
	cout << "\t[4]Main Menue.\n";
	cout << "==========================================\n";

	perfromMainTransactionOption((enTransactions)ReadMainMenueOption("Chosse What Do You Want to do? [1 to 4]?"));
}

void screenPrintListUser()
{
	cout << "\n____________________________________________________________________________________________________________\n\n";
	cout << "| UserName         | Password        | Permissions\n";
	cout << "____________________________________________________________________________________________________________\n\n";
}

void printListUser()
{
	vector <sUeser>Data = LoadUserData(UsersFileName);
	cout << endl << "\t\t\t\t\t Users List (" << Data.size() << ") User(s).";
	screenPrintListUser();
	for (sUeser& p : Data)
	{
		cout << "|" << left << setw(18) << p.UserName << "|" <<  left << setw(17) << p.Password << "|" << p.permissions << endl;
	}
	cout << "____________________________________________________________________________________________________________\n\n";
}

void returnToUserMenue()
{
	cout << "\n\nPress any key To Go Back to Main Menue...";
	system("pause>0");
	system("cls");
	ShowManageUsersClientScreen();

}

short FoundUserAndRetun (string UeserName)
{
	vector<sUeser> Data = LoadUserData(UsersFileName);
	for (sUeser& s : Data)
	{
		if (s.UserName == UeserName)
			return s.permissions;
	}
	return 0;
}

void ShowScreenNotAcsses ()
{
	system("cls");
	cout << "\n------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You Dont Have Permission To Do This,\n";
	cout << "Please Conact Your Admin.\n";
	cout << "------------------------------------\n";
}

void showScreenAddNewUser ()
{
	cout << "\n----------------------------------------\n";
	cout << "\t  Add New User Screen\n";
	cout << "----------------------------------------\n";
	cout << "Adding New User:\n\n";
}

bool isFoundUserName (string UserName , sUeser& User)
{
	vector<sUeser> Data = LoadUserData(UsersFileName);

	for (sUeser& s : Data)
	{
		if (s.UserName == UserName)
		{
			User = s;
			return true;
		}
	}
	return false;


}

sUeser GetUsereNameAndPassword(sUeser& User)
{
	sUeser User0;
	showScreenAddNewUser();
	User.UserName = ReadDataName("Enter UserName? ");
	while ((isFoundUserName(User.UserName , User0)))
	{
		cout << "User With [" << User.UserName << "] already exists, Enter another UserName";
		User.UserName = ReadDataName("? ");
	}
		User.Password = ReadDataName("Enter Password? ");
	return User;
}

bool YesOrNoAccsess(string Massage)
{
	char YesOrNO = 'n';
	cout << Massage;
	cin >> YesOrNO;
	
	return (tolower(YesOrNO) == 'y');
}

short GetAccsessFromAdmin()
{
	short Accsess = 0;

	if (YesOrNoAccsess("\nDo You Want to Give Full Accsess? Y/N? "))
		return -1;


	cout << "\nDo You Want to Give Accsess to: \n";

	if (YesOrNoAccsess("\nShow Client List? y/n?"))
	{
		Accsess |= eUserPermissions::AccessListUsers;
	}
	if (YesOrNoAccsess("\nAdd New Client? y/n?"))
	{
		Accsess |= eUserPermissions::AccessAddNewUser;
	}
	if (YesOrNoAccsess("\nDelete Client? y/n?"))
	{
		Accsess |= eUserPermissions::AccessDeleteUser;
	}
	if (YesOrNoAccsess("\nUpdate Client? y/n?"))
	{
		Accsess |= eUserPermissions::AccessUpdateUser;
	}
	if (YesOrNoAccsess("\nFind Client? y/n?"))
	{
		Accsess |= eUserPermissions::AccessFindUsers;
	}
	if (YesOrNoAccsess("\nTransaction? y/n?"))
	{
		Accsess |= eUserPermissions::nTransactionX;
	}
	if (YesOrNoAccsess("\nManage Users? y/n?"))
	{
		Accsess |= eUserPermissions::ManageUsersX;
	}
	return Accsess;
}

string LineToDataUser(sUeser User , string Sepretor = "#//#")
{
	string Line;
	Line  = User.UserName + Sepretor;
	Line += User.Password + Sepretor;
	Line += to_string(User.permissions);

	return Line;
}

void SaveDateToFile(string FileName , string Data)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << Data << endl;
	}
	Myfile.close();
}

void AddNewUsersinFile ()
{
	do
	{
		system("cls");
		sUeser User;
		GetUsereNameAndPassword(User);

		User.permissions = GetAccsessFromAdmin();

		string LineDataUser = LineToDataUser(User);

		SaveDateToFile(UsersFileName, LineDataUser);

	} while (YesOrNoAccsess("\nUser Added Successfully, do you want to Add More Users? Y/N?"));
}

void ShowScreenDeleteUser ()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Users Screen\n";
	cout << "-----------------------------------\n";
}

void printDataUser (sUeser Data)
{
	cout << "\nThe Following are the client details:\n";
	cout << "----------------------------------\n";
	cout << "UserName    :" << Data.UserName << endl;
	cout << "Password    :" << Data.Password << endl;
	cout << "permissions :" << Data.permissions << endl;
	cout << "----------------------------------\n\n";
}

void DeletedDataFromFile (string UserName)
{
	
	if (YesOrNoAccsess("Are You Sure you want delete this user? y/n ? "))
	{
		vector<sUeser>Date = LoadUserData(UsersFileName);

		fstream Myfile;
		Myfile.open(UsersFileName, ios::out);
		for (sUeser& S : Date)
		{
			if (S.UserName != UserName)
			{
				Myfile << LineToDataUser(S) << endl;
			}
		}
		Myfile.close();
		cout << "\nUser Deleted Successfully.\n";
	}
}

void UpdateDataFromFile (vector<sUeser>vData)
{
		fstream Myfile;
		Myfile.open(UsersFileName, ios::out);
		for (sUeser& S : vData)
		{
			Myfile << LineToDataUser(S) << endl;
		}
		Myfile.close();
		cout << "\nUser Updated Successfully.\n";
}

void DeleteUserByAdmin ()
{
	sUeser Data;
	ShowScreenDeleteUser();
	string UserName;
	cout << "\nPlese Enter UserName? ";
	cin >> UserName;
	if (isFoundUserName(UserName , Data) && UserName != "Admin")
	{
		printDataUser(Data);
		DeletedDataFromFile(UserName);
	}
	else
		cout << "\nUser With UserName (" << UserName << ") is Not Found!\n";
}

void ShowScreenUpdateUser ()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Update Users Screen\n";
	cout << "-------------------------------------\n";
}

void UpdatingDataFromUser()
{
	vector<sUeser>vData = LoadUserData(UsersFileName);
	sUeser Data;
	string UserName , Paswword;
	cout << "\nPlese Enter UserName? ";
	cin >> UserName;
	if (isFoundUserName(UserName, Data) && UserName != "Admin")
	{
		printDataUser(Data);
		if (YesOrNoAccsess("Are You Sure you want Update this user? y/n ? "))
		{
			for (sUeser& D : vData)
			{
				if (D.UserName == UserName)
				{
					cout << "\nEnter Password? ";
					cin >> Paswword;
					D.Password = Paswword;
					D.permissions = GetAccsessFromAdmin();
					UpdateDataFromFile(vData);
				}
			}
		}
	}
}

void showScreenFindUser()
{
	cout << "-----------------------------------\n";
	cout << "\t Find User Screen\n";
	cout << "-----------------------------------\n";
}

void PrintscreenFindUser ()
{
	sUeser Data;
	string UserName;
	cout << "\nPlese Enter UserName? ";
	cin >> UserName;
	if (isFoundUserName(UserName, Data))
	{
		printDataUser(Data);
	}
}

void perfromUsersOption(eUsersGoToFunction User)
{
	switch (User)
	{
	case eUsersGoToFunction::ListUser:
	{
		system("cls");
		printListUser();
		returnToUserMenue();
		break;
	}
	case eUsersGoToFunction::AddNewUsers:
	{
			system("cls");
			AddNewUsersinFile();
			returnToUserMenue();
	}
	case eUsersGoToFunction::DeleteUser:
	{
			system("cls");
			DeleteUserByAdmin();
			returnToUserMenue();
	}
	case eUsersGoToFunction::UpdateUser:
	{
		system("cls");
		ShowScreenUpdateUser();
		UpdatingDataFromUser();
		returnToUserMenue();
	}
	case eUsersGoToFunction::FindUser:
	{
			system("cls");
			showScreenFindUser();
			PrintscreenFindUser();
			returnToUserMenue();
	}
	case eUsersGoToFunction::MainMenue2:
		ShowMainMenue();
		break;
	}
}

void ShowManageUsersClientScreen()
{
	cout << "=======================================\n";
	cout << "       Manage Users Menue Screen\n";
	cout << "=======================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find Users.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "=======================================\n";

	perfromUsersOption((eUsersGoToFunction)ReadMainMenueOption("Chosse What Do You Want to do? [1 to 6]?"));
}	  

void perfromMainMenueOption(enMainMenueOption MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOption::eListClients:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::AccessListUsers) == eUserPermissions::AccessListUsers)
		{
			system("cls");
			ShowAllClientScreen();
			GoBackToMainMenue();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
		break;
	}
	case enMainMenueOption::eAddNewClient:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::AccessAddNewUser) == eUserPermissions::AccessAddNewUser)
		{
			system("cls");
			ShowAddNewClientsScreen();
			GoBackToMainMenue();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
	}
	case enMainMenueOption::eDeleteClient:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::AccessDeleteUser) == eUserPermissions::AccessDeleteUser)
		{
			system("cls");
			ShowDeleteClientScreen();
			GoBackToMainMenue();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
	}
	case enMainMenueOption::eUpdateClient:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::AccessUpdateUser) == eUserPermissions::AccessUpdateUser)
		{
			system("cls");
			ShowUpdateClientScreen();
			GoBackToMainMenue();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
	}
	case enMainMenueOption::eFindClient:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::AccessFindUsers) == eUserPermissions::AccessFindUsers)
		{
			system("cls");
			ShowFindClientScreen();
			GoBackToMainMenue();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
	}
	case enMainMenueOption::Transaction:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::nTransactionX) == eUserPermissions::nTransactionX)
		{
			system("cls");
			ShowTransactionClientScreen();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
		break;
	
	}
	case enMainMenueOption::ManageUsers:
	{
		if (FoundUserAndRetun(UserNameToPermissions) == -1 || (FoundUserAndRetun(UserNameToPermissions) & eUserPermissions::ManageUsersX) == eUserPermissions::ManageUsersX)
		{
			system("cls");
			ShowManageUsersClientScreen();
		}
		else
		{
			ShowScreenNotAcsses();
			GoBackToMainMenue();
		}
		break;
	}
	case enMainMenueOption::eExit:
	{
		system("cls");
		LoginUeser();
		break;
	}
	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "==========================================\n";
	cout << "\t    Main Menue Screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "==========================================\n";

	perfromMainMenueOption((enMainMenueOption)ReadMainMenueOption("Chosse What Do You Want to do? [1 to 8]?"));
}

sUeser ConvertUserLineToRecord(string Line, string Sepretor = "#//#")
{
	sUeser User;
	vector<string> vClientData;
	vClientData = SplitString(Line, Sepretor);

	User.UserName = vClientData[0];
	User.Password = vClientData[1];
	User.permissions = stoi(vClientData[2]);

	return User;
}

vector<sUeser> LoadUserData(string FillNAme)
{
	vector<sUeser>vUser;
	sUeser User;
	fstream MyFile;
	string Line;
	MyFile.open(FillNAme, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile , Line))
		{
			User = ConvertUserLineToRecord(Line);
			vUser.push_back(User);
		}
		MyFile.close();
	}
	return vUser;
}

bool isFoundInUserFile(string UserName , string Password)
{
	vector<sUeser> Data = LoadUserData(UsersFileName);
	for (sUeser &s : Data)
	{
		if (s.UserName == UserName && s.Password == Password)
			return true;
	}
	return false;
}

string ReadDataName(string HeadCin)
{
	string Data;
	cout << HeadCin;
	getline(cin >> ws, Data);
	return Data;
}

void ShowScreenLogin()
{
	cout << "\n---------------------------------\n";
	cout << "\t  Login Screen\n";
	cout << "---------------------------------\n";
}

void LoginUeser()
{
	ShowScreenLogin();
	string UserName, Password;
	UserName = ReadDataName("Enter UserName? ");
	Password = ReadDataName("Enter Password? ");
	while (!(isFoundInUserFile(UserName , Password)))
	{
		system("cls");
		ShowScreenLogin();
		cout << "Invalid UserName/PassWord!\n";
		UserName = ReadDataName("Enter UserName? ");
		Password = ReadDataName("Enter Password? ");
	}
	UserNameToPermissions = UserName;
	ShowMainMenue();
}

int main()
{
	LoginUeser();
	system("pause>0");
}

void BackToTransactionMenue()
{
	cout << "\n\nPress any key To Go Back to Main Menue...";
	system("pause>0");
	perfromMainMenueOption(enMainMenueOption::Transaction);
}
