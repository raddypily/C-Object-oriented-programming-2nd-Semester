#include "iostream"
#include <set>
#include <string>
#include <sstream>

using namespace std;

int main () {
    int duplicates = 0;
    set<int> nums;
    istringstream iss;
    string line;

    while(getline(cin, line)) {
        iss.clear();
        iss.str(line);

        while(iss.good()) {
            int num;
            iss >> num;

            set<int>::iterator it = nums.find(num);

            if(it == nums.end()) {
                nums.insert(num);
            }
            else {
                duplicates++;

                cout << "DUPLICATE" << duplicates << " " << num << endl;
            }
        }
    }

    if(duplicates == 0) {
        cout << "NONE" << endl;
    }
}