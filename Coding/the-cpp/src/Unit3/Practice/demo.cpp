#include "output.h"
#include "vector.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
void testOutput() {
    Output out;
    out << 1 << Output_Format::endl;
    out << 'h' << Output_Format::endl;
}

void testVector() {
    VECTOR::Vector v1(3, 4, (VECTOR::Vector::Mode)3);
    std::cout << v1 << std::endl;

    VECTOR::Vector v2 (3, 4, VECTOR::Vector::POL);
    std::cout << v2 << std::endl;
}

// �� walk ��λ��, �Լ���ǰ�ߵķ�������� path �ļ���
void outputToFile(const std::string & path, const VECTOR::Vector & walk, const VECTOR::Vector & step) {
    std::ofstream out;
    out.open(path);
    if(out.is_open())
        out << "walker: " << walk << ", step: " << step << std::endl;
    else
        std::cout << "Open Failed." << std::endl;
    out.close();
}

// �����������
void randomWalk() {
    using VECTOR::Vector;
    using std::cout;
    using std::cin;
    using std::endl;

    srand(time(0)); // ��������
    Vector result(0, 0, VECTOR::Vector::RECT); // ����ֱ������ϵ��¼��ǰ����λ��
    Vector step; // ��¼��ǰ�����ʸ��
    unsigned long steps = 0; // ��¼�߹����ܲ���

    double target; // ��¼Ŀ�����
    double dstep; // ��¼ÿһ���Ĳ���

    cout << "������Ŀ�����(�� q ��ʾ�˳�):";
    while (cin >> target) {
        cout << "�����벽��:";
        if (!(cin >> dstep)) {
            cout << "����Ĳ�����Ч,�����˳�.";
            break;
        }

        // �������û�дﵽĿ�����, ��������һ��
        while (result.getMagVal() < target) {
            // ���������һ���ķ���, �����ò����ͷ����ռ�����ϵ����ʵ��
            step = Vector(dstep, rand() % 360, Vector::POL);
            // �� step ָʾ����λ��һ��
            result = result + step;
            // �ߵĲ���+Unit1
            steps++;
            cout << step << "  " << result << endl;
            outputToFile("walker.txt", result, step);
        }

        cout << "���� " << steps << " ��֮�󵽴�ָ���ľ���, ��ǰλ��������ʾ: " << endl;
        cout << "(x, y) = (" << result.getXVal() << ", " << result.getYVal()
             << ") or (mag, ang) = (" << result.getMagVal() << ", " << result.getAngVal()
             << ")\n";
        cout << "�ƶ���ƽ������Ϊ: " << result.getMagVal() / steps << endl;

        // ���ò����͵�ǰ����λ��
        steps = 0;
        result.reset(0, 0, Vector::RECT);
        cout << "������Ŀ�����(�� q ��ʾ�˳�):";
    }
    cout << "Bye!\n";
    cin.clear();
}

int main(void) {
//    testOutput();
//    testVector();
    randomWalk();
    return 0;
}