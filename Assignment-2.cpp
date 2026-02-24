#include<iostream>
#include<fstream>

using namespace std;

void standard_deviation(array& vals){

}

void mean(array& vals){

}

int count_entries(){

}

int order_entries(array& vals){

}

int main(){
    //Open file to read and write
    ifstream my_file; // a file created for reading and writing 
    my_file.open("course_marks.dat"); // opens a file called 'data1.dat

    //Check that the file is open before proceeding
    if(!my_file.good()){
        //print error message and exit
        cerr<<"Error:file couldnt be opened"<<endl;
    }

}