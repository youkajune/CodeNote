#ifndef FILEMODE_H
#define FILEMODE_H

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

    ofstream fout1;
    // 以 ios_base::out 模式向一个不存在的文件 WriteFile.txt 中写入两行内容
    fout1.open("WriteFile.txt", ios_base::out);
    if (!fout1.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // 成功打开文件，向其中写入两行内容
        cout << "Open file successfully.\n";
        fout1 << "Hello World.\n" << "Bye Bye!\n";
    }
    fout1.clear();
    fout1.close();

    // 再次以 ios_base::out 模式向 WriteFile.txt 中写入另外的内容
    ofstream fout2("WriteFile.txt", ios_base::out);
    if (!fout2.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // 成功打开文件，向其中写入两行内容
        cout << "Open file successfully.\n";
        fout2 << "If it is a rose, it will blossom.\n";
    }
    fout2.clear();
    fout2.close();

    return 0;
}

/**
 * 测试附加写文件模式的效果
 **/
int test_file_mode_app_write() {
    using namespace std;

    ofstream fout1("WriteAppFile.txt", ios_base::app);

    if (!fout1.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // 成功打开文件，向其中写入两行内容
        cout << "Open file successfully.\n";
        fout1 << "Hello World.\n" << "Bye Bye!\n";
    }
    fout1.clear();
    fout1.close();

    // 再次以 ios_base::out 模式向 WriteFile.txt 中写入另外的内容
    ofstream fout2;
    fout2.open("WriteAppFile.txt", ios_base::app);

    if (!fout2.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // 成功打开文件，向其中写入两行内容
        cout << "Open file successfully.\n";
        fout2 << "If it is a rose, it will blossom.\n";
    }
    fout2.clear();
    fout2.close();
    return 0;
}

// Book 结构的定义和声明
const int LEN = 20;
typedef struct {
    char name[LEN];
    double price;
} Book;

Book b1 = { "C++ Prime Plus", 99.9 };

/**
 * 二进制文件写入的简单例子
 **/
int test_file_mode_a_simple_binary_write() {
    // 文本方式写入
    std::ofstream fout1;
    fout1.open("WriteFile.txt", std::ios_base::out);
    //if (!fout1.is_open()) { ... }
    fout1 << b1.name << " " << b1.price << std::endl;

    // 二进制方式写入
    std::ofstream fout2("WriteFileBinary.txt", std::ios_base::out | std::ios_base::binary);
    fout2.write((char *)&b1, sizeof b1);

    fout1.close();
    fout2.close();
    return 0;
}

#endif // FILEMODE_H
