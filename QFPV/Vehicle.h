# ifndef __VEHICLE_H__
# define __VEHICLE_H__
# include <QObject>
# include <QQmlApplicationEngine>
# include <mavlink.h>

class QUdpSocket;

class Vehicle : public QObject
{
        Q_OBJECT

        Q_PROPERTY(int boot_time MEMBER m_boot_time WRITE set_boot_time NOTIFY boot_time_changed);
        Q_PROPERTY(bool armed MEMBER m_armed WRITE set_armed NOTIFY armed_changed);
        Q_PROPERTY(QString flight_mode MEMBER m_flight_mode WRITE set_flight_mode NOTIFY flight_mode_changed);

        Q_PROPERTY(double lat MEMBER m_lat WRITE set_lat NOTIFY lat_changed);
        Q_PROPERTY(double lon MEMBER m_lon WRITE set_lon NOTIFY lon_changed);
        Q_PROPERTY(double alt_rel MEMBER m_alt_rel WRITE set_alt_rel NOTIFY alt_rel_changed);
        Q_PROPERTY(double alt_msl MEMBER m_alt_msl WRITE set_alt_msl NOTIFY alt_msl_changed);
        Q_PROPERTY(double satellites_visible MEMBER m_satellites_visible WRITE set_satellites_visible NOTIFY satellites_visible_changed);
        Q_PROPERTY(double gps_hdop MEMBER m_gps_hdop WRITE set_gps_hdop NOTIFY gps_hdop_changed);

        Q_PROPERTY(double pitch MEMBER m_pitch WRITE set_pitch NOTIFY pitch_changed);
        Q_PROPERTY(double roll MEMBER m_roll WRITE set_roll NOTIFY roll_changed);
        Q_PROPERTY(double yaw MEMBER m_yaw WRITE set_yaw NOTIFY pitch_changed);

        Q_PROPERTY(double x MEMBER m_x WRITE set_x NOTIFY x_changed);
        Q_PROPERTY(double y MEMBER m_y WRITE set_y NOTIFY y_changed);
        Q_PROPERTY(double z MEMBER m_z WRITE set_z NOTIFY z_changed);

        Q_PROPERTY(double vx MEMBER m_vx WRITE set_vx NOTIFY vx_changed);
        Q_PROPERTY(double vy MEMBER m_vy WRITE set_vy NOTIFY vy_changed);
        Q_PROPERTY(double vz MEMBER m_vz WRITE set_vz NOTIFY vz_changed);

        Q_PROPERTY(double speed MEMBER m_speed WRITE set_speed NOTIFY speed_changed);
        Q_PROPERTY(double airspeed MEMBER m_airspeed WRITE set_airspeed NOTIFY airspeed_changed);

        Q_PROPERTY(int battery_percent MEMBER m_battery_percent WRITE set_battery_percent NOTIFY battery_percent_changed);
        Q_PROPERTY(double battery_voltage MEMBER m_battery_voltage WRITE set_battery_voltage NOTIFY battery_voltage_changed);
        Q_PROPERTY(double battery_current MEMBER m_battery_current WRITE set_battery_current NOTIFY battery_current_changed);

        Q_PROPERTY(double home_lat MEMBER m_home_lat WRITE set_home_lat NOTIFY home_lat_changed);
        Q_PROPERTY(double home_lon MEMBER m_home_lon WRITE set_home_lon NOTIFY home_lon_changed);
        Q_PROPERTY(double home_distance MEMBER m_home_distance WRITE set_home_distance NOTIFY home_distance_changed);
        Q_PROPERTY(bool home_known MEMBER m_home_known WRITE set_home_known NOTIFY home_known_changed);
        Q_PROPERTY(int home_course MEMBER m_home_course WRITE set_home_course NOTIFY home_course_changed);
        Q_PROPERTY(int home_heading MEMBER m_home_heading WRITE set_home_heading NOTIFY home_heading_changed);

public:
        Vehicle(QObject *p = NULL);

        void set_boot_time(int v);
        void set_armed(bool v);
        void set_flight_mode(QString v);

        void set_lat(double v);
        void set_lon(double v);
        void set_alt_rel(double v);
        void set_alt_msl(double v);
        void set_satellites_visible(int v);
        void set_gps_hdop(double v);

        void set_x(double v);
        void set_y(double v);
        void set_z(double v);

        void set_vx(double v);
        void set_vy(double v);
        void set_vz(double v);

        void set_roll(double v);
        void set_pitch(double v);
        void set_yaw(double v);

        void set_speed(double v);
        void set_airspeed(double v);

        void set_battery_percent(int v);
        void set_battery_voltage(double v);
        void set_battery_current(double v);

        void set_home_lat(double v);
        void set_home_lon(double v);
        void set_home_known(bool v);
        void set_home_distance(double v);
        void set_home_course(int v);
        void set_home_heading(int v);

signals:
        void boot_time_changed(int v);
        void armed_changed(bool v);
        void flight_mode_changed(QString v);

        void lat_changed(double v);
        void lon_changed(double v);
        void alt_rel_changed(double v);
        void alt_msl_changed(double v);
        void satellites_visible_changed(int v);
        void gps_hdop_changed(double v);

        void x_changed(double v);
        void y_changed(double v);
        void z_changed(double v);

        void vx_changed(double v);
        void vy_changed(double v);
        void vz_changed(double v);

        void roll_changed(double v);
        void pitch_changed(double v);
        void yaw_changed(double v);

        void speed_changed(double v);
        void airspeed_changed(double v);

        void battery_percent_changed(int v);
        void battery_voltage_changed(double v);
        void battery_current_changed(double v);

        void home_lat_changed(double v);
        void home_lon_changed(double v);
        void home_known_changed(bool v);
        void home_distance_changed(double v);
        void home_course_changed(int v);
        void home_heading_changed(int v);

private slots:
    	void mavlinkDatagrams();
    	void mavlinkMessage(mavlink_message_t msg);

private:
        int 	m_boot_time 		= 0;
        bool 	m_armed 		= false;
      	QString m_flight_mode 		= "------";

        double 	m_lat 			= 0.0;
        double 	m_lon 			= 0.0;
        double 	m_alt_rel 		= 0;
        double 	m_alt_msl 		= 0;
        int 	m_satellites_visible 	= 0;
        double 	m_gps_hdop 		= 99.00;

        double 	m_roll 			= 0.0;
        double 	m_pitch 		= 0.0;
        double 	m_yaw 			= 0.0;

        double 	m_x 			= 0;
        double 	m_y 			= 0;
        double 	m_z 			= 0;

        double 	m_vx 			= 0;
        double 	m_vy 			= 0;
        double 	m_vz 			= 0;

        double 	m_speed 		= 0;
        double 	m_airspeed 		= 0;

        double 	m_home_lat 		= 0.0;
        double 	m_home_lon 		= 0.0;
        bool 	m_home_known 		= false;
        double 	m_home_distance 	= 0.0;
        int 	m_home_heading 		= 0;
        int 	m_home_course 		= 0;

        double 	m_battery_current 	= 0.0;
        double 	m_battery_voltage 	= 0.0;
        int 	m_battery_percent 	= 0;

        QUdpSocket      *socket;
};

QObject* vehicleFactory(QQmlEngine *engine, QJSEngine *scriptEngine);

# endif
