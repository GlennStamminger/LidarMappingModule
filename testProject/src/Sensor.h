#ifndef SENSOR_H
#define SENSOR_H

void SetUartConfig(int baudrate, enum databits, enum parity, enum stopbit, enum flowcontrol, bool refticks);

#endif