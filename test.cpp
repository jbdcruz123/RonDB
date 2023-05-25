



//under testing pa din ito, napagana na ung linear search

//index_user1.db
//user1.db       

/*
data diagram
 
      note: assumingna may index na kasama ung id. dahilan array ang gagamitin ko
      statring index 0 to up
 
      has extension                                              has extension
      Index_user.db  (Index_user1.db etc )                          User.db     (User1.db   etc)
      pasword      Length   range_first  range_last            pasword      Length   range_first  range_last
      etc           5        10             15                    etc           5        10           15

      id    marker                                                id              date          product_name         pcs         amount    Total
      10    1                                                     10             1/1/2023       name1 familyname1     1          100.01    100.01
      11    1                                                     11             1/2/2023       name2 familyname2     1          100.02
      13    0                                                     13             1/3/2023       name1 familyname3     1          100.03
      14    1                                                     14             1/4/2023       name1 familyname4     1          100.04 
      15    1                                                     15             1/5/2023       name1 familyname5     1          100.05    100.05
 
*/


#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include <sstream>
#include <iomanip>

#define ADDRESS_INDEX_USER "index_user1.db"
#define ADDRESS_USER "user1.db"

#define RANGE_ARRAY 10000

struct index_user_password_struct { //2      user_password
 
      int password;
      int length;
      int range_first; //starting range ng id
      int range_last;  //last range ng id
 
}; //2

    
struct index_user_struct{ //2    index_user
 
      int id;
      int marker;
 
} ; //2

struct user_struct{  //2

      
      int id;
      int date;            //asuming na in order ung date, datatype int muna gamit ko
      char product_name[100];
      int pcs;
      double amount;
      double total;      

}; //2

struct index_user_password_struct  gindex_user_password;

struct index_user_struct gindex_user[ RANGE_ARRAY ];

struct user_struct guser[RANGE_ARRAY];

std::ifstream gindex_user_read;  
std::ofstream gindex_user_write;
std::ifstream guser_read;  
std::ofstream guser_write;

void finitial( );
bool get_string(std::string& output);
bool get_integer(int& output);
bool get_floating_point(double& output);
void fdisplay_range( int start_par, int stop_par );
int flinear_search( int target ) ;


//param start_par ex: 0 ang 0 ang first value,  stop_par ex: 10 ang 9 ang last value
void fdisplay_range( int start_par, int stop_par ) { //2
      //L30
      //reopening it

      std::cout << "\ndebug L31 start_par " << start_par << " , stop_par " << stop_par << "\n";


      int fir =start_par;

      std::cout << std::setw(10) << std::right << "id"  << std::setw(7) << std::right << "marker" 
      << std::setw(10) << std::right << "date"  << std::setw(20) << std::right << "product name " 
      << std::setw(10) << std::right << "pcs"  << std::setw(10) << std::right << "amount" 
      << std::setw(10) << std::right << "total" << "\n";      
            
      while( fir < stop_par ){//4
            
            std::cout << std::setw(10) << std::right << gindex_user[fir].id  << std::setw(7) << std::right << gindex_user[fir].marker 
            << std::setw(10) << std::right << guser[fir].date  << std::setw(20) << std::right << guser[fir].product_name 
            << std::setw(10) << std::right << guser[fir].pcs  << std::setw(10) << std::right << guser[fir].amount 
            << std::setw(10) << std::right << guser[fir].total << "\n";      
      
            
            fir+=1;
      }//4


}//2

void finitial(  ) {//2

      //L20       
      gindex_user_write.open( ADDRESS_INDEX_USER, std::ios::binary );

      guser_write.open( ADDRESS_USER, std::ios::binary );

      gindex_user_password.password = 1234;
      gindex_user_password.length = RANGE_ARRAY;
      gindex_user_password.range_first = 10;    //starting range 
      gindex_user_password.range_last = (RANGE_ARRAY + 10) -1 ; //range 10 to 10009

      //intial
      gindex_user_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );

      //intial
      guser_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );

      std::string _str=""; //sub string
      int id =10;

      for( int fir = 0; fir < RANGE_ARRAY ;  fir+=1 ) {//3

            gindex_user[fir].id = id;
            gindex_user[fir].marker = 1;

            guser[fir].id = id;
            guser[fir].date = (id -10) +1;
            _str = "";
            _str = "name" + std::to_string( (id -10) +1);
            strcpy( guser[fir].product_name, _str.c_str(  ) ); 
            guser[fir].pcs = 2;
            guser[fir].amount =  (id -10) +1;
            guser[fir].total = guser[fir].pcs * guser[fir].amount;    

            id+=1;
      }//3

      gindex_user_write.write( (char*) &gindex_user, sizeof( index_user_struct ) * RANGE_ARRAY);

      guser_write.write( (char*) guser, sizeof( user_struct ) * RANGE_ARRAY );

      gindex_user_write.close();

      guser_write.close();


}//2


