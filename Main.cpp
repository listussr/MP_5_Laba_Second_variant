#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<fstream>
#include<regex>
#define EOL '\n'
#define buf_s numeric_limits<streamsize>::max()
using namespace std;

class date {

	int y;
	int m;
	int d;

	bool check_year(string y)
	{
		regex re(R"([1-3][0-9][0-9][0-9])");
		if (regex_match(y, re)) return true;
		else return false;
	}

	bool check_month(string m) 
	{
		regex re1(R"([1-9])");
		regex re2(R"([1][0-2])");
		if (regex_match(m, re1)) return true;
		else if (regex_match(m, re2)) return true;
		else return false;
	}

	bool check_day(string d)
	{
		regex re1(R"([1-9])");
		regex re2(R"([1][0-9])");
		regex re3(R"([2][0-9])");
		regex re4(R"([3][0-1])");
		if (regex_match(d, re1)) return true;
		else if (regex_match(d, re1)) return true;
		else if (regex_match(d, re2)) return true;
		else if (regex_match(d, re3)) return true;
		else if (regex_match(d, re4)) return true;
		else return false;
	}

	bool check_correct_day(int& d, int& m, int& y, bool& v)
	{
		if (m == 3 || m == 5 || m == 7 || m == 8|| m == 10 || m == 12)
		{
			if (d < 1 || d > 31) return false;
			else return true;
		}
		else if (m == 4 || m == 6 || m == 9 || m == 11)
		{
			if (d < 1 || d > 30) return false;
			else return true;
		}
		else
		{
			if (v) {
				if (d < 1 || d > 29) return false;
				else return true;
			}
			else {
				if (d < 1 || d > 28) return false;
				else return true;
			}
		}
	}

	bool check_v(int y)
	{
		bool v;
		if ((!(y % 4) && (y % 100)) || (!(y % 400))) v = true;
		else v = false;
		return v;
	}

public:

	date(){}

	date(int year, int month, int day) :y(year), m(month), d(day) {}

	int year() const { return y; }
	int month() const { return m; }
	int day() const { return d; }

	void year(int year)
	{
		y = year;
	}
	void day(int day)
	{
		d = day;
	}
	void month(int month)
	{
		m = month;
	}

	friend ostream& operator << (ostream& out, date& ref);
	friend istream& operator >> (istream& in, date& ref);
	friend ofstream& operator << (ofstream& out, date& ref);

