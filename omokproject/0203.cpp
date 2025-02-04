#include<iostream>
#include<fstream> // 파일 스트림
#include<vector>
#include<sstream>
#include<unordered_map> // 탐색을 위한 자료구조
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
		cerr << " 저장된 사용자 데이터 없음 (새로 시작)" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		User user = User::fromCSV(line);
		users[user.getId()] = user;
	}
	file.close();
	cout << "사용자 데이터 불러오기 완료!" << endl;
}
void saveUsers() {
	ofstream file(USER_DATA_FILE);
	if (!file)
	{
		cerr << "파일을 열 수 없습니다: " << USER_DATA_FILE << endl;
	}
	for (const auto& pair : users)
	{
		file << pair.second.toCSV();
	}
	file.close();
	cout << "사용자 데이터 저장 완료! " << endl;
}
void signUp() {
	string id, password;
	cout << "아이디: ";
	cin >> id;
	if (users.find(id) != users.end())
	{
		cout << "이미 존재하는 아이디입니다." << endl;
		return;
	}

	cout << "비밀번호: ";
	cin >> password;

	users[id] = User(id, password);
	saveUsers();
	cout << "회원가입 완료" << endl;
}
void login() {
	string id, password;
	cout << "아이디 : ";
	cin >> id;
	cout << "비밀번호 : ";
	cin >> password;
	if (users.find(id) == users.end() || !users[id].checkPassword(password))
	{
		cout << "로그인 실패" << endl;
		return;
	}
	users[id].setOnline(true);
	saveUsers();
	cout << id << "님, 로그인 성공!" << endl;
}
void searchUser() {
	string id;
	cout << "검색할 아이디 : ";
	cin >> id;

	if (users.find(id) == users.end())
	{
		cout << "사용자를 찾을 수 없습니다." << endl;
	}
	else
	{
		cout << "아이디 : " << id << " | 상태" << endl;
	}
}
void deleteUser() {
	string id;
	cout << "삭제할 아이디 : ";
	cin >> id;

	if (users.erase(id)) {
		saveUsers();
		cout << "사용자가 삭제되었습니다." << endl;
	}
	else
	{
		cout << "해당 아이디가 존재하지 않습니다." << endl;
	}
}
void logout() {
	string id;
	cout << "로그아웃할 아이디: ";
	cin >> id;
	if (users.find(id) == users.end())
	{
		cout << "해당 사용자가 존재하지 않습니다." << endl; 
		return;
	}

	users[id].setOnline(false);
	saveUsers();
	cout << id << "님이 로그아웃되었습니다.";
}


void menu() {
	while (true)
	{
		
		cout << "\n==== 사용자 관리 시스템 ====" << endl;

		cout << "1. 회원가입" << endl;
		cout << "2. 로그인" << endl;
		cout << "3. 사용자 검색" << endl;
		cout << "4. 사용자 삭제" << endl;
		cout << "5. 로그아웃" << endl;
		cout << "6. 종료" << endl;
		cout << "선택 : ";

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			signUp();
			break;
		case 2:
			login();
			// 채팅 시스템으로 입장
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
			cout << "존재하지 않는 선택입니다." << endl;
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
