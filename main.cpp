#include<iostream>
#include<string>
#include<cstring>



using namespace std;
bool is_Quistion(string a);

string math(string Fullquistion)
{
    string quistion = Fullquistion;
    while (is_Quistion(quistion))
    {   
        int operatorIndex = -1 ;
        int StartIndex = -1;
        int EndIndex = -1;

        for(size_t aa=0; aa < 2; aa++)  //Get Operator
        {
            for(size_t i=0; i<strlen(quistion.c_str()); i++)
            {
                if(aa == 0)
                {
                    if(quistion[i] == '*')
                    {
                        operatorIndex = i;
                        break;
                    }
                    if(quistion[i] == '/')
                    {
                        operatorIndex = i;
                        break;
                    }
                }

                else if (aa == 1)
                {
                    if(quistion[i] == '+')
                    {
                        operatorIndex = i;
                        break;
                    }
                    if(quistion[i] == '-')
                    {
                        operatorIndex = i;
                        break;
                    }
                }
            }
            if(operatorIndex != -1) // if get Index Number, close for
            {
                break;
            }
        }
        
        cout << "OperatorIndex = " << operatorIndex << endl;
        
        // Get X AND Y Range

        for (size_t cycle = 1; cycle <= strlen(quistion.c_str()); cycle++)
        {
            if(quistion[operatorIndex - cycle] == '+' || quistion[operatorIndex - cycle] == '*' || operatorIndex - cycle == 0)  //Get X Range
            {
                if(operatorIndex - cycle == 0)
                {
                    StartIndex = 0;
                    break;
                }
                else
                {
                    StartIndex = (operatorIndex - cycle) + 1;
                    break;
                }
            }
        }

        for (size_t cycle = 1; cycle <= strlen(quistion.c_str()); cycle++)
        {
            if(operatorIndex + cycle == strlen(quistion.c_str()) - 1 || quistion[operatorIndex + cycle] == '+' || quistion[operatorIndex + cycle] == '*')
            { 
                if(operatorIndex + cycle == strlen(quistion.c_str()) - 1)
                {
                    EndIndex = strlen(quistion.c_str()) - 1;
                    break;
                }
                else
                {
                    EndIndex = (operatorIndex + cycle) - 1;
                    break;
                }

            }

            // cout << "LenQuistion: " << strlen(quistion.c_str() ) - 1 << endl << endl;
            // cout << "OI: " << operatorIndex + cycle << endl;
        }
        

        cout << "Start: " << StartIndex << endl;
        cout << "End: " << EndIndex << endl;
        break;
        
    }
    return quistion;
}

bool is_Quistion(string a)
{
    for(size_t i=0; i< strlen(a.c_str()); i++)
    {
        if(a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '(' || a[i] == ')')
        {
           return true;
        }
    }

    return false;
}


string deleteParaantez(string input)
{
    string Result = input;  // only First Result == input

    while (is_Quistion(Result))
    {
        int openPaIndex = -1;
        int closePaIndex = -1;

        for(size_t a=0; a < strlen(Result.c_str()); a++) //Delete Empty Index
        {
            if(input[a] == ' ')
            {
                continue;
            }
        }

        for(size_t i=0; i<strlen(Result.c_str()); i++)   // Get Open -AND- Close Index 
        {
            if(Result[i] == '(')
            {
                openPaIndex = i;
            }
            else if(Result[i] == ')')
            {
                if(openPaIndex == -1) // if First Close // raise Error
                { 
                    cout << "Parantez Error: First Open Pls ?)" << endl;
                    exit(1);
                    
                }
                else{
                    closePaIndex = i;   //save Close Index
                    break;
                }
            }
        }


        
        string paraantezTMP = "";
        for(size_t a=openPaIndex+1; a<closePaIndex; a++) // Get Quistion
        {
            paraantezTMP += Result[a];
        }

        paraantezTMP = math(paraantezTMP);  //Calculate


        for(size_t a=openPaIndex; a<=closePaIndex; a++) //  Delete Paraantez Quistion
        {
            Result[a] = ' ';
        }

        cout << "OPenINdex: " << openPaIndex  << "Close INdex: " << closePaIndex <<  endl;
        cout << "DELETED QUISTION: " << Result << endl;

        Result.insert(openPaIndex, paraantezTMP);   //Placement Result to Quistion, for create new quistion

        cout << "NEW QUISTION: " << Result << endl;
        
        

    }
    
   



    return Result;
}


bool cal(string User_quistion)
{
    string quistion = User_quistion;   //Get Quistion Paraantez

    while(is_Quistion(quistion))
    {
        if(User_quistion.find("(") == string::npos)  // if open Paraantez Not found
        {
            if(User_quistion.find(")") != string::npos)  // if close Paraantez avilable
            {
                cout << "Sintax Error: Paraantez Error ?)" <<endl;
                return false;
            }
            else    // iF All Parantez Not Found
            {
                string result = math(User_quistion);
                cout << "End Prosess: " << result << endl;
                break;
            }
        }
        else    // If open Paraantez Exist
        {   // If Close Paraantez Is Found
            if(User_quistion.find(")") == string::npos)  //Check INCOMPLATE , open not found but close found
            {
                cout << "Sintax Error: Paraantez not found ?)" << endl;
                return false;
            }
            else    // Prosess Paraantez
            {
                string RESULT = deleteParaantez(User_quistion);
                cout << "result: " << RESULT << endl;
                return true;
            }
        }
    }

    return true;
    
    

    
}


int main()
{
    string userInput;
    cout << "# ";
    getline(cin, userInput);
    cout << endl;

    cal(userInput);
    

}