#ifndef FRIEND_H_
#define FRIEND_H_

/**
 * ��Ԫ����ʾ
 **/

namespace V1 {
    class Tv {
    public:
        friend class Remote; // �� Remote ������Ϊ Tv �����Ԫ��
        enum {ON, OFF}; // ����
        enum {VOLMINVAL, VOLMAXVAL=100}; // ��������Сֵ�����ֵ
        enum {TV, DVD};
        enum {ANTENNA, CABLE};
    private:
        int state; // ON or OFF
        int volume;
        int maxChannel; // Ƶ���������
        int channel; // ��ǰ��Ƶ����
        int mode; // Antenna or Cable
        int input; // TV or DVD
    public:
        // constructor
        Tv(int st = OFF, int mc = 125) : state(st), maxChannel(mc), volume(5),
                                            channel(2), mode(CABLE), input(TV) {}
        // �л�����
        void switchOnOff() { state = (state == OFF) ? ON : OFF; }
        bool isOn() const { return state == ON; } // �Ƿ�ΪON
        bool volUp(); // ��������
        bool volDown(); // ��������
        void nextChan(); // �¸�Ƶ��
        void preChan(); // �ϸ�Ƶ��
        void switchMode() { mode = (mode == CABLE) ? ANTENNA: CABLE; } // �л�ģʽ
        void switchInput() { input = (input == TV) ? DVD : TV; } // �л�����Դ
        void displaySetting() const; // չʾ��������
    };

    class Remote {
    private:
        int mode; // �л����ӻ���ģʽ TV or DVD
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
 * ��Ԫ��Ա������ʾ
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
        // �л�����
        void switchOnOff() { state = (state == OFF) ? ON : OFF; }
        bool isOn() const { return state == ON; } // �Ƿ�ΪON
        bool volUp(); // ��������
        bool volDown(); // ��������
        void nextChan(); // �¸�Ƶ��
        void preChan(); // �ϸ�Ƶ��
        void switchMode() { mode = (mode == CABLE) ? ANTENNA: CABLE; } // �л�ģʽ
        void switchInput() { input = (input == TV) ? DVD : TV; } // �л�����Դ
        void displaySetting() const; // չʾ��������
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