




#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <sstream>
#include <iomanip>


//declarations

#define ADDRESS_INDEX_USER "index_user1.db"
#define ADDRESS_USER "user1.db"

#define RANGE_ARRAY 1000000 // one million elements

//mag hahandle sa file write and read process


//main database 
std::ifstream user_read;  
std::ofstream user_write; 

namespace rondb {//2
        
        //struct para sa format ng file
        struct user_password_struct { //2      user_password
         
                int password;  //format ng file
                int last_id;  //para ascending order ung id
                int length;  //max length ng database by row data
                int range_first; //starting range ng id, future purpose para sa extending of files
                int range_last;  //last range ng id, future purpose para sa extending of files

        }; //2
        
      

        //main database
        struct user_struct{  //2
              
                int id;
                int marker;
                int date;            //asuming na in order ung date, datatype int muna gamit ko
                char product_name[100];
                int quantity;
                double item_price;
                double total_price;      

        }; //2

        //carrier variable ng database
        struct user_password_struct  user_password;        
        struct user_struct user[RANGE_ARRAY];

        //ginamitan ko lang ng alias ung strcpy para oriented ung rondb
        auto kopyko = std::strcpy;

        //gamit ito
        int default_width = 96; 
        
        //L200   marker para hindi ako maligaw pag nag babasa nitong code na ito
        
        //initial value use by user.db
        void initial( );
        
        
        //CRUD functions
      
        int linear_search( int target ) ;

        //function sa display output
        int display_range( int start_par, int stop_par );

        //mag display ng 1 row, gamit ito pag sucess ung process
        //para madetermine ung sucess na row data
        void display_single( std::string title, int fir );
        
        //group ng pang align ng display output        
        std::string cell_data(std::string x, int width);
        std::string cell_data(int x, int width);       
        std::string cell_data(double x, int width);
        std::string truncate(std::string s, int max_length);
        std::string center_string( std::string input,  int length);

        //format ng string number double       
        bool get_string(std::string& output);
        void get_string( ); //L100
        bool get_integer(int& output);
        bool get_floating_point(double& output);
        
}//2


//implementation

void rondb::initial(  ) {//2
        //l20
         
        user_read.open( ADDRESS_USER, std::ios::binary );

        if(  !(!user_read) ){//20

                //leave the initial function if 2 file exists
                user_read.read( (char*) &rondb::user_password, sizeof(user_password_struct ) ) ;                           
                
                if( rondb::user_password.password != 1234 ){ //21

                        std::cout << "\n\nwrong format ng file\ngagawa tayo ulit ng bago";
                        get_string( );
                }else {//21

                        //sucessful now begin to the main menu
                        user_read.read( (char*) &rondb::user, sizeof(user_struct ) * RANGE_ARRAY) ;                           
                
                        user_read.close(  );
                        return;
                }//21
        }else{ //20
                std::cout << "\n\nWlang nakitang laman ng data, gagawa ng inital na laman";
                get_string();

        }//20


        
        user_write.open( ADDRESS_USER, std::ios::binary );

        rondb::user_password.password = 1234;

        rondb::user_password.length = RANGE_ARRAY;
      
        std::string _str=""; //sub string
        int id =10;

        for( int fir = 0; fir < RANGE_ARRAY;  fir+=1 ) {//3
                rondb::user[fir].id = id;
                rondb::user[fir].marker = 1;
                rondb::user[fir].date = (id -10) +1;
                _str = "";
                _str = "name" + std::to_string( (id -10) +1);

                kopyko( user[fir].product_name, _str.c_str(  ) ); 
                
                rondb::user[fir].quantity = 2;
                rondb::user[fir].item_price =  (id -10) +1;
                rondb::user[fir].total_price = rondb::user[fir].quantity * rondb::user[fir].item_price;    

                id+=1;
        }//3
  
        rondb::user_password.last_id = id-1;

        //intial
        user_write.write( (char*) &rondb::user_password, sizeof( rondb::user_password_struct ) );

       
        user_write.write( (char*) rondb::user, sizeof( rondb::user_struct ) * RANGE_ARRAY );


        user_write.close();


}//2

