# include <QApplication>
# include <QQmlApplicationEngine>
# include <QQuickWindow>
# include <QQuickItem>
# include <QRunnable>
# include <QObject>
# include <QtQuick>

# include <gst/gst.h>

# include "Vehicle.h"

class Pipeline : public QRunnable
{
public:
        Pipeline(GstElement* e)
        {
                this->pipeline = e ? static_cast<GstElement *>(gst_object_ref(e)) : NULL;
        }

        ~Pipeline()
        {
                if (!this->pipeline) {
                        return;
                }
                gst_object_unref(this->pipeline);
        }

        void run()
        {
                if (!this->pipeline) {
                        return;
                }
                gst_element_set_state(this->pipeline, GST_STATE_PLAYING);
        }

private:
        GstElement * pipeline;
};

int main(int argc, char *argv[])
{
        gst_init(&argc, &argv);
        GstElement *pipeline = gst_parse_launch("udpsrc port=5000 close-socket=false multicast-iface=false auto-multicast=true ! h264parse! avdec_h264 ! videoconvert ! glupload ! qmlglsink name=sink", NULL);
 //     	GstElement *pipeline = gst_parse_launch("rtspsrc location=rtsp://deer/video latency=0 buffer-mode=auto ! decodebin ! videoconvert ! glupload ! qmlglsink name=sink", NULL);
        GstElement *sink = gst_bin_get_by_name(GST_BIN (pipeline), "sink");

        QGuiApplication app(argc, argv);

        qmlRegisterSingletonType<Vehicle>("QFPV", 1, 0, "Vehicle", vehicleFactory);
        QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));

        QQuickWindow *rootObject = static_cast<QQuickWindow *>(engine.rootObjects().first());
        QQuickItem *videoItem = rootObject->findChild<QQuickItem *>("videoItem");
        g_object_set(sink, "widget", videoItem, NULL);
        rootObject->scheduleRenderJob(new Pipeline(pipeline), QQuickWindow::BeforeSynchronizingStage);

        int ret = app.exec();

        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        gst_deinit();

        return ret;
}