	date operator- (date ref) {
		int post_y;
		int post_m;
		int post_d;
		if (y > ref.y) {
			post_y = y - ref.y;

			if (m > ref.m) { // если месяц растёт
				post_m = m - ref.m;
				if (d > ref.d) { post_d = d - ref.d; }
				else {
					if (check_v(ref.y)) { // visocosnyy god (y >= ref.y; m >= ref.m)
						if ((ref.m == 1) || (ref.m == 3) || (ref.m == 5) || (ref.m == 7) || (ref.m == 8) || (ref.m == 10) || (ref.m == 12))
						{
							post_d = 31 - ref.d + d;
						}
						else if ((ref.m == 4) || (ref.m == 6) || (ref.m == 9) || (ref.m == 11)) {
							post_d = 30 - ref.d - d;
						}
						else { post_d = 29 - ref.d + d; }
					}

					else { // кол-во днеё в зависимости от месяца и года
						if ((ref.m == 1) || (ref.m == 3) || (ref.m == 5) || (ref.m == 7) || (ref.m == 8) || (ref.m == 10) || (ref.m == 12))
						{
							post_d = 31 - ref.d + d;
						}
						else if ((ref.m == 4) || (ref.m == 6) || (ref.m == 9) || (ref.m == 11)) {
							post_d = 30 - ref.d + d;
						}
						else { post_d = 28 - ref.d + d; }
					}
					post_m--;
				}
			}
			else {
				post_m = 12 - ref.m + m; post_y--; // если месяцев не хватает
				if (d >= ref.d) { post_d = d - ref.d; }
				else {
					if (check_v(ref.y)) {
						if (ref.m == 1 || ref.m == 3 || ref.m == 5 || ref.m == 7 || ref.m == 8 || ref.m == 10 || ref.m == 12)
						{
							post_d = 31 - ref.d + d;
						}
						else if (ref.m == 4 || ref.m == 6 || ref.m == 9 || ref.m == 11) {
							post_d = 30 - ref.d - d;
						}
						else { post_d = 29 - ref.d + d; }
					}

					else {
						if (ref.m == 1 || ref.m == 3 || ref.m == 5 || ref.m == 7 || ref.m == 8 || ref.m == 10 || ref.m == 12)
						{
							post_d = 31 - ref.d + d;
						}
						else if (ref.m == 4 || ref.m == 6 || ref.m == 9 || ref.m == 11) {
							post_d = 30 - ref.d + d;
						}
						else { post_d = 28 - ref.d + d; }
					}
					post_m--;

				}
			}
		}
		else if (ref.y > y) {
			post_y = ref.y - y;
			if (ref.m >= m) {
				post_m = ref.m - m;
				if (ref.d >= d) { post_d = ref.d - d; }
				else {
					if (check_v(y)) {
						if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
						{
							post_d = 31 + ref.d - d;
						}
						else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
							post_d = 30 + ref.d - d;
						}
						else { post_d = 29 + ref.d - d; }
					}

					else {
						if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
						{
							post_d = 31 + ref.d - d;
						}
						else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
							post_d = 30 + ref.d - d;
						}
						else { post_d = 28 + ref.d - d; }
					}
					post_m--;
				}
			}
			else {
				post_m = 12 - m + ref.m; post_y--;
				if (ref.d >= d) { post_d = ref.d - d; }
				else {
					if (check_v(y)) {
						if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
						{
							post_d = 31 + ref.d - d;
						}
						else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
							post_d = 30 + ref.d - d;
						}
						else { post_d = 29 + ref.d - d; }
					}
					else {
						if ((ref.m == 1) || (ref.m == 3) || (ref.m == 5) || (ref.m == 7) || (ref.m == 8) || (ref.m == 10) || (ref.m == 12))
						{
							post_d = 31 + ref.d - d;
						}
						else if ((ref.m == 4) || (ref.m == 6) || (ref.m == 9) || (ref.m == 11)) {
							post_d = 30 + ref.d - d;
						}
						else { post_d = 28 + ref.d - d; }
					}
					post_m--;
				}
			}
		}
		else {
			post_y = 0;
			if (ref.m > m) {
				post_m = ref.m - m;
				if (ref.d >= d) { post_d = ref.d - d; }
				else {
					if (check_v(y)) {
						if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
						{
							post_d = 31 + ref.d - d;
						}
						else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
							post_d = 30 + ref.d - d;
						}
						else { post_d = 29 + ref.d - d; }
					}

					else {
						if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
						{
							post_d = 31 + ref.d - d;
						}
						else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
							post_d = 30 + ref.d - d;
						}
						else { post_d = 28 + ref.d - d; }
					}
					post_m--;
				}
			}
			else if (m > ref.m) {
				post_m = m - ref.m;
				if (d >= ref.d) { post_d = ref.d - d; }
				else {
					if (check_v(y)) {
						if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
						{
							post_d = 31 - ref.d + d;
						}
						else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
							post_d = 30 - ref.d + d;
						}
						else { post_d = 29 - ref.d + d; }
					}
					else {
						if ((ref.m == 1) || (ref.m == 3) || (ref.m == 5) || (ref.m == 7) || (ref.m == 8) || (ref.m == 10) || (ref.m == 12))
						{
							post_d = 31 - ref.d + d;
						}
						else if ((ref.m == 4) || (ref.m == 6) || (ref.m == 9) || (ref.m == 11)) {
							post_d = 30 - ref.d + d;
						}
						else { post_d = 28 - ref.d + d; }
					}
					post_m--;
				}
			}
			else {
				post_m = 0;
				if (ref.d > d) { post_d = ref.d - d; }
				else { post_d = d - ref.d; }
			}
		}
		date difference(post_y, post_m, post_d); // возврат конечного значения
		return difference;
	}

	date dif(date ref1, date ref2)
	{
		date d;
		d = ref1 - ref2;
		return d;
	}
};

