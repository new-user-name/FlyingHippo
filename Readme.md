# FlyingHippo
Документ ведётся в Typora, https://typora.io/.

###### 21 июля 2021

##### <b>Установка QT и QTcreator</b>

На страницах QT https://www.qt.io/offline-installers легко перепутать QT и Qtcreator, следим за тем, что ставим.

Сначала QT

https://download.qt.io/official_releases/qt/5.12/5.12.11/qt-opensource-windows-x86-5.12.11.exe.mirrorlist

версия 5.12.11, потом QTcreator

https://www.qt.io/offline-installers

ищем слева Qtcreator, справа появляется линк на загрузку IDE.

https://download.qt.io/official_releases/qtcreator/4.15/4.15.1/

Если где-то спросит, что качать -- качаем opensource. При установке QT (не creator) выбираются компиляторы. Если надо потом добавить/убрать компиляторы, то надо сносить QTcreator и устанавливать заново. Есть MaintenanceTool в каталоге QT (не creator), но он не показывает, что стоит, во всяком случае не ясно, то ли добавлять отмеченные компоненты, то ли удалять, и надо отмечать какие-то "репозитории". Maintenance вызывается и при установке, если уже qt стоит (или криэйтор). При удалении через Revo uninstaller надо не вытереть случайно паки в Вайбере.

Отвлекаемся от QT, <b>устанавливаем Gstreamer и примеры.</b>
1. Сносим предыдущие инсталляции.

2. Ставим заново отсюда https://gstreamer.freedesktop.org/download/, MSVC 64-bit (VS 2019, Release CRT) оба варианта. При инсталляции нельзя выбирать full, потому что поставит неизвестно куда. Выбираем custom, выбираем путь (c:\gstreamer), потом отмечаем руками все плагины и для development, и для runtime.

3. Примеры качаем одним архивом отсюда https://gitlab.freedesktop.org/gstreamer/gst-docs/, разворачиваем.

4. Лезем в D:\CPP\gst-docs-master\examples\tutorials\vs2010\basic-tutorial-1, открываем там в блокноте файл vcxproj, ищем что-то, похожее на GSTREAMER_1_0_ROOT_X86_64, делаем переменную окружения с таким именем и значением C:\gstreamer\1.0\msvc_x86_64\. Зачем -- не ясно, но сделал.

5. Открываем проект, получивщийся в 3 пункте, в Visual studio (не в Qtcreator). Смотрим тут https://stackoverflow.com/questions/49294685/how-do-i-configure-visual-studio-2017-to-run-gstreamer-tutorials, как конфигурировать папки в свойствах проекта. Похоже, конфигурировать надо каждый проект отдельно, их там 14.

  <b>x86_64 в путях ниже меняем на msvc_x86_64</b>

  C/C++ -> Additional Include Directories ->

  `C:\gstreamer\1.0\msvc_x86_64\lib\glib-2.0\include;C:\gstreamer\1.0\msvc_x86_64\include\gstreamer-1.0;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\glib;%(AdditionalIncludeDirectories)`

  Linker -> General -> Adding Library Directories ->

  `C:\gstreamer\1.0\msvc_x86_64\lib;%(AdditionalLibraryDirectories)`

  Linker -> Input -> Additional Dependencies ->

  `gobject-2.0.lib;glib-2.0.lib;gstreamer-1.0.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)`

  все или нет либы надо добавлять -- не ясно.

###### 22 июля 2021

Там же Linker / All options, ставим "Ignore All Default Libraries" No.

Источник https://stackoverflow.com/questions/34572063/lnk2019unresolved-external-symbol-gstreamer-tutorials-visual-studio-2015

После этого первый пример запускается.

Отвлекаемся на "транслятор пакетов", папка FpvMVS. Его можно было бы назвать плейером, но плейер "показывает картинку", а эта программа отправляет пакеты по UDP.

###### 23 июля 2021

Сначала "транслятор" был написан по Linux на чистом С, эта версия под Windows. Что там от "++" -- не ясно.

```
err = WSAStartup(wVersionRequested, &wsaData);
udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
int e = WSAGetLastError();
int g = setsockopt(udp, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(on));
```
кусок, без которого под Windows не работает. Структура fpv занимает 17 байт, в первый подход с этим были проблемы.

Запускаем программу, появляется пустая консоль. Запускаем Wireshark, выбираем Loopback Adapter, видим пакеты. Пакетов должно быть много, идут непрерывно. Адреса, куда идут пакеты, и проигрываемый файл видны в тексте программы. Дальше пока ничего не делаем, возвращаемся к первому примеру Gstreamer (см. вчера).

https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c

Там всё объясняется, но надо прокомментировать.

1) ```c
   /* Initialize GStreamer */
     gst_init (&argc, &argv);
   ```

тут что-то где-то взводится, в ООП-нотации было бы что-то типа Gstreamer gs = new Gstreamer(), соответственно всё происходящее было бы внутри объекта, а здесь оно происходит где-то.

2. ```c
     /* Build the pipeline */
     pipeline =
         gst_parse_launch
         ("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",
         NULL);
   ```

здесь взводятся, как ни странно, две переменные -- pipeline и playbin. В ООП был бы возврат тюпля методом (например), если надо сделать строго в одну строку, или что-то с out.

