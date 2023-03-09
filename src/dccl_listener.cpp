#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include "dccl.h"
#include "navreport.pb.h"

#include <labust_msgs/NanomodemPayload.h>

dccl::Codec codec;

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
void chatterCallback(const labust_msgs::NanomodemPayload::ConstPtr& msg)
{
    ROS_INFO("Raw data: [%s]", msg->msg.data());

    // Decode the message
    std::string encoded_bytes;
    encoded_bytes.assign(msg->msg.begin(), msg->msg.end());

    if(codec.id(encoded_bytes) == codec.id<NavigationReport>())
    {
        NavigationReport r_in;
        codec.decode(encoded_bytes, &r_in);
        std::cout << r_in.ShortDebugString() << std::endl;
    }
}

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{

    // Load the DCCL codecs
    codec.load<NavigationReport>();

    ros::init(argc, argv, "talker");
    ros::NodeHandle n("~");
    ros::NodeHandle nh;

    // Subscribe to "nanomodem_payload"
    ros::Subscriber sub = nh.subscribe("nanomodem_payload", 1000, chatterCallback);

    ros::spin();

    return 0;
}