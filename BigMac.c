#include <kipr/wombat.h>

int lift = 0; // port nubmer for the lifting servo
int claw = 1; // port number for the claw servo 

// up and down positions for the lifting servo
int up = 800;
int down = 0; 

// open and close postiions for the claw servo

int open = 1000;
int close = 0;


void follow_line_right (double coefficient, int position, int power) {
    while(get_create_distance() < position) {
        if(get_create_rfcliff_amt () < 3000) {
            create_drive_direct(power * coefficient, power);
        }
        else {
            create_drive_direct(power, power * coefficient); 
        }
    }
    create_stop();
}

void follow_line (double coefficient, int position, int power, int angle) {
    while(get_create_distance() < position) {
        if(get_create_normalized_angle() < angle) {
            create_drive_direct(power * coefficient, power);
        }
        else {
            create_drive_direct(power, power * coefficient); 
        }
    }
    create_stop();
}

int main()
{
    create_connect();

    set_servo_position(lift, down);
    set_servo_position(claw, open);

    create_drive_direct(-100, -100);
    msleep(1000);

    while(get_create_normalized_angle() >= -80) {
        create_spin_CC(50);
    }
   
    create_drive_direct(100, 100);
    msleep(1000);

    set_servo_position(claw, close);

    create_drive_direct()
    create_stop();
    create_disconnect();
    return 0;
}