#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> 
#include <cctype>
#include <ctime>
#include <cmath>

using namespace std;

class Utils {
public:
    static string getFileContent(string filepath) {
        string content;
        string line;
        ifstream file(filepath);
        if (file.is_open()) {
            while (getline (file, line)) {
                content += line + "\n";
            }
        }
        file.close();
        return content;
    }

    static vector<string> getFileContentV(string filepath) {
        vector<string> content;
        string line;
        ifstream file(filepath);
        if (file.is_open()) {
            while (getline (file, line)) {
                content.push_back(line);
            }
        }
        file.close();
        return content;
    }

    static void printVectorStr(vector<string> v) {
        for (string s : v) {
            cout << s;
        }
        cout << endl;
    }

    static string strip(string s) {
        string output;
        for (char c : s) {
            if (c == ' ' || c == '\t') {
                output += ";";
            }
            else {
                output += c;
            }
        }
        return output;
    }

    static vector<string> splitString(string s, string delimiter) {
        vector<string> output;
        size_t last = 0;
        size_t next = 0;
        while ((next = s.find(delimiter, last)) != string::npos) {
            output.push_back(s.substr(last, next-last));
            last = next + 1;
        }
        output.push_back(s.substr(last));
        return output;
    }


    static int daysBetween(string date1, string date2) {
        string thisWeirdYearFormat1 = "1" + date1.substr(0, 4);
        string thisWeirdYearFormat2 = "1" + date2.substr(0, 4);
        int d1 = stoi(date1.substr(8, 2));
        int d2 = stoi(date2.substr(8, 2));
        int m1 = stoi(date1.substr(5, 2));
        int m2 = stoi(date2.substr(5, 2));
        int y1 = stoi(thisWeirdYearFormat1);
        int y2 = stoi(thisWeirdYearFormat2);
        struct tm a = {0,0,0,d1,m1,y1};
        struct tm b = {0,0,0,d2,m2,y2}; 
        time_t x = mktime(&a);
        time_t y = mktime(&b);
        if ( x != (time_t)(-1) && y != (time_t)(-1) ) {
            int difference = difftime(y, x) / (60 * 60 * 24);
            return difference;
        }
        return 0;
    }
};

class FirmaTransportowaOS_xD {
private:
    vector<string> data_rows;
    vector<map<string, string>> data_table;

public:
    FirmaTransportowaOS_xD(string data_path) {
        data_rows = Utils::getFileContentV(data_path);
        data_rows.erase(data_rows.begin());
        for (string row : data_rows) {
            map<string, string> truck;
            row = Utils::strip(row);
            vector<string> splittedRow = Utils::splitString(row, ";");
            truck["Marka_i_model"] = splittedRow[0] + " " + splittedRow[1];
            truck["Rok_produkcji"] = splittedRow[2];
            truck["Cena_zakupu"] = splittedRow[3];
            truck["Nr_rejestracyjny"] = splittedRow[4] + " " + splittedRow[5] + " " + splittedRow[6];
            truck["Przebieg"] = splittedRow[7];
            truck["Data_ostatniego_remontu"] = splittedRow[8];
            float amortyzacjaCzasu = 0.05 * stoi(truck["Cena_zakupu"]) * (2017 - stoi(truck["Rok_produkcji"]));
            float amortyzacjaPrzebiegu = 0.02 * stoi(truck["Cena_zakupu"]) * floor(stoi(truck["Przebieg"]) / 100000);
            float wartoscObecnie = stoi(truck["Cena_zakupu"]) - amortyzacjaCzasu - amortyzacjaPrzebiegu;
            truck["amortyzacjaCzasu"] = to_string(amortyzacjaCzasu);
            truck["amortyzacjaPrzebiegu"] = to_string(amortyzacjaPrzebiegu);
            truck["wartoscObecnie"] = to_string(wartoscObecnie);
            truck["Marka"] = splittedRow[0];
            truck["Model"] = splittedRow[1];
            data_table.push_back(truck);
        }
    }

    vector<map<string, string>> getData() {
        return data_table;
    }

    void displayData() {
        for (map<string, string> m : data_table) {
            cout << m["Marka_i_model"] << " " << m["Rok_produkcji"] << " " << m["Cena_zakupu"] << " " << m["Nr_rejestracyjny"] << " " << m["Przebieg"] << " " << m["Data_ostatniego_remontu"] << endl;
        }
    }

};


int main() {
    FirmaTransportowaOS_xD f("data.txt");
    vector<map<string, string>> trucksData = f.getData();
    cout << "Ilosc ciezarowek: " << trucksData.size() << endl << endl;

    cout << "5.1 ----------------------------------------------" << endl;
    cout << "a)" << endl;
    map<string, string> VolvoFH;
    string nrRejestracyjny = "ERA 092 TR";
    for (map<string, string> truck : trucksData) {
        if (truck["Nr_rejestracyjny"] == nrRejestracyjny) {
            VolvoFH = truck;
            break;
        }
    }
    cout << "Wartosc w 2017: " << VolvoFH["wartoscObecnie"] << "  amor.Czasu: " << VolvoFH["amortyzacjaCzasu"] << "  amor.Przebiegu: " << VolvoFH["amortyzacjaPrzebiegu"] << endl;
    cout << "b)" << endl;
    map<string, string> cheapestTruck;
    float lowestPrice = 99999999.f;
    for (map<string, string> truck : trucksData) {
        if (stof(truck["wartoscObecnie"]) < lowestPrice) {
            cheapestTruck = truck;
            lowestPrice = stof(truck["wartoscObecnie"]);
        }
    }
    cout << cheapestTruck["Marka_i_model"] << " " << cheapestTruck["Nr_rejestracyjny"] << " " << lowestPrice << endl;

    cout << "\n5.2 ----------------------------------------------" << endl;
    map<string, vector<map<string, string>>> samochodyDanejMarki;
    for (map<string, string> truck : trucksData) {
        samochodyDanejMarki[truck["Marka"]].push_back(truck);
    }
    cout << "a) i b) ... i 5.3" << endl;
    for (auto const& [key, val] : samochodyDanejMarki) {
        float srPrzebieg;
        string rokProdukcji;
        int od2006do2015 = 0;
        for (map<string, string> truck : val) {
            int rok = stoi(truck["Rok_produkcji"]);
            if (rok >= 2005 && rok <= 2015) {
                od2006do2015++;
            }
        }
        for (map<string, string> truck : val) {
            srPrzebieg += stof(truck["Przebieg"]);
        }
        srPrzebieg = round(srPrzebieg / val.size());
        cout << key << " - Ilosc: " << val.size() << "  Sr. Przebieg: " << srPrzebieg << "  od 2006 do 2015: " << od2006do2015 << endl;
    }

    cout << "\n5.4 ----------------------------------------------" << endl;
    multimap<int, map<string, string>> daysXtrucks;
    for (map<string, string> truck : trucksData) {
        int dniOdRemontu = Utils::daysBetween(truck["Data_ostatniego_remontu"], "2017-01-01");
        daysXtrucks.insert(pair<int, map<string, string>>(dniOdRemontu, truck));
    }

    int j = 0;
    for (multimap<int, map<string, string>>::reverse_iterator it = daysXtrucks.rbegin(); it != daysXtrucks.rend(); it++) {
        cout << it->second["Marka_i_model"] << " " << it->second["Nr_rejestracyjny"] << " " << " Dni: " << it->first << endl;
        j++;
        if (j == 4) break;
    }
}
