# FlyingHippo
Документ ведётся в Typora, https://typora.io/.

[Сборник относящихся к делу ссылок](#Сборник-относящихся-к-делу-ссылок).

Главные "потоки" работы:

1) [Установка QT и QTcreator](#Установка-QT-и-QTcreator).
2) [Установка примеров Gstreamer](#Установка-примеров-Gstreamer).
3) [Запуск "передатчика пакетов" FpvMVS](#Запуск-"передатчика-пакетов"-FpvMVS).
4) [Запуск плейера под Windows](#Запуск-плейера-под-Windows).
5) Запуск плейера под Андроид.
6) Запуск плейера под iOs.

##### Установка QT и QTcreator

На страницах QT https://www.qt.io/offline-installers легко перепутать QT и Qtcreator, следим за тем, что ставим.

Сначала QT

https://download.qt.io/official_releases/qt/5.12/5.12.11/qt-opensource-windows-x86-5.12.11.exe.mirrorlist

версия 5.12.11, потом QTcreator

https://www.qt.io/offline-installers

ищем слева Qtcreator, справа появляется линк на загрузку IDE.

https://download.qt.io/official_releases/qtcreator/4.15/4.15.1/

Если где-то спросит, что качать -- качаем opensource. При установке QT (не creator) выбираются компиляторы. Если надо потом добавить/убрать компиляторы, то надо сносить QTcreator и устанавливать заново. Есть MaintenanceTool в каталоге QT (не creator), но он не показывает, что стоит, во всяком случае не ясно, то ли добавлять отмеченные компоненты, то ли удалять, и надо отмечать какие-то "репозитории". Maintenance вызывается и при установке, если уже qt стоит (или криэйтор). При удалении через Revo uninstaller надо не вытереть случайно паки в Вайбере.



##### Установка примеров Gstreamer

1. Сносим предыдущие инсталляции.

2. Ставим заново отсюда https://gstreamer.freedesktop.org/download/, MSVC 64-bit (VS 2019, Release CRT) оба варианта. При инсталляции нельзя выбирать full, потому что поставит неизвестно куда. Выбираем `custom`, выбираем путь (`c:\gstreamer`), потом отмечаем руками все плагины и для `development`, и для `runtime`.

3. Примеры качаем одним архивом отсюда https://gitlab.freedesktop.org/gstreamer/gst-docs/, разворачиваем.

4. Лезем в `D:\CPP\gst-docs-master\examples\tutorials\vs2010\basic-tutorial-1`, открываем там в блокноте файл vcxproj, ищем что-то, похожее на `GSTREAMER_1_0_ROOT_X86_64`, делаем переменную окружения с таким именем и значением `C:\gstreamer\1.0\msvc_x86_64`\. Зачем -- не ясно, но сделал.

5. Открываем `basic-tutorial-1`, получившийся в 3 пункте, в Visual studio (не в Qtcreator). Смотрим тут https://stackoverflow.com/questions/49294685/how-do-i-configure-visual-studio-2017-to-run-gstreamer-tutorials, как конфигурировать папки в свойствах проекта (скопировано ниже), но на этом пункте ничего не конфигурируем, а идём в 6. 