class date_calc {
	date first, second;

	bool check_file_years(string& inp)
	{
		regex reg1(R"([0-3][0-9][0-9][0-9])");
		string year1, year2;
		for (int i = 6; i <= 9; i++) {
			year1.push_back(inp[i]);
		}
		for (int i = 17; i <= 20; i++) {
			year2.push_back(inp[i]);
		}
		if (regex_match(year1, reg1) && regex_match(year2, reg1)) return true;
		else return false;
	}

	bool check_file_monthes(string& inp)
	{
		regex reg1(R"([0][1-9])");
		regex reg2(R"([1][0-2])");
		string month1, month2;
		for (int i = 3; i <= 4; i++) month1.push_back(inp[i]);
		for (int i = 14; i <= 15; i++) month2.push_back(inp[i]);
		if (regex_match(month1, reg1) && regex_match(month2, reg1)) return true;
		else if (regex_match(month1, reg2) && regex_match(month2, reg1)) return true;
		else if (regex_match(month1, reg1) && regex_match(month2, reg2)) return true;
		else if (regex_match(month1, reg2) && regex_match(month2, reg2)) return true;
		else return false;
	}

	bool check_file_day_format(string& inp)
	{
		regex reg1(R"([0][1-9])");
		regex reg2(R"([1][0-9])");
		regex reg3(R"([2][0-9])");
		regex reg4(R"([3][0-1])");
		string day1, day2;
		for (int i = 0; i <= 1; i++) day1.push_back(inp[i]);
		for (int i = 11; i <= 12; i++) day2.push_back(inp[i]);
		if (regex_match(day1, reg1) && regex_match(day2, reg1)) return true;
		else if (regex_match(day1, reg1) && regex_match(day2, reg2)) return true;
		else if (regex_match(day1, reg2) && regex_match(day2, reg1)) return true;
		else if (regex_match(day1, reg2) && regex_match(day2, reg2)) return true;
		else if (regex_match(day1, reg1) && regex_match(day2, reg3)) return true;
		else if (regex_match(day1, reg3) && regex_match(day2, reg1)) return true;
		else if (regex_match(day1, reg2) && regex_match(day2, reg3)) return true;
		else if (regex_match(day1, reg3) && regex_match(day2, reg2)) return true;
		else if (regex_match(day1, reg1) && regex_match(day2, reg4)) return true;
		else if (regex_match(day1, reg2) && regex_match(day2, reg4)) return true;
		else if (regex_match(day1, reg3) && regex_match(day2, reg4)) return true;
		else if (regex_match(day1, reg4) && regex_match(day2, reg4)) return true;
		else if (regex_match(day1, reg4) && regex_match(day2, reg3)) return true;
		else if (regex_match(day1, reg4) && regex_match(day2, reg2)) return true;
		else if (regex_match(day1, reg4) && regex_match(day2, reg1)) return true;
		else if (regex_match(day1, reg3) && regex_match(day2, reg3)) return true;
		else return false;
		}

	bool check_v(int y)
	{
		bool v;
		if ((!(y % 4) && (y % 100)) || (!(y % 400))) v = true;
		else v = false;
		return v;
	}

	bool check_file_day_1(int& y1, int& m1, int& d1, bool& v)
	{
		if (m1 == 3 || m1 == 5 || m1 == 7 || m1 == 8 || m1 == 10 || m1 == 12)
		{
			if (d1 < 1 || d1 > 31) return false;
			else return true;
		}
		else if (m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11)
		{
			if (d1 < 1 || d1 > 30) return false;
			else return true;
		}
		else
		{
			if (v) {
				if (d1 < 1 || d1 > 29) return false;
				else return true;
			}
			else {
				if (d1 < 1 || d1 > 28) return false;
				else return true;
			}
		}
	}

