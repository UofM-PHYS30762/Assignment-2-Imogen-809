#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

// void standard_deviation(vector<double>& vals){

// }

// void mean(vector<double>& vals){

// }

int count_entries(ifstream& my_file){
    int count = 0;
    string line;

    // count the number of lines
    while(getline(my_file, line)){
        count++;
    }

    return count;
}


// int order_entries(array& vals){

// }

int main(){
    //Open file to read and write
    ifstream my_file; // a file created for reading and writing 
    my_file.open("course_marks.dat"); // opens a file called 'data1.dat

    //Check that the file is open before proceeding
    if(!my_file.good()){
        //print error message and exit
        cerr<<"Error:file couldnt be opened"<<endl;
        //stops program running when error occurs
        return 1; 
    }

    // counts and prints number of entries in the open file 
    int number_of_entries{count_entries(my_file)};
    cout<<"Number of entries:"<<number_of_entries<<endl;

    return 0;

}