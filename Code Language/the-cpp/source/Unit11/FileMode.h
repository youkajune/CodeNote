#ifndef FILEMODE_H
#define FILEMODE_H

/**
 * ����ֻ���ļ�ģʽ��Ч��
 **/
int test_file_mode_only_read() {
    using namespace std;

    ifstream fin;
    // �� ios_base::in ģʽ��ȡһ�������ڵ��ļ� ReadFileNoExist.txt�������� in ģʽ��ȡһ�������ڵ��ļ�����Ϊ
    fin.open("ReadFileNoExist.txt", ios_base::in);
    if (!fin.is_open()) {
        cerr << "Failure to open file.\n";
    }
    fin.clear();
    fin.close();

    /**
     * �� ios_base::in ģʽ��ȡһ�����ڵ��ļ� ReadFile.txt������Ϊ
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
 * ����ֻд�ļ�ģʽ��Ч��
 **/
int test_file_mode_only_write() {
    using namespace std;

    ofstream fout1;
    // �� ios_base::out ģʽ��һ�������ڵ��ļ� WriteFile.txt ��д����������
    fout1.open("WriteFile.txt", ios_base::out);
    if (!fout1.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // �ɹ����ļ���������д����������
        cout << "Open file successfully.\n";
        fout1 << "Hello World.\n" << "Bye Bye!\n";
    }
    fout1.clear();
    fout1.close();

    // �ٴ��� ios_base::out ģʽ�� WriteFile.txt ��д�����������
    ofstream fout2("WriteFile.txt", ios_base::out);
    if (!fout2.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // �ɹ����ļ���������д����������
        cout << "Open file successfully.\n";
        fout2 << "If it is a rose, it will blossom.\n";
    }
    fout2.clear();
    fout2.close();

    return 0;
}

/**
 * ���Ը���д�ļ�ģʽ��Ч��
 **/
int test_file_mode_app_write() {
    using namespace std;

    ofstream fout1("WriteAppFile.txt", ios_base::app);

    if (!fout1.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // �ɹ����ļ���������д����������
        cout << "Open file successfully.\n";
        fout1 << "Hello World.\n" << "Bye Bye!\n";
    }
    fout1.clear();
    fout1.close();

    // �ٴ��� ios_base::out ģʽ�� WriteFile.txt ��д�����������
    ofstream fout2;
    fout2.open("WriteAppFile.txt", ios_base::app);

    if (!fout2.is_open()) {
        cerr << "Failure to open file.\n";
    } else {
        // �ɹ����ļ���������д����������
        cout << "Open file successfully.\n";
        fout2 << "If it is a rose, it will blossom.\n";
    }
    fout2.clear();
    fout2.close();
    return 0;
}

// Book �ṹ�Ķ��������
const int LEN = 20;
typedef struct {
    char name[LEN];
    double price;
} Book;

Book b1 = { "C++ Prime Plus", 99.9 };

/**
 * �������ļ�д��ļ�����
 **/
int test_file_mode_a_simple_binary_write() {
    // �ı���ʽд��
    std::ofstream fout1;
    fout1.open("WriteFile.txt", std::ios_base::out);
    //if (!fout1.is_open()) { ... }
    fout1 << b1.name << " " << b1.price << std::endl;

    // �����Ʒ�ʽд��
    std::ofstream fout2("WriteFileBinary.txt", std::ios_base::out | std::ios_base::binary);
    fout2.write((char *)&b1, sizeof b1);

    fout1.close();
    fout2.close();
    return 0;
}

#endif // FILEMODE_H
