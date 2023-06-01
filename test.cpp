

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
      13    0      mark as deleted                                13             1/3/2023       name1 familyname3     1          100.03
      14    1                                                     14             1/4/2023       name1 familyname4     1          100.04 
      15    1                                                     15             1/5/2023       name1 familyname5     1          100.05    100.05
 
      //note:  sa fdisplay, included ung marker any value para malaman kung anung result ng testing
      //saka nalng tatangalin ito pag complete na ung test

      sa initial value na input ko computation (100,000 - 1000 ) (limit na data para sa add for testing purpose) 
      -1 (less 1 para makuha last index dahil staring tyo ng 0)
      range index 0 to 98999

      index       id         date    etc...
        0         10         1
        1         11         2
        98999     99009

      project update
      konting testing pa pag ok na, ung columing naman ang aausin ko
      saka ko nlang muna gawing ung print out column ni sir aj tan, tapusin ko muna ung CRUD ng database
      pag tapus nito, aausin ko na ung print out ng column.
*/


        

#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include <sstream>
#include <iomanip>

#define ADDRESS_INDEX_USER "index_user1.db"
#define ADDRESS_USER "user1.db"

#define RANGE_ARRAY 100000

struct index_user_password_struct { //2      user_password
 
      int password;
      int last_id;
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
bool fget_string(std::string& output);
bool fget_integer(int& output);
bool fget_floating_point(double& output);
int fdisplay_range( int start_par, int stop_par );
int flinear_search( int target ) ;
int fremove( int target );   //L80 
void fedit(  ); //L90
void fget_string( ); //L100


void fadd(  ) {//2

        user_struct user_sub;

        std::string str_;

        std::cout << "\n\nAdd new mode:  ";
                 
        std::cout << "\ninput date:  ";
        while ( fget_integer( user_sub.date  )  ) { //4
                std::cout << "\n\nwrong input of integer.\n";
        } //4

        std::string sub_str="";
        std::cout << "\ninput product name:  ";
        while (  fget_string( str_ )  || str_.size()  >= 100 ) { //4
                std::cout << "\n\nerror invalid input.\n";
        } //4
       
        strcpy(user_sub.product_name, str_.c_str(  ) );

        std::cout << "\ninput pcs:  ";
        while ( fget_integer( user_sub.pcs  )  ) { //4
                std::cout << "\n\nwrong input of integer.\n";
        } //4

        std::cout << "\ninput amount:  ";
        while (  fget_floating_point( user_sub.amount  )  ) { //4
                std::cout << "\n\nwrong input of integer.\n";
        } //4


        while(  1 ){//7

                std::cout << "\nU want to save the added data:  ";
                while (  fget_string( str_ )  ) { //4
                        std::cout << "\n\nwrong input of string.\n";
                } //4

                if( str_ == "Y" || str_ == "y"  ) {//5
                        break;
                }if( str_ == "N" || str_ == "n"  ) {//5

                        std::cout << "\n\nYou have canceled the added data... ";
                        fget_string(  );

                        return;
                }else {//5
                        std::cout << "\n\nMust input Y or N  ";
                        fget_string(  );
                }//5

        }//7

        //computation of total
        guser[ gindex_user_password.length ] = user_sub;

        guser[ gindex_user_password.length ].total = guser[ gindex_user_password.length ].amount  * 
        guser[ gindex_user_password.length ].pcs; 

        //updating the new id
        gindex_user_password.last_id +=1;

        guser[ gindex_user_password.length ].id = gindex_user_password.last_id; 
        gindex_user[ gindex_user_password.length ].id = gindex_user_password.last_id;

        gindex_user[ gindex_user_password.length ].marker = 1;

        guser[ gindex_user_password.length ].id = gindex_user_password.last_id +1;

        //updating the new length
        gindex_user_password.length +=1;

        gindex_user_write.open( ADDRESS_INDEX_USER, std::ios::binary );

        guser_write.open( ADDRESS_USER, std::ios::binary );

        //intial
        gindex_user_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );

        //intial
        guser_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );

        gindex_user_write.write( (char*) &gindex_user, sizeof( index_user_struct ) * gindex_user_password.length );

        guser_write.write( (char*) guser, sizeof( user_struct ) * gindex_user_password.length  );

        gindex_user_write.close();

        guser_write.close();

        std::cout << "\n\ndata sucessfully been saved  ";
        fget_string( );
            
        
}//2

//overloading fget_string, use of pausing on screen
void fget_string( ) { //2
      //L40 

      std::string output;
      // If an error occurs, `output` is left empty.
      std::getline(std::cin, output);

      std::cin.fail();
      std::cin.clear(); // clear error flags

}//2