//return -1 if fails, otherwise 0 to up value sucess
int rondb::linear_search( int target ) {//2
        //L60 
        
        //std::cout << "\ndebug L71 target " << target <<"\n";

        int left= 0, right = rondb::user_password.length-1 , mid;

        mid = (left + right) / 2;

        while( left < right ) {//3

                std::cout << "\ndebug L72 target " << target << ", user[mid].id " << rondb::user[mid].id <<
                ", left " << left << ", mid " << mid << ", right " << right << "\n";

                // < id dadasog pa-baba
                if( target < rondb::user[mid].id ) { //4
                        //( left    m )   right
                        right = mid;
                        mid = (left +  mid) /2;

                // > id then dadasog pataas
                } else if( target > rondb::user[mid].id ) { //4
                        // left    (m    right )

                        left = mid;
                        //para pag nasa dulo pataas ay hindi mag infinite loop
                        if( mid + right % 2 != 0) {//5
                        mid = ( (mid + right) /2) +1;

                        }else {//5

                        mid = (mid + right) /2;
                        }//5

                //it is equal return 
                } else { //4

                        if( rondb::user[mid].marker == 0  ) {//10
                                //it is marked as deleted
                                break;
                        }//10

                        return mid;
                }//4

        }//3

        //cannot return 0 because it is the first index, then if fail return -1
        return -1;
}//2


//note:  included ung marker any value para malaman kung anung result ng testing
//saka nalng tatangalin ito pag complete na ung test
//param start_par ex: 0 ang 0 ang first value,  stop_par ex: 10 ang 9 ang last value
int rondb::display_range( int start_par, int stop_par ) { //2
        //L70
        //reopening it

        //std::cout << "\ndebug L31 start_par " << start_par << " , stop_par " << stop_par << "\n";

        if( stop_par >= rondb::user_password.length ) {//10
            return -1;
        }//10

        int fir =start_par;
        int column_width[] = { 10, 10, 7, 10, 20, 10, 10, 10 };  //8 elements
        std::cout << std::string( rondb::default_width , '=');

        std::cout << "\n|" << cell_data( center_string( "Display the selected range", rondb::default_width -2 ), rondb::default_width -2 ) <<  "|\n";
        std::cout << std::string( rondb::default_width , '-');

        std::cout << "\n|" << cell_data( "Index", column_width[0] ) << "|" 
        << cell_data( "Id" , column_width[1] )  << "|"
        << cell_data( "Marker" , column_width[2] )  << "|"
        << cell_data( "Date" , column_width[3] )  << "|"
        << cell_data( "Product Name" , column_width[4] )  << "|"   
        << cell_data( "Quantity" , column_width[5] )  << "|"
        << cell_data( "Item Price" , column_width[6] )  << "|"
        << cell_data( "Total" , column_width[7] )  << "|";

        while( fir <= stop_par ){//4

                std::cout << "\n" << std::string( rondb::default_width , '-');

                std::cout << "\n|" << cell_data( fir , column_width[0] ) << "|" 
                << cell_data( rondb::user[fir].id , column_width[1] )  << "|"
                << cell_data( rondb::user[fir].marker , column_width[2] )  << "|"
                << cell_data( rondb::user[fir].date , column_width[3] )  << "|"
                << cell_data( rondb::user[fir].product_name , column_width[4] )  << "|"   
                << cell_data( rondb::user[fir].quantity , column_width[5] )  << "|"
                << cell_data( rondb::user[fir].item_price , column_width[6] )  << "|"
                << cell_data( rondb::user[fir].total_price  , column_width[7] )  << "|";

                fir+=1;
        }//4

        std::cout << "\n" << std::string( rondb::default_width , '=');

      return 0;
}//2

