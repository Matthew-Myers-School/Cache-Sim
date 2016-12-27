#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std ;

struct Associativity{
    vector<int> set;
};

string directMapped(string in, int cSize);
string setAssociative(string in, int assoc);
string fullyAssociative(string in);
string noAllocationOnWrite(string in, int assoc);
string nextLine(string in, int assoc);
string preOnMiss(string in, int assoc);

int main(int argc, char *argv[]){

	string infile = argv[1];
	ofstream out(argv[2]);

    out << directMapped(infile, 1024);
    out << directMapped(infile, (1024 * 4) );
    out << directMapped(infile, (1024 * 16) );
    out << directMapped(infile, (1024 * 32) );
	out << endl;
   
    out << setAssociative(infile, 2);
	out << setAssociative(infile, 4);
	out << setAssociative(infile, 8);
	out << setAssociative(infile, 16);
	out << endl;
    
    out << fullyAssociative(infile);
    out << endl;

	out << noAllocationOnWrite(infile, 2);
	out << noAllocationOnWrite(infile, 4);
	out << noAllocationOnWrite(infile, 8);
    out << noAllocationOnWrite(infile, 16);
    out << endl;
	
    
    out << nextLine(infile, 2);
	out << nextLine(infile, 4);
	out << nextLine(infile, 8);
    out << nextLine(infile, 16);
    out << endl;
    
	out << preOnMiss(infile, 2);
	out << preOnMiss(infile, 4);
	out << preOnMiss(infile, 8);
    out << preOnMiss(infile, 16);
    out << endl;

}

string directMapped(string in, int cSize){
    
    ifstream infile(in.c_str()) ;
    
    char SL ;
    int addr ;
    
    int tableSize = cSize / 32 ;
    int table[tableSize] ;
    for(int i = 0 ; i < tableSize ; i++){
        table[i] = -1 ;
    }
    int total = 0 ;
    int hit = 0 ;
    
    while(infile >> SL >> std::hex >> addr ) {
        
        int blockNum = addr / 32 ;
        int setNum = blockNum % tableSize  ;
        if( table[setNum] == blockNum )
            hit ++ ;
        else
            table[setNum] = blockNum ;
        total ++ ;
    }
    string returnString;
    returnString.append(to_string(hit));
    returnString.append(", ");
    returnString.append(to_string(total));
    returnString.append("; ");
    return returnString;
}

string setAssociative(string in, int assoc){
    
    ifstream infile(in.c_str());
    Associativity inVec;
    for (int i = 0; i < assoc; i++)
        inVec.set.push_back(-1);
    char SL ;
    int addr ;
    int tableSize = (16 * 1024) / (32 * assoc);
    
    
    vector<Associativity> table;
    for (int i = 0; i < tableSize; i++)
        table.push_back(inVec);
    
    int total = 0;
    int hit = 0;
    
    while(infile >> SL >> std::hex >> addr ) {
        
        bool foundInSet = false;
        int blockNum = addr / (32);
        int setNum = blockNum % tableSize ;
        for(int i = 0 ; i < assoc ; i++){
            if(table[setNum].set[i] == blockNum){
                hit ++;
                table[setNum].set.erase(table[setNum].set.begin() + (i));
                table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                foundInSet = true;
                break;
            }
        }
        if(!foundInSet)
        {
            table[setNum].set.insert(table[setNum].set.begin(), blockNum);
            table[setNum].set.pop_back();
        }
        total ++ ;
    }
    
    
    string returnString;
    returnString.append(to_string(hit));
    returnString.append(", ");
    returnString.append(to_string(total));
    returnString.append("; ");
    return returnString;

    
}

string fullyAssociative(string in){
    
    ifstream infile(in.c_str());
    
    int total = 0;
    int hit = 0;
    char SL;
    int addr;
    int assoc = (16 * 1024) / (32);
    int tableSize = 1 ;
    Associativity table;
    for (int i = 0; i < assoc; i++)
    {
        table.set.push_back(-1);
    }
    
    while(infile >> SL >> std::hex >> addr)
    {
        
        bool foundInSet = false;
        int blockNum = addr / (32);
        for(int i = 0; i < assoc; i++)
        {
            if(table.set[i] == blockNum)
            {
                hit ++;
                table.set.erase(table.set.begin() + (i));
                table.set.insert(table.set.begin(), blockNum);
                foundInSet = true;
                break ;
            }
        }
        if(!foundInSet)
        {
            table.set.insert(table.set.begin(), blockNum);
            table.set.pop_back();
        }
        total ++;
    }
    string returnString;
    returnString.append(to_string(hit));
    returnString.append(", ");
    returnString.append(to_string(total));
    returnString.append("; ");
    return returnString;
}

