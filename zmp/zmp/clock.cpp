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
   
    //asking for time
    cout << "What time is it ? :";
    string  time;
    cin >> time;
    double needle_angle = clock_needle(time);
   
    cout << "The time angle difference between hour needle and minute needle is: " <<needle_angle  <<" degree" << std::endl;
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
    //calculating
    double needle_angle = 360 * hour / 12 - 360 * minute / 60;
    return needle_angle;

}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
