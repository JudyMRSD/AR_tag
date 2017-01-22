#include <ros/ros.h>
#include <ros/forwards.h>
#include <ros/single_subscriber_publisher.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <visualization_msgs/Marker.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>

// #include <src/TagDetector.h>
// #include <src/TagDetection.h>
// #include <src/TagFamily.h>

// #include "apriltagscpp/TagDetector.h"
// #include "apriltagscpp/TagDetection.h"
// #include "apriltagscpp/TagFamily.h"

#include "TagDetector.h"
#include "TagDetection.h"
#include "TagFamily.h"


// #include <TagDetector.h>
// #include <TagDetection.h>
// #include <TagFamily.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <visualization_msgs/MarkerArray.h>
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <fstream>

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/make_shared.hpp>

#include "apriltags.h"
#include <apriltags/AprilTagDetections.h>
#include <apriltags/AprilTagDetection.h>

#include<tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

using namespace std;

//subscriber
//subscribes the /apriltags/detections  topic


//rostopic info
//apriltags/AprilTagDetections


void chatterCallback(const apriltags::AprilTagDetections::ConstPtr& msg)
{
  //ROS_INFO("AprilTags node started.");

  //cout<<msg->detections[0].pose.position.x;

//update tf
 
  static tf::TransformBroadcaster br;
  tf::Transform tf_kinect_bin;
  tf_kinect_bin.setOrigin(tf::Vector3(msg->detections[0].pose.position.x,msg->detections[0].pose.position.y,msg->detections[0].pose.position.z));
  tf_kinect_bin.setRotation(tf::Quaternion(msg->detections[0].pose.orientation.x,msg->detections[0].pose.orientation.y,msg->detections[0].pose.orientation.z,msg->detections[0].pose.orientation.w));

 //tf_kinect_bin.setOrigin( tf::Vector3(0.0, 2.0, 0.0) );
 //tf_kinect_bin.setRotation( tf::Quaternion(0, 0, 0, 1) );
//send tf to rviz
  br.sendTransform(tf::StampedTransform(tf_kinect_bin, ros::Time::now(), "world","kinect2_rgb_optical_frame"));

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "apriltag_kinect_tf");

  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe<apriltags::AprilTagDetections>("/apriltags/detections", 1, chatterCallback);
 
  ros::spin();

  return 0;
}
