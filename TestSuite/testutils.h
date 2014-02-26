#ifndef TESTUTILS_H
#define TESTUTILS_H

#define ROOT_TESTDATA "D:/data/coding/ilwis/testdata"

class QIODevice;
class QString;
class QFile;

class Utils
{
public:
    static QFile *openFile(QString relPath)
    {
        QString path = QCoreApplication::applicationDirPath();
        QFile *file = new QFile(path+"/"+relPath);
        if ( !file->open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open file with relPath: " << relPath << "! Please check, if file is deployed before execution!";
        }
        return file;
    }


};

#endif // TESTUTILS_H
