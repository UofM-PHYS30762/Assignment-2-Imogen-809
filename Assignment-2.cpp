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

double standard_error(const vector<double>& vals, int num_entries){
    double std_dev = standard_deviation(vals, num_entries);
    return std_dev / sqrt(num_entries);
}

double stats(const vector<double>& vals, int num_entries){
    double mean_val = mean(vals, num_entries);
    double std_dev = standard_deviation(vals, num_entries);
    double std_err = standard_error(vals, num_entries);

    cout<<"Mean:"<<mean_val<<endl;
    cout<<"Standard Deviation:"<<std_dev<<endl;
    cout<<"Standard Error:"<<std_err<<endl;

    return 0.0; // we return 0.0 because we are not actually returning any value, we are just printing the stats to the console
}
int count_entries(const vector<double>& vals){
    return vals.size();
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

    vector<double> values;
    double mark;
    int code;
    string course_name;

    // write the marks into a new vector.
    while(my_file >> mark >> code){
        values.push_back(mark);
        getline(my_file, course_name);  // discard rest of line
    }

    // counts and prints number of entries in the open file 
    int number_of_entries{count_entries(values)};
    cout<<"Number of entries:"<<number_of_entries<<endl;

    // Reset file before we do anything else, as the file pointer is at the end of the file after counting entries, we need to reset it to the beginning of the file before we can read it again
    my_file.clear();
    my_file.seekg(0);

    // calculate and print mean value, the grades are stored in the first column of the file, so we access it using my_file[0]
    double total_stats{stats(values, number_of_entries)};

    my_file.clear();
    my_file.seekg(0);


    //------------ stats for a specific year --------------

    vector<double> year_values;
    double year_mark;
    int year_code;
    string year_course_name;

    // ask what year we want the stats for, and print the stats for that year
    int year;
    cout<<"Enter year (1-4) to get stats for that year:"<<endl;
    cin>>year;
   
    // select the data for the selected year and store it in a new vector
    while(my_file >> year_mark >> year_code){

    int first_digit = year_code / 10000;

    if(first_digit == year){
        year_values.push_back(year_mark);
    }

    getline(my_file, year_course_name);
}
    // calulate number of entries for that year
    int year_entries{count_entries(year_values)};

    // calculate and print mean value, the grades are stored in the first column of the file, so we access it using my_file[0]
    double year_mean_val{mean(year_values, year_entries)};
    cout<<"Year "<<year<<" Mean:"<<year_mean_val<<endl;

    // calculate and print standard deviation
    double year_std_dev{standard_deviation(year_values, number_of_entries)};
    cout<<"Year "<<year<<" Standard Deviation:"<<year_std_dev<<endl;

    // calculate and print standard error
    double year_std_err{standard_error(year_values, number_of_entries)};
    cout<<"Year "<<year<<" Standard Error:"<<year_std_err<<endl;


    return 0;

}