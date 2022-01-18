#include "output.h"
Output & Output::operator<<(int i) {
    printf("%d", i);
    return *this;
}

Output & Output::operator<<(char ch) {
    printf("%c", ch);
    return *this;
}

Output & Output::operator<<(double d) {
    printf("%lf", d);
    return *this;
}

Output & Output::operator<<(Output_Format of) {
    if (of == Output_Format::endl)
        printf("\n");
    return *this;
}