void fedit(  ) {//2
      //L90

      user_struct user_sub;

      int id_inp=-1;
      std::cout << "\n\nEdit mode:\ninput id to edit:  ";
      while(  fget_integer(id_inp  ) ) {//3
            std::cout << "\n\nwrong input of integer ";
      }//3

      int _return = flinear_search( id_inp );
      if( _return  == -1) {//3
            std::cout << "\n\ndid not find the id " << id_inp << "...";    
            fget_string();
            return;
      }//3 

      //to avoid loss of column data salin ng buo
      user_sub = guser[_return];  

      std::cout << "\n\ninput new date:  ";
      while(  fget_integer(id_inp  )  ) {//3
            std::cout << "\n\nwrong input of integer ";
      }//3
      user_sub.date = id_inp;

      std::string inp_str;
      std::cout << "\n\ninput new product_name:  ";
      while(  fget_string(inp_str  ) || inp_str.size(  ) > 100) {//3
            std::cout << "\n\nover length of string or other error";
      }//3
      strcpy( user_sub.product_name , inp_str.c_str(  ) ) ;

      std::cout << "\n\ninput new pcs:  ";
      while(  fget_integer(id_inp  ) ) {//3
            std::cout << "\n\nwrong input of integer ";
      }//3
      user_sub.pcs = id_inp;

      double inp_double;
      std::cout << "\n\ninput new amount:  ";
      while(  fget_floating_point(inp_double  ) ) {//3
            std::cout << "\n\nwrong input of integer ";
      }//3
      
      user_sub.amount = inp_double;
      user_sub.total = user_sub.amount * user_sub.pcs;

      while( 1 ) {//5

            std::cout << "\n\nAre u sure you want to save the edited data\ny for yes / n for no... ";

            while(  fget_string(inp_str  ) || inp_str.size(  ) > 100) {//3
                  std::cout << "\n\nover length of string or other error  ";
            }//3

            if(inp_str == "Y" || inp_str == "y" ){//4

                  guser[_return] = user_sub;
                  
                  std::cout << "\n\nSucessfully save data\n";
 
                  std::cout << std::setw(10) << std::right << "id"  << std::setw(7) << std::right << "marker" 
                  << std::setw(10) << std::right << "date"  << std::setw(20) << std::right << "product name " 
                  << std::setw(10) << std::right << "pcs"  << std::setw(10) << std::right << "amount" 
                  << std::setw(10) << std::right << "total" << "\n";      

                  std::cout << std::setw(10) << std::right << gindex_user[_return].id  << std::setw(7) << std::right << gindex_user[_return].marker 
                  << std::setw(10) << std::right << guser[_return].date  << std::setw(20) << std::right << guser[_return].product_name 
                  << std::setw(10) << std::right << guser[_return].pcs  << std::setw(10) << std::right << guser[_return].amount 
                  << std::setw(10) << std::right << guser[_return].total << "\n";      

                  std::cout << "press any... ";

                  fget_string(); 
                  break;
            }else if( inp_str == "N" || inp_str == "n"  ) {//4
                  std::cout << "\n\nYou have canceled saving it\npress any... ";
                  fget_string();
                  break;
            }//4

            std::cout << "\n\nerror you must input y or n only... ";

       }//5

}//2

//param target the id to be deleted
//returns -1 if fail, otherwise 0 to up sucessfull
int fremove( int target ){//2
        //L80 
        std::string str_;    
        int index = flinear_search( target );

        if( index == -1 ){//3
                //did not find it
                return -1;
        }//3

        while(  1 ){//7

                std::cout << "\nAre u sure u want to delete Y or N:  ";
                while (  fget_string( str_ )  ) { //4
                        std::cout << "\n\nwrong input of string.\n";
                } //4

                if( str_ == "Y" || str_ == "y"  ) {//5
                        break;
                }if( str_ == "N" || str_ == "n"  ) {//5

                        std::cout << "\n\nYou have canceled to delete... ";
                        fget_string(  );

                        return -2;
                }else {//5
                        std::cout << "\n\nMust input Y or N  ";
                        fget_string(  );
                }//5

        }//7
        //put the flag to delete
        gindex_user[index ].marker = 0;

        gindex_user_write.open( ADDRESS_INDEX_USER, std::ios::binary );
        gindex_user_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );
        gindex_user_write.write( (char*) gindex_user, sizeof( index_user_struct ) * gindex_user_password.length );
        gindex_user_write.close();

        return index;
}//2

