#include <ros/ros.h>
//incluyedno el tipo de mensaja que leera el nodo
#include <sensor_msgs/LaserScan.h>




//funcion callback
void lasercallback(const sensor_msgs::LaserScan::ConstPtr& ranlaser)
{
  float minrange=30.0;
  int i=0;
  float ang=0;
   while(i<720)
    {
// Algoritmo que imprime el rango en el cual un objeto se encuentra
//      ROS_INFO("ANG %f  DIST  %f",ang,ranlaser->ranges[i]);
//
//      i=i+1;
//      ang=ang + 0.37;

// algortimo para encontrar el range mas chico cuando hay un objeo

     if (ranlaser->ranges[i] < minrange)
     {
       minrange = ranlaser->ranges[i];
     }

     i=i+1;
    }

   ROS_INFO("El objeto esta a %f",minrange);

 }
//end funcion callback





//funcion main
int main(int argc, char **argv) {

// ejemplo de como usar un string en parametros de un funcion
//  std::string tema ="scan";
//  ROS_INFO("%s",tema.c_str());
//  ros::Subscriber sub_scan = nh.subscribe(tema.c_str(),700,lasercallback);


  //declaracion de variables para parametros

    std::string topicscan;
    int quesize;


 //inicializando node ros con el nombre scan_listen
  ros::init(argc,argv,"scan_listen");
 // node handle declaration
  ros::NodeHandle nh;

  // get param
    ros::param::get("/topscan",topicscan);
    ros::param::get("/quesize",quesize);

    //declare subscriber
 ros::Subscriber sub_scan = nh.subscribe(topicscan.c_str(),quesize,lasercallback);




  ros::spin();

  return 0;


}
//end funcion main
