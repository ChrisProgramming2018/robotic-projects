#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    //  Request a service and pass the velocities to it to drive the robot
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;
  client.call(srv);
  if (!client.call(srv)) {
    ROS_ERROR("Failed to call service drive to target");
  }
}


// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
  int white_pixel = 255;
  // Information about ros sensor_msgs http://docs.ros.org/melodic/api/sensor_msgs/html/msg/Image.html
  // find the white ball in the image
  // Loop through each pixel in the image and check if there's a bright white one
  // 800 height and 800 width step 2400
  float pos = 0;
  float speed = 0;
  float direction = 0;
  bool found = false;
  // image size is 800 x  800 
  int count_pixels = 0;
  int position;
  float offset = 0;
  // iterate of the Image 
  for (int i = 0; i < img.height; i++) {
    for(int j = 0; j < img.step; j++) {
      position = i * img.step + j;
      // chck if pixel is white (255 value)
      if (img.data[position] == white_pixel){ 
        offset += j - img.step / 2.0;   // offset = 0 middle of Image 
        found = true;
        count_pixels++;
      }
    }
  }

  // if in front stop robot
  int stop = 100 * 1000;
  if (count_pixels >= stop) {
   ROS_INFO_STREAM("Infront of Ball  ");
    drive_robot(0.0, 0);
    return;
  }
  // calcuate the stearing of the robot
  pos = 4.0 * offset / count_pixels / (img.step /2.0);
  if (found) {
    drive_robot(0.1, pos);
  } else {
    // search turn 360 degree
    ROS_INFO_STREAM("No Ball found Search Mode ");
    drive_robot(0.1,-1);
  }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
