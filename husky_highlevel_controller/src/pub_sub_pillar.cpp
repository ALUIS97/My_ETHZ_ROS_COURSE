#include <ros/ros.h>
//incluyedno el tipo de mensaja que leera el nodo
#include <sensor_msgs/LaserScan.h>
// incluir tip de mensaje twist
#include <geometry_msgs/Twist.h>


float PObjectX; //guarda LA DISTANCIA
float PObjectY; // ANGULO EN RADIANES

//funcion callback callLaser
void callLaser(const sensor_msgs::LaserScan::ConstPtr& ranlasers)
{
   int i=0;
   float ang= 2.356;
   //while para obtener la distancia del objecto y el angulo con respecto al marco de referencia
   // del lazer
    while(i<720)
     {

      if (ranlasers->ranges[i] < 30.0)
      {

        PObjectX=ranlasers->ranges[i]; //GUARDAR LA DISANCIA A LA CUAL EL OBJETO ESTA
        PObjectY=ang; // el angulo al cual se encuentra
          break;
      }

      i=i+1;
      ang= ang - 0.0065; /// angulo con respeto al marco de referencia base_link
     }


  }
//fin de callLaser



int main(int argc, char **argv) {

  //inicializando node ros con el nombre scan_listen
    ros::init(argc,argv,"pub_sub_pillar");
   // node handle declaration
    ros::NodeHandle nh;

    //declare subscriber
     ros::Subscriber pub_sub_p = nh.subscribe("scan",100,callLaser);
     ros::Publisher velo_pub= nh.advertise<geometry_msgs::Twist>("cmd_vel",1000);

     ros::Rate loop_rate(10);

     while (ros::ok())

     {

       //    CONTROL DEL ROBOT CODIGO
                  //PUBLICAR EN /cmd_vel
                geometry_msgs::Twist CONTROL;
                CONTROL.linear.x = 0.2 * PObjectX;
                CONTROL.angular.z= 0.8 * PObjectY;


                velo_pub.publish(CONTROL);

                //fin codigo control del robot


       ros::spinOnce();
       loop_rate.sleep();
     }
  return 0;
}





