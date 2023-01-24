#ifndef BOOLVALIDATION_H
#define BOOLVALIDATION_H

#include <QValidator>

class boolValidation : public QValidator
{
public:
    explicit boolValidation(QObject *parent = nullptr);
    virtual State validate(QString & str, int & pos) const {
        QRegularExpression rxp = QRegularExpression("1");
        if (str.contains(rxp)) {
            return Acceptable;
        }
        return Invalid;
    }
};

#endif // BOOLVALIDATION_H
