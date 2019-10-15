#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"



// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities



class SubscribeAndPublish {
 public:
  SubscribeAndPublish() {
    _motor_command_publisher = this->_n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);  
    _service = this->_n.advertiseService("/ball_chaser/command_robot", &SubscribeAndPublish::move_robot, this);
  }
  bool move_robot(ball_chaser::DriveToTarget::Request& req,
      ball_chaser::DriveToTarget::Response& res) {
    ROS_INFO("GoToPositionRequest received - j1:%1.2f, j2:%1.2f", (float)req.linear_x, (float)req.angular_z);
    // Create a motor_command object of type geometry_msgs::Twist
    geometry_msgs::Twist motor_command;
    // Set wheel velocities, forward [0.5, 0.0]
     motor_command.linear.x = (float)req.linear_x;
     motor_command.angular.z =(float)req.angular_z;
     // Publish angles to drive the robot
     _motor_command_publisher.publish(motor_command);
  }

 private:
  ros::NodeHandle _n;   
  ros::ServiceServer _service;
  ros::Publisher _motor_command_publisher;
};


int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");


    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    ROS_INFO("Ready to send joint commands");
    SubscribeAndPublish SAPObject;
    ros::spin();

    return 0;
}
