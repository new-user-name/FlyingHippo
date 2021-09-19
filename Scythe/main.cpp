#include <QCoreApplication>
#include <QtAndroidExtras>

int main(int argc, char *argv[])
{

    //check if program can find our java class and use it
    if(QAndroidJniObject::isClassAvailable("Scythe/SomeJavaClass")) {
        qDebug() << "SUCCESS!.. SOME JAVA CLASS AVAIABLE!";
        QAndroidJniObject someJavaObject = QAndroidJniObject("Scythe/SomeJavaClass");
        //calling object method
        qDebug() << someJavaObject.callObjectMethod<jstring>("sayHello").toString();
        qDebug() << "2 * 3 equals: " << QAndroidJniObject::callStaticMethod<jint>("Scythe/SomeJavaClass", "multiply", "(II)I", 2, 3);
    }

    else {
        qDebug() << "FAIL!.. SOME JAVA CLASS UNAVAIABLE!";
    }

    QCoreApplication a(argc, argv);

    return a.exec();
}
