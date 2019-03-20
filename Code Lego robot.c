#include <kipr/botball.h>


void gripper_startpoint(void);    			// moves the gripper to front for the citiziens and water dots 
void lowposition(void);					// lowers the gripper to the floor by driving down the igus slide
void lowpositiondots(void);				// opens the gripperarm and turns the whole gripper by 45° to push the water dots ahead
void highposition(void);				// highers the gripper to the floor by driving up the igus slide
void gripper_download(void);				// turns the gripper back to the loading area
void forward_to_black(void);				// moves the robot to the next black line
		

void gripper_turn(void);				// turns the gripperconstruct 
void gripper_open(void);				// opens the gripperarm 
void turn_robot_right(int turn_ticks);			// turns the robot right; angle depends on the ticks
void turn_robot_left(int turn_ticks);			// turns the robot left; angle depends on the ticks	
void move_robot_forward(int distance_ticks);		// moves the robot forward the given distance (distance_ticks)
void move_robot_backward(int distance_ticks);		// moves the robot backward the given distance (distance_ticks)
void follow_black_line(int distance_ticks);		// follows the black line until the distance (distance_ticks) is reached


void sort_skybridge(void);				// sorts (servo on the loading area) the citiziens from the skybridge (green, red, green)
void sort_underbridge(void);				// sorts the citiziens from under the skybridge (red, green, red)
void open_green_door(void);				// releases the green citiziens on the right side
void open_red_door(void);				// releases the red citiziens on the left side

//---------------initialising----------------
int updown=0;
int motor_left=2;
int motor_right=3;
int turn_ticks_1=1150;					// ticks to turn by 90°
int distance_ticks_1=11000;
int turn_ticks_2=900;					// ticks to turn by 75°		

//--------------servo defines----------------
int arm_serv=0;
int turn_serv=2;
int gripper_serv=1;
int sort_serv = 3;

//--------------servo positions--------------
int front_serv_pos = 2037;
int left_serv_pos=1230;
int close_serv_pos=1750;

//--------------analogsensor colors-----------------
int blackngrey = 3000;
int blue = 1200;


//-------------------main-------------------			
int main()
{

    // move to the water dots on the left side
	
    printf("Lets start");
    move_robot_forward(1500); 
    forward_to_black();
    move_robot_forward(200);
    turn_robot_left(turn_ticks_1);
    forward_to_black();
    move_robot_forward(2350);
    turn_robot_right(turn_ticks_1);
    forward_to_black();
    move_robot_forward(456);
    turn_robot_right(778);
    enable_servos();
    gripper_startpoint()
    lowpositiondots();
    
    forward_to_blue();
    follow_blue_line();
    highposition();
    
    /* take citiziens underbrigde
    enable_servos();
    gripper_startpoint();
    lowposition();
    msleep(1000);
    highposition();
    gripper_download();
    msleep(2000);
    sort_underbridge();
    msleep(2000);
    open_green_door();
    msleep(1000);
    open_red_door();*/
    
    disable_servos();
        
    return 0;
}

//---------------subprograms---------------

void gripper_startpoint(void)
{
    int position_servo=0;
    								// turn the gripper slowly to the front
    while(position_servo <= front_serv_pos)
    {
        position_servo=position_servo+40;
        msleep(50);
   	set_servo_position(arm_serv, position_servo);			
    }
    msleep(1000);
    								// turn the gripper in the right position
    set_servo_position(turn_serv, left_serv_pos);
    set_servo_position(gripper_serv, close_serv_pos);
        
}
void lowposition(void){
    int l=0;
    								// turn the gripper in the "citiziens" position
    set_servo_position(turn_serv, 1230);
    set_servo_position(gripper_serv, 486);
    
    while(digital(1)==0) 					//until the floor is reached
    {
        motor(updown,-50);     
    }
     
    while (l<250)						// higher the gripper a bit
	{
        l++;
        motor(updown,50);
    }
    ao();
	
    msleep(2000);
    set_servo_position(gripper_serv, 1750);			// opens the gripperarm
    
}

void lowpositiondots(void){
    int l=0;
    								// turn the gripper in the pushing - position
    set_servo_position(turn_serv, 760);
    set_servo_position(gripper_serv, 400);
    
    while(digital(1)==0)
    {
        motor(updown,-50);     
    }
    ao();
   								// higher the gripperconstruct a bit from the floor
    while (l<250){
        l++;
        motor(updown,50);
    }
     
}

void highposition(void){
    int t=0;
    while(digital(0)==0)
    {
        motor(updown,50);     
    }
    ao();
    								// drive down the igus slide to 
    while (t<750){
        t++;
        motor(updown,-50);
    }
    ao();
    set_servo_position(turn_serv, 350);
    set_servo_position(gripper_serv, 1750);  			// close the gripperarm
    msleep(500);

}

