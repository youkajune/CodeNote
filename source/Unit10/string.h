#ifndef STRING_H
#define STRING_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

/**
 * ���� string ��Ĺ��캯����ctor �ǹ��캯������д
 **/
void test_string_ctor() {
    using namespace std;
    string one("Hello World."); // ctor #1, �� string ��ʼ��Ϊָ�� s ָ��� NBTS
    cout << "1: " << one << endl;

    string two(20, 'A'); // ctor #2, �� string ��ʼ��Ϊ���� n ���ַ� c ���ַ���
    cout << "2: " << two << endl;

    string three(one); // ctor #3 ���ƹ��캯������ string ��ʼ��Ϊ��һ�� string ����
    cout << "3: " << three << endl;

    one += " Opos!"; // ���� += �����
    cout << one << endl;

    two = "Sorry! That was "; // ���� = �����
    cout << two << endl;

    three[0] = 'P'; // ���� [] �����
    cout << three << endl;

    string four; // ctor #4 Ĭ�Ϲ��캯��
    four = two + three; // ���� +, = �����
    cout << "4: " << four << endl;

    char cString[] = "All's well that ends well";
    string five(cString, 20); // ctor #5
    cout << "5: " << five << endl;

    string six_1(cString + 6, cString + 10); // ctor #6
    cout << "6: " << six_1 << ", ";
    string six_2(&five[6], &five[10]);
    cout << six_2 << ".\n";

    string seven(four, 7, 16); // ctor #7
    cout << "7: " << seven << endl;
}

/**
 * ���� string ������뺯�������ļ��ж�ȡ�ַ�����
 * �����ļ��а�����ð���ַ��ָ����ַ�����
 **/
void test_string_file_input() {
    using namespace std;
    ifstream fin;
    fin.open("E:\\Note\\Code Language\\the-cpp\\source\\Unit10\\tobuy.txt"); // path: E:\Note\Code Language\the-cpp\source\Unit10\tobuy.txt
    if (fin.is_open() == false) {
        cerr << "Can't open file. Please check path.\n";
        exit(EXIT_FAILURE);
    }

    string str;
    int count = 0;
    getline(fin, str, ':');
    while (fin) { // input is good
        ++count;
        cout << count << ": " << str << endl;
        getline(fin, str, ':');
    }
    cout << "Read file end.\n";
    fin.close();
}

/**
 * �ж� Hangman ��Ϸ��Ҳ²���ַ��Ƿ�Ϸ�
 *  - ����²�Ĳ���Сд��ĸ�������벻�Ϸ�����Ҫ������²���ĸ
 *  - ����²����ĸ��֮ǰ�Ѳ²�ģ���Ҳ���Ϸ�����Ҫ������²���ĸ
 *  @return true - �²����ĸ�ȺϷ�Ҳδ�����¹���false - �²����ĸ���Ϸ��򱻲¹���
 **/
bool isGuessValid(char ch, std::string& goodStr, std::string& badStr) {
    if (ch >= 'a' && ch <= 'z' && std::string::npos == goodStr.find(ch) && std::string::npos == badStr.find(ch))
        return true;
    return false;
}

/**
 * Hangman ��Ϸ��
 * ��������µ��ʣ�ÿ�β�һ����ĸ��
 *  - ����¶ԣ���ô�����ʶ�Ӧλ����ʾ���ն��С�������ʱ�ȫ�ų����ˣ���Ϸ�ɹ�
 *  - ����´���ô�ᱻ��¼�������´��ߴΣ���Ϸʧ�ܡ�
 **/
