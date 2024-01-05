#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>

void test_file_io() {
    using namespace std;
    string fileName;
    cout << "Please input file name: ";
    cin >> fileName;

    ofstream fout(fileName.c_str());
    fout << "Hello, World.\n";
    int num;
    cout << "Please input a int number: ";
    cin >> num;
    fout << "User inputs a number: " << num << endl;
    fout.close();

    ifstream fin(fileName.c_str());
    cout << "Here are the contents of " << fileName.c_str() << ":\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
    cout << "Finish.\n";
}

#endif // FILEIO_H
