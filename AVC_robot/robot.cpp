
#include "robot.hpp"
int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 34.0;
    double vRight = 30.0;
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
      setMotors(vLeft,vRight);   
      std::cout << "Bruh" << std::endl;
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
      usleep(1000);
  } //while

} // main

//take picture
//init var storing the total amount of white pixels we fine - totalWhitePixels
//init var storing the index of all the white pixels we find - totalWhiteIndexes
//for loop init y value, to make it in the centre, while the x value is the one that changes, so it'll scan along the centre row. 
//get each pixel in the centre horizontal row. Use the getPixel to get RGB vals 
//If all those are above 250 (play around with that one)
	//add the index of whatever white is at to that var its being stored in
	//add one to a variable that counts the amount of ones (var++)
//close for loop
//calc the amount of 1's for the total line
//calc the avg amount of 1's based on the indexes (indexes/1's)
	//EXAMPLE: so, you've got three 1's there, so add each of where you saw each 1 (the index of the 1), and divide by the amount of 1's you saw. This value needs to be the new centre.
//Calculate the distance between the average we just worked out and the centre pixel. If the avg is 80, but the centre is 75, then we need to move 5 pixels.

//Move the robot

//Play around with this one, just to see how it works.

//Change the speed of the wheels based on that difference
	//We could divide the difference by the absolute difference. This would give us 1 or -1. Or 0, I guess. 
	//The robot would then turn based on whatever number it is.
	
	//Use the equations Aruthur gave us 
	//Vright = v_go + dv
	//Vleft = v_go - dv
	//dv = the difference btwn L&R













