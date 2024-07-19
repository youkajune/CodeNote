#ifndef FILECOUNT_H
#define FILECOUNT_H

#include <fstream>

/**
 * ��дһ�������д����������Ҫ���������в�����ָ�����ļ���������
 **/

int test_file_count(int argc, char * argv[]) {
    using namespace std;

    if (argc == 1) { // û�н��ܲ������˳�����
        cerr << argv[0] << " no param, exit.\n";
        exit(EXIT_FAILURE);
    }

    cout << "���ܵ�����������Ϊ: ";
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl << endl;

    ifstream fin;
    long count;
    long total = 0;
    char ch;
    for (int file = 1; file < argc; ++file) {
        fin.open(argv[file]);

        if (!fin.is_open()) { // ���ļ���ʧ��
            cerr << "Open " << argv[file] << " failed.\n";
            fin.clear();
            continue;
        }

        count = 0;
        while (fin.get(ch))
            count++;
        total += count;
        cout << count << " characters in " << argv[file] << ".\n";
        fin.clear();
        fin.close();
    }
    return 0;
}

#endif // FILECOUNT_H