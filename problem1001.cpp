#include <iostream>
#include <vector>
using namespace std;
void check(uint8_t* pos, uint8_t low, uint8_t high){
    uint8_t jin = (*pos+ low)/10;
    *pos = (*pos+ low)%10;
    high += jin;
    if(high){
        check(pos-1,high,0);
    }
}
void stringinit(string & value, int8_t flag, vector<uint8_t>& ptr, vector<uint8_t>& temp, uint16_t & pointIndex, uint16_t n){
    int8_t pointflag = 0,continueflag =0;
    for(int i=0 ; i<=(int)value.length();){
        if(!continueflag && value[0] == '0'){
            value.erase(value.begin());
        }
        else if(flag && value[0] != '0'){
            return;
        }
        else if(value[i] == '.' ){
            for(int j=0 ; j<=(int)value.length();){
                if(value.back() == '0')
                    value.pop_back();
                else if(value[j] == '.'){
                    pointIndex =(value.length()-j-1)*n;
                    value.erase(value.begin()+j);
                    pointflag = 1;
                    continueflag = 1;
                    break;
                    }
                else j++;
            }
        }
        else if(!value.size()) {
               value.push_back('0');
               break;
         }
        else if(continueflag) break;
        else i++;
    }
    for(auto it:value){
        ptr.push_back(uint8_t(it-48));
        temp.push_back(uint8_t(it-48));
    }
    if(!pointflag) pointIndex = 0;
}
void calculator(vector<uint8_t> & ptr,vector<uint8_t> & temp, string& container, uint16_t pointIndex,uint16_t & n){
    if(ptr.size()==1 && ptr[0] == 0){
        container.push_back('0');
        return;
    }
    else if(n<2){
        for(auto it:temp){
            container.push_back((it+48));
        }
        if(pointIndex)
            container.insert(container.end()-pointIndex,'.');
            stringinit(container,1,ptr,temp,pointIndex, n);
        return ;
    }
    else{
        uint8_t *data = new uint8_t[temp.size()+ptr.size()]();
        for(int16_t i = (temp.size()-1) ; i>=0; i--){
            for(int16_t j = (ptr.size()-1) ; j>=0; j--){
                uint8_t low = (temp[i]*ptr[j])%10, high = (temp[i]*ptr[j])/10;
                check(&data[i+j+1],low, high);
            }
        }
        temp.resize(temp.size()+ptr.size());
        for(int16_t k =0 ; k<temp.size() ; k++ ){
            temp[k] = data[k];
        }
        delete[]  data;
        n--;
        calculator(ptr, temp,container,pointIndex,n);
    }
}
int main()
{
    uint16_t pointIndex;
    uint16_t n=5;
    vector<uint8_t> ptr, temp;
    string input="01.100";
    string container;
    while (cin>>input>>n) {
        if(n == 0){
            cout<<"1"<<endl;
            continue;
        }
        else {
            stringinit(input,0,ptr,temp,pointIndex,n);
            calculator(ptr, temp,container,pointIndex,n);
            cout<<container<<endl;
            input.clear();
            container.clear();
            ptr.clear();
            temp.clear();
        }
    }
    return 0;
}
