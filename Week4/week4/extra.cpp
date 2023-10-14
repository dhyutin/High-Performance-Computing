#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "omp.h"

using namespace std;

int array[1000][1000];
int arr[1000][1000];
vector<int> pf;
vector<float> pr;
vector<float> cpr;
vector<int> fin;

// Function that creates a frequency array of pixels in the image

vector<int> create_frequency_array(int numrows, int numcols){
    
    cout<<1<<endl;
    #pragma omp parallel
    {
    #pragma omp for
    for(int i = 0; i < 257; i++){
        pf.push_back(0);
    }
    
    }

    #pragma omp parallel
    {  
    #pragma omp for
    for(int row = 1; row <= numrows; row++){
        for(int col = 1; col <= numcols; col++){
	    pf[256]++;
	    pf[array[row][col]]++;
	}
    }
    }
    return pf;  
}

// Function to find individual probabilities of occurence of each of 256 values of pixel
vector<float> individual_probabilities(vector<int> pixel_frequency, int num_pixels){
    cout<<2<<endl;
    #pragma omp parallel
    {  
    #pragma omp for
    for(int i = 0; i < 256; i++){
        pr.push_back(0);
    }
    }
    #pragma omp parallel
    {     
    #pragma omp for
    for(int i = 0; i < 256; i++){
        pr[i] = ((float)pixel_frequency[i])/((float)num_pixels);
    }
    }
    return pr;
}

// Function to find cumulative probability of each of 256 values of pixel
vector<float> cumulative_probability(vector<float> pr){
    cout<<3<<endl;
    #pragma omp parallel
    {     
    #pragma omp for
    for(int i = 0; i < 256; i++){
        cpr.push_back(0);
    }
    }
    #pragma omp parallel
    {     
    cpr[0] = pr[0];
    #pragma omp for
    for(int i = 1; i < 256; i++){
        cpr[i] = pr[i] + cpr[i-1];
    }
    }
    return cpr;
}

// Function to calculate C(r) X (L-1)
vector<int> cpr_into_max_pixel(vector<float> cpr){
    cout<<4<<endl;
    #pragma omp parallel
    { 
    #pragma omp for
    for(int i = 0; i < 256; i++){
        fin.push_back(0);
    }
    }
    #pragma omp parallel
    {     
    #pragma omp for
    for(int i = 0; i < 256; i++){
        fin[i] = round(cpr[i]*255);
    }
    }
    return fin;
}

// Function to update with new pixel values
void final_step(int numrows, int numcols, vector<int> finall){
    cout<<5<<endl;
    #pragma omp parallel
    { 
    #pragma omp for
    for(int row = 1; row <= numrows; row++){
	for(int col = 1; col <= numcols; col++){
	    arr[row][col] = finall[array[row][col]];
	}
    }
    }
}

int main()
{
	int row = 0, col = 0, numrows = 0, numcols = 0,MAX=0;
	ifstream infile("Images/casablanca.ascii.pgm");
	stringstream ss;
	string inputLine = "";

	// First line : version
	getline(infile,inputLine);
	if(inputLine.compare("P2") != 0) cerr << "Version error" << endl;
	else cout << "Version : " << inputLine << endl;

	// Continue with a stringstream
	ss << infile.rdbuf();

	// Secondline : size of image
	ss >> numcols >> numrows >> MAX;

	//print total number of rows, columns and maximum intensity of image
	cout << numcols << " columns and " << numrows << " rows" <<endl<<"Maximum Intensity "<< MAX <<endl;


	//Initialize a new array of same size of image with 0
	for(row = 0; row <= numrows; ++row){
	    array[row][0]=0;
	    //arr[row][0] = 0;
	    for(col = 0; col <= numcols; col++){
	        array[0][col] = 0;
	        //arr[0][col] = 0;
	    }
	}
		
	// Following lines : data
	for(row = 1; row <= numrows; ++row)
	{
		for (col = 1; col <= numcols; ++col)
		{
			//original data store in new array
			ss >> array[row][col];
		}
	}


    // Histogram Equalization begins
        double wallclock_initial = omp_get_wtime();
	// Step 1: Find frequencies of each pixel value
	vector<int> pixel_frequency = create_frequency_array(numrows, numcols);
	int num_pixels = pixel_frequency[256];

	// Step 2: P(r)
	vector<float> pr = individual_probabilities(pixel_frequency, num_pixels);

	// Step 3: Cumulative Frequency
	vector<float> cpr = cumulative_probability(pr);

	// Step 4: C(r) X (L-1)
	vector<int> finall = cpr_into_max_pixel(cpr);


	// Step 5: Updare new image with respective updation
	final_step(numrows, numcols, finall);
	

	ofstream outfile;
	
	//new file open to store the output image
	outfile.open("AfterHistogramEqualization.ascii.pgm");
	outfile<<"P2"<<endl;
	outfile<<numcols<<" "<<numrows<<endl;
	outfile<<"255"<<endl;

	for(row = 1; row <= numrows; ++row)
	{
		for (col = 1; col <= numcols; ++col)
		{
			//store resultant pixel values to the output file
			outfile << arr[row][col]<<" ";
		}
	}

	double wallclock_final = omp_get_wtime();
	cout<<"Time: "<<wallclock_final-wallclock_initial<<endl;
	outfile.close();
	infile.close();
	return 0 ;
}
