#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>

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

    return 0.0;
}
int count_entries(const vector<double>& vals){
    return vals.size();
}

class Course
{
private:
    string name;
    double mark;

public:
    Course(string n, double m)
        : name(n), mark(m) {}

    // returns course name
    string get_name() const
    {
        return name;
    }

    //returns course mark
    double get_mark() const
    {
        return mark;
    }
};


bool order_entries(const Course* a, const Course* b){
                    // 'a' is the pointer to first course and 'b' is the pointer the the second course
                    // if 'a' should appear before 'b', return true, otherwise return false
    return a->get_name() < b->get_name();
}

int main(){
    // set up constants
    vector<double> values;
    vector<string> course_names;
    vector<Course*> total_course_data; 
    string course_name;
    double mark;
    int code;
    string total_sort_choice;

    // open file to read and write
    ifstream my_file; // a file created for reading only
    my_file.open("course_marks.dat"); // opens a file

    //Check that the file is open before proceeding
    if(!my_file.good()){
        //print error message and exit
        cerr<<"Error:file couldnt be opened"<<endl;
        //stops program running when error occurs
        return 1; 
    }

    // write the marks into a new vector.
    while(my_file >> mark >> code){
        getline(my_file, course_name); 
        values.push_back(mark);
        course_names.push_back(course_name);
        total_course_data.push_back(new Course(course_name, mark));
    }

    // counts and prints number of entries in the open file 
    int number_of_entries{count_entries(values)};
    cout<<"Number of entries:"<<number_of_entries<<endl;

    // Ask if the user wants to sort data by course name, alphabetically
    cout << "Do you want to order the total marks by course name? (y/n): ";
    cin >> total_sort_choice;

    // orders the data if the user has selected y or Y
    if (total_sort_choice == "y" || total_sort_choice == "Y") {
        sort(total_course_data.begin(), total_course_data.end(), order_entries);
        cout << "Grades (sorted):";
    }

    // the data is not sorted if the user has selected n or N
    else if (total_sort_choice == "n" || total_sort_choice == "N") {
        cout << "Grades:";
    }

    else {
        cout << "Invalid choice. Displaying unsorted grades." << endl;
    }

    // prints out the data, sorted or unsorted depending in the user's choice
    for (Course* c : total_course_data) {
        cout << c->get_mark() << " - " << c->get_name() << endl;
}

    // calculate and print mean value
    double total_stats{stats(values, number_of_entries)};

    // Clean up memory
    for (Course* c : total_course_data) {
        delete c;
    }

    my_file.clear();
    my_file.seekg(0);


    //------------ stats for a specific year --------------

    // set up constants for the year stats
    vector<double> year_values;
    vector<string> year_course_names;
    vector<Course*> year_data;
    double year_mark;
    int year_code;
    string year_course_name;
    string year_sort_choice;
    int year;

    // ask what year we want the stats for, and print the stats for that year
    cout<<"Enter year (1-4) to get stats for that year:"<<endl;
    cin>>year;

    cout << "Do you want to order the marks by course name? (y/n): ";
    cin >> year_sort_choice;

    // select the data for the selected year and store it in a new vector
    while(my_file >> year_mark >> year_code){

        int first_digit = year_code / 10000;
        getline(my_file, year_course_name);

        if(first_digit == year){
            year_values.push_back(year_mark);
            year_course_names.push_back(year_course_name);
            year_data.push_back(new Course(year_course_name, year_mark));
        }
    }

    if (year_data.empty()){
        cout << "No data found for year " << year << endl;
        return 1;
    }

    if (year_sort_choice == "y" || year_sort_choice == "Y") {
        sort(year_data.begin(), year_data.end(), order_entries);
        cout << "Grades with course names:";
    }

    else if (year_sort_choice == "n" || year_sort_choice == "N"){
        cout << "Grades for year " << year << ":";
        
    }

    else {
        cout << "Invalid choice. Displaying unsorted grades." << endl;
    }

    // print the data for the selected year, sorted or unsorted depending on the user's choice
    for (Course* c : year_data) {
        cout << c->get_mark() << " - " << c->get_name() << endl;
    }

    // calulate number of entries for that year
    int year_entries{count_entries(year_values)};

    // print stats for the year
    double year_stats(stats(year_values, year_entries));

    // clean up memory
    for (Course* c : year_data)
        delete c;
    
    // close the file
    my_file.close();

    return 0;

}
