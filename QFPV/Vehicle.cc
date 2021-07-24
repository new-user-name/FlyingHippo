# include <QUdpSocket>
# include "Vehicle.h"

QObject* vehicleFactory(QQmlEngine *engine, QJSEngine *scriptEngine)
{
        Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)

        return new Vehicle();
}

Vehicle::Vehicle(QObject *parent)
	: QObject(parent)
{
        socket = new QUdpSocket(this);
        socket->bind(14550, QUdpSocket::ShareAddress);
        connect(socket, &QUdpSocket::readyRead, this, &Vehicle::mavlinkDatagrams);
}

void Vehicle::set_boot_time(int v)
{
        if (m_boot_time != v) {
                emit boot_time_changed(m_boot_time = v);
        }
}

void Vehicle::set_armed(bool v)
{
        if (m_armed != v) {
                emit armed_changed(m_armed = v);
        }
}

void Vehicle::set_flight_mode(QString v)
{
        if (m_flight_mode != v) {
                emit flight_mode_changed(m_flight_mode = v);
        }
}

void Vehicle::set_lat(double v)
{
        if (m_lat != v) {
                emit lat_changed(m_lat = v);
        }
}

void Vehicle::set_lon(double v)
{
        if (m_lon != v) {
                emit lon_changed(m_lon = v);
        }
}

void Vehicle::set_alt_rel(double v)
{
        if (m_alt_rel != v) {
                emit alt_rel_changed(m_alt_rel = v);
        }
}

void Vehicle::set_alt_msl(double v)
{
        if (m_alt_msl != v) {
                emit alt_msl_changed(m_alt_msl = v);
        }
}

void Vehicle::set_satellites_visible(int v)
{
        if (m_satellites_visible != v) {
                emit satellites_visible_changed(m_satellites_visible = v);
        }
}

void Vehicle::set_gps_hdop(double v)
{
        if (m_gps_hdop != v) {
                emit gps_hdop_changed(m_gps_hdop = v);
        }
}

void Vehicle::set_roll(double v)
{
        if (m_roll != v) {
                emit roll_changed(m_roll = v);
        }
}

void Vehicle::set_pitch(double v)
{
        if (m_pitch != v) {
                emit pitch_changed(m_pitch = v);
        }
}

void Vehicle::set_yaw(double v)
{
        if (m_yaw != v) {
                emit yaw_changed(m_yaw = v);
        }
}

void Vehicle::set_x(double v)
{
        if (m_x != v) {
                emit x_changed(m_x = v);
        }
}

void Vehicle::set_y(double v)
{
        if (m_y != v) {
                emit y_changed(m_y = v);
        }
}

void Vehicle::set_z(double v)
{
        if (m_z != v) {
                emit z_changed(m_z = v);
        }
}

void Vehicle::set_vx(double v)
{
        if (m_vx != v) {
                emit vx_changed(m_vx = v);
        }
}

void Vehicle::set_vy(double v)
{
        if (m_vy != v) {
                emit vy_changed(m_vy = v);
        }
}

void Vehicle::set_vz(double v)
{
        if (m_vz != v) {
                emit vz_changed(m_vz = v);
        }
}


void Vehicle::set_speed(double v)
{
        if (m_speed != v) {
                emit speed_changed(m_speed = v);
        }
}

void Vehicle::set_airspeed(double v)
{
        if (m_airspeed != v) {
                emit airspeed_changed(m_airspeed = v);
        }
}

void Vehicle::set_home_lat(double v)
{
        if (m_home_lat != v) {
                emit home_lat_changed(m_home_lat = v);
        }
}

void Vehicle::set_home_lon(double v)
{
        if (m_home_lon != v) {
                emit home_lon_changed(m_home_lon = v);
        }
}

void Vehicle::set_home_known(bool v)
{
        if (m_home_known != v) {
                emit home_known_changed(m_home_known = v);
        }
}

void Vehicle::set_home_distance(double v)
{
        if (m_home_distance != v) {
                emit home_distance_changed(m_home_distance = v);
        }
}

void Vehicle::set_home_heading(int v)
{
        if (m_home_heading != v) {
                emit home_heading_changed(m_home_heading = v);
        }
}

void Vehicle::set_home_course(int v)
{
        if (m_home_course != v) {
                emit home_course_changed(m_home_course = v);
        }
}

