#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

//Define a simple Records

struct Record{
    string name;
    int id;

    //constructor for easy initialization 
    Record(string n = "", int i = 0): name(n), id(i){}

};

//Over load the <<operator to print the record

ostream& operator<<(ostream& os, const Record& r){
    os<<"Record{name: " <<r.name<<", id: "<<r.id<<"}";
    return os;
};

//Comparison function for equal range( lambda alternative )

bool rec_eq(const Record& r1, const Record& r2){
    return r1.name<r2.name;
}

void f(const vector<Record>& v){
    cout<<"=== Searching for 'Reg' ===\n";

    //equal_range return a PAIR of iterators
    //. first = iterator to first element >="Reg"
    //.secord = iterator to the first element >"Reg"

    auto er = equal_range(v.begin(), v.end(), Record{"Reg"}, rec_eq);

    cout<<"Found "<<distance(er.first, er.second)<<" matching records: \n";

    //Iterate through the range 
    for(auto p = er.first; p!= er.second; ++p){
        cout<<" "<<*p<<"\n";
    }
    cout<<"\n";
}

int main(){
    cout<<"====PAIR AND EQUAL_RANGE EXAMPLE =====\n\n";

    //================================================
    //Part1: Understanding PAIR
    //================================================
    cout<<"1.What is a PAIR?\n";
    cout<<" A pair is a simple container for TWO values \n\n";

    //Creating pairs
    pair<int, string> p1 {1, "Alice"};
    pair<double, char> p2 {3.14, 'A'};
    auto p3 = make_pair(42, "Answer");

    cout<<" Pair 1: (" <<p1.first<<", "<<p1.second<<")\n";
    cout<<" Pair 2: (" <<p2.first<<", "<<p2.second<<")\n";
    cout<<" Pair 3: (" <<p3.first<<", "<<p3.second<<")\n";

    //====================================================
    //Part2 : PAIR of Iterators
    //====================================================

    cout<<"2. PAIR of Iterators: \n";
    cout<<" equa_range returns pair<iterator, iterator>\n\n";

    vector<int> numbers = {1,2,3,3,3,4,5,6};

    cout<<"  Numbers: ";
    for( int n: numbers)cout<<n<<" ";
    cout<<"\n\n";

    //Find range of value 3

    auto range = equal_range(numbers.begin(), numbers.end(), 3);

    cout<<"     Range of value 3: \n";
    cout<<"     .first points to:   "<<*range.first<<"\n";
    cout<<"     .second points to:  "<<*range.second<<"\n";
    cout<<"     Elements in range:  ";
    for(auto it =range.first; it!=range.second;++it){
        cout<<*it<<" ";
    }
    cout<<"\n\n";

    //===========================================
    //Part 3: Record Example (Author's Code)
    //===========================================

    cout<<"3. Record Search Example:\n\n";

    //Create sorted vector of Records
    vector<Record> records={
        {"Alice", 100},
        {"Bob", 101},
        {"Charlie", 102},
        {"Reg", 103},
        {"Reg", 104},
        {"Reg", 105},
        {"Sarah", 106},
        {"Tom", 107}
    };

    cout<<"     All Records (sorted by name): \n";
    for(const auto& r: records){
        cout<<"     "<<r<<"\n";
    }
    cout<<"\n";

    //Search for "Reg"

    f(records);

    //===============================================
    //Part4: Different Searches
    //===============================================
    cout<<"4. Searching for different names:\n\n";

    //Search for Alice
    cout<<"     Searching for 'Alice':\n";
    auto alice_range = equal_range(records.begin(), records.end(),
                                    Record{"Alice"}, rec_eq);

    for(auto p = alice_range.first; p!=alice_range.second;++p){
        cout<<"     "<<*p<<"\n";
    }

    cout<<"\n";

      // Search for "Bob"
    cout << "   Searching for 'Bob':\n";
    auto bob_range = equal_range(records.begin(), records.end(), 
                                 Record{"Bob"}, rec_eq);
    for (auto p = bob_range.first; p != bob_range.second; ++p) {
        cout << "   " << *p << "\n";
    }
    cout << "\n";
    
    // Search for non-existent name
    cout << "   Searching for 'Zoe' (doesn't exist):\n";
    auto zoe_range = equal_range(records.begin(), records.end(), 
                                 Record{"Zoe"}, rec_eq);
    if (zoe_range.first == zoe_range.second) {
        cout << "   Not found!\n";
    }
    cout << "\n";


    //===========================================
    //Using Lambda
    //===========================================
    cout<<"5.   Using Lambda instead of function:\n\n";

    //Define comparison as Lambda
    auto req_eq_lambda = [](const Record& r1, const Record& r2){
        return r1.name<r2.name;
    };

    auto lambda_range = equal_range(records.begin(),records.end(),Record{"Reg"}, req_eq_lambda);

    cout<<"     Found using lambda:\n";
    for( auto p = lambda_range.first;p!= lambda_range.second;++p){
        cout<<"     "<<*p<<"\n";

    }
    cout<<"\n";

    //=============================================
    //Part6: Understanding equal_range return value
    //=============================================

    cout<<"6. Understanding the PAIR returned:\n\n";

    auto result = equal_range(records.begin(),records.end(), Record{"Reg"}, rec_eq);

    cout << "   Type: pair<iterator, iterator>\n";
    cout << "   .first  = iterator to FIRST 'Reg'\n";
    cout << "   .second = iterator to element AFTER last 'Reg'\n";
    cout << "   Range: [first, second) - half-open interval\n\n";
    
    cout << "   Distance between iterators: " 
         << distance(result.first, result.second) << " elements\n";
    
    return 0;


}