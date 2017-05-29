#define forward 0
#define backward 1
// bipolar 2 phase full step
unsigned char steps2[] = {0b00000101, 
						  0b00000110,
						  0b00001010,
						  0b00001001};

// MOTOR 1
// bipolar 1 phase full step
// forward
unsigned char steps1f[] = {0b00000001, 
						   0b00000100,
				   		   0b00000010,
						   0b00001000};
// backward
unsigned char steps1b[] = {0b00000001, 
						   0b00001000,
				   		   0b00000010,
						   0b00000100};
// MOTOR 2
// bipolar 1 phase full step
// forward
unsigned char steps1f_motor2[] = {0b00010000, 
						   		  0b01000000,
				   		   		  0b00100000,
						   		  0b10000000};
// backward
unsigned char steps1b_motor2[] = {0b00010000, 
						   		  0b10000000,
				   		   		  0b00100000,
						   		  0b01000000};

unsigned int motor1_step_time = 100;
volatile unsigned int motor1_current_step = 0;
volatile unsigned char motor1_step_index = 0;
volatile unsigned int number_of_steps_motor1 = 0;
volatile unsigned int number_of_turns_motor1 = 0;

unsigned int motor2_step_time;
volatile unsigned int motor2_current_step = 0;
volatile unsigned char motor2_step_index = 0;
volatile unsigned char motor2_direction = forward;

volatile unsigned char temp_motor;
