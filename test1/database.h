#ifndef DATABASE_H
#define DATABASE_H
#include <BookAccess.h>
extern BookAccess bookAccess;
/*检查日期格式*/
static bool checkDate(string date) {
    bool error = false;
    for (int i = 0; i < date.size(); i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        else {
            if (date[i] < '0' || date[i] > '9') {
                error = true;
            }
        }
    }
    if (date[4] != '-' || date[7] != '-') {
        error = true;
    }
    if (date.size() != 10) {
        error = true;
    }
    return error;
}

/*检查是否为数字*/
static bool checkIfNumbers(string str) {
    bool isNumber = true;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            isNumber = false;
        }
    }
    return isNumber;
}
#endif // DATABASE_H