void gripper_download(void){
    int t=0;
    int position_servo2;
    position_servo2=2030; 
	
								// turn the servo back to the payload
	
    while(position_servo2>=10)
    {
        position_servo2=position_servo2-10;
        msleep(25);
        set_servo_position(arm_serv, position_servo2);
    }
								// load down the citiziens
	
    if(position_servo2<=10){
        set_servo_position(turn_serv, 620);
        while(digital(2)==0)
        {
            motor(0,-30);     
        }
        ao();
        msleep(50);
        set_servo_position(1, 1300);
        msleep(5000);
        while(digital(0)==0)
        {
            motor(0,20);     
        }  
        ao();
        while (t<550){
        	t++;
       		motor(updown,-50);
    	}
    	ao();
    }
}


void gripper_turn(void)
{
    int position_servo_3;
    
    position_servo_3=0;
    
    while(position_servo_3<=1250)				// turn the gripper slowly
    {
         position_servo_3=position_servo_3+40;
         msleep(7);
   	 set_servo_position(3, position_servo_3);
    }
}

void gripper_open(void)
{
    int position_servo_2;
    
    position_servo_2=0;
    
    while(position_servo_2<=550)				// turn the gripper slowly	
    {
         position_servo_2=position_servo_2+40;
         msleep(5);
   	 set_servo_position(2, position_servo_2);
    }
}  

void sort_skybridge()
{
   
	set_servo_position(sort_serv, 950);
    	msleep(2000);
	set_servo_position(sort_serv, 1400);
    	msleep(2000);
	set_servo_position(sort_serv, 950);
}

void sort_underbridge()
{
    	set_servo_position(sort_serv, 1300);
    	msleep(2000);
	set_servo_position(sort_serv, 850);
    	msleep(2000);
	set_servo_position(sort_serv, 1300);
    	msleep(2000);
	set_servo_position(sort_serv, 850);
    	msleep(2000);
    	set_servo_position(sort_serv, 1300);
    	msleep(2000);
}

void open_green_door()
{
    
	set_servo_position(sort_serv,2000);
}

void open_red_door()
{
   
	set_servo_position(sort_serv,100);
}
	

void forward_to_black(void){
    
    int motor_left=2;
    int motor_right=3;

    while(analog(0) < blackngrey){				// stop when black is detected
        motor(motor_left,50);
        motor(motor_right,50); 
    }
    ao();
    
}

    
void move_robot_forward(int distance_ticks)
{
  
    cmpc(motor_left);
    cmpc(motor_right);
    
    while(distance_ticks >= gmpc(motor_left) && distance_ticks >= gmpc(motor_right))
    {
    	motor(motor_left,50);
    	motor(motor_right,50);
    } 
    
    ao();
}

void move_robot_backward(int distance_ticks)
{
   
    cmpc(motor_left);
    cmpc(motor_right);
    
    while(distance_ticks >= gmpc(motor_left) && distance_ticks >= gmpc(motor_right))
    {
    	motor(motor_left,-100*0.97);
    	motor(motor_right,-100);
    } 
    
    ao();
}

void turn_robot_right(int turn_ticks)
{
   
    cmpc(motor_left);
    cmpc(motor_right);
    
    while(turn_ticks >= gmpc(motor_left) && turn_ticks >= gmpc(motor_right))
    {
    	motor(motor_left,60);
    	motor(motor_right,-50);
    }    
    motor(motor_left,0);
    motor(motor_right,0);  
}

void turn_robot_left(int turn_ticks)
{
    cmpc(motor_left);
    cmpc(motor_right);
    
    while(turn_ticks >= gmpc(motor_left*0.97) && turn_ticks >= gmpc(motor_right))
    {
    	motor(motor_left,-50);
    	motor(motor_right,60);
    }   
    motor(motor_left,0);
    motor(motor_right,0);
}

void follow_black_line(int distance_ticks){
    
    cmpc(motor_left);
    cmpc(motor_right);
    
    while(distance_ticks <= gmpc(motor_left)){
            if(analog(0)<1600){				//white detected
                motor(motor_right,50);			//turn left
                motor(motor_left,40);
            }
            else{
                if(analog(0) >1600){			//black detected
                    motor(motor_left,50);		//turn right
                    motor(motor_right,40);
                }
            }    
    	
    }
}

void follow_blue_line(void){
    while (digital(8)==0){
        if(analog(0)<blue){				//white detected
            motor(motor_right,50);			//turn left
            motor(motor_left,40);
        }
        else{
            if(analog(0) >blue){			//blue detected
                motor(motor_left,50);			// turn right
                motor(motor_right,40);
            }
        }    
    }
}

void forward_to_blue(void){
    
    int motor_left=2;
    int motor_right=3;
    while(analog(0) < blue){
        motor(motor_left,50);
        motor(motor_right,50); 
    }
    ao();
    
}

