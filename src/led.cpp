#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <iostream>
#include "wiringPi.h"

#define LED 1
int i;

void blink_callback (const std_msgs::Int8::ConstPtr& msg)
{
  //ROS_INFO("Please publish 0-2 bool data to led_blink");
  if (msg->data == 0)
  {
    digitalWrite (LED,HIGH);
    ROS_INFO("LED ON");
  }
  else if (msg->data == 1)
  {
    digitalWrite (LED,LOW);
    ROS_INFO("LED OFF");
  }
  else if (msg->data == 2)
  {
    ROS_INFO("LED blinks ten times");
    
    for (i = 0; i < 10; i++)
    {
      digitalWrite(LED,HIGH);
      ROS_INFO("LED ON");
      delay(500);
    
      digitalWrite(LED,LOW);
      ROS_INFO("LED OFF");
      delay(500);    
    }
  }
}

int main(int argc,char** argv)
{
  ros::init(argc, argv, "blink");
  ROS_INFO("Start RPI LED Blink node");
  wiringPiSetup();
  pinMode(LED, OUTPUT);

  ros::NodeHandle nh;
	
  double freq;
  nh.getParam("/print_freq", freq);
  
  ros::Subscriber sub = nh.subscribe("sensor", 10, blink_callback);
 
  ros::Duration(freq).sleep();  
  ros::spin();
}

