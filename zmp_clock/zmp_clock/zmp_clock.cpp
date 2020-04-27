// zmp.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


//includes
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
//declarations
double clock_needle(string time);

//main
int main()
{

    //asking for timeg\ given such as HH:MM with Hour in [0;12]
    cout << "What time is it ? \n (please enter in the following format : HH:MM)\n time : ";
    string  time;
    cin >> time;
    double needle_angle = clock_needle(time);

    cout << "The time angle difference between hour needle and minute needle is: " << needle_angle << " degree" << std::endl;
}

double clock_needle(string time) {
    //separating hours and minutes
    string hour10, hour1, minute10, minute1;
    hour10 = time[0];
    hour1 = time[1];
    minute10 = time[3];
    minute1 = time[4];
    //converting 
    double hour = 10 * atof(hour10.c_str()) + atof(hour1.c_str());
    double minute = 10 * atof(minute10.c_str()) + atof(minute1.c_str());

    //calculating : returned angle in degree
    int needle_angle = int(360 * hour / 12 - 360 * minute / 60) % 360;
    return needle_angle;

}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

