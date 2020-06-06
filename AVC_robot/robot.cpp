
#include "robot.hpp"
int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    
    int photoWidth = 150;
	int photoHeight = 100;
	
    while(1){
		
		//take picture
		takePicture();
		SavePPMFile("i0.ppm",cameraView);
		
		//init var storing the total amount of white pixels we find - totalWhitePixels
		int totalWhitePixels = 0;
		//init var storing the index of all the white pixels we find - totalWhiteIndexes
		int totalWhiteIndexes = 0;
		
		//for loop init y value, to make it in the centre, while the x value is the one that changes, so it'll scan along the centre row. 
		for(int curCol = 0; curCol < photoWidth; curCol++) {
			//get each pixel in the centre horizontal row. Use the getPixel to get RGB vals 
			int curPixRed = get_pixel(cameraView, photoHeight / 2, curCol, 0);
			int curPixGreen = get_pixel(cameraView, photoHeight / 2, curCol, 1);
			int curPixBlue = get_pixel(cameraView, photoHeight / 2, curCol, 2);
			
			
			//If all those are above 250 (play around with that one)
			if(curPixRed > 250 && curPixGreen > 250 && curPixBlue > 250) {
				std::cout << "curWhitePix: " << curCol << std::endl;
				//add the index of whatever white is at to that var its being stored in
				totalWhiteIndexes += curCol;
				std::cout << "Total White Index: " << totalWhiteIndexes << std::endl;
				//add one to a variable that counts the amount of ones (var++)
				totalWhitePixels++;
				std::cout << "Total White: " << totalWhitePixels << std::endl;
			} //close if
		} //close for
		//calc the avg amount of 1's based on the indexes (indexes/1's)
		int whitePositionAvg = (int) totalWhiteIndexes / totalWhitePixels;
		//EXAMPLE: so, you've got three 1's there, so add each of where you saw each 1 (the index of the 1), and divide by the amount of 1's you saw. This value needs to be the new centre.
		
		//Calculate the distance between the average we just worked out and the centre pixel. If the avg is 80, but the centre is 75, then we need to move 5 pixels.
		int distanceFromCentre = (int) (photoWidth/2) - whitePositionAvg;
	
		//Change the speed of the wheels based on that difference
		//The robot would then turn based on whatever number it is.

		//Is the distance from the centre greater than 0?
		if(distanceFromCentre > 0) {
			//Yes, which means the robot needs to turn left.
			std::cout << "Left" << std::endl;
			vLeft = 10.0;
			vRight = 13.0;
		}
		//Is the distance from the centre less than 0?
		else if(distanceFromCentre < 0) {
			//Yes, which means the robot needs to turn right.
			std::cout << "Right" << std::endl;
			vLeft = 13.0;
			vRight = 10.0;
		}
		//Does the distance from the centre equal 0?
		else if(distanceFromCentre == 0) {
			//Yes, which means the robot doesn't need to do anything except go straight.
			std::cout << "Forward" << std::endl;
			vLeft = 10.0;
			vRight = 10.0;
		}
		setMotors(vLeft, vRight);
		//setMotors(0,0);
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		std::cout<<std::endl;
		//usleep(1000);
  } //while
} // main















