#include <iostream>
#include <string>
using namespace std;
int main()
{
    // string data = "twitter_combined_tp";
    string data = "soc-sign-bitcoinotc_tp";
    // string data = "facebook_combined_tp";
    
    char tw = 'twitter';
    char fb = 'facebook';
    char bitcoin = 'bitcoin';
    // Check if string contains the character or not
    if ((data.find(tw) != string::npos ) || (data.find(fb) != string::npos ) || (data.find(bitcoin) != string::npos ))
    {
        cout<<"Yes, string contains the character - "<< endl;
    }
    else
    {
        cout<<"No, string do not contains the character - "<< endl;
    }
    return 0;
}
