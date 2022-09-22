#include <iostream>
#include <fstream>
#include <string>

#define COMPLICATED "complicated"
#define SIMPLE "simple"
#define ENCRYPT "encrypt"
#define DECRYPT "decrypt"
#define NUM 11

using namespace std;

void simple_encrypt(const string& password, ifstream& input_file, ofstream& output_file);
void complicated_encrypt(const string& password,ifstream& input_file,ofstream& output_file);
int calculate_special_num(const string& password);
void simple_decrypt(const string& password,ifstream& input_file,ofstream& output_file);
void complicated_decrypt(const string& password,ifstream& input_file,ofstream& output_file);
void write_int_onfile(ofstream& output_file,int& code);
void write_char_onfile(ofstream& output_file,int& code);
string get_from_user();
void selectivity();

void simple_encrypt(const string& password, ifstream& input_file,ofstream& output_file){
  char note;
  int i=0;
  int code;
  while(input_file.get(note)){
    code=(int)password[i%password.size()]+(int)note;
    write_int_onfile(output_file,code);
    i++;
  }
}
void complicated_encrypt(const string& password,ifstream& input_file,ofstream& output_file){
  int code;
  char note;
  int random;
  srand(calculate_special_num(password));
  while(input_file.get(note)){
    random = rand()% NUM;
    code=random+(int)note;
    write_int_onfile(output_file,code);
  }
}
int calculate_special_num(const string& password){
  int sum=0;
  for(int i = 0;i<password.length();i++){
    sum = sum + password[i];
  }
  return sum;  
}
void simple_decrypt(const string& password,ifstream& input_file,ofstream& output_file){
  string line;
  int i=0;
  int code;
  int note;
  while(getline(input_file, line)){
    code=stoi(line);
    note=code-(int)password[i%(password.length())];
    write_char_onfile(output_file,note);
    i++;
  }
}
void complicated_decrypt(const string& password,ifstream& input_file,ofstream& output_file){
  string line;
  int code , sum=0;
  int note;
  int random;
  srand(calculate_special_num(password));
  while(getline(input_file, line)){
    code=stoi(line);
    random = rand()%NUM;
    note=code-random;
    write_char_onfile(output_file,note);
  
  }
}
void write_int_onfile(ofstream& output_file,int& code){
  output_file<<code<<endl;
}
void write_char_onfile(ofstream& output_file,int& code){
  output_file<<(char)code;
}

string get_from_user(){
  string command;
  cin>>command;
  return command;
}
void selectivity(){
  string first_command=get_from_user();
  string second_command=get_from_user();
  string password=get_from_user();
  ifstream input_file (get_from_user());
  ofstream output_file(get_from_user());

  if(first_command==ENCRYPT){
    if(second_command==SIMPLE)
      simple_encrypt(password,input_file,output_file);
    if(second_command==COMPLICATED)
      complicated_encrypt(password,input_file,output_file);
  }
  if(first_command==DECRYPT){
    if(second_command==SIMPLE)
      simple_decrypt(password,input_file,output_file);
    if(second_command==COMPLICATED)
      complicated_decrypt(password,input_file,output_file);
  }
}
int main(){
  selectivity();
}
