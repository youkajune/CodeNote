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

/**
 * 测试只读文件模式的效果
 **/
int test_file_mode_only_read() {
    using namespace std;

    ifstream fin;
    // 以 ios_base::in 模式读取一个不存在的文件 ReadFileNoExist.txt，测试以 in 模式读取一个不存在的文件的行为
    fin.open("ReadFileNoExist.txt", ios_base::in);
    if (!fin.is_open()) {
        cerr << "Failure to open file.\n";
    }
    fin.clear();
    fin.close();

    /**
     * 以 ios_base::in 模式读取一个存在的文件 ReadFile.txt，内容为
     * Hello, World!
     * Hello, Worl
     * Hello, Wor
     * Hello, Wo
     */
    fin.open("ReadFile.txt", ios_base::in);
    if (!fin.is_open()) {
        cerr << "Failure to open file.\n";
    }
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.clear();
    fin.close();
    return 0;
}

/**
 * 测试只写文件模式的效果
 **/
int test_file_mode_only_write() {
    using namespace std;

    ofstream fout;
    // 以 ios_base::out 模式向一个不存在的文件 WriteFile.txt 中写入两行内容
    fout.open("WriteFile.txt", ios_base::out);
    if (!fout.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // 成功打开文件，向其中写入两行内容
        cout << "Open file successfully.\n";
        fout << "Hello World.\n" << "Bye Bye!\n";
    }
    fout.clear();
    fout.close();

    // 再次以 ios_base::out 模式向 WriteFile.txt 中写入另外的内容
    fout.open("WriteFile.txt", ios_base::out);
    if (!fout.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // 成功打开文件，向其中写入两行内容
        cout << "Open file successfully.\n";
        fout << "If it is a rose, it will blossom.\n";
    }
    fout.clear();
    fout.close();

    return 0;
}

#endif // FILECOUNT_H