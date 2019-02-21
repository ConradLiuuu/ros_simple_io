#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <iostream>
#include "wiringPi.h"
#include "softPwm.h"
#include <string.h>
#define motor 1
void callback(const std_msgs::Int8::ConstPtr& msg)
{
  if (msg -> data == 25){
  ROS_INFO("motor open");
  softPwmWrite(motor,25);
  }

  if (msg -> data == 10){
  ROS_INFO("motor close");
  softPwmWrite(motor,10);
  }
}
int main(int argc ,char** argv)
{
  ros::init(argc,argv,"motor");
  ROS_INFO("motor on");
  wiringPiSetup();
  softPwmCreate (motor,0,200);
  delay(800);

  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("qq",10,callback);
  ros::spin();  
  /*int degree = 20;
  ROS_INFO("motor open");
  if (degree == 20){
  for(degree = 20; degree < 26; degree++)
  {
    ROS_INFO("degree = %d",degree);
    softPwmWrite(motor,degree);
    delay(800);
  }
  ROS_INFO("motor close");
  for(degree = 25; degree > 19; degree--)
  {
    ROS_INFO("degree = %d",degree);
    softPwmWrite(motor,degree);
    delay(800);
  }

  }*/
/*  ROS_INFO("motor close");
  if (degree == 24){
  for(degree = 24; degree > 19; degree--)
  {
    ROS_INFO("degree = %d",degree);
    softPwmWrite(motor,degree);
    delay(800);
  }
  }*/

  return 0;
}

/*int main(int argc,char** argv)
{
  wiringPiSetup();
  softPwmCreate (motor,0,200);
  int degree;
  degree = atof(argv[1]);
  softPwmWrite(motor,degree);
  delay(100);
  return 0;
}*/

