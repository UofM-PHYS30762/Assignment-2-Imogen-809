#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;


double mean(const vector<double>& vals, int num_entries){
    double sum = 0.0;
    for(double val : vals){
        sum += val;
    }
    return sum / num_entries;

}

double standard_deviation(const vector<double>& vals, int num_entries){
    double mean_val = mean(vals, num_entries);
    double sum_squared_diff = 0.0;

    for(double val : vals){
        sum_squared_diff += (val - mean_val) * (val - mean_val);
    }

    return sqrt(sum_squared_diff / num_entries);

}
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

    // Reset file before we do anything else, as the file pointer is at the end of the file after counting entries, we need to reset it to the beginning of the file before we can read it again
    my_file.clear();
    my_file.seekg(0);

    // Read numbers into vector
    vector<double> values;
    double mark;
    int code;
    string course_name;

    while(my_file >> mark >> code){
        values.push_back(mark);
        getline(my_file, course_name);  // discard rest of line
    }

    // calculate and print mean value, the grades are stored in the first column of the file, so we access it using my_file[0]
    double mean_val{mean(values, number_of_entries)};
    cout<<"Mean:"<<mean_val<<endl;

    // calculate and print standard deviation
    double std_dev{standard_deviation(values, number_of_entries)};
    cout<<"Standard Deviation:"<<std_dev<<endl;


    return 0;

}