//note:  included ung marker any value para malaman kung anung result ng testing
//saka nalng tatangalin ito pag complete na ung test
//param start_par ex: 0 ang 0 ang first value,  stop_par ex: 10 ang 9 ang last value
int fdisplay_range( int start_par, int stop_par ) { //2
      //L30
      //reopening it

      //std::cout << "\ndebug L31 start_par " << start_par << " , stop_par " << stop_par << "\n";

      if( stop_par >= gindex_user_password.length ) {//10
            return -1;
      }//10

      int fir =start_par;

      std::cout << "\n\n" << std::setw( 40 ) << std::right << "Title database " << ADDRESS_USER << "\n";

      std::cout << std::setw(10) << std::right << "index" << std::setw(10) << std::right << "id"  << std::setw(7) << std::right << "marker" 
      << std::setw(10) << std::right << "date"  << std::setw(20) << std::right << "product name " 
      << std::setw(10) << std::right << "pcs"  << std::setw(10) << std::right << "amount" 
      << std::setw(10) << std::right << "total" << "\n";      
            
      while( fir <= stop_par ){//4
            
            std::cout << std::setw(10) << std::right << fir << std::setw(10) << std::right << gindex_user[fir].id  << std::setw(7) << std::right << gindex_user[fir].marker 
            << std::setw(10) << std::right << guser[fir].date  << std::setw(20) << std::right << guser[fir].product_name 
            << std::setw(10) << std::right << guser[fir].pcs  << std::setw(10) << std::right << guser[fir].amount 
            << std::setw(10) << std::right << guser[fir].total << "\n";      
      
            
            fir+=1;
      }//4

      return 0;
}//2

void finitial(  ) {//2

      //L20       
      gindex_user_write.open( ADDRESS_INDEX_USER, std::ios::binary );

      guser_write.open( ADDRESS_USER, std::ios::binary );

      gindex_user_password.password = 1234;

      gindex_user_password.length = RANGE_ARRAY - 1000;
      gindex_user_password.range_first = 10;    //starting range 
      gindex_user_password.range_last =  ( (RANGE_ARRAY - 1000)  + 10) -1 ; //range 10 to 10009

      //intial
      gindex_user_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );

      //intial
      guser_write.write( (char*) &gindex_user_password, sizeof( index_user_password_struct ) );

      std::string _str=""; //sub string
      int id =10;

      for( int fir = 0; fir < RANGE_ARRAY - 1000 ;  fir+=1 ) {//3

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

      
      gindex_user_password.last_id = id-1;

      gindex_user_write.write( (char*) &gindex_user, sizeof( index_user_struct ) * RANGE_ARRAY);

      guser_write.write( (char*) guser, sizeof( user_struct ) * RANGE_ARRAY );

      gindex_user_write.close();

      guser_write.close();


}//2


bool fget_string(std::string& output) { 
      //L40 

      // If an error occurs, `output` is left empty.
      std::getline(std::cin, output);

      bool fail = std::cin.fail();
      std::cin.clear(); // clear error flags

      //std::cout << "debug L41 output " << output << " ,fail " << fail << "\n";

      return fail;
}

bool fget_integer(int& output) {
      //L50 

      std::string s;
      std::istringstream iss;

      if ( fget_string(s) ) {
            return false;
      }

   
      iss.str(s); // assign a new string buffer to the input stream
      output = 0;
      // If an error occurs, `output` is not modified.
      iss >> output;

      //std::cout << "debug L51 output " << output << " ,fail " << fail << "\n";

      return iss.fail() ;
}


bool fget_floating_point(double& output) {
      //L60 

      std::string s;
      std::istringstream iss;

      if ( fget_string(s) ) {
            return false;
      }

      iss.str(s); // assign a new string buffer to the input stream
      output = 0;
      // If an error occurs, `output` is not modified.
      iss >> output;

      return iss.fail()  ;
}

