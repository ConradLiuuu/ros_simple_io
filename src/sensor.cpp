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

/*  while(1)
  {
    ROS_INFO("%d",i);
  }*/
  ros::NodeHandle n;
  double freq;
  n.getParam("/print_freq",freq);
  ros::Publisher sensorr_pub = n.advertise<std_msgs::Int8>("sensorr",1000,false);
  //led_blink is topic name
  ros::Rate r(10);
  while (ros::ok())
  {
    std_msgs::Int8 msgaa;
    msgaa.data = digitalRead(Sensor);
    ROS_INFO("sensor value is %d",msgaa.data);
    sensorr_pub.publish(msgaa);
    ros::Duration(freq).sleep();
    ros::spinOnce();
//    r.sleep();
  }
  return 0;
}
