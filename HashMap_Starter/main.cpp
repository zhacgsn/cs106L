#include "hashmap.h"
#include <set>
using namespace std;
//UNCOMMENT THESE FOR MILESTONE 2
#include "tests.cpp"
#include "test_settings.cpp"
#include <iostream>

//declaring functions now so we can use them befpre we implement them!
int student_main();

//student_main helpers. Remember to change the necessary function signatures here and 
//where they are implemented for milestone 1!

// 想改变调用函数时传递的对象：按引用 / 指针传递，如 void f(X&), void f(X*)
// 不想改变调用函数时传递的对象，但对象很“大”：按指向常量的引用传递， 如 void f(const X&)
//（只是不能通过该引用来改变实参，而非实参本身一定为常量）
// 否则，按值传递， 如 void f(X)
void init_map(HashMap<string, int>& map);
void print_difference(const HashMap<string, int>& lecturer_record, const string lecturer1, const string lecturer2);
template<typename KeyType, typename MappedTyped>
std::set<KeyType> find_keys(const HashMap<KeyType, MappedTyped>& map);

int main() {
    int answer;
    cout << "Please enter a number and then hit ENTER\n1) Milestone 1 code\n2) Milestone 2 tests" << endl;
    cin >> answer;
    if(answer == 1){
        student_main();
    } else if (answer == 2) {
        cout << ":P" << endl;
        //UNCOMMENT THIS FOR MILESTONE 2
        run_test_harness();
    } else {
        cout << "Please run your code again and hit 1 or 2 only!";
    }
}

int student_main() {
    cout << "This is student main. You can try using HashMap as a client by editing the code here!" << endl;
    HashMap<string, int> map;
    init_map(map);
    std::set<string> keys = find_keys(map);
    cout << "Find the difference in time between two lecturers! \n" <<
        "Please enter two names from this list, separated by a space. Then hit ENTER\n" << endl;
    for(auto it = keys.begin(); it != keys.end(); ++it){
        cout << *it << endl;
    }
    string name1;
    string name2;
    cin >> name1;
    cin >> name2;
    print_difference(map, name1, name2);
    return 0;
}

//This will fill parameter map with lecturer -> year they lectured pairs
void init_map(HashMap<string, int>& map) {
    cout << "Hello from your past and current lecturers!" << endl;
    map.insert({"Anna", 2019});
    map.insert({"Avery", 2019});
    map.insert({"Nikhil", 2020});
    map.insert({"Ethan", 2020});
    map.insert({"Frankie", 2021});
    map.insert({"Sathya", 2021});
    //demonstrate the map in action!
    map.debug();
    map.rehash(5);
    map.debug();
}

//this will return a set of all the keys in parameter map
// 可以把非 const的 HashMap map传给 const HashMap& map吗？可以！
// 但是通过 const HashMap& map来调用成员函数，必须是 const成员函数
template<typename KeyType, typename MappedTyped>
std::set<KeyType> find_keys(const HashMap<KeyType, MappedTyped>& map){
    std::set<KeyType> res;
    // 如果 map是 reference to const，begin()和 end()必须有 const版本
    for(auto it = map.begin(); it != map.end(); ++it){
        //Remember structured binding? :)
        auto [key, val] = *it; //at iterator points to a key, value pair in a map!
        res.insert(key);
    }
    return res;
}

//this will find and print which lecturer lectured first, and how long after them the
//second lecturer lectured
void print_difference(const HashMap<string, int>& lecturer_record, const string lecturer1, const string lecturer2){
    int year1 = lecturer_record.at(lecturer1);
    int year2 = lecturer_record.at(lecturer2);
    if(year1 < year2){
        cout << lecturer1 << " lectured first and " << year2 - year1 << " year(s) later, " << lecturer2 << " lectured" << endl;
    } else if (year1 > year2) {
        cout << lecturer2 << " lectured first and " << year1 - year2 << " year(s) later, " << lecturer1 << " lectured" << endl;
    } else {
        cout << lecturer1 << " and " << lecturer2 << " lectured the same year, " << year1 << endl;
    }
}