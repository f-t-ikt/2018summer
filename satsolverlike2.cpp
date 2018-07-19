#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/*bool is_satisfied(vector<int> var, int cls_n, vector<vector<int>> cls)
{
    for (int i = 0; i < cls_n; ++i) {
        int j;
        for (j = 0; j < cls[i].size(); ++j) {
            int v = cls[i][j];
            if (v > 0 && var[v - 1] == 1) {
                //cout<<"found "<<v<<" ("<<i<<","<<j<<")\n";
                break;
            }
            if (v < 0 && var[-v - 1] == 0) {
                //cout<<"found "<<v<<" ("<<i<<","<<j<<")\n";
                break;
            }
        }
        
        if (j == cls[i].size()) {
            return false;
        }
    }
    
    return true;
}*/
void debug(int var_n, vector<int> var);
bool is_satisfied(int var_n, vector<int> &var, int cls_n, vector<vector<int>> cls, int k)
{
    if (k == cls_n) {
        for (int i = 0; i < var_n; ++i) {
            if (var[i] == 0) {
                var[i] = 1;
            }
        }
        return true;
    }
    
    for (int i = 0; i < cls[k].size(); ++i) {
        int v = cls[k][i];
        int temp = var[abs(v) - 1];
        cout << "k = " << k << ", v = " << v <<", temp = " << temp << endl;
        if (temp != 0 && ((temp > 0 && v < 0) || (temp < 0 && v > 0))) {
            continue;
        }
        
        var[abs(v) - 1] = (v > 0) ? 1 : -1;
        cout << "set:" << abs(v) <<", " << var[abs(v) - 1] << endl;
        cout << "var:";
        debug(var_n, var);
        
        if(is_satisfied(var_n, var, cls_n, cls, k + 1)) {
            return true;
        } else {
            var[abs(v) - 1] *= -1;
            return is_satisfied(var_n, var, cls_n, cls, k + 1);
        }
    }
    
    return false;
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

void debug(int var_n, vector<int> var)
{
    for (int i = 0; i < var_n; ++i) {
        if (i > 0) {
            cout <<" ";
        }
        cout << var[i];
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
    vector<vector<int>> cls(clauses_number);
    
    for (int i = 0; i < clauses_number; ++i) {        
        while (true) {
            int v;
            
            cin >> v;
            
            if (v == 0) {
                break;
            }
            
            cls[i].push_back(v);
        }
    }
    
    /*
    for (int k = 0; k < (1 << variables_number); ++k) {
        for (int i = 0; i < variables_number; ++i) {
            var[i] = !!(k & (1 << i));
        }
        //debug(variables_number,var);
        if (is_satisfied(var, clauses_number, cls)) {
            print_variablse(variables_number, var);
            return 0;
        }
    }*/
    if (is_satisfied(variables_number, var, clauses_number, cls, 0)) {
        print_variablse(variables_number, var);
    } else {
        cout << "UNSATISFIABLE" << endl;
    }
    
    return 0;
}