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
    else
        return;
}

void stringinit(string & value, int8_t flag, vector<uint8_t>& ptr, vector<uint8_t>& temp, uint16_t & pointIndex, uint16_t n){
    for(int i=0 ; i<=(int)value.length();){
        if(value.front() == '0')
            value.erase(value.begin());
        else if(value.back() == '0')
            value.pop_back();
        else if(value[i] == '.'){
            if(flag) return;
            pointIndex =(value.length()-i-1)*n;
            value.erase(value.begin()+i);
            for(auto it:value){
                ptr.push_back(uint8_t(it-48));
                temp.push_back(uint8_t(it-48));
            }
            return;
        }
        else i++;
    }
}

void calculator(vector<uint8_t> & ptr,vector<uint8_t> & temp, string& container, uint16_t pointIndex,uint16_t & n){
    if(n<2){
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
