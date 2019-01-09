#include <iostream>
#include <vector>
using namespace std;
string& swap(string& input, int16_t target, int16_t now){
    char temp =input[now];
    input[now] = input[target];
    input[target] = temp;
    return input;
}
void sequence(vector<string>& ptr, string& input, int16_t n){
    if(n == 1) return;
    for(int i = 0; i< n ; ){
        string temp =input;
        swap(temp, input.length()- n , input.length()- n+i);
        if(n==2) ptr.push_back(temp);
        sequence(ptr,temp, n-1);
        i++;
    }
}
int main()
{
    string input;
    vector<string> contianer;
    while (cin>>input) {
        sequence(contianer,input, input.length());
        for(int i = 0; i<contianer.size();i++){
            for(int j=i+1; j<contianer.size() ; ){
                 if(contianer[i] == contianer[j]) contianer.erase(contianer.begin()+j);
                 else j++;
            }
            cout<<contianer[i]<<endl;
        }
        contianer.clear();
    }
    return 0;
}
