#include <iostream>
#include <vector>
#include <algorithm>
#define PB push_back
using namespace std;

class Library {
private:
	int id;
	int n;
	int signup;
	int throughput;
	vector<int> list_book {};

public: 
	// extra properties of the library
	int strength {};
	bool is_signed {false};

	Library(const int &id_val = -1, const int &num_books = 0, const int &sign_day = 0, const int &th_put = 0, const vector<int> &list = vector<int> {}, const vector<int> &SCORE = vector<int> {});
	void decreaseSign();
	void getScaned(vector<int> &SCORE, vector<int> &bbk_sc);
	void removeScanned(const int &bbk_rm);

	// TEST
	int getId() const { return id; }
	int getTotalBooks() const { return n; }
	int getSignUpDays() const { return signup; }
	int getThroughput() const { return throughput; }
	int getStrength() const { return strength; }
	bool isSigned() const { return is_signed; }
	void getList() const {
		for (auto const &val: list_book) cout<<val<<" ";
		cout<<endl;
	}

	// operator overloading
	bool operator<(const Library &rhs) const { return (strength < rhs.getStrength()); };
	bool operator>(const Library &rhs) const { return (strength > rhs.getStrength()); };
	bool operator<=(const Library &rhs) const { return (strength <= rhs.getStrength()); };
	bool operator>=(const Library &rhs) const { return (strength >= rhs.getStrength()); };
	bool operator==(const Library &rhs) const { return (strength == rhs.getStrength()); };
};

Library::Library(const int &id_val, const int &num_books, const int &sign_day, const int &th_put, const vector<int> &list, const vector<int> &SCORE) 
	:id {id_val}, n {num_books}, signup {sign_day}, throughput {th_put}, list_book {list} {
		int curr_score {};
		for (auto const &val: list_book) {
			curr_score += SCORE.at(val);
		}
		strength = curr_score + throughput - signup;
	}

void Library::decreaseSign() {
	if (signup > 0) --signup;
	else cout<<"INVALID:--> Tried Decrementing Towards Negative Value !!!"<<endl;
}

void Library::getScaned(vector<int> &SCORE, vector<int> &bbk_sc) {
	for (int i {}; i < throughput; ++i) {
		int max_scr {};
		int max_ind {};
		for (int j {}; j < static_cast<int>(list_book.size()); ++j) {
			if (SCORE.at(list_book.at(j)) > max_scr) {
				max_scr = SCORE.at(list_book.at(j));
				max_ind = list_book.at(j);
			}
		}
		if (max_scr) {
			bbk_sc.PB(max_ind);
			SCORE.at(max_ind) = 0;
		}
		else break;
	}
}

// TEST
// void display(const Library &source) {
// 	cout<<"Id: "<<source.getId()<<endl;
// 	cout<<"Total no. of books: "<<source.getTotalBooks()<<endl;;
// 	cout<<"Total no. of sign up days: "<<source.getSignUpDays()<<endl;
// 	cout<<"Throughput value: "<<source.getThroughput()<<endl;
// 	cout<<"Strength: "<<source.getStrength()<<endl;
// 	cout<<"Library signed: "<<boolalpha<<source.isSigned()<<endl;
// 	cout<<"List of books' ids: ";
// 	source.getList();
// 	cout<<"================================"<<endl;
// }
// ------------------------------------------------------------------------

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int B {}, L {}, D {};
    cin >> B >> L >> D;

    vector<int> SCORE (B);
    for (auto &val: SCORE) cin >> val;

    vector<Library> lib {};
	for (int i {}; i < L; ++i) {
		int num_books {}, sign_day {}, th_put {};
		cin >> num_books >> sign_day >> th_put;

		vector<int> list (num_books);
		for (auto &nbk: list) cin >> nbk;
		lib.PB(Library {i, num_books, sign_day, th_put, list, SCORE});
	}

	// TEST
	// cout<<"Book scoring: ";
	// for (auto const &sc: SCORE) cout<<sc<<" ";
	// cout<<endl<<endl;
	// for (auto const &val: lib) {
	// 	display(val);
	// }

	// ===============================================
	sort(lib.rbegin(), lib.rend());
	int sign_ind {-1};
	bool sign_comp {true};

	// submission data
	int total_signed {};
	vector<int> sign_seq {};

	vector<vector<int>> scaned_id (L, vector<int> (0));
	//-------------------------------

	for (int d {}; d < D; ++d) {
		if (sign_comp) {
			lib.at(++sign_ind).decreaseSign();  
			sign_comp = false;
		}
		else {
			if (!lib.at(sign_ind).getSignUpDays()) {
				lib.at(sign_ind).is_signed = true;
				sign_comp = true;
				++total_signed;  // input phase
				sign_seq.PB(lib.at(sign_ind).getId());  // input phase
			}
			else {
				lib.at(sign_ind).decreaseSign();
			}
		}

		for (auto &lbr: lib) {
			if (lbr.is_signed) {
				lbr.getScaned(SCORE, scaned_id.at(lbr.getId()));
				// for (auto const &val: scaned_id.at(lbr.getId()))
				// 	for (auto &lb1: lib)
				// 		lb1.removeScanned(val);
			}
		}
	}

	cout<<total_signed<<endl;
	for (auto const &val: sign_seq) {
		cout<<val<<" "<<scaned_id.at(val).size()<<endl;
		for (auto const &scid: scaned_id.at(val)) 
			cout<<scid<<" ";
		cout<<endl;
	}
    return 0;
}