bool get_string(std::string& output) { 
      //L40 

  // If an error occurs, `output` is left empty.
  std::getline(std::cin, output);

  bool fail = std::cin.fail();
  std::cin.clear(); // clear error flags

  return !fail;
}

bool get_integer(int& output) {
      //L50 

  std::string s;
  std::istringstream iss;

  if ( !(get_string(s)) ) {
    return false;
  }

  iss.str(s); // assign a new string buffer to the input stream
  output = 0;
  // If an error occurs, `output` is not modified.
  iss >> output;

  return !(iss.fail()) ;
}


bool get_floating_point(double& output) {
      //L60 

  std::string s;
  std::istringstream iss;

  if ( !(get_string(s)) ) {
    return false;
  }

  iss.str(s); // assign a new string buffer to the input stream
  output = 0;
  // If an error occurs, `output` is not modified.
  iss >> output;

  return !( iss.fail() ) ;
}

//return -1 if fails, otherwise 0 to up value sucess
int flinear_search( int target ) {//2
      //L70 


      std::cout << "\ndebug L71 target " << target <<"\n";

      int left= 0, right = RANGE_ARRAY, mid;

      mid = (left + right) / 2;
      
      while( left < right ) {//3

            if( target < guser[mid].id ) { //4
                  //( left    m )   right
                  right = mid;
                  mid = (left +  mid) /2;

            } else if( target > guser[mid].id ) { //4
                  // left    (m    right )
                  
                  left = mid;
                  mid = (mid + right) /2;
                  
            } else { //4

                  std::cout << "\n\ntarget is been found :  target " << mid << "  ";
                  getchar( );
                  //the target index
                  return mid;
            }//4

      }//3

      //cannot return 0 because it is the first index, then if fail return -1
      return -1;
}//2


int main(void  ) {//2
      
      //L10 
      std::string ch;
      int input_integer;
      
      finitial();
      while(1) {//3
      
            std::cout << "\n\nMain menu:\nf to find id, d to display selected range, q to leave:  ";
            while ( ! ( get_string(ch) ) || ch.size()  >= 100 ) { //4
                  std::cout << "\n\nerror invalid input.\n";
            } //4

            if( ch == "q" || ch == "Q") {//5
                  break;
            }else if( ch == "d" || ch == "D" ) { //5
                  //dislay mode

                  int start_int, length_int;
                  
                  std::cout << "\n\ninput starting index:  ";
                  while ( ! get_integer(start_int)  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4

                  std::cout << "\n\ninput length:  ";
                  while ( ! get_integer(length_int)  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4
                  
                  fdisplay_range( start_int, length_int );

            } else if( ch == "f" || ch == "F" ) { //5
            
                  int input;

                  std::cout << "\n\nFind mode:\ninput index for target:  ";
                  while ( ! get_integer( input )  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4

                  int _return = flinear_search( input ) ;
                  if( _return == -1 ) {//7
                        std::cout << "\n\nfail to find target " << input << "\npress any key... ";
                        getchar();
                        continue;
                  }//7

                  std::cout << "\n\nsucess target " << _return << " has been found \n" ;
                  std::cout << std::setw(10) << std::right << "id"  << std::setw(7) << std::right << "marker" 
                  << std::setw(10) << std::right << "date"  << std::setw(20) << std::right << "product name " 
                  << std::setw(10) << std::right << "pcs"  << std::setw(10) << std::right << "amount" 
                  << std::setw(10) << std::right << "total" << "\n";      


                  std::cout << std::setw(10) << std::right << gindex_user[_return].id  << std::setw(7) << std::right << gindex_user[_return].marker 
                  << std::setw(10) << std::right << guser[_return].date  << std::setw(20) << std::right << guser[_return].product_name 
                  << std::setw(10) << std::right << guser[_return].pcs  << std::setw(10) << std::right << guser[_return].amount 
                  << std::setw(10) << std::right << guser[_return].total << "\n";      
      
 
                  std::cout << "\n\npress any key... ";

                  getchar( );

            }//5


      }//3

      std::cout << "\n\nexiting \n";
      return 0;
}//2



