/*
 *This file was last edited 4/7/23

* Made by Christopher A. Mendoza
 * UTEP 2023
 * 
*/
#include <cmath>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <math.h>

#define OUTPUT_BUFF 4
const float BIAS = 1.0;
//For the data
const int COL_DATA = 3;
const int ROW_DATA = 4;
//For the weights
const int WEIGHT_ROW = 3;
const int WEIGHT_COL = 3;
/*=====================*/
const float HIGH = 1;
const float LOW = 0;
int rows;

class xorgate{
	public:
	//Theses hold the data for the 
	float data_arr[ROW_DATA][COL_DATA];
	float weight_arr[WEIGHT_ROW][WEIGHT_COL];
	//Values after being inputed into the sigmoid
	float OUTPUT_F3[OUTPUT_BUFF];
	float OUTPUT_F2[OUTPUT_BUFF];
	float OUTPUT_F1[OUTPUT_BUFF];
	//Values before inputed into the sigmoid function
	float OUTPUT_Y1[OUTPUT_BUFF];
	float OUTPUT_Y2[OUTPUT_BUFF];
	float OUTPUT_Y3[OUTPUT_BUFF];
	//Percentage values for Hits and Misses
	double target_y1[OUTPUT_BUFF];
	double target_y2[OUTPUT_BUFF];
	double target_y3[OUTPUT_BUFF];
};
/*Setting this class as a global variable*/
xorgate methods; 

/*This will handle the backpropagation aspect*/
void backpropagation(){
  
}

void feed_foward(){
	double y1,y2,y3;	
	//This gives us the values for the first nueron
	for(int i = 0; i < rows; i++){
		y1 = BIAS*methods.weight_arr[0][0] + methods.data_arr[i][0]*methods.weight_arr[0][1] + methods.data_arr[i][1]*methods.weight_arr[0][2];
		methods.OUTPUT_Y1[i] = y1;
		methods.OUTPUT_F1[i] = 1/(1 + std::exp(-y1));
	}
	std::cout << std::endl;
	//This gives us the values for the second nueron;
	for(int i = 0; i < rows; i++){
		y2 = BIAS*methods.weight_arr[1][0] + methods.data_arr[i][0]*methods.weight_arr[1][1] + methods.data_arr[i][1]*methods.weight_arr[1][2];
		methods.OUTPUT_Y2[i] = y2;
		methods.OUTPUT_F2[i] = 1/(1 + std::exp(-y2));
	}
	/*
	*/
	//Here we calculate the output of the value
	for(int i = 0; i < rows;i++){
		y3 = BIAS*methods.weight_arr[2][0] + methods.OUTPUT_F1[i]*methods.weight_arr[2][1] + methods.OUTPUT_F2[i]*methods.weight_arr[2][2];
		methods.OUTPUT_Y3[i] = y3;
		methods.OUTPUT_F3[i] = 1/(1+std::exp(-y3));
	}

}	

//Print the calculated value and the target value
void target_actual_checker(){
	for(int i = 0; i < rows ;i++){
		std::cout << "Target -> "<< methods.data_arr[i][2] << " ," << "Actual  Output -> "<< methods.OUTPUT_F3[i] << std::endl;
	}	
}
//check for hits and miss
void report_hitmiss(){
	//float per_tolerance;
	float target_1 = 1;
	float target_0 = 0;
	float threshold = 0.2;
	int hit = 0;
	int miss = 0;
	//Here we process the Hits and Misses for Nueron 1
	for(int i = 0; i < rows; i++){
		if(methods.data_arr[i][2] == target_1){
			methods.target_y1[i] = std::abs(target_1 - methods.OUTPUT_F1[i]);
			methods.target_y2[i] = std::abs(target_1 - methods.OUTPUT_F2[i]);
			methods.target_y3[i] = std::abs(target_1 - methods.OUTPUT_F3[i]);
		}
		else{
			methods.target_y1[i] = std::abs(target_0 - methods.OUTPUT_F1[i]);
			methods.target_y2[i] = std::abs(target_0 - methods.OUTPUT_F2[i]);
			methods.target_y3[i] = std::abs(target_0 - methods.OUTPUT_F3[i]);
		}
	}
	std::cout << std::endl;
	std::cout << "<======= For Nueron-1 =======>" <<std::endl;
	//Here we determine whether it was a miss or hit
	for(int i = 0; i < rows; i++){
		if(methods.target_y1[i] <= threshold)
			std::cout << i << " -> " << methods.target_y1[i] << " (HIT)" << std::endl;
		else
			std::cout << i << " -> " << methods.target_y1[i] << " (MISS)" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "<====== For Nueron-2 =======>" << std::endl;
	//For Nueron 2
	for(int i = 0; i < rows; i++){
		if(methods.target_y2[i] <= threshold)
			std::cout << i << " -> " << methods.target_y2[i] << " (HIT)" << std::endl; 
		else
			std::cout << i  << " -> " << methods.target_y2[i] << " (MISS)" << std::endl; 
	}
	std::cout << std::endl; 
	std::cout << "<======= For Nueron-3 =======> " << std::endl;
	//For Nueron 3
	for(int i = 0; i < rows; i++){
		if(methods.target_y3[i] <= threshold){
			std::cout << i << " -> " << methods.target_y3[i] << " (HIT)" << std::endl;
			hit++;
		}
		else{
			std::cout << i << " -> " << methods.target_y3[i] << " (MISS)" << std::endl;
			miss++;
		}
	}
	std::cout << std::endl;
	if(hit > miss){
		std::cout << "This xorgate is accurrate!!" << std::endl;
	}
	else{
		std::cout << "This xorgate is not accurate!!" << std::endl;
	}
	std::cout << std::endl;
		
}
void file_handler(){	
   	//Read from the files
	std::ifstream fileRead_data;
	std::ifstream fileRead_weight;
	fileRead_data.open("XOR-data.txt", std::ios::in);
	fileRead_weight.open("XOR-weights.txt", std::ios::in);
	
	fileRead_data >> rows;
	std::cout <<"This how many inupts we have currently right now -> " << rows << std::endl << std::endl;
	
	float data_arr[ROW_DATA][COL_DATA];
	float weight_arr[WEIGHT_ROW][WEIGHT_COL];
	//here we put the values form the txt files into here
	for(int i = 0; i < ROW_DATA; i++)
		for(int j = 0; j < COL_DATA; j++)
			fileRead_data >> methods.data_arr[i][j];
		
	for(int i = 0; i < WEIGHT_ROW; i++)
		for(int j = 0; j < WEIGHT_COL; j++)
			fileRead_weight >> methods.weight_arr[i][j];
	//Close files
	fileRead_data.close();
	fileRead_weight.close();
	/*===================== Here we output both the data and weight from 2d array ================*/
	//output the data
	std::cout << "Here are the data values" << std::endl;
	for(int i = 0; i < ROW_DATA; i++){
			for(int j = 0; j < COL_DATA; j++){
				std::cout << methods.data_arr[i][j] << " ";
			}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//output the weight
	std::cout << "Here are the weight values" << std::endl;
		for(int i = 0; i < WEIGHT_ROW; i++){
			for(int j = 0; j < WEIGHT_COL; j++){
				std::cout << methods.weight_arr[i][j] << " ";
			}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(int argv, char **argc){
    /*Read each data line by line*/
	file_handler(); //takes the values from the files and puts them in them 2d array	
	/*Here after the data is extracted we feed foward*/
	feed_foward();
	target_actual_checker();
	report_hitmiss();
	return 0;
} 
