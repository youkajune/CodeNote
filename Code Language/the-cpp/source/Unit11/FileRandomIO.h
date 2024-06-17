#ifndef FILERANDOMIO_H
#define FILERANDOMIO_H

#include <iomanip>

const int NAME_LEN = 20;

struct plant {
    char name[NAME_LEN]; // ��������
    double weight; // ��������
    double g; // �������ٶ�
};

/**
 * ����ʾ�����ƶ�д���Լ� fstream �������һ���ļ�ָ��
 **/
int test_file_random_io_simple() {
    std::fstream finout;
    std::string fileName = "RandomReadAndWriteFile.txt";
    finout.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (!finout.is_open()) {
        std::cerr << "Open file failed.\n" << std::endl;
        exit(EXIT_FAILURE);
    }
    plant p1 = { "Neptune", 1.0241, 11.15 };
    finout.write((char *) &p1, sizeof p1);
    std::cout << "Input point: " << finout.tellg() << ", Output point: " << finout.tellp() << std::endl;

    finout.seekg(0);
    plant p2;
    finout.read((char *) &p2, sizeof p2);
    std::cout << p2.name << " " << p2.weight << " " << p2.g << std::endl;
    finout.close();
    return 0;
}

/** Ϊ�����д����׼����ʼ���� */
void test_init_data() {
    using namespace std;
    int n = 0;
    plant pl;
    fstream finout("PlantsRecord.txt", ios_base::in | ios_base::out | ios_base::binary);
    plant pl1 = {"Mercury", 3.3011, 3.70};
    plant pl2 = {"Venus", 48.675, 8.87};
    plant pl3 = {"Earth", 59.7237, 9.798};
    plant pl4 = {"Mars", 6.4171, 3.71};
    plant pl5 = {"Jupiter", 18982, 24.79};
    plant pl6 = {"Saturn", 5683.4, 10.44};
    plant pl7 = {"Uranus", 868.1, 8.87};
    plant pl8 = {"Neptune", 1024.1, 11.15};

    finout.write((char *) &pl1, sizeof pl);
    finout.write((char *) &pl2, sizeof pl);
    finout.write((char *) &pl3, sizeof pl);
    finout.write((char *) &pl4, sizeof pl);
    finout.write((char *) &pl5, sizeof pl);
    finout.write((char *) &pl6, sizeof pl);
    finout.write((char *) &pl7, sizeof pl);
    finout.write((char *) &pl8, sizeof pl);
    finout.close();
}

// ȥ������̨�����еĶ�����ַ�
inline void eatline() { while(std::cin.get() != '\n') continue; }
const char * file = "PlantsRecord.txt";

int test_file_random_io() {
    using namespace std;

    plant pl; // ���ڶ�ȡ���޸ġ�д���¼
    fstream finout(file, ios_base::in | ios_base::out | ios_base::binary);

    /** �ڲ���֮ǰ����չʾ�ļ��������ݣ�Ҳ�ǹ��û��鿴��ѡ����Ҫ�޸ĵļ�¼ */
    int pn; // plant ��¼����
    if (!finout.is_open()) {
        cerr << file << " can not be opened.\n";
        exit(EXIT_FAILURE);
    }

    cout << "Here are the current contents of the \"" << file << "\" file:\n";
    finout.seekg(0); // ���ļ�ָ������Ϊ��ͷ
    // ѭ����ȡ�ļ��еļ�¼�������������̨��
    while (finout.read((char *) &pl, sizeof pl)) {
        // �ļ�ָ�����ȡ�Զ��ƶ�
        cout << pn++ << ": " << setw(NAME_LEN) << pl.name
             << setprecision(0) << setw(12) << pl.weight
             << setprecision(2) << setw(6) << pl.g << endl;
    }
    if (finout.eof())
        finout.clear(); // ��� eof flag���������ʹ��
    else {
        cerr << "Error in reading " << file << ".\n"; // ������ȡ����
        exit(EXIT_FAILURE);
    }

    /** ָ����Ҫ�޸ĵļ�¼ */
    cout << "Enter the record number you wish to change: ";
    long rec;
    cin >> rec; // �û�����ָ����Ҫ�޸ĵļ�¼
    eatline(); // ���ʣ���ַ�
    if (rec < 0 || rec >= pn) {
        cerr << "Invalid record number. Bye!\n";
        exit(EXIT_FAILURE);
    }
    streampos place = rec * sizeof pl; // ��λָ����¼��λ��
    finout.seekg(place); // �ƶ��ļ�ָ�뵽ָ��λ��
    if (finout.fail()) {
        cerr << "Error on attempted seek.\n"; // ��ѯʱ���ʹ���
        exit(EXIT_FAILURE);
    }
    finout.read((char *) &pl, sizeof pl); // ����¼��ȡ����
    // ���û�ָ���ļ�¼��ʾ�ڿ���̨��
    cout << "Your selection:\n";
    cout << rec << ": " << setw(NAME_LEN) << pl.name
         << setprecision(0) << setw(12) << pl.weight
         << setprecision(2) << setw(6) << pl.g << endl;

    /** ���û���������ѯ�޸ĺ������Ӧ��ʲô */
    cout << "Enter plant name: ";
    cin.get(pl.name, NAME_LEN);
    eatline();
    cout << "Enter planetary weight: ";
    cin >> pl.weight;
    cout << "Enter planet's acceleration of gravity: ";
    cin >> pl.g;
    eatline();

    /** ������д���ļ� */
    finout.seekp(place); // ��ָ���ƻؼ�¼λ��
    finout.write((char *) &pl, sizeof pl) << flush; // ������д���ļ�����ˢ�������
    if (finout.fail()) {
        cerr << "Error on attempted write.\n"; // д�ļ�ʱ���ʹ���
        exit(EXIT_FAILURE);
    }

    /** �ٴν��ļ�����չʾ���� */
    cout << "Here are the current contents of the \"" << file << "\" file:\n";
    pn = 0;
    finout.seekg(0); // ���ļ�ָ���ƻؿ�ͷ
    while (finout.read((char *) &pl, sizeof pl)) {
        cout << pn++ << ": " << setw(NAME_LEN) << pl.name
             << setprecision(0) << setw(12) << pl.weight
             << setprecision(2) << setw(6) << pl.g << endl;
    }
    finout.close();
    cout << "Done.\n";
    return 0;
}

#endif // FILERANDOMIO_H