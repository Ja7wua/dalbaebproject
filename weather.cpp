#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using json = nlohmann::json;
using cpr::Response;
using cpr::Get;
using cpr::Parameters;
using cpr::Url;

int main() {
    string apiKey = "e08f0755c19b51580b1252bb907c583b"; 
    string city;

    cout << "Введите город (на английском, например Moscow): ";
    cin >> city;

    Response r = Get(Url{"api.openweathermap.org/data/2.5/weather"},
                     Parameters{{"q", city}, {"appid", apiKey}, {"units", "metric"}, {"lang", "ru"}});

    if (r.status_code == 200) {
        auto data = json::parse(r.text);
        
        double temp = data["main"]["temp"];
        string description = data["weather"][0]["description"]; 

        cout << "\n--- Прогноз для " << city << " ---" << endl;
        cout << "Температура: " << temp << "°C" << endl;
        cout << "На улице: " << description << endl;
    } else if (r.status_code == 401) {
        cout << "Ошибка 401: Ключ еще не активирован. Подождите 30-60 минут." << endl;
    } else if (r.status_code == 404) {
        cout << "Ошибка 404: Город не найден." << endl;
    } else {
        cout << "Ошибка запроса: " << r.status_code << endl;
    }

    return 0;
}