	bool check_file_day_2(int& y1, int& m1, int& d1, bool& v)
	{
		if (m1 == 3 || m1 == 5 || m1 == 7 || m1 == 8 || m1 == 10 || m1 == 12)
		{
			if (d1 < 1 || d1 > 31) return false;
			else return true;
		}
		else if (m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11)
		{
			if (d1 < 1 || d1 > 30) return false;
			else return true;
		}
		else
		{
			if (v) {
				if (d1 < 1 || d1 > 29) return false;
				else return true;
			}
			else {
				if (d1 < 1 || d1 > 28) return false;
				else return true;
			}
		}
	}

	bool correct_format(string& inp)
	{
		regex reg(R"([0-3][0-9][.][0-1][0-9][.][0-9][0-9][0-9][0-9][ ][0-3][0-9][.][0-1][0-9][.][0-9][0-9][0-9][0-9])");
		return regex_match(inp, reg);
	}

public:
	date_calc() {}

	date_calc(date first_, date second_) :first(first_), second(second_) {}

	date GetFirst() const { return first; }
	date GetSecond() const { return second; }

	void SetFirst(date year)
	{
		first = year;
	}

	void SetSecond(date day)
	{
		second = day;
	}

	friend ostream& operator << (ostream& out, date_calc& ref);
	friend istream& operator >> (istream& in, date_calc& ref);
	friend ofstream& operator << (ofstream& out, date_calc& ref);
	friend ifstream& operator >> (ifstream& in, date_calc& ref);
};

ostream& operator << (ostream& out, date& ref) {
	out << setfill('0') << setw(2) << ref.d << '.' << setfill('0') << setw(2) << ref.m << '.' << setfill('0') << setw(4) << ref.y;
	return out;
}
istream& operator >> (istream& in, date& ref) {
	string year, month, day;
	cout << "Enter year" << endl;
	bool flag = true;
	while (flag) {
		in >> year;
		if (ref.check_year(year)) flag = false;
		else {
			cout << "Incorrect input!" << endl;
		}
	}
	ref.year(stoi(year));
	bool v;
	if ((!(ref.y % 4) && (ref.y % 100)) || (!(ref.y % 400))) v = true;
	else v = false;
	cout << "Enter month" << endl;
	flag = true;
	while (flag) {
		in >> month;
		if (ref.check_month(month)) flag = false;
		else {
			cout << "Incorrect input!" << endl;
		}
	}
	ref.month(stoi(month));
	cout << "Enter day" << endl;
	flag = true;
	while (flag)
	{
		in >> day;
		if (ref.check_day(day)) {
			int d = stoi(day);
			if (ref.check_correct_day(d, ref.m, ref.y, v)) flag = false;
			else cout << "Incorrect input!" << endl;
		}
		else cout << "Incorrect input!" << endl;
	}
	ref.day(stoi(day));
	return in;
}
ofstream& operator << (ofstream& out, date& ref) {
	out << setfill('0') << setw(2) << ref.d << '.' << setfill('0') << setw(2) << ref.m << '.' << setfill('0') << setw(4) << ref.y;
	return out;
}
ifstream& operator >> (ifstream& in, date_calc& ref){
	string line;
	getline(in, line);
	if (ref.correct_format(line)) {
		if (ref.check_file_years(line) && ref.check_file_monthes(line) && ref.check_file_day_format(line))
		{
			string year1s, year2s, month1s, month2s, day1s, day2s;
			for (int i = 6; i <= 9; i++) year1s.push_back(line[i]);
			for (int i = 17; i <= 20; i++) year2s.push_back(line[i]);
			for (int i = 3; i <= 4; i++) month1s.push_back(line[i]);
			for (int i = 14; i <= 15; i++) month2s.push_back(line[i]);
			for (int i = 0; i <= 1; i++) day1s.push_back(line[i]);
			for (int i = 11; i <= 12; i++) day2s.push_back(line[i]);
			int year1 = stoi(year1s);
			int year2 = stoi(year2s);
			int month1 = stoi(month1s);
			int month2 = stoi(month2s);
			int day1 = stoi(day1s);
			int day2 = stoi(day2s);
			bool v = ref.check_v(year1);
			if (ref.check_file_day_1(year1, month1, day1, v) && ref.check_file_day_2(year2, month2, day2, v)) {
				ref.first.year(year1);
				ref.first.month(month1);
				ref.first.day(day1);
				ref.second.year(year2);
				ref.second.month(month2);
				ref.second.day(day2);
			}
		}
	}
	else {
		cout << "Incorrect input! -> data is lost!" << endl;
		ref.first.year(1974);
		ref.first.month(01);
		ref.first.day(01);
		ref.second.year(2022);
		ref.second.month(01);
		ref.second.day(01);
	}
	return in;
}
ostream& operator << (ostream& out, date_calc& ref) {
	out << ref.first << endl << ref.second;
	return out;
}
ofstream& operator << (ofstream& out, date_calc& ref) {
	out << ref.first << ' ' << ref.second;
	return out;
}
istream& operator >> (istream& in, date_calc& ref) {
	cout << "Enter first date: " << endl;
	in >> ref.first;
	cout << "Enter second date: " << endl;
	in >> ref.second;
	return in;
}
//___________________________________________________разделение______________________________________________________

