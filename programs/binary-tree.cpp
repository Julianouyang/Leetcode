#include <iostream>
#include <vector>
#include <memory>

using namespace std;

vector<int>* create () {
    return new vector<int>();
}
void write (vector<int>& vec, const int input) {
    vec.push_back(input);
}
void print (vector<int>& vec) {
    for (auto &v : vec) {
        cout << v << endl;
    }
}

// typedef shared_ptr<vector<int>> share_vec;
shared_ptr<vector<int>> _create () {
    return make_shared<vector<int>>();
}
void _write (shared_ptr<vector<int>> vec, const int input) {
    vec->push_back(input);
}
void _print (shared_ptr<vector<int>> vec) {
    for (auto &v : *vec) {
        cout << v << endl;
    }
}

int main() {
    vector<int> *vec = create();
    int input;
    // while (cin >> input) {
    //     write(*vec, input);
    // }
    // print(*vec);
    delete vec;

    shared_ptr<vector<int>> _vec = _create();
    while (cin >> input) {
        _write(_vec, input);
    }
    _print(_vec);

    return 0;
}