void rondb::display_single( std::string title, int fir ){//2
        //L80
        int column_width[] = { 10, 10, 7, 10, 20, 10, 10, 10 };  //8 elements
        std::cout << std::string( rondb::default_width , '=');

      
        std::cout << "\n|" << rondb::cell_data( rondb::center_string( title, rondb::default_width -2) , rondb::default_width -2 ) <<  "|\n";
        std::cout << std::string( rondb::default_width , '-');

        std::cout << "\n|" << rondb::cell_data( "Index", column_width[0] ) << "|" 
        << rondb::cell_data( "Id" , column_width[1] )  << "|"
        << rondb::cell_data( "Marker" , column_width[2] )  << "|"
        << rondb::cell_data( "Date" , column_width[3] )  << "|"
        << rondb::cell_data( "Product Name" , column_width[4] )  << "|"   
        << rondb::cell_data( "Quantity" , column_width[5] )  << "|"
        << rondb::cell_data( "Item Price" , column_width[6] )  << "|"
        << rondb::cell_data( "Total" , column_width[7] )  << "|";

        std::cout << "\n" << std::string( rondb::default_width , '-');

        std::cout << "\n|" << cell_data( fir , column_width[0] ) << "|" 
        << rondb::cell_data( rondb::user[fir].id , column_width[1] )  << "|"
        << rondb::cell_data( rondb::user[fir].marker , column_width[2] )  << "|"
        << rondb::cell_data( rondb::user[fir].date , column_width[3] )  << "|"
        << rondb::cell_data( rondb::user[fir].product_name , column_width[4] )  << "|"   
        << rondb::cell_data( rondb::user[fir].quantity , column_width[5] )  << "|"
        << rondb::cell_data( rondb::user[fir].item_price , column_width[6] )  << "|"
        << rondb::cell_data( rondb::user[fir].total_price  , column_width[7] )  << "|";
        
        std::cout << "\n" << std::string( rondb::default_width , '=');
}//2

std::string rondb::cell_data(std::string x, int width) {
        //L90
        std::ostringstream oss;

        oss << std::setw(width) << std::left << rondb::truncate(x, width);

        return oss.str();
}
 
std::string rondb::cell_data(int x, int width) {
        //L100
        std::string s;
        std::ostringstream oss;

        oss << x;
        s = rondb::truncate(oss.str(), width);
        oss.str(""); // reset internal string buffer
        oss << std::setw(width) << std::right << s;

        return oss.str();
}
 
std::string rondb::cell_data(double x, int width) {
        //L110
        std::string s;
        std::ostringstream oss;

        oss << std::fixed << std::setprecision(2) << x;
        s = rondb::truncate(oss.str(), width);
        oss.str(""); // reset internal string buffer
        oss << std::setw(width) << std::right << s;

        return oss.str();
}
 
std::string rondb::truncate(std::string s, int max_length) {
        //L120
        if ((int)s.size() > max_length) {
                s.erase(s.begin() + max_length - 1, s.end());
                s += '~'; // signify that truncation has occurred
        }

        return s;
}

std::string rondb::center_string( std::string input, int length){//2
        //L130
        
      
        
        //nag rondb::default_width -2, ung 2 ay para sa dalawang '|' para sa
        //output

        //tuloy ito isakto ung center_string palibutan ng space
        //pag sakto ng == length ay hindi na ito papakelaman
        
        int length_input = input.length(  );
        std::string return_str;

        if( length_input > length ){

                return_str = input.substr(0, length);
                return return_str;                
        }

        int start_index_input = ( ( length -1 ) / 2)  -  ( (length_input - 1)  / 2 );

        return_str = std::string( start_index_input, ' ' ) + input;
        
        int last_index_length = (length -1) - ( start_index_input + (length_input -1) );

        return_str += std::string( last_index_length, ' ' );

        //std::cout << "\ndebug L131 return_str.length " << return_str.length(  ) << "\n";
     
        /*
        title
        96 -2 = 94 -1   = 93 /2 => 46
        5 - 1 /2 = 2

        46 - 2 =>  44 4  start_index_input

        44 + 5-1 => 48   

        93 - 48 = 45     


           44   +  4  + 45 = 93
        */
        return return_str;

}//2

bool rondb::get_string(std::string& output) { 
        //L40 

        // If an error occurs, `output` is left empty.
        std::getline(std::cin, output);

        bool fail = std::cin.fail();
        std::cin.clear(); // clear error flags

        //std::cout << "debug L41 output " << output << " ,fail " << fail << "\n";

        return fail;
}

