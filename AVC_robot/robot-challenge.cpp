#include "robot.hpp"

double vDefault = 25;	
double vLeft = vDefault;
double vRight = vDefault;

int photoWidth = 150;
int photoHeight = 100;

void adjustSpeed(double vL, double vR, bool forceSet) {
	vLeft = vL;
	vRight = vR;
	if (forceSet == true) {setMotors(vLeft, vRight);}
}

int main(){
	if (initClientRobot() !=0){
 		std::cout<<" Error initializing robot"<<std::endl;
 	}
	
	while(1){//loops forever
		
 		takePicture();
 		SavePPMFile("i0.ppm",cameraView);
		
 		int totalWhitePixels = 0; 
 		int totalWhiteIndexes = 0;
 		int redDifference = 0;
 		
 		bool red = false;
		bool black = false;
		
		// Check for White Pixels
 		for(int curCol = 0; curCol < photoWidth; curCol++) { 
			int curPixRed = get_pixel(cameraView, photoHeight/1.2, curCol, 0);
 			int curPixGreen = get_pixel(cameraView, photoHeight/1.2, curCol, 1);
 			int curPixBlue = get_pixel(cameraView, photoHeight/1.2, curCol, 2);

 			if(curPixRed > 250 && curPixGreen > 250 && curPixBlue > 250) { 
 				std::cout << "curWhitePix: " << curCol << std::endl;
 				totalWhiteIndexes += curCol; 
 				std::cout << "Total White Index: " << totalWhiteIndexes << std::endl;
 				totalWhitePixels++; 
 				std::cout << "Total White: " << totalWhitePixels << std::endl;
 			} 
 		} 
 		
 		// Check for Red Pixels
 		for (int curCol = 75; red == false && curCol != 0; curCol--){
			int leftWall = get_pixel(cameraView,75,curCol,0);
			if (leftWall != 255){redDifference++;}
			else {red = true;}
		} 
		
 		// Follow White Line
 		std::cout << totalWhitePixels << std::endl;
 		if (totalWhitePixels > 0) {
			int whitePositionAvg = (int) totalWhiteIndexes / totalWhitePixels;
 			int distanceFromCentre = (int) (photoWidth/2) - whitePositionAvg;
 			
 			if(distanceFromCentre > 0) { 	
 				std::cout << "Left" << std::endl;
 				adjustSpeed(vDefault, vDefault+(vDefault*0.05*distanceFromCentre), true); 
 			}
 			
 			else if(distanceFromCentre < 0) {  	 
 				std::cout << "Right" << std::endl;
 				adjustSpeed(vDefault-(vDefault*0.05*distanceFromCentre), vDefault, true);
 			}
 			
 			else if(distanceFromCentre == 0) {	 
 				std::cout << "Forward" << std::endl;
 				adjustSpeed(vDefault, vDefault, true); 
 			} 
				
 			std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
 			std::cout<<std::endl;
 			
 		} else if (totalWhiteIndexes == 0 && red == false){ 
			std::cout<<"NoWhiteLine Spinning";
			adjustSpeed(vDefault/2, 1.1, true);
		} 
 		
 		
 		// Follow left Wall
 		if (totalWhitePixels == 0) {
			if(red == false &&  redDifference != 75){adjustSpeed(vDefault, 0.0, false);}		
			else {	
				if (redDifference == 0){
					int delay = 0;
					while (delay < photoHeight*0.1){
						adjustSpeed(vDefault, 1.1, true);
						delay++;
					}
				}
				if (redDifference == (photoWidth/2)){int delay = 0;int delayy = 0;
					while (delay < photoWidth-127){
						adjustSpeed(vDefault, vDefault, true);
						delay++;
					}
					while (delayy < photoWidth-138){
						adjustSpeed(1.1, vDefault, true);
						delayy++;
					}
				}
				if (redDifference > 30 && redDifference < 70){
					adjustSpeed(vDefault, vDefault, false);
				}
				else if (redDifference < photoHeight-70){
					adjustSpeed(vDefault-10, vDefault/2, false);
				}
				else if (redDifference > photoHeight-30){
					adjustSpeed(vDefault/2, vDefault-10, false);
				}
				setMotors(vLeft, vRight);
			}
		} 
    } 
} // closes main
