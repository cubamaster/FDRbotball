#include <kipr/wombat.h>
//motor 0 -right motor 
//motor 1 - left motor

int rw = 0; // right wheel
int lw = 1; // left wheel 
int down = 2047; // stadnard lowest position for the lifting servo
int up = 1740; // standard upper position for the lifting servo 
int open = 600; // standard open position for the claw 
int close = 1248; // standard closed open position for the claw
int claw = 2; // claw servo- port 2
int lift = 1; // lifting servo - port 1 
int grab = 0; // grabbing sevro - port 0
int touch1 = 0; // digital touching sensor - port 0
int touch2 = 1; // digital touching sensor - port 1
// function to follow the line forward. 
void follow_line_1 (double coefficient) {
    while(1 == 1) {
        if (analog(0) > 3000) { // case if robot went over the black tape 
            motor(rw, 100 * coefficient);
            motor(lw, -100);
        } // close if function 
        
        else if(analog(0) < 3000) { // case if robot went over the white board
            motor(rw, 100);
            motor(lw, -100 * coefficient);
        } // close if function
    
    }

}

// function to follow the line backwards. 
void follow_line_2 (double coefficient) {
    while(1 == 1) {
        if (analog(0) > 3000) { // case if robot went over the black tape 
            motor(rw, -100);
            motor(lw, 100 * coefficient);
        } // close if function 
        
        else if(analog(0) < 3000) { // case if robot went over the white board
            motor(rw, -100 * coefficient);
            motor(lw, 100);
        } // close if function
    }
}
int main()
{   
    enable_servos();
    set_servo_position(lift, down);
    set_servo_position(claw, open);
    set_servo_position(grab, up);
    motor(lw, -100);
    motor(rw, 20);
    msleep(2000);
    
    follow_line_1(0.7);
    msleep(20000);
    
    set_servo_position(claw, close);
    set_servo_position(lift, up);
    
    while(get_digital_value(touch1) != 1) {
    	follow_line_1(0.7);
    }
    
    motor(lw, 100);
    motor(rw, -100);
    msleep(2000);
    
    while (get_digital_value(touch2) != 1) {
        follow_line_2(0.7);
    }
    
    set_servo_position(grab, down);
    
    while(get_digital_value(touch1) != 1) {
    	follow_line_2(0.8);
    }
    
    motor(lw, 100);
    msleep(2000);
    
    motor(lw, -100);
    motor(rw, 100);
    msleep(5000);

    disable_servos();
    ao();
    return 0;
} // program ends
