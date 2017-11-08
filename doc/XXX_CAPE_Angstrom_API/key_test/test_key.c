/***********************************************************************
 *******************************key_test********************************
 ***********************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fd;	
	int ret;
	struct input_event *key_ev; 
      
    fd = open("/dev/input/event2", O_RDONLY);
	if(fd<=0)
	{
        printf("open devices error!\n");
		return 0;
	}

	key_ev = malloc(sizeof(struct input_event));
	memset(key_ev,0,sizeof(key_ev));

	while(1)
	{	
        ret = read(fd,key_ev,sizeof(struct input_event)); 
		if(ret < 0)
		{
			printf("read error\n");
			exit(1);
		}
		
	    if(key_ev->type != EV_KEY)
				continue;
		else
		{
			switch(key_ev->code)
			{
				case 100:
					if(0==key_ev->value)
						printf("key0 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key0 is released code ------->%d\n",key_ev->code);
		    		break;
		    	
		    	case 101:
					if(0==key_ev->value)
						printf("key1 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key1 is released code ------->%d\n",key_ev->code);
		    		break;
		    	
		    	case 102:
		    		if(0==key_ev->value)
						printf("key2 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key2 is released code ------->%d\n",key_ev->code);
		    		break;
		    	
		    	case 103:
					if(0==key_ev->value)
						printf("key3 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key3 is released code ------->%d\n",key_ev->code);
		    		break;
		    	
		    	case 104:
					if(0==key_ev->value)
						printf("key4 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key4 is released code ------->%d\n",key_ev->code);
		    		break;

				case 105:
					if(0==key_ev->value)
						printf("key5 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key5 is released code ------->%d\n",key_ev->code);
		    		break;

		    	case 106:
					if(0==key_ev->value)
						printf("key6 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key6 is released code ------->%d\n",key_ev->code);
		    		break;
		    	
		    	case 107:
					if(0==key_ev->value)
						printf("key7 is pressed  code ------->%d\n",key_ev->code);
					else
		    			printf("key7 is released code ------->%d\n",key_ev->code);
		    		break;
				
		    	default:
		    		break;
		    }
		}
	}
	close(fd);	
    return 0;
}

