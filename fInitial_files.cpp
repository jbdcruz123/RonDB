



/*
gagawa ako ng 3 files User_table1.db,  User_table2.db,  User_table3.db na naglalaman ng 100,000 slot of data struct

pag papatuloy

data diagram


      Index_table.db                   User_table.db
     
      index     id    marker           id     date        name                  amount
      0         100    1               100    1/1/2023    name1 familyname1     100.01
      1         101    1               101    1/2/2023    name2 familyname2     100.02
      2         103    0               103    1/3/2023    name1 familyname3     100.03
      3         104    1               104    1/4/2023    name1 familyname4     100.04 
      4         105    1               105    1/5/2023    name1 familyname5     100.05 

      Files.db


*/

#include<iostream>
#include<fstream>
#include<string>

#define _Extension ".db"
#define _Files "Files" 
#define _Index "Files" 
#define _User "Files" 

typedef struct { //2

      int Index;
      int Id;
      int Marker;

}stIndex; //2



typedef struct { //2

      int Id;
      char Date[100];
      char Name[100;
      double Amount;
} stUser; //2


std::ofstream oflIndex; 
std::ofstream oflUser;

stIndex gIndex[100000];
stUser  gUser[100000];

fInitial_user_table(  ){//2

      std::string _str;
      

      int Total_row_data = 100000, Number_files = 3;
      int Fir = 0, Sec=0, Hundred = 100;

      for( ;Sec < Number_files ; Sec+=1 ){//4
            flFiles.open( _Files + _Extension, ""  );
            flIndex.open(  );

            for( ; Fir < Total_row_data ; fir+=1) {//3

                  gIndex.Index[Fir] = Fir;
                  gIndex.Id[Fir] = Fir+ 1 + Hundred;
                  gIndex.Marker[Fir] = 0;

                  _str = "date" + std::to_string( Fir );
                  
                  

            }//3


      }//4


}//2




