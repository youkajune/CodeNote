#ifndef STRING_H
#define STRING_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

/**
 * 测试 string 类的构造函数，ctor 是构造函数的缩写
 **/
void test_string_ctor() {
    using namespace std;
    string one("Hello World."); // ctor #1, 将 string 初始化为指针 s 指向的 NBTS
    cout << "1: " << one << endl;

    string two(20, 'A'); // ctor #2, 将 string 初始化为包含 n 个字符 c 的字符串
    cout << "2: " << two << endl;

    string three(one); // ctor #3 复制构造函数，将 string 初始化为另一个 string 对象
    cout << "3: " << three << endl;

    one += " Opos!"; // 重载 += 运算符
    cout << one << endl;

    two = "Sorry! That was "; // 重载 = 运算符
    cout << two << endl;

    three[0] = 'P'; // 重载 [] 运算符
    cout << three << endl;

    string four; // ctor #4 默认构造函数
    four = two + three; // 重载 +, = 运算符
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
 * 测试 string 类的输入函数，从文件中读取字符串。
 * 假设文件中包含用冒号字符分隔的字符串。
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
 * 判断 Hangman 游戏玩家猜测的字符是否合法
 *  - 如果猜测的不是小写字母，则输入不合法，需要玩家重新猜字母
 *  - 如果猜测的字母是之前已猜测的，则也不合法，需要玩家重新猜字母
 *  @return true - 猜测的字母既合法也未曾被猜过；false - 猜测的字母不合法或被猜过了
 **/
bool isGuessValid(char ch, std::string& goodStr, std::string& badStr) {
    if (ch >= 'a' && ch <= 'z' && std::string::npos == goodStr.find(ch) && std::string::npos == badStr.find(ch))
        return true;
    return false;
}

/**
 * Hangman 游戏。
 * 由玩家来猜单词，每次猜一个字母。
 *  - 如果猜对，那么将单词对应位置显示在终端中。如果单词被全才出来了，游戏成功
 *  - 如果猜错，那么会被记录下来。猜错七次，游戏失败。
 **/
void test_Hangman() {
    using namespace std;
    const int WORD_NUM = 20; // 程序准备的用于 Hangman 游戏的单词数目
    const string wordList[WORD_NUM] = {
            "identity", "belong", "department", "medical", "conversation",
            "imagine", "describe", "fold", "aloud", "politician",
            "reason", "height", "grammar", "member", "notice",
            "crystal", "destiny", "teacher", "exactly", "dislike"
    }; // 程序准备的用于 Hangman 游戏的单词

    srand(time(0));
    char guess; // 用于保存玩家本回合猜测的字母

    cout << "Will you play Hangman game?<y/n>: ";
    cin >> guess;
    guess = tolower(guess); // ctype.h 中的函数，用于将大写字母调整为小写字母，对于非大写字母不做调整

    while ('y' == guess) {
        string target = wordList[rand() % WORD_NUM]; // 选中本次游戏需要猜的单词
        int wordLength = target.length(); // 计算选中的单词的长度，以便用于生成记录猜对的字母的字符串
        string goodChars(wordLength, '-'); // 记录已猜对的字母
        string badChars; // 记录猜错的字母
        int lives = 7; // 玩家剩余的试错次数

        cout << "Hangman Game. Guess my screct word. It has " << wordLength << " letters, and you guess one letter at a time. You have " << lives << " wrong chances.\n"; // 提醒玩家待猜测的单词的长度，以及目前玩家剩余的机会
        cout << "Now your guess: " << goodChars << endl; // 将目前玩家已完成的进度打印出来

        while (lives && target != goodChars) { // 判断游戏是否结束
            cout << "Please guess a letter: ";
            cin >> guess; // 玩家输入猜测的字母
            guess = tolower(guess);
            // 判断输入是否合法
            if (!isGuessValid(guess, badChars, goodChars)) { // 输入不合法，或已经输入过该字母
                cout << "You already guess this letter or invalid guess. Try again.\n";
                continue;
            }

            int pos = target.find(guess);
            if (string::npos != pos) { // 猜对了 - 即猜测的字符在 target 中
                cout << "Good guess.\n";
                // 需要将正确的字符放置到 goodChars 对应的位置上
                do {
                    goodChars[pos] = guess;
                    pos = target.find(guess, pos + 1);
                } while (string::npos != pos);
            } else { // 猜错了
                cout << "Oh, bad guess!\n";
                --lives; // 试错机会减一
                badChars += guess; // 将猜错的字母更新到 badChars 中
            }

            cout << "Your guess: " << goodChars << ".";
            if (target != goodChars) { // 还没有完全猜对，打印当前进度信息
                if (badChars.length() > 0) // 有猜错的字母，则把猜错的字母都打印出来
                    cout << " Bad guess: [ " << badChars << " ]." ;
                cout << " Now you have " << lives << " chances to fail.";
            }
            cout << endl;
        }

        // 本轮游戏已结束，需要判断游戏的胜负
        if (lives) { // 剩余次数大于0，游戏胜利
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
 * 演示 string 类的 capacity() 和 reserve() 方法的使用
 *  - capacity() 返回当前分配给字符串的内存块大小；
 *  - reserve() 让您能够请求内存块的最小长度
 **/
void test_string_mem() {
    using namespace std;
    string empty; // 空字符串
    string small = "small"; // 短的字符串
    string larger = "This is a larger string. This is a larger string."; // 长字符串

    cout << "Size: \n"; // 输出各个字符串的长度
    cout << " empty:  " << empty.size() << endl;
    cout << " small:  " << small.size() << endl;
    cout << " larger: " << larger.size() << endl;

    cout << "Length: \n";
    cout << " empty:  " << empty.length() << endl;
    cout << " small:  " << small.length() << endl;
    cout << " larger: " << larger.length() << endl;

    cout << "Capacity: \n"; // 输出个字符串被分配的内存大小
    cout << " empty:  " << empty.capacity() << endl;
    cout << " small:  " << small.capacity() << endl;
    cout << " larger: " << larger.capacity() << endl;

    empty.reserve(50); // 修改 empty 分配的内存大小
    cout << "Capacity after empty.reserve(50):  " << empty.capacity() << endl;
}

#endif //STRING_H