string noAllocationOnWrite(string in, int assoc){
    
    
    ifstream infile(in.c_str());
    Associativity inVec;
    for (int i = 0; i < assoc; i++)
        inVec.set.push_back(-1);
    char SL ;
    int addr ;
    int tableSize = (16 * 1024) / (32 * assoc);
    
    
    vector<Associativity> table;
    for (int i = 0; i < tableSize; i++)
        table.push_back(inVec);
    
    int total = 0;
    int hit = 0;
    
    while(infile >> SL >> std::hex >> addr ) {
        
        bool foundInSet = false;
        int blockNum = addr / (32);
        int setNum = blockNum % tableSize ;
        for(int i = 0 ; i < assoc ; i++){
            if(table[setNum].set[i] == blockNum){
                hit ++;
                table[setNum].set.erase(table[setNum].set.begin() + (i));
                table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                
                foundInSet = true;
                break;
            }
        }
        if(!foundInSet && SL != 'S')
        {
            table[setNum].set.insert(table[setNum].set.begin(), blockNum);
            table[setNum].set.pop_back();
        }
        total ++;
    }
    
    
    string returnString;
    returnString.append(to_string(hit));
    returnString.append(", ");
    returnString.append(to_string(total));
    returnString.append("; ");
    return returnString;
}


string nextLine(string in, int assoc){
    
    ifstream infile(in.c_str());
    Associativity inVec;
    for (int i = 0; i < assoc; i++)
        inVec.set.push_back(-1);
    char SL ;
    int addr ;
    int tableSize = (16 * 1024) / (32 * assoc);
    
    
    vector<Associativity> table;
    for (int i = 0; i < tableSize; i++)
        table.push_back(inVec);
    
    int total = 0;
    int hit = 0;
    
    while(infile >> SL >> std::hex >> addr ) {
        
        bool foundInSet = false;
        int blockNum = addr / (32);
        int setNum = blockNum % tableSize ;
        for(int i = 0 ; i < assoc ; i++){
            if(table[setNum].set[i] == blockNum){
                hit ++;
                table[setNum].set.erase(table[setNum].set.begin() + (i));
                table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                
                foundInSet = true;
                break;
            }
        }
        if(!foundInSet)
        {
            table[setNum].set.insert(table[setNum].set.begin(), blockNum);
            table[setNum].set.pop_back();
        }
        addr = addr + 32 ;
        foundInSet = false ;
        blockNum = addr / (32) ;
        setNum = blockNum % tableSize  ;
        for(int i = 0 ; i < assoc ; i++){
            if(table[setNum].set[i] == blockNum){
                table[setNum].set.erase(table[setNum].set.begin() + (i));
                table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                
                foundInSet = true;
                break;
            }
        }
        if(!foundInSet)
        {
            table[setNum].set.insert(table[setNum].set.begin(), blockNum);
            table[setNum].set.pop_back();
        }
        total ++ ;
    }
    
    
    string returnString;
    returnString.append(to_string(hit));
    returnString.append(", ");
    returnString.append(to_string(total));
    returnString.append("; ");
    return returnString;
}

string preOnMiss(string in, int assoc){
    
    
    ifstream infile(in.c_str());
    Associativity inVec;
    for (int i = 0; i < assoc; i++)
        inVec.set.push_back(-1);
    char SL ;
    int addr ;
    int tableSize = (16 * 1024) / (32 * assoc);
    
    
    vector<Associativity> table;
    for (int i = 0; i < tableSize; i++)
        table.push_back(inVec);
    
    int total = 0;
    int hit = 0;
    
    while(infile >> SL >> std::hex >> addr ) {
        
        bool foundInSet = false;
        int blockNum = addr / (32);
        int setNum = blockNum % tableSize ;
        for(int i = 0 ; i < assoc ; i++){
            if(table[setNum].set[i] == blockNum){
                hit ++;
                table[setNum].set.erase(table[setNum].set.begin() + (i));
                table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                
                foundInSet = true;
                break;
            }
        }
        if(!foundInSet)
        {
            table[setNum].set.insert(table[setNum].set.begin(), blockNum);
            table[setNum].set.pop_back();
            addr = addr + 32 ;
            foundInSet = false ;
            blockNum = addr / (32) ;
            setNum = blockNum % tableSize  ;
            for(int i = 0 ; i < assoc ; i++){
                if(table[setNum].set[i] == blockNum){
                    table[setNum].set.erase(table[setNum].set.begin() + (i));
                    table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                
                    foundInSet = true;
                    break;
                }
            }
            if(!foundInSet)
            {
                table[setNum].set.insert(table[setNum].set.begin(), blockNum);
                table[setNum].set.pop_back();
            }
        }
        total ++ ;
    }
    string returnString;
    returnString.append(to_string(hit));
    returnString.append(", ");
    returnString.append(to_string(total));
    returnString.append("; ");
    return returnString;
}