void test_Hangman() {
    using namespace std;
    const int WORD_NUM = 20; // ����׼�������� Hangman ��Ϸ�ĵ�����Ŀ
    const string wordList[WORD_NUM] = {
            "identity", "belong", "department", "medical", "conversation",
            "imagine", "describe", "fold", "aloud", "politician",
            "reason", "height", "grammar", "member", "notice",
            "crystal", "destiny", "teacher", "exactly", "dislike"
    }; // ����׼�������� Hangman ��Ϸ�ĵ���

    srand(time(0));
    char guess; // ���ڱ�����ұ��غϲ²����ĸ

    cout << "Will you play Hangman game?<y/n>: ";
    cin >> guess;
    guess = tolower(guess); // ctype.h �еĺ��������ڽ���д��ĸ����ΪСд��ĸ�����ڷǴ�д��ĸ��������

    while ('y' == guess) {
        string target = wordList[rand() % WORD_NUM]; // ѡ�б�����Ϸ��Ҫ�µĵ���
        int wordLength = target.length(); // ����ѡ�еĵ��ʵĳ��ȣ��Ա��������ɼ�¼�¶Ե���ĸ���ַ���
        string goodChars(wordLength, '-'); // ��¼�Ѳ¶Ե���ĸ
        string badChars; // ��¼�´����ĸ
        int lives = 7; // ���ʣ����Դ����

        cout << "Hangman Game. Guess my screct word. It has " << wordLength << " letters, and you guess one letter at a time. You have " << lives << " wrong chances.\n"; // ������Ҵ��²�ĵ��ʵĳ��ȣ��Լ�Ŀǰ���ʣ��Ļ���
        cout << "Now your guess: " << goodChars << endl; // ��Ŀǰ�������ɵĽ��ȴ�ӡ����

        while (lives && target != goodChars) { // �ж���Ϸ�Ƿ����
            cout << "Please guess a letter: ";
            cin >> guess; // �������²����ĸ
            guess = tolower(guess);
            // �ж������Ƿ�Ϸ�
            if (!isGuessValid(guess, badChars, goodChars)) { // ���벻�Ϸ������Ѿ����������ĸ
                cout << "You already guess this letter or invalid guess. Try again.\n";
                continue;
            }

            int pos = target.find(guess);
            if (string::npos != pos) { // �¶��� - ���²���ַ��� target ��
                cout << "Good guess.\n";
                // ��Ҫ����ȷ���ַ����õ� goodChars ��Ӧ��λ����
                do {
                    goodChars[pos] = guess;
                    pos = target.find(guess, pos + 1);
                } while (string::npos != pos);
            } else { // �´���
                cout << "Oh, bad guess!\n";
                --lives; // �Դ�����һ
                badChars += guess; // ���´����ĸ���µ� badChars ��
            }

            cout << "Your guess: " << goodChars << ".";
            if (target != goodChars) { // ��û����ȫ�¶ԣ���ӡ��ǰ������Ϣ
                if (badChars.length() > 0) // �в´����ĸ����Ѳ´����ĸ����ӡ����
                    cout << " Bad guess: [ " << badChars << " ]." ;
                cout << " Now you have " << lives << " chances to fail.";
            }
            cout << endl;
        }

        // ������Ϸ�ѽ�������Ҫ�ж���Ϸ��ʤ��
        if (lives) { // ʣ���������0����Ϸʤ��
            cout << "Congratulations. Game winner. Correct word: " << target << ".\n";
        } else {
            cout << "Unfortunately. Game failed. Correct word: " << target << ".\n";
        }
        cout << "Will you play another? <y/n> :";
        cin >> guess;
        guess = tolower(guess);
    }
    cout << "Bye.\n";
}

/**
 * ��ʾ string ��� capacity() �� reserve() ������ʹ��
 *  - capacity() ���ص�ǰ������ַ������ڴ���С��
 *  - reserve() �����ܹ������ڴ�����С����
 **/
void test_string_mem() {
    using namespace std;
    string empty; // ���ַ���
    string small = "small"; // �̵��ַ���
    string larger = "This is a larger string. This is a larger string."; // ���ַ���

    cout << "Size: \n"; // ��������ַ����ĳ���
    cout << " empty:  " << empty.size() << endl;
    cout << " small:  " << small.size() << endl;
    cout << " larger: " << larger.size() << endl;

    cout << "Length: \n";
    cout << " empty:  " << empty.length() << endl;
    cout << " small:  " << small.length() << endl;
    cout << " larger: " << larger.length() << endl;

    cout << "Capacity: \n"; // ������ַ�����������ڴ��С
    cout << " empty:  " << empty.capacity() << endl;
    cout << " small:  " << small.capacity() << endl;
    cout << " larger: " << larger.capacity() << endl;

    empty.reserve(50); // �޸� empty ������ڴ��С
    cout << "Capacity after empty.reserve(50):  " << empty.capacity() << endl;
}

#endif //STRING_H