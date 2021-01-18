/*
 * mark_scan.cpp
 *
 *  Created on: Jan 6, 2021
 *      Author: student
 */
#include <ros/ros.h>
//incluyedno el tipo de mensaja que leera el nodo
#include <sensor_msgs/LaserScan.h>
//invluid mensaje para marca
#include <visualization_msgs/Marker.h>




float PObjectX; //POS X
float PObjectY; // POSITION Y




//callback to get the information in topic /scan
void callLaser2(const sensor_msgs::LaserScan::ConstPtr& ranlasers)
{
  //CALLABCK PARA TOMAR LA INFORMACION Y CONVERTIRLA EN COORDENADAS PARA EL MARKER
  float rangel;
  int i=0;
    float ang= -2.356;
    //while para obtener la distancia del objecto y el angulo con respecto al marco de referencia
    // del lazer
     while(i<720)
      {

       if (ranlasers->ranges[i] < 30.0)
       {

         rangel=ranlasers->ranges[i]; //GUARDAR LA DISANCIA A LA CUAL EL OBJETO ESTA

         //calculo de X y Y
         PObjectX = rangel * cosf(ang);
         PObjectY = rangel * sinf(ang);
         //fin calculo X y Y

           break;
       }

       i=i+1;
       ang= ang + 0.0065; /// angulo con respeto al marco de referencia base_link
      }





}
//edn callback callLaser2

int main(int argc, char **argv) {


  //inicializando node ros con el nombre scan_listen
      ros::init(argc,argv,"mark_scan");
     // node handle declaration
      ros::NodeHandle nh;

      //declare subscriber
       ros::Subscriber pub_sub_p = nh.subscribe("scan",100,callLaser2);


       ros::Rate r(1); //rate to loops velocity
       ros::Publisher marker_s = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);


       uint32_t shape = visualization_msgs::Marker::CUBE; //code to say which shape we want



       //loop inf declaration

       while(ros::ok())
       {
         //CODIGO CONFIGURACION DEL MARKER (FORMA, NOMBRE DEL MARKER ,ID,SCALE )
         visualization_msgs::Marker marker;
         marker.header.frame_id = "base_laser";
         marker.ns = "Pillar";
         marker.id = 0;
         marker.type = shape;
           //CODIGO SCALE

         marker.scale.x = 0.5;
         marker.scale.y = 0.5;
         marker.scale.z = 0.5;
           //FIN CODIGO SCALE(ESCALA)

         //COLOR MARKER
         marker.color.r = 0.0f;
         marker.color.g = 1.0f;
         marker.color.b = 0.0f;
         marker.color.a = 1.0;
         // FIN COLOR MARKER
      // FIN CODIGO CONFIGURACION DEL MARKER (FORMA, NOMBRE DEL MARKER ,ID )




         //CODIGO POSITION AND ORIENTATION MARKER
         marker.pose.position.x = PObjectX;
         marker.pose.position.y = PObjectY;
         marker.pose.position.z = 0;


         marker.pose.orientation.x = 0.0;
         marker.pose.orientation.y = 0.0;
         marker.pose.orientation.z = 0.0;
         marker.pose.orientation.w = 1.0;

         //FIN CODIGO POSITION AND ORIENTATION MARKER

         // never delete the marker
         marker.lifetime = ros::Duration();

         //wait for a subscriber
         while (marker_s.getNumSubscribers() < 1)
         {
           if (!ros::ok())
           {
             return 0;

           }

           ROS_WARN_ONCE("Please create a subscriber to the marker");
           sleep(1);
         }
         marker_s.publish(marker);


         ros::spinOnce();
         r.sleep();
       }







}




