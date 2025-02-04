#include<iostream>
#include<fstream> // ���� ��Ʈ��
#include<vector>
#include<sstream>
#include<unordered_map> // Ž���� ���� �ڷᱸ��
//#define login
#ifdef login


using namespace std;

class User {
private:
	string id;
	string password;
	bool is_online;
public:
	User(): id(""), password(""),is_online(false){}

	User(string u, string p) :
		id(u), password(p), is_online(false) {}

	string getId() {
		return id;
	}

	bool checkPassword(string p) {
		return password == p;
	}

	void setOnline(bool status) {
		is_online = status;
	}

	bool isOnline() {
		return is_online;
	}

	string toCSV() const {
		return id + "," + password + "," + (is_online ? "1" : "0");
	}

	static User fromCSV(const string& line) {
		stringstream ss(line);
		string u, p, s;
		getline(ss, u, ',');
		getline(ss, p, ',');
		getline(ss, s, ',');
		User user(u, p);
		user.setOnline(s == "1");
		return user;
	}
};
const string USER_DATA_FILE = "C:/Users/wiewk/Documents/c++/TestMain/users.csv";
const string USER_CAHT_DATA_FILE = "C:/Users/wiewk/Documents/c++/TestMain/chat_history.csv";
unordered_map<string, User> users;
void loadUsers() {
	ifstream file(USER_DATA_FILE);
	if (!file) {
		cerr << " ����� ����� ������ ���� (���� ����)" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		User user = User::fromCSV(line);
		users[user.getId()] = user;
	}
	file.close();
	cout << "����� ������ �ҷ����� �Ϸ�!" << endl;
}
void saveUsers() {
	ofstream file(USER_DATA_FILE);
	if (!file)
	{
		cerr << "������ �� �� �����ϴ�: " << USER_DATA_FILE << endl;
	}
	for (const auto& pair : users)
	{
		file << pair.second.toCSV();
	}
	file.close();
	cout << "����� ������ ���� �Ϸ�! " << endl;
}
void signUp() {
	string id, password;
	cout << "���̵�: ";
	cin >> id;
	if (users.find(id) != users.end())
	{
		cout << "�̹� �����ϴ� ���̵��Դϴ�." << endl;
		return;
	}

	cout << "��й�ȣ: ";
	cin >> password;

	users[id] = User(id, password);
	saveUsers();
	cout << "ȸ������ �Ϸ�" << endl;
}
void login() {
	string id, password;
	cout << "���̵� : ";
	cin >> id;
	cout << "��й�ȣ : ";
	cin >> password;
	if (users.find(id) == users.end() || !users[id].checkPassword(password))
	{
		cout << "�α��� ����" << endl;
		return;
	}
	users[id].setOnline(true);
	saveUsers();
	cout << id << "��, �α��� ����!" << endl;
}
void searchUser() {
	string id;
	cout << "�˻��� ���̵� : ";
	cin >> id;

	if (users.find(id) == users.end())
	{
		cout << "����ڸ� ã�� �� �����ϴ�." << endl;
	}
	else
	{
		cout << "���̵� : " << id << " | ����" << endl;
	}
}
void deleteUser() {
	string id;
	cout << "������ ���̵� : ";
	cin >> id;

	if (users.erase(id)) {
		saveUsers();
		cout << "����ڰ� �����Ǿ����ϴ�." << endl;
	}
	else
	{
		cout << "�ش� ���̵� �������� �ʽ��ϴ�." << endl;
	}
}
void logout() {
	string id;
	cout << "�α׾ƿ��� ���̵�: ";
	cin >> id;
	if (users.find(id) == users.end())
	{
		cout << "�ش� ����ڰ� �������� �ʽ��ϴ�." << endl; 
		return;
	}

	users[id].setOnline(false);
	saveUsers();
	cout << id << "���� �α׾ƿ��Ǿ����ϴ�.";
}


void menu() {
	while (true)
	{
		
		cout << "\n==== ����� ���� �ý��� ====" << endl;

		cout << "1. ȸ������" << endl;
		cout << "2. �α���" << endl;
		cout << "3. ����� �˻�" << endl;
		cout << "4. ����� ����" << endl;
		cout << "5. �α׾ƿ�" << endl;
		cout << "6. ����" << endl;
		cout << "���� : ";

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			signUp();
			break;
		case 2:
			login();
			// ä�� �ý������� ����
			break;
		case 3:
			saveUsers();
			break;
		case 4:
			deleteUser();
			break;
		case 5:
			logout();
			break;
		case 6:
			return;
		default:
			cout << "�������� �ʴ� �����Դϴ�." << endl;
			break;
		}
	}
}

int main() {
	loadUsers();
	menu();
	saveUsers();
	return 0;
}
#endif // login
