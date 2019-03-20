#include <kipr/botball.h>

//----------------definitions---------------------

//---------------define motor---------------------
int motor_rise = 0;
int motor_extension = 2;

//---------------define servo---------------------
int servo_gripper = 1; 
int servo_rotation = 0;

//------------define servo rotation---------------
int horizontal = 1350;
int vertical = 475;

//------------define servo gripper----------------
int open = 300;
int close_botguy = 1600;
int close_master = 700;
int close_watercube = 400;

//-----------------analog sensors-----------------
int sensor_gripper = 0;
int sensor_line = 2;
int sensor_distance = 3;

//---------------digital sensors------------------
int sensor_height = 0;

//----------sensor dedected something-------------
int gripper_distance = 700;

//-----------------height/ticks-------------------
int skyscrapper1 = 10;
int skyscrapper0 = 1000;
int flor = 100;
int powergrid = 2000;
int ventile = 1000; 
int risen = 4300;
int bottom_extension = 5600;

//---------------------speed----------------------
int fast = 150;
int avg = 90;
int low = 40;

//END---------------definitions-------------------


//--------------function prototypes---------------

void gripper(int *gripped);						// open / close the gripper
void extend_extension(int speed);					// extends the lifting mechanism to the maximum
void retract_extension(int position, int speed);			// extension can be placed on every height and with any speed
void rise_extension(int position, int speed);				// rises the gripper to the highest position
void fold_extension(int position, int speed);				// folding the extension by speed and position
void gripper_rotate(int position, int *gripped);			// rotates the gripper by 90° for the gas valves
	

//END------------function prototypes-------------		
                  


int main()								
{
    int gripped=0;
    enable_servos();
    //create_connect();
    
    //wait_for_light(1)
    msleep(500);
    rise_extension(3800,fast);
    msleep(500);
    extend_extension(fast); 
    gripper_rotate(horizontal, &gripped);
    msleep(500);
    
   	do
    {
    	printf("gripped is now %d\n", gripped);

        gripper(&gripped);  
    }
    while(gripped == 0);
    gripper_rotate(vertical, &gripped); 
    
   
    msleep(2000);
    gripper(&gripped);
    
    msleep(500);
    
    retract_extension(bottom_extension,avg);
    fold_extension(2800,avg);
    
    msleep(500);
    
    
    
    disable_servos();
    //create_disconnect();
    return 0;
}



//-----------------subprogramms--------------------------

void rise_extension(int steps, int speed)				//function to deploy the extension by steps and speed
{
    cmpc(motor_rise);   
  	while(gmpc(motor_rise) <= steps)				//operate in this while loop, until the number of steps is smaller than var1
          {
              motor_power(motor_rise, speed);
          } 
    motor_power(motor_rise, 1);
    msleep(10);
    
}
void fold_extension(int steps, int speed)				//function to deploy the extension by steps and speed
{
    cmpc(motor_rise);   
    steps = steps * (-1);
    speed = speed * (-1);
    
  	while(gmpc(motor_rise) >= steps)				//operate in this while loop, until the number of steps is smaller than var1
          {
              motor_power(motor_rise, speed);
          }   
    ao();
}


void extend_extension(int speed)					//function to deploy the extension with variable speed
{
       
  	while(digital(sensor_height) == 0)				//while condition is fulfilled as long as the digital sensor on the top of the create is not pressed
          {
              motor_power(motor_extension, speed);
          }
  	cmpc(motor_extension);
    ao();
    msleep(2000);
    
 
}
void retract_extension(int steps, int speed)				//function to deploy the extension by steps and speed
{
    cmpc(motor_extension);
    steps = steps * (-1);
    speed = speed * (-1);
    
  	while(gmpc(motor_extension) >= steps)				//operate in this while loop, until the number of steps is smaller than steps
          {
              motor_power(motor_extension, speed);
          }   
    ao();
}


void gripper(int *gripped)						//function to grip the diffrent objects depending on the reflection of the tophat sensor
{									//it will be called in a loop
    int position;
    
    if(*gripped == 1)
    {
        set_servo_position(servo_gripper, open);
        msleep(10);
        
        printf("should be open now\n");
        msleep(10);
        *gripped = 0;
    }
    else
    {
           
  	if(1)						
        position = close_botguy;
    	}
    	else
        {
        	if(0)
        	{
            	position = close_master;
        	}
    		else
        	{
            	position = close_watercube;
        	}
        }
        
       	if(analog(sensor_gripper) < gripper_distance)			//the gripper is only operating if an object is close enough to the tophat sensor 
    	{
    		set_servo_position(servo_gripper, position);
            msleep(10);
            *gripped = 1;
            msleep(500);
            printf("should be closed now %d\n",*gripped);
    		
            
    	}
        else
        {
            *gripped = 0;
            msleep(10);
        }
    
        
        
    }
}


void gripper_rotate(int position, int *gripped)				//function to rotate the gripper it can only rotate if the gripper is closed, otherwise the camera will get damaged
{									//therefor we used a variable of the function gripper()
    if(*gripped == 0)
    {
        set_servo_position(servo_gripper, close_botguy);
        msleep(500);
    	set_servo_position(servo_rotation, position);
        msleep(500);
        set_servo_position(servo_gripper, open);
    }
    else
    {
        set_servo_position(servo_rotation, position);
        msleep(500);
    }
}