void Vehicle::set_battery_current(double v)
{
        if (m_battery_current != v) {
                emit battery_current_changed(m_battery_current = v);
        }
}

void Vehicle::set_battery_voltage(double v)
{
        if (m_battery_voltage != v) {
                emit battery_voltage_changed(m_battery_voltage = v);
        }
}

void Vehicle::set_battery_percent(int v)
{
        if (m_battery_percent != v) {
                emit battery_percent_changed(m_battery_percent = v);
        }
}
void Vehicle::mavlinkMessage(mavlink_message_t msg)
{
        switch (msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
                {
                        mavlink_heartbeat_t heartbeat;
                        mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                        MAV_MODE_FLAG mode = (MAV_MODE_FLAG)heartbeat.base_mode;

                        set_armed(mode & MAV_MODE_FLAG_SAFETY_ARMED);
                }
                break;

        case MAVLINK_MSG_ID_SYS_STATUS:
                {
                        mavlink_sys_status_t sys_status;
                        mavlink_msg_sys_status_decode(&msg, &sys_status);

                        set_battery_voltage(sys_status.voltage_battery / 1000.0);
                        set_battery_current(sys_status.current_battery);
                }
                break;

        case MAVLINK_MSG_ID_SYSTEM_TIME:
                {
                        mavlink_system_time_t sys_time;
                        mavlink_msg_system_time_decode(&msg, &sys_time);

                        set_boot_time(sys_time.time_boot_ms);
                }
                break;

        case MAVLINK_MSG_ID_GPS_RAW_INT:
                {
                        mavlink_gps_raw_int_t gps_status;
                        mavlink_msg_gps_raw_int_decode(&msg, &gps_status);

                        set_satellites_visible(gps_status.satellites_visible);
                        set_gps_hdop(gps_status.eph / 100.0);
                }
                break;

        case MAVLINK_MSG_ID_ATTITUDE:
                {
                        mavlink_attitude_t attitude;
                        mavlink_msg_attitude_decode (&msg, &attitude);

                        set_pitch((double)attitude.pitch * 57.2958);
                        set_roll((double)attitude.roll * 57.2958);
                }
                break;

        case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
                {
                        mavlink_local_position_ned_t local_position;
                        mavlink_msg_local_position_ned_decode(&msg, &local_position);

                        set_boot_time(local_position.time_boot_ms);
                        set_x( local_position.x);
                        set_y( local_position.y);
                        set_z(-local_position.z);

                        /*
                        printf("%6.2f %6.2f %6.2f %6.2f %6.2f %6.2f\n",
                               local_position.x,
                               local_position.y,
                               local_position.z,
                               local_position.vx,
                               local_position.vy,
                               local_position.vz);
                        */
                }             
                break;

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
                {
                        mavlink_global_position_int_t global_position;
                        mavlink_msg_global_position_int_decode(&msg, &global_position);

                        set_boot_time(global_position.time_boot_ms);
                        set_lat((double)global_position.lat / 10000000.0);
                        set_lon((double)global_position.lon / 10000000.0);
                        set_alt_rel(global_position.relative_alt / 1000.0);
                        set_alt_msl(global_position.alt / 1000.0);
                        set_yaw(global_position.hdg / 100.0);
                        set_vx(global_position.vx / 100.0);
                        set_vy(global_position.vy / 100.0);
                        set_vz(global_position.vz / 100.0);

                        break;
                }

        case MAVLINK_MSG_ID_HOME_POSITION:
                {
                        mavlink_home_position_t home;
                        mavlink_msg_home_position_decode(&msg, &home);

                        set_home_lat((double)home.latitude  / 10000000.0);
                        set_home_lon((double)home.longitude / 10000000.0);
                }
                break;

        default:
                break;
        }
}


void Vehicle::mavlinkDatagrams()
{
        QByteArray datagram;
        typedef QByteArray::Iterator Iterator;
        mavlink_status_t mavlink_status;
        mavlink_message_t msg;

        while (socket->hasPendingDatagrams()) {
                datagram.resize(int(socket->pendingDatagramSize()));
                socket->readDatagram(datagram.data(), datagram.size());
                for (Iterator i = datagram.begin(); i != datagram.end(); i++) {
                        char c = *i;

                        if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)c, &msg, &mavlink_status)) {
                                mavlinkMessage(msg);
                        }
                }
        }
}
