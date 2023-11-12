#include "Demo.h"
#include "../Exception/Exception.h"
#include "cmath"
// 全局函数
double hmean(double x, double y) {
    if (x == -y)
        throw HmeanException(x, y);
    return 2.0 * x * y / ( x + y);
}

double gmean(double x, double y) {
    if (x < 0 || y < 0)
        throw GmeanException(x, y);
    return std::sqrt(x * y);
}

double means(double x, double y) {
    double atmp, htmp, gtmp;
    Demo temp("Demo temp in the means()");
    
    atmp = ( x + y ) / 2.0;
    
    try {
        htmp = hmean(x, y);
        gtmp = gmean(x, y);
    } catch (HmeanException & err) {
        std::cout << err.getMessage() << std::endl;
        std::cout << "Caught in means().\n";
        throw;
    }
    temp.show();
    return (atmp + gtmp + htmp)  / 3.0;
}

// main 函数
int main() {
    using std::cin;
    using std::cout;
    using std::endl;

    double x, y, z;
    {
        Demo d("Demo d in main()");
        cout << "Please enter 2 numbers:";
        while (cin >> x >> y) {
            try {
                z = means(x, y);
                cout << "The value of means(" << x << ", " << y << ") is " << z << endl;
            } catch (HmeanException & err) {
                cout << err.getMessage() << endl;
                cout << "Caught in main().\n";
            } catch (GmeanException & err) {
                cout << err.getMessage() << endl;
                cout << "Caught in main().\n";
                cout << "Sorry, the process end.\n";
                break;
            }
            cout << "Please enter next pair:";
        }
        d.show();
    }
    return 0;
}