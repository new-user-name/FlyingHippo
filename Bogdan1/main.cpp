#include <QCoreApplication>
#include <QAndroidJniObject>
#include <QtAndroidExtras>

int fibonacci(int n) {
 return QAndroidJniObject::callStaticMethod<jint>
 ("Bogdan1/BogdanFibonacci" // java class name
 , "fibonacci" // method name
 , "(I)I" // signature
 , n);
 }

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Bogdan tells" << fibonacci(5);

    return a.exec();
}
