void int_to_string(unsigned int data, unsigned char buf[])
{
unsigned int mx = 10000;
unsigned char i = 0;
unsigned char c = 0;

	if (data == 0)
	{
		buf[c] = 48;
		c++;
	}
	else
	{
		while(i<5)
		{
		 	if (data>=mx)
			{
				buf[c] = (data/mx)%10 + 48;
				c++;
			}
			mx = mx/10;
			i++;
		}
	}
	buf[c] = 0;
}

void reset_array(unsigned char array[], unsigned char number_of_elements)
{
unsigned char i;

	for (i = 0; i < number_of_elements; i++)
	{
		array[i] = 0;
	}
}

void string_to_int(unsigned char buf[])
{
	unsigned int array[4];
	unsigned int res = 0;
	unsigned char i = 0, k;

	for (k = 0; k < 4; k++)
	{
		while (buf[i] != ',' && i < 25)
		{
			res = res*10 + (buf[i] - '0');
			i++;
		}
		array[k] = res;
		res = 0;
		i++;
	}
	wire_thickness = array[0];
	coil_width = array[1];
	number_of_turns = array[2];
	rotation_speed = array[3];
}
