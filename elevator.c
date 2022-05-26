#pragma config(Sensor, dgtl1,  switch1, sensorTouch)
#pragma config(Sensor, dgtl2,  switch2, sensorTouch)
#pragma config(Sensor, dgtl3,  switch3, sensorTouch)
#pragma config(Sensor, dgtl4,  led1_1,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl5,  led1_2,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl6,  led1_3,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl7,  led2_1,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl8,  led2_2,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl9,  led2_3,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, led3_1,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, led3_2,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, led3_3,  sensorLEDtoVCC)
#pragma config(Motor,  port9,  servo,   tmotorServoStandard, openLoop)

void set_leds(int floor) {
    if (floor == 1) {
        SensorValue(led1_1) = 1;
        SensorValue(led1_2) = 1;
        SensorValue(led1_3) = 1;
        SensorValue(led2_1) = 0;
        SensorValue(led2_2) = 0;
        SensorValue(led2_3) = 0;
        SensorValue(led3_1) = 0;
        SensorValue(led3_2) = 0;
        SensorValue(led3_3) = 0;
    } else if (floor == 2) {
        SensorValue(led1_1) = 0;
        SensorValue(led1_2) = 0;
        SensorValue(led1_3) = 0;
        SensorValue(led2_1) = 1;
        SensorValue(led2_2) = 1;
        SensorValue(led2_3) = 1;
        SensorValue(led3_1) = 0;
        SensorValue(led3_2) = 0;
        SensorValue(led3_3) = 0;
    } else if (floor == 3) {
        SensorValue(led1_1) = 0;
        SensorValue(led1_2) = 0;
        SensorValue(led1_3) = 0;
        SensorValue(led2_1) = 0;
        SensorValue(led2_2) = 0;
        SensorValue(led2_3) = 0;
        SensorValue(led3_1) = 1;
        SensorValue(led3_2) = 1;
        SensorValue(led3_3) = 1;
    } else {
        SensorValue(led1_1) = 0;
        SensorValue(led1_2) = 0;
        SensorValue(led1_3) = 0;
    }
}

void move_servo(int position) {
	int i = motor[servo];
	int speed = 1;
	if (i < position) {
		for (; i < position; i++) {
			motor[servo] = i;
			wait(speed/20);
		}
	} else if (i > position) {
		for (; i > position; i--) {
			motor[servo] = i;
			wait(speed/20);
		}
	}
}

void to_1() {
    move_servo(-127);
    set_leds(1);
}

void to_2() {
    move_servo(0);
    set_leds(2);
}

void to_3() {
    move_servo(127);
    set_leds(3);
}

task main() {
    int counter = 0;
    to_1();
    while (true) {
        if (SensorValue(switch1) == 1) {
            to_1();
            counter = 0;
        } else if (SensorValue(switch2) == 1) {
            to_2();
            counter = 0;
        } else if (SensorValue(switch3) == 1) {
            to_3();
            counter = 0;
        }
        counter++;
        wait(1);
        if (counter == 10) {
            counter = 0;
            to_1();
        }
    }
}
