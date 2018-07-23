#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

void variable_allocate(int v, vector<int> &var, vector<set<int>> &cls)
{
    var[abs(v) - 1] = (v > 0) ? 1 : -1;
    
    vector<set<int>>::iterator itr = cls.begin();
    while (itr != cls.end()) {
        if (cls.empty()) {
            return ;
        }
        
        if ((*itr).find(v) != (*itr).end()) {
            itr = cls.erase(itr);
        } else {
            (*itr).erase(-v);
            itr++;
        }
    }
}

bool is_satisfied(vector<int> &var, vector<set<int>> cls)
{   
    bool has_one_literal;
    
    do {
        has_one_literal = false;
        
        for (vector<set<int>>::iterator itr = cls.begin(); itr != cls.end(); itr++) {
            if (cls.empty()) {
                return true;
            }
            
            if ((*itr).empty()) {
                return false;
            }
            
            if ((*itr).size() == 1) {
                has_one_literal = true;
                
                int v = *((*itr).begin());
                variable_allocate(v, var, cls);
            }
        }
    } while (has_one_literal);
    
    if (cls.empty()) {
        return true;
    }
    
    for (vector<set<int>>::iterator itr = cls.begin(); itr != cls.end(); itr++) {
        
        if ((*itr).empty()) {
            return false;
        }
    }
    
    vector<set<int>> cls_copy(cls.size());
    copy(cls.begin(), cls.end(), cls_copy.begin());
    int v = *(cls[0].begin());
    
    variable_allocate(v, var, cls_copy);
    if (is_satisfied(var, cls_copy)) {
        return true;
    }
    
    cls_copy.resize(cls.size());
    copy(cls.begin(), cls.end(), cls_copy.begin());
    variable_allocate(-v, var, cls_copy);
    return is_satisfied(var, cls_copy);
}

void print_variablse(int var_n, vector<int> var)
{
    cout << "SATISFIABLE" << endl;
    
    for (int i = 0; i < var_n; ++i) {
        if (i > 0) {
            cout <<" ";
        }
        cout << (var[i] == 1 ? (i + 1) : -(i + 1));
    }
    
    cout << endl;
}

int main()
{
    string input_string;
    
    do {
        getline(cin, input_string);
    } while (input_string[0] == 'c');
    
    stringstream ss{input_string};
    vector<string> v;
    string buf;
    
    while (getline(ss, buf, ' ')) {
        v.push_back(buf);
    }
    
    string variables_string = v[2];
    string clauses_string = v[3];
    
    int variables_number = atoi(variables_string.c_str());
    int clauses_number = atoi(clauses_string.c_str());
    
    vector<int> var(variables_number);
    vector<set<int>> cls(clauses_number);
    
    for (int i = 0; i < clauses_number; ++i) {        
        while (true) {
            int v;
            
            cin >> v;
            
            if (v == 0) {
                break;
            }
            
            cls[i].insert(v);
        }
    }
    
    if (is_satisfied(var, cls)) {
        print_variablse(variables_number, var);
    } else {
        cout << "UNSATISFIABLE" << endl;
    }
    
    return 0;
}