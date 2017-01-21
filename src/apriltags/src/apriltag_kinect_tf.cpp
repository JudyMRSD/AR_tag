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
  ROS_INFO("AprilTags node started.");
  cout<<msg->header.frame_id;
}

void updateTF()
{
  static tf::TransformBroadcaster br;
  tf::Transform tf_kinect_bin;
  
  br.sendTransform(tf::StampedTransform(tf_kinect_bin, ros::Time::now(), "map","kinect2_rgb_optal_frame"));

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "apriltag_kinect_tf");

  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe<apriltags::AprilTagDetections>("/apriltags/detections", 1, chatterCallback);
 
  ros::spin();

  return 0;
}