bool check_amount_string(string input_string)
{
	if (input_string.empty())
		return false;
	bool dot_found = false;
	for (int i = 0; i < input_string.length(); i++)
	{
		char symbol = input_string[i];
		if (symbol == '.') return false;
		if (symbol == '-') return false;
		if (isdigit(symbol) == 0 && symbol != '.' && symbol != '-')
			return false;
		if (isspace(symbol) != 0)
			return false;
	}
	return true;
}

int entering_array_size() {
	string s;
	bool input = true;
	while (input) {
		getline(cin, s);
		input = !check_amount_string(s);
	}
	return stoi(s);
}

bool continue_check()
{
	bool flag = true;
	char symbol;
	cout << endl << "Do you want to continue?" << endl;
	cout << "If you want - press q or Q" << endl;
	cout << "If you want to quit - press x or X" << endl;
	while (!(cin >> symbol) || flag) {
		cin.clear();
		if ((symbol == 'X' || symbol == 'x') && (cin.peek() == EOL)) {
			flag = false;
			return false;
		}
		else if ((symbol == 'Q' || symbol == 'q') && (cin.peek() == EOL)) {
			flag = false;
			return true;
		}
		else {
			flag = true;
		}
		while (cin.get() != EOL);
		cout << "Do you want to continue? --> Q / X / q / x" << endl;
	}
}

void users_guide()
{
	cout << "Now you will see a app for calculating difference in two dates" << endl << endl;
	cout << "If you'd like to enter dates from a text file - enter information by this way: " << endl;
	cout << "Event	year	month	day" << endl;
	cout << "(Example: '\t' birthday 2004 12 21)" << endl;
	cout << "If you want to enter dates from console - you'll see guide later" << endl << endl;
}

bool entering_way()
{
	cout << "Enter the way you'd like to enter information" << endl;
	cout << "if you want to use console - press '1'" << endl;
	cout << "if you want to use file - press '0'" << endl;
	char symbol;
	bool flag = true;
	while (!(cin >> symbol) || flag) {
		cin.clear();
		if ((symbol == '0') && (cin.peek() == EOL)) {
			flag = false;
			return false;
		}
		else if ((symbol == '1') && (cin.peek() == EOL)) {
			flag = false;
			return true;
		}
		else {
			flag = true;
		}
		while (cin.get() != EOL);
		cout << "Do you want to continue? --> 1/0" << endl;
	}
}

