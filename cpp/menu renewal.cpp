#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int order_to_bit(string order) {
    int bit = 0;
    for (auto menu : order) {
        bit |= 1 << (menu - 'A');
    }

    return bit;
}

string bit_to_course(int bit) {
    string course = "";
    for (int i = 0; bit != 0; i++) {
        if (bit % 2) {
            course += ('A' + i);
        }
        bit /= 2;
    }
    return course;
}

vector<string> solution(vector<string> orders, vector<int> course) {

    vector<string> answer;
    vector<int> order_with_bits;
    set<int> course_with_bits;

    
    for (auto order : orders) {
        order_with_bits.push_back(order_to_bit(order));
    }

    for (int i = 0; i < order_with_bits.size(); i++) {
        for (int j = i + 1; j < order_with_bits.size(); j++) {
            course_with_bits.insert(order_with_bits[i] & order_with_bits[j]);
        }
    }
    
    for (auto bit : course_with_bits) {
        string corse = bit_to_course(bit);
        for (auto size : course) {
            if (size == corse.size()) {
                answer.push_back(corse);
            }
        }
    }
   
    sort(answer.begin(), answer.end());

    return answer;
}