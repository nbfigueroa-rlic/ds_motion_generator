/*
 * Copyright (C) 2018 Learning Algorithms and Systems Laboratory, EPFL, Switzerland
 * Author:  Nadia Figueroa
 * email:   nadia.figueroafernandez@epfl.ch
 * website: lasa.epfl.ch
 *
 * This work was supported by the EU project Cogimon H2020-ICT-23-2014.
 *
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */


#include "ros/ros.h"
#include "lpvDSMotionGenerator.h"
#include <vector>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "lpvDS_motion_generator_node");

  ros::NodeHandle nh;
  double frequency = 500.0;

  // Parameters
  std::string input_topic_name;
  std::string input_target_topic_name;
  std::string output_topic_name;
  std::string output_filtered_topic_name;
  
  double K;
  double M;
  bool bPublish_DS_path (false);
  bool bDynamic_target (false);
  std::vector<double> Priors;
  std::vector<double> Mu;
  std::vector<double> Sigma;
  std::vector<double> A;
  std::vector<double> attractor;
  double path_offset;

  if (!nh.getParam("input_topic_name", input_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the input. ");
    return -1;
  }

  if (!nh.getParam("input_target_topic_name", input_target_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the input. ");
    // return -1;
  }

  if (!nh.getParam("output_topic_name", output_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the output. ");
    // return -1;
  }

  if (!nh.getParam("output_filtered_topic_name", output_filtered_topic_name))   {
    ROS_ERROR("Couldn't retrieve the topic name for the filtered output. ");
    // return -1;
  }

  if (!nh.getParam("publish_DS_path", bPublish_DS_path))   {
    ROS_ERROR("Couldn't retrieve the publish DS path boolean. ");
    // return -1;
  }

  if (!nh.getParam("dynamic_target", bDynamic_target))   {
    ROS_ERROR("Couldn't retrieve the dynamic target boolean. ");
    // return -1;
  }

  if (!nh.getParam("K", K))   {
    ROS_ERROR("Couldn't retrieve the number of guassians. ");
    // return -1;
  }

  if (!nh.getParam("M", M))  {
    ROS_ERROR("Couldn't retrieve the dimension of the state space. ");
    // return -1;
  }

  if (!nh.getParam("Priors", Priors))   {
    ROS_ERROR("Couldn't retrieve Priors. Maybe you need to use [] in case of k=1");
    // return -1;
  }

  if (!nh.getParam("Mu", Mu))   {
    ROS_ERROR("Couldn't retrieve Mu. ");
    // return -1;
  }

  if (!nh.getParam("Sigma", Sigma))  {
    ROS_ERROR("Couldn't retrieve Sigma. ");
    // return -1;
  }


  if (!nh.getParam("A", A))  {
    ROS_ERROR("Couldn't retrieve Sigma. ");
    // return -1;
  }

  if (!nh.getParam("attractor", attractor))  {
    ROS_ERROR("Couldn't retrieve the attractor for the DS. ");
    // return -1;
  }

  if (!nh.getParam("path_offset", path_offset))   {
    ROS_ERROR("Couldn't retrieve path_offset. ");
    // return -1;
  }

  if (bPublish_DS_path)
        ROS_INFO("Starting the lpv-DS Motion generator... Publishing path in this node. ");
  else
      ROS_INFO("Starting the lpv-DS Motion generator... NOT Publishing path in this node. ");

  lpvDSMotionGenerator lpvDS_motion_generator(nh, frequency,
                                        (int)K, (int)M, Priors, Mu, Sigma, A,                                        
                                        attractor,
                                        input_topic_name,
                                        output_topic_name,
                                        output_filtered_topic_name,
                                        input_target_topic_name,
                                        bPublish_DS_path,
                                        bDynamic_target,
                                        path_offset);
  if (!lpvDS_motion_generator.Init()) {
    return -1;
  }
  else {
    lpvDS_motion_generator.Run();
  }

  return 0;
}