3. ```c
   /* Start playing */
     gst_element_set_state (pipeline, GST_STATE_PLAYING);
   ```

В ООП было бы что-то типа gs.Play(pipeline), здесь же отдельная функция для изменения состояния, находится в глобальном пространстве имён, переключается ключом GST_STATE_PLAYING.

4. ```c
   bus = gst_element_get_bus (pipeline);
   ```

Скорее всего функция выше может упасть или закончиться, она что-то изменит в результате падения или окончания в pipeline, и новое сосотяния pipeline можно прожевать gst_element_get_bus.

5. ```c
   msg =
         gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
         GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
   ```

Отдельная функция для получения сообщения.

6. ```c
   /* Free resources */
     if (msg != NULL)
       gst_message_unref (msg);
     gst_object_unref (bus);
     gst_element_set_state (pipeline, GST_STATE_NULL);
     gst_object_unref (pipeline);
     return 0;
   ```

Печатаем сообщение и освобождаем ресурсы.

###### 24 июля 2021 года

Отвлекаемся от примеров Gstreamera и возвращаемся к связке "транслятор пакетов + плейер под Виндоус". Плейер запускается из Qtcreator, папка QFPV.

Под MSVC QFPV не компилится. Идём в tools/options/build and run, вкладка general, выключаем там с лева внизу jom. jom отвечает за распараллеливание компиляции, связано ли это с тем, процессор Intel или Amd -- не ясно, на одном ядре компилит медленно, но без ошибок. Есть ошибки в логе с xcopy, но добавление опции /С в pro-файл не помогло.

*Это не спасло от падения в рантайме, но пусть остаётся -- поможет при добавлении компиляторов дла Андроида. Ставим через Maintenance Tool MinGW в максимальным номером и разрядностью, слева в Qtcreator выбираем гаечный ключ и меняем компилятор на MinGW.*

Ищем `gst-plugins-good`, это набор плагинов для Gstreamera. Качаем его, но только ту версию, которая по номеру совпадает с версией самого Gstreamer. Поставил в папку CPP, не в папку Gstreamer. Лезем там в ext/qt, видим набор файлов, из них надо сделать dll, это будет нужный и пока отсутствующий плагин для Жстримера [*почему так -- см. следующий день*]. 

`C:\gstreamer\1.0\msvc_x86_64\bin` -- надо добавить в path, возможно, путь надо будет подправить, если компилятор другой.

`C:\gstreamer\1.0\msvc_x86_64\` -- путь к самому Жстримеру, его надо дописать в pro файл в QTcreator (то же замечание про путь).

Полученную dll надо скопировать сюда `C:\gstreamer\1.0\msvc_x86_64\lib\gstreamer-1.0\`, только один dll файл.

Деталь про плагин: для Gstreamer есть "просмотрщик" установленных плагинов, но он не увидит этот плагин, даже если очистить кэш плагинов. Кэш плагинов сидит тут

`C:\Users\user\AppData\Local\Microsoft\Windows\INetCache`

 Цитата из моего поста на форуме:

\`> gst-inspect-1.0 gstqmlgl.dll`

`gives me` 

`(gst-inspect-1.0:3360): GStreamer-WARNING **: 23:25:49.199: Failed to load plugin 'gstqmlgl.dll': 'gstqmlgl.dll': The specified module could not be found.`

`Could not load plugin file: Opening module failed: 'gstqmlgl.dll': The specified module could not be found.`

Но QFPV всё равно скомпилится. Запускаем его, запускаем транслятор и видим фильм в окне.

Про вьюер пакетов
https://stackoverflow.com/questions/36467649/whats-wrong-with-this-gstreamer-pipeline

###### 25 июля 2021 года

Дополнение по компиляции QFPV под MinGW и MSVC.

Сначала компилим под MinGW [*это продолжение вчерашней линии, потом стало ясно, что и под MSVC работает*]. Несмотря на то, что в main.qml видно, что не найден GLVideoItem, компиляция проходит успешно. Ошибка возникает только во время выполнения -- не ясно, почему так. **В прошлый заход этой ошибки я не видел и раскручивал задачу со стороны ошибки рантайма**. Читаем http://gstreamer-devel.966125.n4.nabble.com/Import-Error-when-Integrating-Qt-and-GStreamer-td4697144.html,  проверяем наличие нужного плагина в установке Gstreamer. В папке `C:\gstreamer\1.0\msvc_x86_64\lib\gstreamer-1.0` запускаем терминал, в нём

`gst-inspect-1.0` -- показывает список всех плагинов, длинный,

`gst-inspect-1.0 qmlglsink` -- показывает, что плагина нет

`gst-inspect-1.0 a52dec` -- а этот плагин есть

Дальше решаем скомпилировать `D:\CPP\gst-plugins-good-1.18\ext\qt` как dll и перенести в каталог плагинов. Открываем в QTcreator .pro файл, меняем в нём `GSTREAMER_PATH=C:/gstreamer/1.0/msvc_x86_64` . После билда поднимаемся на один уровень выше, видим папку с длинным именем, в ней папка Debug. Там нам нужна только dll. Её копируем в `C:\gstreamer\1.0\msvc_x86_64\lib\gstreamer-1.0`. После копирования dll ошибка в qml файле проекта пропадает.