6. В Студии `view/other views/Property manager`, там находим нужный конфиг, то есть `Debug|x64`, потом контекстное меню `add new project property sheet`, добавляем лист `Gstreamer`, смотрим его `properties` и добавляем туда всё из пункта 5. Сохраняем. Гаечный ключ `Gstreamer` появляется в списке `sheets` самым верхним, т.е. он будет обрабатываться позже всех и иметь приоритет. Что в остальных листах -- не ясно. Теперь лезем на той же вкладке в `basic-tutorial-2` и добавляем `existing property sheet`, выбирая `Gstreamer`. После и первый, и второй пример нормально билдятся.

     *C/C++ -> Additional Include Directories ->*

     *`C:\gstreamer\1.0\msvc_x86_64\lib\glib-2.0\include;C:\gstreamer\1.0\msvc_x86_64\include\gstreamer-1.0;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\;C:\gstreamer\1.0\msvc_x86_64\include\glib-2.0\glib;%(AdditionalIncludeDirectories)`*

     *Linker -> General -> Adding Library Directories ->*

     *`C:\gstreamer\1.0\msvc_x86_64\lib;%(AdditionalLibraryDirectories)`*

     *Linker -> Input -> Additional Dependencies ->*

     *`gobject-2.0.lib;glib-2.0.lib;gstreamer-1.0.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)`*

     *все или нет либы надо добавлять -- не ясно.*

   *Там же Linker / All options, ставим "Ignore All Default Libraries" No (https://stackoverflow.com/questions/34572063/lnk2019unresolved-external-symbol-gstreamer-tutorials-visual-studio-2015).*

 

##### Запуск "передатчика пакетов" FpvMVS

"Транслятор (передатчик) пакетов", папка FpvMVS. Его можно было бы назвать плейером, но плейер "показывает картинку", а эта программа отправляет пакеты по UDP.

Сначала "транслятор" был написан по Linux на чистом С, эта версия под Windows. Что там от "++" -- не ясно.

```
err = WSAStartup(wVersionRequested, &wsaData);
udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
int e = WSAGetLastError();
int g = setsockopt(udp, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(on));
```
кусок, без которого под Windows не работает. Структура fpv занимает 17 байт, в первый подход с этим были проблемы.

Запускаем программу, появляется пустая консоль. Запускаем Wireshark, выбираем Loopback Adapter, видим пакеты. Пакетов должно быть много, идут непрерывно. Адреса, куда идут пакеты, и проигрываемый файл видны в тексте программы.





Дальше пока ничего не делаем, возвращаемся к первому примеру Gstreamer (см. вчера).

https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c

Там всё объясняется, но надо прокомментировать.

1) ```c
   /* Initialize GStreamer */
     gst_init (&argc, &argv);
   ```

тут что-то где-то взводится, в ООП-нотации было бы что-то типа `Gstreamer gs = new Gstreamer()`, соответственно всё происходящее было бы внутри объекта, а здесь оно происходит где-то.

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

В ООП было бы что-то типа `gs.Play(pipeline)`, здесь же отдельная функция для изменения состояния, находится в глобальном пространстве имён, переключается ключом `GST_STATE_PLAYING`.

4. ```c
   bus = gst_element_get_bus (pipeline);
   ```

Скорее всего функция выше может упасть или закончиться, она что-то изменит в результате падения или окончания в pipeline, и новое состояния pipeline можно прожевать `gst_element_get_bus`.

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

##### Запуск плейера под Windows

Плейер запускается из Qtcreator, папка QFPV.

Под MSVC QFPV не компилится при дефолтных настройках. Идём в tools/options/build and run, вкладка general, выключаем там с лева внизу jom. jom отвечает за распараллеливание компиляции, связано ли это с тем, процессор Intel или Amd -- не ясно, на одном ядре компилит медленно, но без ошибок. Есть ошибки в логе с xcopy, но добавление опции /С в pro-файл не помогло.

В `main.qml` видно, что не найден `GLVideoItem`. Читаем http://gstreamer-devel.966125.n4.nabble.com/Import-Error-when-Integrating-Qt-and-GStreamer-td4697144.html.

Ищем `gst-plugins-good`, это набор плагинов для Gstreamera. Качаем его, но только ту версию, которая по номеру совпадает с версией самого Gstreamer. Ставим в папку CPP, не в папку Gstreamer. Проверяем наличие нужного плагина (`qmlglsink`) в установке `Gstreamer`. Для этого в папке `C:\gstreamer\1.0\msvc_x86_64\lib\gstreamer-1.0` запускаем терминал, в нём

`gst-inspect-1.0` -- показывает список всех плагинов, длинный,

`gst-inspect-1.0 qmlglsink` -- показывает, что плагина, нужного нам, нет

`gst-inspect-1.0 a52dec` -- а этот плагин есть

Лезем там в `ext/qt`, видим набор файлов, из них надо сделать dll, это будет нужный и пока отсутствующий плагин для `Gstreamer`. 

`C:\gstreamer\1.0\msvc_x86_64\bin` -- надо добавить в path, возможно, путь надо будет подправить, если компилятор другой.

