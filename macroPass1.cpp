//1913097    KUMARI SAUMYA SINGH   CS216


#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
using namespace std;

// macroname FUCTION BREAKS STRING BY SPACE
string macroname(string MyText,int f=0)
{
	string line ;
	line=MyText;
    vector <string> tokens;	 
    stringstream check1(line); 
    string intermediate; 
    while(getline(check1, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    } 
	if(f==0)
		return tokens[0];
	return tokens[1];
}

// argumentList FUCTION BREAKS STRING BY ','(comma) and prepares argument list.
vector<string> argumentList(string MyText)
{
	
	string line1;
	line1=macroname(MyText,1);
    vector <string> parameters;	
    stringstream check2(line1); 
    string intermediate1;  
    while(getline(check2, intermediate1, ',')) 
    { 
        parameters.push_back(intermediate1); 
    } 
	return parameters;
}

/*argIndex FUNCTION RETURNS THE INDEX VALUE AT WHICH ARGUMENT WITH '&' is present in
argument list*/
inline int argIndex(vector<string> p,vector<string> q)
{
	int i;
	for(i = 0; i < p.size(); i++)
		{
			if(p[i]==q[1])
				return i;
		}
	i=-1;
	cout<<i;
	return i;
}
int main() 
{
	string MyText;
	vector <string> ARG;
	int MDTC,MNTC,MDI;	
	//MDI-macro difinition indicator(ON when "MACRO" KEYWORD FOUND AND OFF WHEN "MEND" keyword)
	MDTC=1;
	MNTC=1;
	MDI=0;
	ofstream MNT("MNT.txt");
	ofstream MDT("MDT.txt");
	ofstream Output("pass1output.txt");
	ifstream ReadFile("filename.txt");
	while (getline (ReadFile, MyText)) 
	{
		if(MyText=="MACRO")
		{
			MDI=1;
			continue;  //FOR READING NEXT LINE WHEN "MACRO" PESUDO-OP FOUND
		}
		else 
			if(MDI)
			{
				if(MyText=="MEND")
				{
					MDT <<MDTC<<" "<<MyText<<endl;
					MDTC++;
					MDI=0;
					continue;
				}
				if(MDI==1)     //WHEN MACRO NAME COMES IT WILL STORE IN BOTH MNT AND MDT TABLE
				{
					MNT<<MNTC<<" "<<MyText<<" "<<MDTC<<endl;
					MNTC++;
					MDT <<MDTC<<" "<< MyText<<endl;
					ARG=argumentList(MyText);
					MDTC++;
				}
				else	//after macro name all lines store in MDT till MEND
				{
					string name;
					name=macroname(MyText);
					vector<string> line;
					line=argumentList(MyText);
					int indexNotation;
					indexNotation=argIndex(ARG,line);
					MDT <<MDTC<<" "<<name<<" "<<line[0]<<",#"<<indexNotation<<endl;
					MDTC++;
				}
				MDI++;
			}
			else
			{
				//LINES NOT INSIDE "MACRO" AND "MEND" WILL STORE IN PASS1 OUTPUT
				Output<<MyText<<endl;
			}
	}
	ReadFile.close(); 
	MDT.close(); 
	MNT.close();
	Output.close();
	cout<<"pass 1 successfully executed";
	return 0;
}