//return -1 if fails, otherwise 0 to up value sucess
int flinear_search( int target ) {//2
        //L70 

        std::cout << "\ndebug L71 target " << target <<"\n";

        int left= 0, right = gindex_user_password.length-1 , mid;

        mid = (left + right) / 2;

        while( left < right ) {//3

                std::cout << "\ndebug L72 target " << target << ", guser[mid].id " << guser[mid].id <<
                ", left " << left << ", mid " << mid << ", right " << right << "\n";

                // < id dadasog pa-baba
                if( target < guser[mid].id ) { //4
                        //( left    m )   right
                        right = mid;
                        mid = (left +  mid) /2;

                // > id then dadasog pataas
                } else if( target > guser[mid].id ) { //4
                        // left    (m    right )

                        left = mid;

                        if( mid + right % 2 != 0) {//5
                        mid = ( (mid + right) /2) +1;

                        }else {//5

                        mid = (mid + right) /2;
                        }//5

                //it is equal return 
                } else { //4

                        if( gindex_user[mid].marker == 0  ) {//10
                                //it is marked as deleted
                                break;
                        }//10

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
      
            std::cout << "\n\nMain menu:\ntotal index 0 to " << gindex_user_password.length -1 <<  "\nf to find id, d to display selected range, r remove data, a addnew, e edit data\nq to leave:  ";
            while (  fget_string(ch)  || ch.size()  >= 100 ) { //4
                  std::cout << "\n\nerror invalid input.\n";
            } //4

            if( ch == "q" || ch == "Q") {//5
                  break;
            }else if( ch == "d" || ch == "D" ) { //5
                  //dislay mode

                  int start_int, length_int;
                  
                  std::cout << "\n\nDisplay mode:\nstart in 0 end at actual number \nex: 1 to 10 is 0 to 9\ninput starting index:  ";
                  while (  fget_integer(start_int)  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4

                  std::cout << "\n\ninput length:  ";
                  while ( fget_integer(length_int)  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4
                  
                  int return_ = fdisplay_range( start_int, length_int );
        
                  if( return_ ==-1) {//10
                        std::cout << "\n\nover range of length input must not over " << gindex_user_password.length-1 << " ... ";
                        fget_string(  );
                        continue;
                  }//10

            } else if( ch == "f" || ch == "F" ) { //5
                  //find mode

                  int input;

                  std::cout << "\n\nFind mode:\ninput id for target:  ";
                  while (  fget_integer( input )  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4

                  int _return = flinear_search( input ) ;
                  if( _return == -1 ) {//7
                        std::cout << "\n\nfail to find target " << input << "\npress any key... ";
                        fget_string();
                        continue;
                  }//7

                  std::cout << "\n\nsucess target " << _return << " has been found \n" ;
                  std::cout << std::setw(10) << std::right << "index" << std::setw(10) << std::right << "id"  << std::setw(7) << std::right << "marker" 
                  << std::setw(10) << std::right << "date"  << std::setw(20) << std::right << "product name " 
                  << std::setw(10) << std::right << "pcs"  << std::setw(10) << std::right << "amount" 
                  << std::setw(10) << std::right << "total" << "\n";      


                  std::cout << std::setw(10) << std::right << _return << std::setw(10) << std::right << gindex_user[_return].id  << std::setw(7) << std::right << gindex_user[_return].marker 
                  << std::setw(10) << std::right << guser[_return].date  << std::setw(20) << std::right << guser[_return].product_name 
                  << std::setw(10) << std::right << guser[_return].pcs  << std::setw(10) << std::right << guser[_return].amount 
                  << std::setw(10) << std::right << guser[_return].total << "\n";      
 
                  std::cout << "\n\npress any key... ";

                  fget_string();
            
            } else if( ch == "R" || ch == "r" ) { //5
                  //remove mode
                  
                  int id_inp;

                  std::cout << "\n\nRemove data mode:\ninput id to remove:  ";              
                  
                  while ( fget_integer(id_inp)  ) { //4
                        std::cout << "\n\nwrong input of integer.\n";
                  } //4
                  
                  int _return = fremove( id_inp );    

                  if( _return == -1  ) {//7
                        std::cout << "\n\ndid not found target " << id_inp << "\n";
                        fget_string(  );
                        continue;
                  } else if(_return == -2 ){//7
                        //canceled the deleted command
                        continue;                
                  }//7
                       
                  std::cout << "\n\nsucess input " << _return << " deleted \n" ;
                  std::cout << std::setw(10) << std::right << "id"  << std::setw(7) << std::right << "marker" 
                  << std::setw(10) << std::right << "date"  << std::setw(20) << std::right << "product name " 
                  << std::setw(10) << std::right << "pcs"  << std::setw(10) << std::right << "amount" 
                  << std::setw(10) << std::right << "total" << "\n";      

                  std::cout << std::setw(10) << std::right << gindex_user[_return].id  << std::setw(7) << std::right << gindex_user[_return].marker 
                  << std::setw(10) << std::right << guser[_return].date  << std::setw(20) << std::right << guser[_return].product_name 
                  << std::setw(10) << std::right << guser[_return].pcs  << std::setw(10) << std::right << guser[_return].amount 
                  << std::setw(10) << std::right << guser[_return].total << "\n";      
 
                  std::cout << "\n\npress any key... ";
                  fget_string( );
            
            } else if( ch == "A" || ch == "a" ) { //5
                  //Addnew
                        fadd( ); 
            //edit mode
            } else if( ch == "E" || ch == "e" ) { //5
                  
                  fedit(  );

            }//5

      }//3

      std::cout << "\n\nexiting \n";
      return 0;
}//2
























