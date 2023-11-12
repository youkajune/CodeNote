#ifndef FRIEND_H_
#define FRIEND_H_

/**
 * 友元类演示
 **/

namespace V1 {
    class Tv {
    public:
        friend class Remote; // 将 Remote 类声明为 Tv 类的友元类
        enum {ON, OFF}; // 开关
        enum {VOLMINVAL, VOLMAXVAL=100}; // 音量的最小值和最大值
        enum {TV, DVD};
        enum {ANTENNA, CABLE};
    private:
        int state; // ON or OFF
        int volume;
        int maxChannel; // 频道的最大数
        int channel; // 当前的频道号
        int mode; // Antenna or Cable
        int input; // TV or DVD
    public:
        // constructor
        Tv(int st = OFF, int mc = 125) : state(st), maxChannel(mc), volume(5),
                                            channel(2), mode(CABLE), input(TV) {}
        // 切换开关
        void switchOnOff() { state = (state == OFF) ? ON : OFF; }
        bool isOn() const { return state == ON; } // 是否为ON
        bool volUp(); // 音量增加
        bool volDown(); // 音量减少
        void nextChan(); // 下个频道
        void preChan(); // 上个频道
        void switchMode() { mode = (mode == CABLE) ? ANTENNA: CABLE; } // 切换模式
        void switchInput() { input = (input == TV) ? DVD : TV; } // 切换输入源
        void displaySetting() const; // 展示所有设置
    };

    class Remote {
    private:
        int mode; // 切换电视机的模式 TV or DVD
    public:
        // constructor
        Remote(int m = Tv::TV) : mode(m) {}
        void switchOnOff(Tv & t) { t.switchOnOff(); }
        bool volUp(Tv & t) { return t.volUp(); }
        bool volDown(Tv & t) { return t.volDown(); }
        void nextChan(Tv & t) { return t.nextChan(); }
        void preChan(Tv & t) { return t.preChan(); }
        void setChan(Tv & t, int c) { t.channel = c; }
        void switchMode(Tv & t) { t.switchMode(); }
        void switchInput(Tv & t) { t.switchInput(); }
    };
}

/**
 * 友元成员函数演示
 **/

namespace V2 {
    class Tv;

    class Remote {
    private:
        int mode;
        enum {OFF, ON};
        enum {VOlMINVAL, VOLMAXVAL = 100};
        enum {TV, DVD};
        enum {ANTENNA, CABLE};
    public:
        Remote(int m = TV) : mode(m) {}
        void switchOnOff(Tv & t);
        bool volUp(Tv & t);
        bool volDown(Tv & t);
        void nextChan(Tv & t);
        void preChan(Tv & t);
        void setChan(Tv & t, int c);
        void switchMode(Tv & t);
        void switchInput(Tv & t);
    };

    class Tv {
    public:
        friend void Remote::setChan(Tv & t, int c);
        enum {OFF, ON};
        enum {VOlMINVAL, VOLMAXVAL = 100};
        enum {TV, DVD};
        enum {ANTENNA, CABLE};
    private:
        int state;
        int volume;
        int maxChannel;
        int channel;
        int input;
        int mode;
    public:
        Tv(int st = OFF, int mc = 125) : state(st), volume(5), maxChannel(mc),
                                          channel(1), input(TV), mode(CABLE) {}
        // 切换开关
        void switchOnOff() { state = (state == OFF) ? ON : OFF; }
        bool isOn() const { return state == ON; } // 是否为ON
        bool volUp(); // 音量增加
        bool volDown(); // 音量减少
        void nextChan(); // 下个频道
        void preChan(); // 上个频道
        void switchMode() { mode = (mode == CABLE) ? ANTENNA: CABLE; } // 切换模式
        void switchInput() { input = (input == TV) ? DVD : TV; } // 切换输入源
        void displaySetting() const; // 展示所有设置
    };

    inline void Remote::setChan(Tv &t, int c) { t.channel = c; }
    inline void Remote::nextChan(Tv &t) { t.nextChan(); }
    inline void Remote::preChan(Tv &t) { t.preChan(); }
    inline void Remote::switchOnOff(Tv &t) { t.switchOnOff(); }
    inline void Remote::switchInput(Tv &t) { t.switchInput(); }
    inline void Remote::switchMode(Tv &t) { t.switchMode(); }
    inline bool Remote::volDown(Tv &t) { return t.volDown(); }
    inline bool Remote::volUp(Tv &t) { return t.volUp(); }
}

#endif // FRIEND_H_