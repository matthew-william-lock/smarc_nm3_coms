#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include "dccl.h"
#include "navreport.pb.h"

#include <labust_msgs/NanomodemRequest.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n("~");
    ros::NodeHandle nh;

    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);
    ros::Publisher nanomodem_pub = nh.advertise<labust_msgs::NanomodemRequest>("nanomodem_request", 1000);

    ros::Rate loop_rate(0.5);

    // Params
    int listener_id;

    // Get the listener ID
    if (n.param<int>("listener_address", listener_id, 0))
    {
        // print the value of the parameter
        ROS_INFO("Got param: %d", listener_id);
    }
    else
    {
        ROS_ERROR("Failed to get param 'listener_address'");
        return 1;
    }

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
            report.set_x(0);
            report.set_y(0);
            report.set_z(-999);
            // report.set_veh_class( testdccl::NavigationReport::AUV );
            report.set_battery_ok(true);
            codec.encode(&encoded_bytes, report);
            ROS_INFO("Encoded message: %s", report.ShortDebugString().c_str());

            // Serialize the protobuf data
            message.data = encoded_bytes;
            ROS_INFO("Publishing %s", message.data.c_str());
            chatter_pub.publish(message);

            // Convert message to uint8[]
            std::vector<uint8_t> myVector(message.data.begin(), message.data.end());

            // Publish the nanomodem request
            labust_msgs::NanomodemRequest request;
            request.header.stamp = ros::Time::now();
            request.req_type = labust_msgs::NanomodemRequest::UNICST;
            request.msg = myVector;
            request.id = listener_id;
            nanomodem_pub.publish(request);
        }

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }

    return 0;
}