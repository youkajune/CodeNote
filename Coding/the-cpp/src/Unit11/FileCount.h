#ifndef FILECOUNT_H
#define FILECOUNT_H

#include <fstream>

/**
 * 编写一个命令行处理程序，它需要计算命令行参数中指明的文件的字数。
 **/

int test_file_count(int argc, char * argv[]) {
    using namespace std;

    if (argc == 1) { // 没有接受参数，退出程序
        cerr << argv[0] << " no param, exit.\n";
        exit(EXIT_FAILURE);
    }

    cout << "接受的命令行命令为: ";
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

        if (!fin.is_open()) { // 该文件打开失败
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