//overloading fget_string, use of pausing on screen
void rondb::get_string( ) { //2
        //L150 

        std::string output;
        // If an error occurs, `output` is left empty.
        std::getline(std::cin, output);

        std::cin.fail();
        std::cin.clear(); // clear error flags

}//2

bool rondb::get_integer(int& output) {
      //L160
      
      std::string s;
      std::istringstream iss;

      if ( rondb::get_string(s) ) {
            return false;
      }
 
      iss.str(s); // assign a new string buffer to the input stream
      output = 0;
      // If an error occurs, `output` is not modified.
      iss >> output;

      //std::cout << "debug L51 output " << output << " ,fail " << fail << "\n";

      return iss.fail() ;
}

bool rondb::get_floating_point(double& output) {
      //L170 

      std::string s;
      std::istringstream iss;

      if ( rondb::get_string(s) ) {
            return false;
      }

      iss.str(s); // assign a new string buffer to the input stream
      output = 0;
      // If an error occurs, `output` is not modified.
      iss >> output;

      return iss.fail()  ;
}

int main(void  ) {//2
      
        //L10 
        
        std::string ch;
      
        int screen_wide = 30;

        rondb::initial();

        while(1) {//3
                
                std::cout << "\n\n\n" << std::string( screen_wide ,'=') 
                << "\n|"<< rondb::center_string( "Main menu:", screen_wide-2) << "|\n"
                << std::string( screen_wide ,'-')
                << "\na addnew"                
                << "\ne edit data"
                << "\nr remove data"
                << "\nf to find id" 
                << "\nd to display selected range"
                << "\nq to leave "
                << "\n" << std::string( screen_wide ,'-')
                << "\nTotal Index 0 to " << rondb::user_password.length -1 
                << "\n" << std::string( screen_wide ,'=') << "\n";

                while (  rondb::get_string(ch)  || ch.size()  >= 100 ) { //4
                        std::cout << "\n\nerror invalid input.\n";
                } //4

                if( ch == "q" || ch == "Q") {//5
                        break;
                }else if( ch == "d" || ch == "D" ) { //5

                        //dislay mode

                        int start_int, length_int;

                        std::cout << "\n\nDisplay mode:\nstart in 0 end at actual number \nex: 1 to 10 is 0 to 9\ninput starting index:  ";
                        while (  rondb::get_integer(start_int)  ) { //4
                                std::cout << "\n\nwrong input of integer.\n";
                        } //4

                        std::cout << "\n\ninput length:  ";
                        while ( rondb::get_integer(length_int)  ) { //4
                                std::cout << "\n\nwrong input of integer.\n";
                        } //4

                        int return_ = rondb::display_range( start_int, length_int );

                        if( return_ ==-1) {//10
                                std::cout << "\n\nover range of length input must not over " << rondb::user_password.length-1 << " ... ";
                                rondb::get_string(  );
                                continue;
                        }//10

                } else if( ch == "f" || ch == "F" ) { //5
                        //find mode

                        int input;

                        std::cout << "\n\nFind mode:\ninput id for target:  ";
                        while (  rondb::get_integer( input )  ) { //4
                                std::cout << "\n\nwrong input of integer.\n";
                        } //4

                        //return_ holds the result and index number
                        int return_ = rondb::linear_search( input ) ;
                        if( return_ == -1 ) {//7
                                std::cout << "\n\nfail to find target " << input << "\npress any key... ";
                                rondb::get_string();
                                continue;
                        }//7

                        std::cout << "\n\nsucess target id is " << input << " has been found \n" ;
                        std::string sub_str = std::string( " target id is " ) + std::to_string( input ) ;

                        rondb::display_single( 
                            rondb::center_string(sub_str, sub_str.length(  ) ),
                                   return_ );

                        std::cout << "\n\npress any key... ";

                        rondb::get_string();

                } else if( ch == "R" || ch == "r" ) { //5
                        
                        //remove mode                 
                       
                } else if( ch == "A" || ch == "a" ) { //5

                        //Addnew
                       
                } else if( ch == "E" || ch == "e" ) { //5
                        
                        //edit mode  
                }//5

        }//3

        std::cout << "\n\nexiting \n";
        return 0;
}//2























