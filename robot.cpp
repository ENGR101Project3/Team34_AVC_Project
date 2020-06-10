 #include "robot.hpp"

 //Initialising variables 
 double vDefault = 10;		//default L & R velocities of
 double vLeft = vDefault;
 double vRight = vDefault;

 int photoWidth = 150;
 int photoHeight = 100;

 //Adjusts the left and right velocities
 void adjustSpeed(double vL, double vR) {
	vLeft = vL;
	vRight = vR;
 }

 int main(){
	if (initClientRobot() !=0){
 		std::cout<<" Error initializing robot"<<std::endl;
 	}
	
	while(1){	//loops forever
		//Takes picture
 		takePicture();
 		SavePPMFile("i0.ppm",cameraView);

		//Stores white pixel information	 (used to calc centre white pixel)
 		int totalWhitePixels = 0; //Stores total amount of white pixels
 		int totalWhiteIndexes = 0; //Stores total of indexes of each white pixels

 		//Scans pixels in bottom horizontal row 	(x val increments, y val is constant)
 		for(int curCol = 0; curCol < photoWidth; curCol++) {
			
 			//Uses getPixel method to get RGB values of pixel 
			int curPixRed = get_pixel(cameraView, photoHeight/1.01, curCol, 0);
 			int curPixGreen = get_pixel(cameraView, photoHeight/1.01, curCol, 1);
 			int curPixBlue = get_pixel(cameraView, photoHeight/1.01, curCol, 2);

 			//Calculates quantity & location of white pixels
 			if(curPixRed > 250 && curPixGreen > 250 && curPixBlue > 250) { //if RGB vals are all more than 250, then pixel is considered white
 				std::cout << "curWhitePix: " << curCol << std::endl;
 				
 				totalWhiteIndexes += curCol; //adds index of white pixel to total of indexes
 				std::cout << "Total White Index: " << totalWhiteIndexes << std::endl;
 				
 				totalWhitePixels++; //increments total white pixels by one
 				std::cout << "Total White: " << totalWhitePixels << std::endl;
 			} //close if
 		} //close for


		//Calculates direction change of robot (by L/R wheel velocities)
 		if (totalWhitePixels != 0) { //checks if there is white line to follow
			
 			//Calculates the avg index of white pixels - this avg index needs to be the new centre
			int whitePositionAvg = (int) totalWhiteIndexes / totalWhitePixels;
 			
 			//Calculates distance between avg white pixel and centre pixel
 			int distanceFromCentre = (int) (photoWidth/2) - whitePositionAvg;

 			
 			//Changes the speed of the wheels based on the difference & following conditions

 			//Turns robot left if robot is too far right
 			if(distanceFromCentre > 0) { 	//positive difference means too far right
 				std::cout << "Left" << std::endl;
 				adjustSpeed(vDefault, vDefault+(vDefault*0.05*distanceFromCentre)); //vLeft < vRight
 			}
 			//Turns robot right if robot is too far left
 			else if(distanceFromCentre < 0) {  	 //negative difference means too far left
 				std::cout << "Right" << std::endl;
 				adjustSpeed(vDefault-(vDefault*0.05*distanceFromCentre), vDefault); //vLeft > vRight
 			}
 			//Makes robot go straight if robot is centered
 			else if(distanceFromCentre == 0) {	  //no difference means no error
 				std::cout << "Forward" << std::endl;
 				adjustSpeed(vDefault, vDefault); //vLeft = vRight
 			} //closes velocity change (if)

			//Sets L and R motors to adjusted velocities
 			setMotors(vLeft, vRight);
 			//setMotors(0,0);
 			std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
 			std::cout<<std::endl;
 			//usleep(1000);
 			
 		} else { //no white line detected
 			std::cout<<"No white line detected.";
 			break;
 		} //closes if

   } //closes while
   
 } // closes main
