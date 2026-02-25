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

    return 0.0; // we return 0.0 because we are not actually returning any value, we are just printing the stats to the console
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

    string get_name() const
    {
        return name;
    }

    double get_mark() const
    {
        return mark;
    }
};



bool order_entries(const Course* a,
                   const Course* b)
{
    return a->get_name() < b->get_name();
}

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
    vector<string> course_names;
    vector<Course*> total_course_data; 
    string course_name;
    double mark;
    int code;

    // write the marks into a new vector.
    while(my_file >> mark >> code){
    getline(my_file, course_name);  // read rest of line
    values.push_back(mark);
    course_names.push_back(course_name);
    total_course_data.push_back(new Course(course_name, mark)); // <- use course_name, not vector
}

    // counts and prints number of entries in the open file 
    int number_of_entries{count_entries(values)};
    cout<<"Number of entries:"<<number_of_entries<<endl;


    string sort_choice;
    cout << "Do you want to order the marks by course name? (y/n): ";
    cin >> sort_choice;
    
    // Ask if the user wants to sort
    string sort_total_choice;
    cout << "Do you want to order the total marks by course name? (y/n): ";
    cin >> sort_total_choice;

    if (sort_total_choice == "y" || sort_total_choice == "Y") {
        sort(total_course_data.begin(), total_course_data.end(), order_entries);
    }

    // Display
    for (Course* c : total_course_data) {
        cout << c->get_mark() << " - " << c->get_name() << endl;
    }

    // Clean up memory
    for (Course* c : total_course_data) {
        delete c;
    }

    if (sort_total_choice == "y" || sort_total_choice == "Y") {
    sort(total_course_data.begin(), total_course_data.end(), order_entries);
    cout << "Grades (sorted):";
        for (int i = 0; i < number_of_entries; ++i) {
            cout << values[i] << " - " << course_names[i] << endl;
        }
    }
    else if (sort_total_choice == "n" || sort_total_choice == "N") {
        cout << "Grades:";
        for (int i = 0; i < number_of_entries; ++i) {
            cout << values[i] << endl;
        }
    }
    else {
        cout << "Invalid choice. Displaying unsorted grades." << endl;
        for (int i = 0; i < number_of_entries; ++i) {
            cout << values[i] << endl;
        }
    }

    // calculate and print mean value, the grades are stored in the first column of the file, so we access it using my_file[0]
    double total_stats{stats(values, number_of_entries)};

    my_file.clear();
    my_file.seekg(0);


    //------------ stats for a specific year --------------

    vector<double> year_values;
    vector<string> year_course_names;
    vector<Course*> year_data;
    double year_mark;
    int year_code;
    string year_course_name;

    // ask what year we want the stats for, and print the stats for that year
    int year;
    cout<<"Enter year (1-4) to get stats for that year:"<<endl;
    cin>>year;

    string year_sort_choice;
    cout << "Do you want to order the marks by course name? (y/n): ";
    cin >> year_sort_choice;


    // ask the user if they want course names included for the year stats
    string year_include_courses;
    cout << "Do you want to include course names when displaying results? (y/n): ";
    cin >> year_include_courses;


    // select the data for the selected year and store it in a new vector
    while(my_file >> year_mark >> year_code){

    int first_digit = year_code / 10000;

    if(first_digit == year){
        year_values.push_back(year_mark);
        getline(my_file, year_course_name);
        year_course_names.push_back(year_course_name);
        year_data.push_back(new Course(year_course_name, year_mark));
    }

    getline(my_file, year_course_name);
}

    if (year_data.empty()){
    cout << "No data found for year " << year << endl;
    return 1;
}

    sort(year_data.begin(), year_data.end(), order_entries);

    for (const Course* c : year_data)
    {
        cout << c->get_mark() << " - " << c->get_name() << endl;
    }

    for (Course* c : year_data)
        delete c;


    if (year_include_courses == "y" || year_include_courses == "Y") {
    cout << "Grades with course names:";
    for (const Course* c : year_data) {
        cout << c->get_mark() << " - "<< c->get_name() << endl;
    }
}
else {
    cout << "Grades for year " << year << ":";
    for (const Course* c : year_data) {
        cout << c->get_mark() << endl;
    }
}

    // calulate number of entries for that year
    int year_entries{count_entries(year_values)};

    // calculate and print mean value, the grades are stored in the first column of the file, so we access it using my_file[0]
    double year_mean_val{mean(year_values, year_entries)};
    cout<<"Year "<<year<<" Mean:"<<year_mean_val<<endl;

    // calculate and print standard deviation
    double year_std_dev{standard_deviation(year_values, year_entries)};
    cout<<"Year "<<year<<" Standard Deviation:"<<year_std_dev<<endl;

    // calculate and print standard error
    double year_std_err{standard_error(year_values, year_entries)};
    cout<<"Year "<<year<<" Standard Error:"<<year_std_err<<endl;


    return 0;

}
