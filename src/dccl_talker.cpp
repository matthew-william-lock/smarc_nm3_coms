#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include "dccl.h"
#include "navreport.pb.h"

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    // Publish a message
    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);

    // DCCL Message
    {

        auto message = std_msgs::String();
        std::string encoded_bytes;
        dccl::Codec codec;

        // Create the DCCL-encoded protobuf message
        codec.load<NavigationReport>();

        NavigationReport report;
        report.set_x( 0 );
        report.set_y( 0 );
        report.set_z( -999 );
        //report.set_veh_class( testdccl::NavigationReport::AUV );
        report.set_battery_ok( true );

        codec.encode( &encoded_bytes, report );

        // Serialize the protobuf data
        message.data = encoded_bytes;
        ROS_INFO("Publishing %s", message.data.c_str());
        chatter_pub.publish(message);
    }


    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}