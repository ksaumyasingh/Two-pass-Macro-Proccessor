//1913097    KUMARI SAUMYA SINGH   CS216

#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include<stdlib.h>
using namespace std;

// macroname FUCTION BREAKS STRING BY SPACE
string macroname(string myText,int f=0,string s="NO1")
{
	string line ;
	line=myText;
    vector <string> tokens;	 
    stringstream check1(line); 
    string intermediate; 
    while(getline(check1, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    } 
	if(s=="END")
		return tokens[tokens.size()-1];
	if(f==0)
		return tokens[0];
	if(f==2)
		return tokens[2];
	return tokens[1];
}

//  stringToIntConversion FUCTION CONVERTS STRING TO INTEGER like "1"->1. 
int stringToIntConversion(string s)
{
	stringstream s1(s);
	int x=0;
	s1>>x;
	return x;
}

/*searchMNT function compares each line so that it is present in macro name table
if yes then returns line no. from which its macro definition starts*/
int SearchMNT(string myText)
{
	string MN;
	ifstream MNT("MNT.txt");
	string s,p;
	s=macroname(myText);
	while (getline (MNT, MN)) 
	{
		p=macroname(MN,1);
		if(s == p)
		{
			int x=stringToIntConversion(macroname(MN,1,"END"));
			return x;
		}
	}
	MNT.close();
	return 0;
}

// argumentList FUCTION BREAKS STRING BY ','(comma) and prepares argument list.
vector<string> argumentList(string myText,int f=1)
{
	
	string line1;
	line1=macroname(myText,f);
    vector <string> parameters;	
    stringstream check2(line1); 
    string intermediate1;  
    while(getline(check2, intermediate1, ',')) 
    { 
        parameters.push_back(intermediate1); 
    } 
	return parameters;
}

/*argumentSubstitution FUCTION -it substitues argument from argument LIST which is specified 
at index no specified with # in MDT */
vector<string> argumentSubstitution(vector<string> ARG,string MD)
{
	vector <string> ARG1;
	ARG1=argumentList(MD,2);
	for(int i=0;i<ARG1.size();i++)
	{
		if(ARG1[i][0]=='#')
		{
			int x=ARG1[i][1]-'0';
			ARG1[i]=ARG[x];
		}
	}
	return ARG1;
}
int main()
{
	int MDTP;
	string myText,MN,MD;
	vector <string> ARG1,ARG;
	ifstream pass1("pass1output.txt");
	ofstream Output("finaloutput.txt");
	while (getline (pass1, myText)) 
	{
		
		if(SearchMNT(myText))
		{
			MDTP=SearchMNT(myText);
			ARG=argumentList(myText);   //arg. list prepared
			MDTP++;
			
			//macro call is expanded using macro definition
			ifstream MDT("MDT.txt");
			while (getline (MDT, MD)) 
			{
				int x=stringToIntConversion(macroname(MD));
				if(x>=MDTP)
				{
					string s1;
					s1=macroname(MD,1);
					if(s1=="MEND")
					{
						break;
					}
					ARG1=argumentSubstitution(ARG,MD);
					Output<<s1<<" ";
					for(int i=0;i<ARG1.size()-1;i++)
						Output<<ARG1[i]<<",";
					Output<<ARG1[ARG1.size()-1]<<endl;
				}
				x++;
			}
			MDT.close();
		}
		else
		{
			
			//not macro call then directly placed in output file.
			Output<<myText<<endl;
			if(myText=="END")
			{
				cout<<"pass 2 successfully executed";
				exit(0);
			}
		}
	}
	pass1.close();  
	Output.close();
}