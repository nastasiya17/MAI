#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {

	string str, str1, str2, str3, str4, str5, str6, str7;
    int n;
    double count1=0;
    double count2=0;
    double count3=0;
    double count4=0;
    double count5=0;

	ifstream in("data/first_text.txt");
	ofstream out("data/new_text.txt");
	if ((in.is_open())&&(out.is_open())) {
        while (getline(in, str)) {
        	transform(str.begin(), str.end(), str.begin(), ::tolower);
            for (int i=0; i<str.size(); i++) {
            	if ((str[i]=='-') && (isalpha(str[i-1]))) 
            		out << ' ';
                else if ((isalpha(str[i])) || (str[i]==' '))
            		out << str[i];
            }
            if (str.size()!=0)
            	out << ' ';
        }
    }
    in.close();
    out.close();

    ifstream in1("data/new_text.txt");
	ofstream out1("data/text1.txt");
	ofstream out2("data/text2.txt");
    if ((in1.is_open())&&(out1.is_open())&&(out2.is_open())) {
	    getline(in1, str1);
        n=str1.size();
	    for (int i=0; i<n/2; i++) {
            out1 << str1[i];
        }
        for (int i=n/2; i<n; i++) {
            out2 << str1[i];
        }
    }
    in1.close();
    out1.close();
    out2.close();

    ofstream out3("data/letters1.txt");
    ofstream out4("data/letters2.txt");
    if ((out3.is_open())&&(out4.is_open())) {
        int i=0;
        while (i<n/2) {
            int sp=1+rand()%10;
            i+=sp+1;
            for (int j=0; j<sp; j++) {
                char ch=97+rand()%26;
                out3 << ch;
            }
            out3 << ' ';
        }
        i=0;
        while (i<n/2) {
            int sp=1+rand()%10;
            i+=sp+1;
            for (int j=0; j<sp; j++) {
                char ch=97+rand()%26;
                out4 << ch;
            }
            out4 << ' ';
        }
    }
    out3.close();
    out4.close();

    ofstream out5("data/words1.txt");
    ofstream out6("data/words2.txt");
    if ((out5.is_open())&&(out6.is_open())) {
        int i=0;
        int k;
        while (i<n/2) {
            int pos=rand()%(n/2);
            while ((str1[pos]!=' ')&&(pos!=0)) {
                pos--;
            }
            pos++;
            k=0;
            while (str1[pos]!=' '){
                out5 << str1[pos];
                pos++;
                k++;
            }
            out5 << ' ';
            k++;
            i+=k;
        } 
        i=0;
        while (i<n/2) {
            int pos=rand()%(n/2);
            while ((str1[pos]!=' ')&&(pos!=0)) {
                pos--;
            }
            pos++;
            k=0;
            while (str1[pos]!=' '){
                out6 << str1[pos];
                pos++;
                k++;
            }
            out6 << ' ';
            k++;
            i+=k;
        } 
    }
    out5.close();
    out6.close();

    ifstream in2("data/text1.txt");
    ifstream in3("data/text2.txt");
    ifstream in4("data/letters1.txt");
    ifstream in5("data/letters2.txt");
    ifstream in6("data/words1.txt");
    ifstream in7("data/words2.txt");
    if ((in2.is_open())&&(in3.is_open())&&(in4.is_open())&&(in5.is_open())&&(in6.is_open())&&(in7.is_open())) {
        getline(in2, str2);
        getline(in3, str3);
        getline(in4, str4);
        getline(in5, str5);
        getline(in6, str6);
        getline(in7, str7);
        for (int i=0; i<n/2; i++) {
            if (str2[i]==str3[i])
                count1++;
            if (str2[i]==str4[i])
                count2++;
            if (str2[i]==str6[i])
                count3++;
            if (str4[i]==str5[i])
                count4++;
            if (str6[i]==str7[i])
                count5++;
        }
    }
    in2.close();
    in3.close();
    in4.close();
    in5.close();
    in6.close();
    in7.close();

    double p1=100*count1/(n/2);
    double p2=100*count2/(n/2);
    double p3=100*count3/(n/2);
    double p4=100*count4/(n/2);
    double p5=100*count5/(n/2);

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;
    cout << p5 << endl;
}
