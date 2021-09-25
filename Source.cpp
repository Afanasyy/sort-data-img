#include <iostream>
#include <fstream>
#include <limits>
#include <bitset>
#include <string>
#include <sys/stat.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

constexpr size_t BITS_PER_BYTE = 8;
const string path_photo = "R:\\Photo and Videos\\disc 1000\\JPEG Image (.jpg)\\t\\fol";
const string path_f = "R:\\Photo and Videos\\disc 1000\\JPEG Image (.jpg)";
const string path_photo_tmp = "R:\\Photo and Videos\\disc 1000\\JPEG Image (.jpg)\\fol";
const string path_file_last = "S:\\Users\\griki\\Source\\Repos\\sort-data-img\\last.txt";
const string path_1="R:\\Photo and Videos\\CD 8\\sorted by size";
const string path_2="R:\\Photo and Videos\\disc 1000\\sorted by size";
const int COUNT_IMG = 871;

string read_bits(const string& file_name) {
    if (ifstream file{ file_name, ios::binary }) {
        file >> noskipws;
        unsigned char b;
        string str = "";
        bool flag = false;
        int n = 0;
        while (file >> b) {
            ++n;
            if (!flag) {
                if (char(b) == '2')
                    str += char(b);
                else if (char(b) == '0' && str == "2")
                    str += char(b);
                else if (int(char(b)) >= 48 && int(char(b)) <= 50 && str == "20")
                    str += char(b);
                else if (int(char(b)) >= 48 && int(char(b)) <= 57 && str.length() == 3)
                    str += char(b);
                else
                    str = "";
            }
            else {
                if (char(b) == ':' && str.length() == 4) 
                    str += char(b);                
                else if (int(char(b)) >= 48 && int(char(b)) <= 49 && str.length() == 5) 
                    str += char(b);                
                else if (int(char(b)) >= 48 && int(char(b)) <= 57 && str.length() == 6) 
                    str += char(b);                
                else {
                    str = "";
                    flag = false;
                }
            }
            if (str.length() == 4 && stoi(str) < 2021 && stoi(str) >= 2000)
                flag = true;
            else if (str.length() == 7 && stoi(str.substr(5, 2)) >= 1 && stoi(str.substr(5, 2)) <= 12)
                return str;
            
        }
        return {};
    }
    return {};
}
string getName(const string &s) {
    for (int i = s.length() - 1; i >= 0; --i) 
        if (s[i] == '\\') 
            return s.substr(i, s.length() - i);
}
void rel(string t) {
    string date = read_bits(t);
    string tmp = "\\" + getName(t);
    if (!date.empty()) {
        string t1 = path_f + "\\" + date.substr(0, 4) + "\\" + date.substr(5, 2);
        fs::create_directories(t1);
        rename((t).c_str(), (t1 + tmp).c_str());
    }    
    ofstream f(path_file_last);
    f << t;
    f.close();
    cout << t << endl;
}

int main() {    
    ifstream f_l_i(path_file_last);
    int last = 0;
    if (f_l_i.is_open()) 
        f_l_i >> last;    
    f_l_i.close();
    last = 4;
    for (const auto& entry : fs::directory_iterator(path_1))
        rel((entry.path()).string());
    return 0;
}