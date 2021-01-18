
#include <ros/ros.h>






int  main(int argc, char **argv) {

  ros::init(argc,argv,"scan_param");
  ros::NodeHandle nh;
  // set dos parametros topic y qeue size
  nh.setParam("topscan", "scan");
  nh.setParam("quesize", 100);








  return 0;
}