Дальше компилируем `D:\CPP\gst-plugins-good-1.18\ext\qt` как dll и переносим в каталог плагинов. Открываем в QTcreator .pro файл, меняем в нём `GSTREAMER_PATH=C:/gstreamer/1.0/msvc_x86_64` . После билда поднимаемся на один уровень выше, видим папку с длинным именем, в ней папка Debug. Там нам нужна только dll. Её копируем в `C:\gstreamer\1.0\msvc_x86_64\lib\gstreamer-1.0`. После копирования dll ошибка в qml файле проекта пропадает.

Деталь про плагин: "просмотрщик" установленных плагинов, но он не увидит наш плагин, даже если очистить кэш плагинов. Кэш плагинов сидит тут

`C:\Users\user\AppData\Local\Microsoft\Windows\INetCache`

 Цитата из моего поста на форуме:

\`> gst-inspect-1.0 gstqmlgl.dll`

`gives me` 

`(gst-inspect-1.0:3360): GStreamer-WARNING **: 23:25:49.199: Failed to load plugin 'gstqmlgl.dll': 'gstqmlgl.dll': The specified module could not be found.`

`Could not load plugin file: Opening module failed: 'gstqmlgl.dll': The specified module could not be found.`

Про вьюер пакетов дополнительно.
https://stackoverflow.com/questions/36467649/whats-wrong-with-this-gstreamer-pipeline

Но QFPV всё равно скомпилится. Запускаем его (из QTcreator), запускаем транслятор FpvMVS (из Visual Studio) и видим фильм в окне.

![QFPV показывает фильм, транслируемый FpvMVS](https://raw.githubusercontent.com/new-user-name/FlyingHippo/main/Images/QFPV_windows.png)

Возвращаемся ко второму примеру Gstreamer (см. 23 июля). Туда надо каким-то образом экспортировать опции первого примера. 

Разбор второго примера.

https://gstreamer.freedesktop.org/documentation/tutorials/basic/concepts.html?gi-language=c

```c
/* Create the elements */
  source = gst_element_factory_make ("videotestsrc", "source");
  sink = gst_element_factory_make ("autovideosink", "sink");
```

В обоих случаях первый аргумент -- тип создаваемого элемента, при этом он задаётся строкой. Как минимум тип можно было бы задать через Enum, но скорее всего через что-то типа Интерфейс `IElement`, например `IElement videotestsrc = new Videotestsrc()` , и у этого же объекта задать имя. Здесь же идёт простая свалка параметров, понятная только авторам.

```c
 /* Create the empty pipeline */
  pipeline = gst_pipeline_new ("test-pipeline");
```

Этот приём я разбирал выше -- меняется какой-то глобал стейт, и снова вместо объекта конкретного типа передаётся "ключ" `test-pipeline`, по которому он где-то там создаётся. Дальше пихаем оба элемента в пайплайн и, как если бы этого было мало, их ещё надо соединить, что может и не получиться.

```c
/* Modify the source's properties */
  g_object_set (source, "pattern", 0, NULL);
```

У элементов Жстримера есть геттеры и сеттеры, работают как вот такие вот "отдельные" функции. Дальше там проверка на ошибки, вроде всё понятно. Всё идёт прямо, никаких callbacks, но видео идёт в отдельном потоке, который говорит с Gstreamer bus. То есть создаём элементы, создаём пайплайн, пихаем элементы в пайплайн, связываем их, меняем стейт пайплайна и слушаем bus.

##### Сборник относящихся к делу ссылок

[Mavlink]: https://mavlink.io/en/

протокол обмена между дроном и наземной станцией и между системами дрона. Прилжение, работает поверх протокола https://docs.qgroundcontrol.com/master/en/index.html.

[Open.HD]: https://openhd.gitbook.io/open-hd/

связь с дроном через обычные wi-fi передатчики, настроенные особым образом. Есть другой похожий проект, https://github.com/rodizio1/EZ-WifiBroadcast/wiki/General-~-Faq.

Приложение https://github.com/OpenHD/QOpenHD.

