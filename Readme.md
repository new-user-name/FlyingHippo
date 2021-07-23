# FlyingHippo
###### 21 июля 2021

##### <b>Установка QT и QTcreator</b>

На страницах QT https://www.qt.io/offline-installers легко перепутать QT и Qtcreator, следим за тем, что ставим.

Сначала QT

https://download.qt.io/official_releases/qt/5.12/5.12.11/qt-opensource-windows-x86-5.12.11.exe.mirrorlist

версия 5.12.11, потом QTcreator

https://www.qt.io/offline-installers

ищем слева Qtcreator, справа появляется линк на загрузку IDE.

https://download.qt.io/official_releases/qtcreator/4.15/4.15.1/

Если где-то спросит, что качать -- качаем opensource. При установке выбираются компиляторы. Если надо потом добавить/убрать компиляторы, то надо сносить QTcreator и устанавливать заново. В корневом каталоге QtCreator есть Maintenance, но она не показывает, что стоит, и что-то мне не нравилось в ней, то ли нельзя убирать/добавить компиляторы, то ли что-то такое.

Отвлекаемся от QT, <b>устанавливаем Gstreamer и примеры.</b></br>
1) Сносим предыдущие инсталляции.</br>
2) Ставим заново отсюда https://gstreamer.freedesktop.org/download/, MSVC 64-bit (VS 2019, Release CRT) оба варианта. При инсталляции нельзя выбирать full, потому что поставит неизвестно куда. Выбираем custom, выбираем путь (c:\gstreamer), потом отмечаем руками все плагины и для development, и для runtime.
3) Примеры качаем одним архивом отсюда https://gitlab.freedesktop.org/gstreamer/gst-docs/, разворачиваем.
4) Лезем в D:\CPP\gst-docs-master\examples\tutorials\vs2010\basic-tutorial-1, открываем там в блокноте файл vcxproj, ищем что-то, похожее на GSTREAMER_1_0_ROOT_X86_64, делаем переменную окружения с таким именем и значением C:\gstreamer\1.0\msvc_x86_64\. Зачем -- не ясно, но сделал.
5) Открываем проект, получивщийся в 3 пункте, в Visual studio (не в Qtcreator). Смотрим тут https://stackoverflow.com/questions/49294685/how-do-i-configure-visual-studio-2017-to-run-gstreamer-tutorials, как конфигурировать папки в свойствах проекта. Похоже, конфигурировать надо каждый проект отдельно, их там 14.</br>
<b>x86_64 в путях меняем на msvc_x86_64</b></br></br>
C/C++ -> Additional Include Directories -></br>
C:\gstreamer\1.0\msvc_x86_64\lib\glib-2.0\include;C:\gstreamer\1.0\msvc_x86_64\include\gstreamer-1.0;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\glib;%(AdditionalIncludeDirectories)</br></br>
Linker -> General -> Adding Library Directories -></br>
C:\gstreamer\1.0\msvc_x86_64\lib;%(AdditionalLibraryDirectories)</br></br>
Linker -> Input -> Additional Dependencies -></br>
gobject-2.0.lib;glib-2.0.lib;gstreamer-1.0.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</br>
все или нет либы надо добавлять -- не ясно.
</br>
22 июля 2021</br>
Там же Linker / All options, ставим "Ignore All Default Libraries" No.</br>
Источник https://stackoverflow.com/questions/34572063/lnk2019unresolved-external-symbol-gstreamer-tutorials-visual-studio-2015</br>
После этого первый пример запускается</br>
Отвлекаемся на "транслятор пакетов", папка FpvMVS. Его можно было бы назвать плейером, но плейер "показывает картинку", а эта программа отправляет пакеты по UDP.</br>
23 июля 2021</br>
Сначала "транслятор" был написан по Linux на чистом С, эта версия под Windows. Что там от "++" -- не ясно.
```
err = WSAStartup(wVersionRequested, &wsaData);
udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
int e = WSAGetLastError();
int g = setsockopt(udp, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(on));
```
кусок, без которого под Windows не работает. Структура fpv занимает 17 байт, в первый подход с этим были проблемы.
