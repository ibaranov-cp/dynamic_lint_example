

#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_lint_example/TutorialsConfig.h>
#include <std_msgs/String.h>

std_msgs::String msg;

void callback(dynamic_tutorials::TutorialsConfig &config, uint32_t level)
{
  ROS_INFO("Reconfigure Request: %d %f %s %s %d",
           config.int_param, config.double_param,
           config.str_param.c_str(),
           config.bool_param ? "True" : "False",
           config.size);
  msg.data = config.str_param.c_str();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamic_tutorials");
  ros::NodeHandle nh;

  dynamic_reconfigure::Server<dynamic_tutorials::TutorialsConfig> server;
  dynamic_reconfigure::Server<dynamic_tutorials::TutorialsConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  ros::Publisher pub = nh.advertise<std_msgs::String>("dynamic_string", 1);

  ROS_INFO("Spinning node");
  ros::Rate rate(10);
  while (ros::ok())
  {
    pub.publish(msg);
    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}
