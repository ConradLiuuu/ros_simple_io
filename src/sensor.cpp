#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <iostream>
#include "wiringPi.h"
#include <stdio.h>

#define Sensor 4

int main(int argc,char** argv)
{
  ros::init(argc ,argv ,"sensor");
  ROS_INFO("Start RPI Seneor");
  
  wiringPiSetup();
  pinMode(Sensor,INPUT);

  ros::NodeHandle nh;
  
  double freq;
  nh.getParam("/print_freq", freq);
  
  ros::Publisher sensorr_pub = nh.advertise<std_msgs::Int8>("sensorr", 1000, false);

  ros::Rate r(10);
  std_msgs::Int8 msg;
  
  while (ros::ok())
  {
    msg.data = digitalRead(Sensor);
    ROS_INFO("sensor value is %d",msg.data);
    sensorr_pub.publish(msg);
    ros::Duration(freq).sleep();
    ros::spinOnce();
  }
  return 0;
}
