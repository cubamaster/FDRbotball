#include <kipr/wombat.h> // we always have to include the libraby provided by botoball, in order to use their motors, servors, and sensors.

/**
 * @brief now we need to initiate all the servoes, motors, and sensors to the accoring ports where we connected them on a robot brain
 * value for the right wheel is called rw and will have a port 0
 * value for the left wheel is called lw and will have a port 1
 * value for the bottom servo of the scissors mechanisms is called bottom_s and will have a port 0
 * value for the top servo of the scissors mechanisms is called top_s and will have a port 1
 * value for the back servo of the grabbing mechanisms is called back_s and will have a port 2
 */

int rw = 0;
int lw = 1;
int bottom_s = 0;
int top_s = 1;
int back_s = 2;

/**
 * @brief we also need to set an intial position for all three servos, in order to ensure that every time we start with the same initial setting
 * because we did not measure the inital positions yet, I will asssume the values (ATTENTION: they should and will be changed later)
 * the initial position for the top_s will be 800
 * the initial position for the bottom_s will be 0
 * the initial position for the back_s will be 800
 */

int top_s_init = 1000;
int bottom_s_init = 300;
int back_s_init = 2000;

/**
 * @brief although we don't yet installed the light/line sensor, we will have it later, and therefore we need to include it in our code
 * value for the light sensor will be called line and will have a port 0
 */

int line_left = 0;
int line_right = 1;
/**
 * @brief this is the function that will be used to follow the black tape line
 * it will work on the proportion function and will be excecuted untill the motors will reach a certain
 * cmps - Clears the motor position counter
 * gmpc - Gets the current motor position.
 */

void follow_line_right (double coefficient, int position, int power) {
    cmpc(rw);
    cmpc(lw);
    int i = 0;
    while(i <= position) {
        if (analog(line_left) < 3000) { // case if robot went over the black tape
            motor(rw, power * coefficient);
            motor(lw, -power);
        } // close if function
       
        else if(analog(line_left) > 3000) { // case if robot went over the white board
            motor(rw, power);
            motor(lw, -1 * power * coefficient);
        } // close if function
    i = gmpc(rw);
    }
    freeze(rw); // Active braking to stop a motor.
    freeze(lw);
}

void follow_line_left (double coefficient, int position, int power) {
    cmpc(rw);
    cmpc(lw);
    int i = 0;
    while(i <= position) {
        if (analog(line_right) > 3000) { // case if robot went over the black tape
            motor(rw, power * coefficient);
            motor(lw, -power);
        } // close if function
       
        else if(analog(line_right) < 3000) { // case if robot went over the white board
            motor(rw, power);
            motor(lw, -power * coefficient);
        } // close if function
    i = gmpc(rw);
    }
    freeze(rw); // Active braking to stop a motor.
    freeze(lw);
}


void scissors() {
    int pos;
    int pos_top = get_servo_position(bottom_s);
    // check the position of each motor
    if(get_servo_position(top_s) >= 1300) {
        for (pos = get_servo_position(top_s); pos > 1000; pos -= 1) {
            set_servo_position(top_s, pos);
            set_servo_position(bottom_s, pos_top);
            pos_top -= 1;
            msleep(3);
        }  
    }
    else if(get_servo_position(top_s) < 1300) {
        for (pos = get_servo_position(top_s); pos < 1700; pos += 1) {
            set_servo_position(top_s, pos);
            set_servo_position(bottom_s, pos_top);
            pos_top += 1;
            msleep(3);
        }
    }
}

int main()
{
    enable_servos(); // we need to enable all the sevros before using them
    set_servo_position(top_s, top_s_init);
    msleep(500);
    set_servo_position(bottom_s, bottom_s_init);
  msleep(500);
    set_servo_position(back_s, back_s_init);
    msleep(500);
   
    motor(rw, 30);
    motor(lw, 30);
    msleep(200);
   
    motor(rw, 100);
    motor(lw, -100);
    msleep(1000);
   
    motor(rw, -30);
    motor(lw, -30);
    msleep(200);
   
    set_servo_position(bottom_s, 0);
   
    motor(rw, 100);
    motor(lw, -100);
    msleep(1000);
   
    motor(rw, 30);
    motor(lw, 30);
    msleep(2200);
    freeze(rw);
    freeze(lw);
   
    scissors();
   
    int i;
    for(i = 0; i < 5; i+= 1) {
    follow_line_left(0.8, 1580, 80);
        scissors();
    }
   
    motor(rw, -30);
    motor(lw, -30);
    msleep(4500);
    /**
    set_servo_position(bottom_s, 0);
    msleep(2000);
    printf("Hello World\n");
    scissors();
    msleep(2000);
    scissors();
    //follow_line_right(0.8, 10000, 100);
    **/
   
    return 0;
   
}