vector<date_calc> console_input() {
	cout << "Enter amount of elements in array" << endl;
	int amount = entering_array_size();
	vector<date_calc>vec;
	date_calc d;
	for (int i = 0; i < amount; i++){
		cout << "Enter " << i + 1 << " element" << endl;
		cin >> d;
		vec.push_back(d);
	}
	return vec;
}

vector<date_calc> file_input(ifstream& in) {
	vector<date_calc> inp;
	date_calc a;
	while (!in.eof()) {
		in >> a;
		inp.push_back(a);
	}
	in.close();
	return inp;
}

bool choosing_output_way()
{
	bool flag = true;
	char symbol;
	cout << endl << "Choose output way" << endl;
	cout << "If you want console result - press 1" << endl;
	cout << "If you want file result - press 0" << endl;
	while (!(cin >> symbol) || flag) {
		cin.clear();
		if ((symbol == '0') && (cin.peek() == EOL)) {
			flag = false;
			return false;
		}
		else if ((symbol == '1') && (cin.peek() == EOL)) {
			flag = false;
			return true;
		}
		else {
			flag = true;
		}
		while (cin.get() != EOL);
		cout << "Do you want to continue? --> 1/0" << endl;
	}
}

date calculation(date_calc& a)
{
	return a.GetFirst() - a.GetSecond();
}

vector<date> result_of_calculation(vector<date_calc>& a)
{
	vector<date> res;
	for (int i = 0; i < a.size(); i++)
		res.push_back(calculation(a[i]));
	return res;
}

void console_output(vector<date>& res, vector<date_calc>& beg) 
{
	for (int i = 0; i < res.size(); i++) {
		cout << beg[i] << endl;
		cout << res[i] << endl;
		cout << "_________________" << endl;
	}
}

void file_output(vector<date>& res, vector<date_calc>& beg, ofstream& out)
{
	for (int i = 0; i < res.size(); i++)
	{
		out << beg[i] << endl;
		out << res[i] << endl;
	}
	out.close();
}

bool string_format(string& name)
{
	regex reg(R"([\w]+[.][t][x][t])");
	return regex_match(name, reg);
}

string entering_filename()
{
	cout << "Enter filename: " << endl;
	string name;
	bool flag = true;
	while (flag)
	{
		cin >> name;
		if (string_format(name)) flag = false;
		else cout << "Incorrect format!" << endl;
	}
	return name;
}

bool changing_file()
{
	bool flag = true;
	char symbol;
	cout << endl << "Do you want to change input file?" << endl;
	cout << "If you want  - press 1" << endl;
	cout << "If not - press 0" << endl;
	while (!(cin >> symbol) || flag) {
		cin.clear();
		if ((symbol == '0') && (cin.peek() == EOL)) {
			flag = false;
			return false;
		}
		else if ((symbol == '1') && (cin.peek() == EOL)) {
			flag = false;
			return true;
		}
		else {
			flag = true;
		}
		while (cin.get() != EOL);
		cout << "Do you want to continue? --> 1/0" << endl;
	}
}

int main()
{
	users_guide();
	bool iteration = true;
	vector<date_calc> first_vec;
	vector<date> result_vec;
	static string name;
	static int amount_of_iter = 0;
	while (iteration) {
		if (entering_way()) { 
			system("cls");
			first_vec = console_input(); 
		}
		else  {
			if(amount_of_iter == 0)
				name = entering_filename();
			if (amount_of_iter > 0 && changing_file()) 
				name = entering_filename();

			ifstream in(name);
			if (in.is_open()) {
				first_vec = file_input(in);
				amount_of_iter++;
			}
			else {
				cout << "Incorrect filename!" << endl;
				name.clear();
				amount_of_iter = 0;
			}
		}
		if (amount_of_iter > 0) {
			result_vec = result_of_calculation(first_vec);
			if (choosing_output_way())
				console_output(result_vec, first_vec);
			else {
				ofstream out("Output.txt");
				file_output(result_vec, first_vec, out);
			}
		}
		iteration = continue_check();
		system("cls");
	}
}
