#include <QCoreApplication>
//#include <QtTest>
#include <iostream>
#include "ilwistestclass.h"
#include "testsuite.h"

int main(int argc, char** argv) {

    QCoreApplication app(argc, argv);
    std::string input;

    QString inputData, outputData;
    if ( argc == 1) {
        std::cout << "Enter module list name to be tested\n";
        std::cout << "'all' is run all tests, comma seperated list is a list of modules\n";
     std::cin >> input;
    }else {
        input = argv[1];
        if ( argc > 2){
            inputData = QString(argv[2])    ;
        }
        if ( argc == 4){
            outputData = QString(argv[3])    ;
        }
    }
    if ( input != "") {
        QString s(input.c_str());
        QStringList modules = s.split(",");
        TestSuite::instance()->run(modules, inputData, outputData);
    }
    return 1;

}
